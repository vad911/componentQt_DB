#include <databaseSQLite/databaseSQlite.h>
#include <databaseSQLite/databaseTypes.h>
#include <QDir>

namespace bur {
namespace mapRS {
namespace db {

bool DatabaseSQLite::beginTransaction()
{
    if (!(*m_connectionDB.get()).transaction()) {
        qDebug() << "Error transaction : " << (*m_connectionDB.get()).lastError().text();
        return false;
    }
    return true;
}

bool DatabaseSQLite::commitTransaction()
{
    if (!(*m_connectionDB.get()).commit()) {
        qDebug() << "Error commit transaction : " << (*m_connectionDB.get()).lastError().text();
        return false;
    }
    return true;
}

bool DatabaseSQLite::rollbackTransaction()
{
    if (!(*m_connectionDB.get()).rollback()) {
        qDebug() << "Error rollback : " << (*m_connectionDB.get()).lastError().text();
        return false;
    }
    return true;
}

DatabaseSQLite::DatabaseSQLite()
{
    // Указываем драйвер базы данных (SQLite)
    // m_connectionDB = QSqlDatabase::addDatabase("QSQLITE", "connectionNameSQLite");
    m_connectionDB.reset(new QSqlDatabase());
    (*m_connectionDB.get()) = (QSqlDatabase::addDatabase("QSQLITE", "connectionNameSQLite"));
    m_filename = ConstDB::NameDB;
    transaction_flag.clear(std::memory_order_release);
}

void DatabaseSQLite::setupDB()
{
    // -- setup name DB
    // m_connectionDB.setDatabaseName("my.db");

    QString path = getFullpathDB();
    (*m_connectionDB.get()).setDatabaseName(m_filename);
    auto pathDB = (*m_connectionDB.get()).databaseName();

    // -- user name
    (*m_connectionDB.get()).setUserName("Vadim");
    (*m_connectionDB.get()).setHostName(ConstDB::HOST_NAMEDB);
    // QString options = QString();
    // m_connectionDB.setConnectOptions(options);
    // m_connectionDB.setPassword(ConstDB::pswDB);
}


DatabaseSQLite::~DatabaseSQLite()
{
    // Закрываем базу данных
    closeDataBase();
}

void DatabaseSQLite::connectToDataBase(const QString &fullpath)
{
    // init(fullpath);

    // Перед подключением к базе данных производим проверку на её существование.
    // В зависимости от результата производим открытие базы данных или её создание
    setupDB();
    bool isNewDB = isDatabaseNew(m_fullpath);


    qDebug() << "[debug] DB is new isNewDB: " << isNewDB;
    if(isNewDB){
        qDebug() << "Не могу открыть базу данных :" << m_fullpath;
        qDebug() << "БД будет создана с нуля.    ";

        qDebug() << "[debug] DB create from start ";
        this->createDataBase();
    } else {

        qDebug() << "Connection to DB : [" << m_fullpath << "] OK.";
        qDebug() << "[debug] openDataBase() ";
        this->openDataBase();
    }
}


bool DatabaseSQLite::openDataBase()
{


    // Открываем базу данных
    bool openDB = (*m_connectionDB.get()).open();
    qDebug() << "[!!!debug2] openDB : " << openDB;
    if (!openDB) {
        qDebug() << "Ошибка подключения к базе данных:" << (*m_connectionDB.get()).lastError().text();
        return ErrorConnectionToDB;
    } else {

        // -- удаляем все таблицы если есть
        // deleteTabs();
        // -- only here !!!, only after open DB!!!

        // -- создаем таблицу
        bindPreparedToDB();
        createTables();

        makePreparedforDB();
    }


    return openDB;
}


bool DatabaseSQLite::createDataBase()
{
    bool result  = false;
    bool openDB = openDataBase();
    if(openDB) {
        // -- создаем базу по умолчанию
        createDefaultDB();
    }
    return true;
}

void DatabaseSQLite::closeDataBase()
{
    // qDebug() << "close db : " << getFullpathDB();
    qDebug() << "close db : " << m_filename;

    (*m_connectionDB.get()).close();
}



bool DatabaseSQLite::createTableVersion(const QString& tabName)
{

    qDebug() << " -- [debug info]  createTableVersion;";
    // Создание таблицы
    QString commandCreateTableVersionQuery = "CREATE TABLE  IF NOT EXISTS " + tabName + "("
                                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                             "major_version INTEGER NOT NULL, "
                                             "minor_version INTEGER NOT NULL, "
                                             "patch_version INTEGER NOT NULL)";
    bool res = executionQuery(*m_queryCreateTable.get(), commandCreateTableVersionQuery);
    return res;
}


// -- system    - система Si-Ge-C, AlAs-GaAs-InAs итд
// -- component - компонент - Si,SiC и тд
// -- TwoTheta  - 2Theta   бреговский угол
// -- lattice   - Параметр элементарной ячейки (ПЭЯ) решетки
// -- hkl       - коэффициенты
// -- dhkl      - это межплоскостное расстояние (межплоскостный промежуток) между кристаллографическими плоскостями в кристаллической решётке
bool DatabaseSQLite::createTableChemicalCompounds(const QString &tabName)
{
    qDebug() << " -- [debug info]  createTableChemicalCompounds;";
    // Создание таблицы
    QString commandCreateTableChemicalCompounds = "CREATE TABLE  IF NOT EXISTS " + tabName + "("
                                                  "id            INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                  "system        TEXT NOT NULL, "
                                                  "component     TEXT NOT NULL, "
                                                  "two_theta     REAL NOT NULL, "
                                                  "crystal_structure  TEXT NOT NULL, "
                                                  "lattice_a     REAL NOT NULL, "
                                                  "lattice_c     REAL NOT NULL, "
                                                  "h             INTEGER  NOT NULL,      "
                                                  "k             INTEGER  NOT NULL,      "
                                                  "l             INTEGER  NOT NULL,      "
                                                  "dhkl          REAL NOT NULL, "
                                                  "description   TEXT)";

    bool res = executionQuery(*m_queryCreateTable.get(), commandCreateTableChemicalCompounds);
    return res;
}

bool DatabaseSQLite::createTableSystems(const QString &tabName)
{
    qDebug() << " -- [debug info]  createTableSystems;";
    // Создание таблицы
    QString commandCreateTableSystems = "CREATE TABLE  IF NOT EXISTS " + tabName + "("
                                        "id          INTEGER PRIMARY KEY AUTOINCREMENT,"
                                        "system_name TEXT NOT NULL,"
                                        "description TEXT)";

    bool res = executionQuery(*m_queryCreateTable.get(), commandCreateTableSystems);
    return res;
}

bool DatabaseSQLite::createTables()
{
    createTableVersion(ConstDB::nameTableVersion);
    createTableSystems(ConstDB::nameTableSystems);
    createTableChemicalCompounds(ConstDB::nameTableChemicalCompounds);
    return true;
}


bool DatabaseSQLite::removeRecord(const QString& nameTab, const int id)
{
    QString strID = QString::number(id);
    // QString deleteQuery = "DELETE FROM db_version WHERE id = 1";
    QString deleteQuery = "DELETE FROM " + nameTab +  " WHERE id = " + strID;
    bool res = executionQuery(*m_queryDeleteRecord.get(), deleteQuery);
    return res;
}


bool DatabaseSQLite::fillTableVersion(const VersionData& version)
{
    // insertRecordVersion(ConstDB::nameTableVersion, version);
    insertRecordVersion(version);
    return true;
}


bool DatabaseSQLite::fillTableSystems()
{
    namespace bmdb = bur::mapRS::db;
    int count = 1;
    for (const auto& systemData : bmdb::ConstDB::vecSystemData)
    {
        insertRecordSystem(systemData);
        qDebug() <<"insert data in db count:" << count;
        ++count;
    }
    return true;
}

bool DatabaseSQLite::fillTableChemicalCompounds()
{
    namespace bmdb = bur::mapRS::db;
    int count = 0;
    for (const auto& componentData : bmdb::ConstDB::vecCompanentData)
    {
        insertChemicalCompounds(componentData);
        qDebug() <<"insert data in db count:" << count;
        ++count;
    }
    return true;
}

bool DatabaseSQLite::deleteTabVersion()
{
    if (!(*m_queryDeleteTableVersion.get()).exec()) {
        qDebug() << "Ошибка: Не удалось удалить таблицу db_version." << (*m_queryDeleteTableVersion.get()).lastError();
        return false;
    }

    qDebug() << "Таблица db_version успешно удалена.";
    return true;
}

bool DatabaseSQLite::deleteTabSystems()
{
    if (!(*m_queryDeleteTableSystem.get()).exec()) {
        qDebug() << "Ошибка: Не удалось удалить таблицу systems." << (*m_queryDeleteTableSystem.get()).lastError();
        return false;
    }

    qDebug() << "Таблица systems успешно удалена.";
    return true;
}

bool DatabaseSQLite::deleteTabChemicalCompounds()
{
    if (!(*m_queryDeleteTableChemicalCompounds.get()).exec()) {
        qDebug() << "Ошибка: Не удалось удалить таблицу chemical_compounds." << (*m_queryDeleteTableChemicalCompounds.get()).lastError();
        return false;
    }

    qDebug() << "Таблица chemical_compounds успешно удалена.";
    return true;
}

bool DatabaseSQLite::deleteTabs()
{
    deleteTabVersion();
    deleteTabSystems();
    deleteTabChemicalCompounds();
    return true;
}

void DatabaseSQLite::createDefaultDB()
{


    // -- готовм prepare
    // makePreparedforDB();
    // -- создаем базу


    // // -- заполняем таблицы данными
    VersionData version(1,0,0);
    fillTableVersion(version);
    // fillTableVersion(ConstDB::nameTableVersion, version);
    // bool res = fillTableVersion(version);

    // if (res)
    // {
    //     qDebug()<< " fillTableSystems! res = True" ;
    // } else
    // {
    //     qDebug()<< " fillTableSystems! res = false" ;
    // }
    fillTableSystems();
    fillTableChemicalCompounds();
}



void DatabaseSQLite::testIsOpenDB(const QString& msg)
{
    // -- test is openDB
    bool isopenDB = (*m_connectionDB.get()).isOpen();
    if(isopenDB)
    {
        qDebug() << msg;
        qDebug() << "DB is opened!!!";
    }
}

bool DatabaseSQLite::isDatabaseNew(const QString &fullpathDB)
{
    return !QFile::exists(fullpathDB); // Если файл не существует, база новая
}

void DatabaseSQLite::setPath(const QString &fullpath)
{
    m_fullpath  = fullpath;
    m_shortpath = QFileInfo(fullpath).path();
    m_filename  = QFileInfo(fullpath).fileName();

    qDebug() << "[info Fileinfo] m_fullpath: "   << m_fullpath;
    qDebug() << "[info Fileinfo] m_shortpath: "  << m_shortpath;
    qDebug() << "[info Fileinfo] m_filename: "   << m_filename;

    // m_fullpath = "";
    // m_shortpath = "";
    // m_filename = ConstDB::NameDB;
}

void DatabaseSQLite::setPath(const QString &fullpath, const QString &shortpath, const QString &filename)
{
    m_fullpath  = fullpath;
    m_shortpath = shortpath;
    m_filename  = filename;
}

void DatabaseSQLite::init(const QString &fullpath)
{
    setPath(fullpath);
}

QString DatabaseSQLite::getNameDB()
{
    return m_filename;
}

QString DatabaseSQLite::getShortpathDB()
{
    return m_shortpath;
}

QString DatabaseSQLite::getFullpathDB()
{
    return m_fullpath;
}

QVector<ComponentData> DatabaseSQLite::readRecordsChemicalCompounds()
{
    QVector<ComponentData>  containerComponentData;


    if (!(*m_queryReadRecordsChemicalCompounds.get()).exec()) {
        qDebug() << "Ошибка: Не удалось выполнить запрос к таблице chemical_compounds." << (*m_queryReadRecordsChemicalCompounds.get()).lastError();
        Error = Failed_to_query_the_chemical_compounds_table;
        return containerComponentData;
    }

    qDebug() << "Данные из таблицы chemical_compounds:";
    while ((*m_queryReadRecordsChemicalCompounds.get()).next()) {
        int id                   = (*m_queryReadRecordsChemicalCompounds.get()).value("id").toInt();
        QString system           = (*m_queryReadRecordsChemicalCompounds.get()).value("system").toString();
        QString component        = (*m_queryReadRecordsChemicalCompounds.get()).value("component").toString();
        double twoTheta          = (*m_queryReadRecordsChemicalCompounds.get()).value("two_theta").toDouble();
        QString crystalStructure = (*m_queryReadRecordsChemicalCompounds.get()).value("crystal_structure").toString();
        double latticeA          = (*m_queryReadRecordsChemicalCompounds.get()).value("lattice_a").toDouble();
        double latticeC          = (*m_queryReadRecordsChemicalCompounds.get()).value("lattice_c").toDouble();
        int h                    = (*m_queryReadRecordsChemicalCompounds.get()).value("h").toInt();
        int k                    = (*m_queryReadRecordsChemicalCompounds.get()).value("k").toInt();
        int l                    = (*m_queryReadRecordsChemicalCompounds.get()).value("l").toInt();
        double dhkl              = (*m_queryReadRecordsChemicalCompounds.get()).value("dhkl").toDouble();
        QString description      = (*m_queryReadRecordsChemicalCompounds.get()).value("description").toString();

        CrystalStructure typeCrystalStructure = String2CrystalStructure(crystalStructure);

        containerComponentData.append(ComponentData{id, system, component, twoTheta, typeCrystalStructure, latticeA, latticeC, h, k, l, dhkl, description });


        qDebug() << "ID          : " << id
                 << "system      : " << system
                 << "component   : " << component
                 << "2Theta      : " << twoTheta
                 << "Crystal Structure : " << crystalStructure
                 << "Lattice A   : " << latticeA
                 << "Lattice C   : " << latticeC
                 << "h           : " << h
                 << "k           : " << k
                 << "l           : " << l
                 << "d_hkl       : " << dhkl
                 << "Description : " << description;
    }

    return containerComponentData;
}

ComponentData DatabaseSQLite::readRecordChemicalCompounds(int id_ReadRecord)
{
    ComponentData componentData;
    // m_queryReadRecordChemicalCompounds

    (*m_queryReadRecordChemicalCompounds.get()).bindValue(":id", id_ReadRecord);

    if (!(*m_queryReadRecordChemicalCompounds.get()).exec()) {
        qDebug() << "Ошибка: Не удалось выполнить запрос." << (*m_queryReadRecordChemicalCompounds.get()).lastError();
        Error = Failed_to_execute_query;
        return componentData;
    }

    if ((*m_queryReadRecordChemicalCompounds.get()).next()) {
        int id                   = (*m_queryReadRecordChemicalCompounds.get()).value("id").toInt();
        QString system           = (*m_queryReadRecordChemicalCompounds.get()).value("system").toString();
        QString component        = (*m_queryReadRecordChemicalCompounds.get()).value("component").toString();
        double twoTheta          = (*m_queryReadRecordChemicalCompounds.get()).value("two_theta").toDouble();
        QString crystalStructure = (*m_queryReadRecordChemicalCompounds.get()).value("crystal_structure").toString();
        double latticeA          = (*m_queryReadRecordChemicalCompounds.get()).value("lattice_a").toDouble();
        double latticeC          = (*m_queryReadRecordChemicalCompounds.get()).value("lattice_c").toDouble();
        int h                    = (*m_queryReadRecordChemicalCompounds.get()).value("h").toInt();
        int k                    = (*m_queryReadRecordChemicalCompounds.get()).value("k").toInt();
        int l                    = (*m_queryReadRecordChemicalCompounds.get()).value("l").toInt();
        double dhkl              = (*m_queryReadRecordChemicalCompounds.get()).value("dhkl").toDouble();
        QString description      = (*m_queryReadRecordChemicalCompounds.get()).value("description").toString();

        CrystalStructure typeCrystalStructure = String2CrystalStructure(crystalStructure);

        componentData = ComponentData{id, system, component, twoTheta, typeCrystalStructure, latticeA, latticeC, h, k, l, dhkl, description };

        qDebug() << "ID          : " << id
                 << "system      : " << system
                 << "component   : " << component
                 << "2Theta      : " << twoTheta
                 << "Crystal Structure : " << crystalStructure
                 << "Lattice A   : " << latticeA
                 << "Lattice C   : " << latticeC
                 << "h           : " << h
                 << "k           : " << k
                 << "l           : " << l
                 << "d_hkl       : " << dhkl
                 << "Description : " << description;

    } else {
        qDebug() << "Строка с ID" << id_ReadRecord << "не найдена.";
    }
    return componentData;
}

SystemData DatabaseSQLite::readRecordSystem(int id_ReadRecord)
{
    (*m_queryReadRecordSystem.get()).bindValue(":id", id_ReadRecord);
    SystemData systemData;

    if (!(*m_queryReadRecordSystem.get()).exec()) {
        qDebug() << "Ошибка: Не удалось выполнить запрос." << (*m_queryReadRecordSystem.get()).lastError();
        Error = Failed_to_execute_query;
        return systemData;
    }

    if ((*m_queryReadRecordSystem.get()).next()) {
        int       id_system = (*m_queryReadRecordSystem.get()).value("id").toInt();
        QString system_name = (*m_queryReadRecordSystem.get()).value("system_name").toString();
        QString description = (*m_queryReadRecordSystem.get()).value("description").toString();

        systemData = SystemData{system_name, description};

        qDebug() << "ID          : " << id_system
                 << "system_name : " << system_name
                 << "description : " << description;
    } else {
        qDebug() << "Строка с ID" << id_ReadRecord << "не найдена.";
    }
    return systemData;
}


// -- fix
QVector<SystemData> DatabaseSQLite::readRecordsSystem()
{
    QVector<SystemData>  containerSystemData;
    if (!(*m_queryReadRecordsSystem.get()).exec()) {
        qDebug() << "Ошибка: Не удалось выполнить запрос к таблице systems." << (*m_queryReadRecordsSystem.get()).lastError();
        Error = Failed_to_query_the_systems_table;
        return containerSystemData;
    }

    qDebug() << "Данные из таблицы systems:";
    while ((*m_queryReadRecordsSystem.get()).next()) {

        int       id_system = (*m_queryReadRecordSystem.get()).value("id").toInt();
        QString system_name = (*m_queryReadRecordSystem.get()).value("system_name").toString();
        QString description = (*m_queryReadRecordSystem.get()).value("description").toString();

        SystemData systemData = SystemData{system_name, description};
        containerSystemData.append(systemData);

        qDebug() << "ID          : " << id_system
                 << "system_name : " << system_name
                 << "description : " << description;
    }
    return containerSystemData;
}

VersionData DatabaseSQLite::readRecordVersion(int id_ReadRecord)
{
    (*m_queryReadRecordVersion.get()).bindValue(":id", id_ReadRecord);
    VersionData versionData;

    if (!(*m_queryReadRecordVersion.get()).exec()) {
        qDebug() << "Ошибка: Не удалось выполнить запрос." << (*m_queryReadRecordVersion.get()).lastError();
        Error = Failed_to_execute_query;
        return versionData;
    }

    if ((*m_queryReadRecordVersion.get()).next()) {
        // Извлечение данных
        int       id_version = (*m_queryReadRecordVersion.get()).value("id").toInt();
        int       major_ver  = (*m_queryReadRecordVersion.get()).value("major_version").toInt();
        int       minor_ver  = (*m_queryReadRecordVersion.get()).value("minor_version").toInt();
        int       patch_ver  = (*m_queryReadRecordVersion.get()).value("patch_version").toInt();



        versionData = VersionData{major_ver, minor_ver, patch_ver};

        qDebug() << "ID          : " << id_version
                 << "major_ver   : " << major_ver
                 << "minor_ver   : " << minor_ver
                 << "patch_ver   : " << patch_ver;
    } else {
        qDebug() << "Строка с ID" << id_ReadRecord << "не найдена.";
    }
    return versionData;
}

int DatabaseSQLite::howManyRecordsInChemicalCompounds()
{
    int rowCount;

    if (!(*m_queryReadHowManyRecordsChemicalCompounds.get()).exec()) {
        qDebug() << "Ошибка: Не удалось выполнить запрос." << (*m_queryReadHowManyRecordsChemicalCompounds.get()).lastError();
        return -1;
    }

    if ((*m_queryReadHowManyRecordsChemicalCompounds.get()).next()) {
        rowCount = (*m_queryReadHowManyRecordsChemicalCompounds.get()).value(0).toInt();
        qDebug() << "Количество строк в таблице elements:" << rowCount;
    } else {
        qDebug() << "Ошибка: Не удалось получить количество строк.";
    }
    return rowCount;
}

int DatabaseSQLite::howManyRecordsInSystem()
{
    int rowCount;
    if (!(*m_queryReadHowManyRecordsSystem.get()).exec()) {
        qDebug() << "Ошибка: Не удалось выполнить запрос." << (*m_queryReadHowManyRecordsSystem.get()).lastError();
        return Failed_to_execute_query;
    }

    if ((*m_queryReadHowManyRecordsSystem.get()).next()) {
        rowCount = (*m_queryReadHowManyRecordsSystem.get()).value(0).toInt();
        qDebug() << "Количество строк в таблице elements:" << rowCount;
    } else {
        qDebug() << "Ошибка: Не удалось получить количество строк.";
    }
    return rowCount;
}

int DatabaseSQLite::howManyRecordsInVersion()
{
    int rowCount;
    if (!(*m_queryReadHowManyRecordsVersion.get()).exec()) {
        qDebug() << "Ошибка: Не удалось выполнить запрос." << (*m_queryReadHowManyRecordsVersion.get()).lastError();
        return Failed_to_execute_query;
    }

    if ((*m_queryReadHowManyRecordsVersion.get()).next()) {
        rowCount = (*m_queryReadHowManyRecordsVersion.get()).value(0).toInt();
        qDebug() << "Количество строк в таблице elements:" << rowCount;
    } else {
        qDebug() << "Ошибка: Не удалось получить количество строк.";
    }
    return rowCount;
}


bool DatabaseSQLite::executionQuery(QSqlQuery &query, const QString &queryForExecution)
{
    bool result = false;
    // -- old
    if (!query.exec(queryForExecution)) {
        qDebug() << "[EXECUTION ERROR] Ошибка при выполнении запроса  :" << queryForExecution;
        qDebug() << "[EXECUTION ERROR] Значение Ошибки при выполнении запроса :" << query.lastError().text();
    } else {
        qDebug() << "[EXECUTION OK] Запрос успешно выполнен!";
    }
    return result;
}


bool DatabaseSQLite::makePrepared(QSqlQuery &query, QString &commandQuery)
{
    if (!query.prepare(commandQuery)) {
        qDebug() << "Ошибка: Не удалось подготовить запрос." << query.lastError();
        qDebug() << "Ошибка: запрос :" << commandQuery;
        return false;
    }
    return true;

}

void DatabaseSQLite::makePreparedforDB()
{

    qDebug() << "[debug] makePreparedforDB [1]";
    QString commandInsertVersionQuery =  "INSERT INTO " + ConstDB::nameTableVersion + " (major_version, minor_version, patch_version) "
                                  "VALUES (:major_version, :minor_version, :patch_version)";
    QString commandInsertRecordSystem = "INSERT INTO systems (system_name, description) VALUES (:system_name, :description)";
    QString commandInsertChemicalCompoundsQuery = " INSERT INTO " +  ConstDB::nameTableChemicalCompounds + "("
    "system,  component, two_theta, crystal_structure, lattice_a, lattice_c,  h, k, l, dhkl, description"
    ") VALUES ("
    ":system,  :component, :two_theta, :crystal_structure, :lattice_a, :lattice_c, :h, :k, :l,  :dhkl, :description)";


    QString readRecordsCompaundsQuery = "SELECT * FROM " +  ConstDB::nameTableChemicalCompounds;
    QString readRecordCompaundsQuery  = "SELECT * FROM " +  ConstDB::nameTableChemicalCompounds + " WHERE id = :id";

    QString readRecordsSystem = "SELECT * FROM " +  ConstDB::nameTableSystems;
    QString readRecordSystem  = "SELECT * FROM " +  ConstDB::nameTableSystems + " WHERE id = :id";
    QString readRecordVersion = "SELECT * FROM " +  ConstDB::nameTableVersion + " WHERE id = :id";

    QString readHowManyRecordsCompaundsQuery = "SELECT COUNT(*) FROM " + ConstDB::nameTableChemicalCompounds;
    QString readHowManyRecordsSystemQuery    = "SELECT COUNT(*) FROM " + ConstDB::nameTableSystems;
    QString readHowManyRecordsVersionQuery   = "SELECT COUNT(*) FROM " + ConstDB::nameTableVersion;

    QString commandDeleteTableVersion    = "DROP TABLE IF EXISTS " + ConstDB::nameTableVersion;
    QString commandDeleteTableSystem     = "DROP TABLE IF EXISTS " + ConstDB::nameTableSystems;
    QString commandDeleteTableCompaunds  = "DROP TABLE IF EXISTS " + ConstDB::nameTableChemicalCompounds;


    // -- stack
    // makePrepared(m_queryDeleteTableVersion,                   commandDeleteTableVersion);
    // makePrepared(m_queryDeleteTableSystem,                    commandDeleteTableSystem);
    // makePrepared(m_queryDeleteTableChemicalCompounds,         commandDeleteTableCompaunds);

    // makePrepared(m_queryInsertVersion,                        commandInsertVersionQuery);
    // makePrepared(m_queryInsertChemicalCompounds,              commandInsertChemicalCompoundsQuery);
    // makePrepared(m_queryInsertRecordSystem,                   commandInsertRecordSystem);

    // makePrepared(m_queryReadRecordVersion,                    readRecordVersion);                // -- чтение только одной строчки в таблице db_version
    // makePrepared(m_queryReadRecordSystem,                     readRecordSystem);                 // -- чтение только одной строчки в таблице systems
    // makePrepared(m_queryReadRecordsSystem,                    readRecordsSystem);                // -- чтение всех строчек в таблице  systems

    // makePrepared(m_queryReadRecordsChemicalCompounds,         readRecordsCompaundsQuery);        // -- чтение всех строчек в таблице chemical_compounds
    // makePrepared(m_queryReadRecordChemicalCompounds,          readRecordCompaundsQuery);         // -- чтение только одной строчки в таблице chemical_compounds

    // makePrepared(m_queryReadHowManyRecordsChemicalCompounds,  readHowManyRecordsCompaundsQuery); // -- сколько строчек в таблице chemical_compounds
    // makePrepared(m_queryReadHowManyRecordsSystem,             readHowManyRecordsSystemQuery);    // -- сколько строчек в таблице systems
    // makePrepared(m_queryReadHowManyRecordsVersion,            readHowManyRecordsVersionQuery);   // -- сколько строчек в таблице db_version

    // -- in heap
    makePrepared(*m_queryDeleteTableVersion.get(),                   commandDeleteTableVersion);
    makePrepared(*m_queryDeleteTableSystem.get(),                    commandDeleteTableSystem);
    makePrepared(*m_queryDeleteTableChemicalCompounds.get(),         commandDeleteTableCompaunds);

    makePrepared(*m_queryInsertVersion.get(),                        commandInsertVersionQuery);
    makePrepared(*m_queryInsertChemicalCompounds.get(),              commandInsertChemicalCompoundsQuery);
    makePrepared(*m_queryInsertRecordSystem.get(),                   commandInsertRecordSystem);

    makePrepared(*m_queryReadRecordVersion.get(),                    readRecordVersion);                // -- чтение только одной строчки в таблице db_version
    makePrepared(*m_queryReadRecordSystem.get(),                     readRecordSystem);                 // -- чтение только одной строчки в таблице systems
    makePrepared(*m_queryReadRecordsSystem.get(),                    readRecordsSystem);                // -- чтение всех строчек в таблице  systems

    makePrepared(*m_queryReadRecordsChemicalCompounds.get(),         readRecordsCompaundsQuery);        // -- чтение всех строчек в таблице chemical_compounds
    makePrepared(*m_queryReadRecordChemicalCompounds.get(),          readRecordCompaundsQuery);         // -- чтение только одной строчки в таблице chemical_compounds

    makePrepared(*m_queryReadHowManyRecordsChemicalCompounds.get(),  readHowManyRecordsCompaundsQuery); // -- сколько строчек в таблице chemical_compounds
    makePrepared(*m_queryReadHowManyRecordsSystem.get(),             readHowManyRecordsSystemQuery);    // -- сколько строчек в таблице systems
    makePrepared(*m_queryReadHowManyRecordsVersion.get(),            readHowManyRecordsVersionQuery);   // -- сколько строчек в таблице db_version
    qDebug() << "[debug] makePreparedforDB [2]";
}

bool DatabaseSQLite::insertRecordVersion(const VersionData &version)
{
    // QString commandInsertVersionQuery =  "INSERT INTO " + ConstDB::nameTableVersion + " (major_version, minor_version, patch_version) "
    //                                                                                  "VALUES (:major_version, :minor_version, :patch_version)";

    // // makePrepared((*m_queryInsertVersion.get()),                        commandInsertVersionQuery);

    // QSqlQuery queryInsertVersion;
    // queryInsertVersion.prepare(commandInsertVersionQuery);

    // if (beginTransaction()) {
    //     queryInsertVersion.bindValue(":major_version",           version.m_versionMajor);
    //     queryInsertVersion.bindValue(":minor_version",           version.m_versionMinor);
    //     queryInsertVersion.bindValue(":patch_version",           version.m_versionPatch);

    //         if(!queryInsertVersion.exec()) {
    //             rollbackTransaction();
    //         } else {
    //             commitTransaction();
    //         }
    // }






    // m_queryInsertVersion.clear();
    // Начинаем транзакцию
    //    if (beginTransaction()) {
    //
    //
    //        m_queryInsertVersion.bindValue(":major_version",           version.m_versionMajor);
    //        m_queryInsertVersion.bindValue(":minor_version",           version.m_versionMinor);
    //        m_queryInsertVersion.bindValue(":patch_version",           version.m_versionPatch);


    //        if(!m_queryInsertVersion.exec()) {
    //            rollbackTransaction();
    //        } else {
    //            commitTransaction();
    //        }
    //    }


    // -- ver
    bool retry           = true;
    bool write_completed = false;

    // Начинаем транзакцию
    while ( ((retry == true) && (write_completed == false)) )
    {
        if (beginTransaction()) {
            {
                 qDebug()<< "record data version DB beginTransaction!";
                m_queryInsertVersion.get()->bindValue(":major_version",           version.m_versionMajor);
                m_queryInsertVersion.get()->bindValue(":minor_version",           version.m_versionMinor);
                m_queryInsertVersion.get()->bindValue(":patch_version",           version.m_versionPatch);

                write_completed = m_queryInsertVersion.get()->exec();

                if(write_completed)
                {
                    m_queryInsertVersion.get()->clear();
                    bool res = commitTransaction();
                    if (res) {
                        retry = false;

                        qDebug()<< "data version DB inserted commitTransaction!";
                    }
                } else {
                    retry = true;
                    write_completed = false;
                    qDebug()<< "record data version DB rollbackTransaction!";
                    rollbackTransaction();
                }
            }
        }

        qDebug()<< "version DB finished!";
    } // -- end beginTransaction

    qDebug()<< "version DB finished out while!";
    return true;
}




bool DatabaseSQLite::insertChemicalCompounds(const ComponentData &componentData)
{

    bool retry           = true;
    bool write_completed = false;

    // Начинаем транзакцию
    while ( ((retry == true) && (write_completed == false)) )
    {
        if (beginTransaction()) {
            m_queryInsertChemicalCompounds.get()->bindValue(":system",      componentData.system);
            m_queryInsertChemicalCompounds.get()->bindValue(":component",   componentData.component);
            m_queryInsertChemicalCompounds.get()->bindValue(":two_theta",   componentData.TwoTheta);
            m_queryInsertChemicalCompounds.get()->bindValue(":crystal_structure", CrystalStructure2String(componentData.crystalStructure));
            m_queryInsertChemicalCompounds.get()->bindValue(":lattice_a",   componentData.lattice_a );
            m_queryInsertChemicalCompounds.get()->bindValue(":lattice_c",   componentData.lattice_c);
            m_queryInsertChemicalCompounds.get()->bindValue(":h",           componentData.h);
            m_queryInsertChemicalCompounds.get()->bindValue(":k",           componentData.k);
            m_queryInsertChemicalCompounds.get()->bindValue(":l",           componentData.l);
            m_queryInsertChemicalCompounds.get()->bindValue(":dhkl",        componentData.dhkl);
            m_queryInsertChemicalCompounds.get()->bindValue(":description", componentData.description);

            write_completed = m_queryInsertChemicalCompounds.get()->exec();

            if(write_completed)
            {
                // m_queryInsertChemicalCompounds.get()->clear();
                bool res = commitTransaction();
                if (res) {
                    retry = false;
                    m_queryInsertChemicalCompounds.get()->finish(); // Сбрасываем запрос
                    qDebug()<< "record data ChemicalCompounds inserted!";
                }
            } else {
                retry = true;
                 write_completed = false;
                qDebug()<< "record data ChemicalCompounds rollbackTransaction!";
                rollbackTransaction();
            }
        }
    } // -- end beginTransaction
    return true;
}     // -- end insertChemicalCompounds





bool DatabaseSQLite::insertRecordSystem(const SystemData &systemData)
{
    // -- ver 2[1]
    bool retry = true;
    bool write_completed = false;

    while ( ((retry == true) && (write_completed == false)) )
    {

        if (beginTransaction()) {
            qDebug() << "Recording data for system:" << systemData.system_name;
            // Привязываем значения
            m_queryInsertRecordSystem.get()->bindValue(":system_name", systemData.system_name);
            m_queryInsertRecordSystem.get()->bindValue(":description", systemData.description);

            // Выполняем запрос
            write_completed = m_queryInsertRecordSystem.get()->exec();

            if (write_completed) {
                bool res = commitTransaction();
                if (res) {
                    retry = false;
                    m_queryInsertRecordSystem.get()->finish(); // Сбрасываем запрос
                    qDebug() << "Data inserted successfully!";
                }
            } else {
                qCritical() << "Failed to insert data:" << m_queryInsertRecordSystem.get()->lastError().text();
                retry = true;
                write_completed = false;
                rollbackTransaction(); // Откатываем транзакцию в случае ошибки
            }

            // Если нужно вставить несколько строк, обновите systemData здесь
            // Например: systemData = getNextSystemData();

            // Если это последняя строка, завершаем цикл
            // if (/* условие завершения */) {
            //     retry = false;
            // }
        }
    }

    return true;
} // -- end insertRecordSystem

void DatabaseSQLite::bindPreparedToDB()
{
    // -- [Warning, Important!!!] -- use bindPreparedToDB only after open DB, or prepare willn't work!: ( m_connectionDB.open(); ) !!!
    qDebug() << "[debug] bindPreparedToDB [1]";
    // m_queryCreateTable                         = QSqlQuery(m_connectionDB);
    // m_queryDeleteRecord                        = QSqlQuery(m_connectionDB);
    // m_queryDeleteTableVersion                  = QSqlQuery(m_connectionDB);
    // m_queryDeleteTableSystem                   = QSqlQuery(m_connectionDB);
    // m_queryDeleteTableChemicalCompounds        = QSqlQuery(m_connectionDB);
    // m_queryInsertVersion                       = QSqlQuery(m_connectionDB);
    // m_queryInsertRecordSystem                  = QSqlQuery(m_connectionDB);
    // m_queryInsertChemicalCompounds             = QSqlQuery(m_connectionDB);
    // m_queryReadRecordVersion                   = QSqlQuery(m_connectionDB);
    // m_queryReadRecordSystem                    = QSqlQuery(m_connectionDB);
    // m_queryReadRecordsSystem                   = QSqlQuery(m_connectionDB);
    // m_queryReadRecordChemicalCompounds         = QSqlQuery(m_connectionDB);
    // m_queryReadRecordsChemicalCompounds        = QSqlQuery(m_connectionDB);
    // m_queryReadHowManyRecordsChemicalCompounds = QSqlQuery(m_connectionDB);
    // m_queryReadHowManyRecordsSystem            = QSqlQuery(m_connectionDB);
    // m_queryReadHowManyRecordsVersion           = QSqlQuery(m_connectionDB);


    m_queryCreateTable.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryDeleteRecord.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryDeleteTableVersion.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryDeleteTableSystem.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryDeleteTableChemicalCompounds.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryInsertVersion.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryInsertRecordSystem.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryInsertChemicalCompounds.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryReadRecordVersion.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryReadRecordSystem.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryReadRecordsSystem.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryReadRecordChemicalCompounds.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryReadRecordsChemicalCompounds.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryReadHowManyRecordsChemicalCompounds.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryReadHowManyRecordsSystem.reset(new QSqlQuery((*m_connectionDB.get())));
    m_queryReadHowManyRecordsVersion.reset(new QSqlQuery((*m_connectionDB.get())));
    qDebug() << "[debug] bindPreparedToDB [2]";
}



} // -- end namespace db
} // -- end namespace mapRS
} // -- end namespace bur



