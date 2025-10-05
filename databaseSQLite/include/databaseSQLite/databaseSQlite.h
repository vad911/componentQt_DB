#ifndef DATABASESQLITE_H
#define DATABASESQLITE_H

#include "databaseAbstract.h"
// #include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <atomic>
#include <memory>

namespace bur {
namespace mapRS {
namespace db {

class DatabaseSQLite : public DatabaseAbstract
{
private:

    // QSqlDatabase m_connectionDB;

    // QSqlQuery    m_queryInsertChemicalCompounds;                // -- вставка данных в таблицу chemical_compounds
    // QSqlQuery    m_queryInsertRecordSystem;                     // -- вставка данных в таблицу systems
    // QSqlQuery    m_queryInsertVersion;                          // -- вставка данных в таблицу db_version
    //
    // QSqlQuery    m_queryCreateTable;                            // -- создание таблиц
    // QSqlQuery    m_queryDeleteRecord;                           // -- удалить запись
    // QSqlQuery    m_queryDeleteTableVersion;                     // -- удалить таблицу db_version
    // QSqlQuery    m_queryDeleteTableSystem;                      // -- удалить таблицу systems
    // QSqlQuery    m_queryDeleteTableChemicalCompounds;           // -- удалить таблицу chemical_compounds
    //
    // QSqlQuery    m_queryReadRecordVersion;                      // -- прочитать запись из таблицы db_version, версия БД
    // QSqlQuery    m_queryReadRecordSystem;                       // -- прочитать строчку из таблицы systems
    // QSqlQuery    m_queryReadRecordsSystem;                      // -- прочитать все записи из таблицы systems
    // QSqlQuery    m_queryReadRecordsChemicalCompounds;           // -- прочитать все записи из бд chemical_compounds
    // QSqlQuery    m_queryReadRecordChemicalCompounds;            // -- прочитать одну запись из бд chemical_compounds
    //
    // QSqlQuery    m_queryReadHowManyRecordsChemicalCompounds;    // -- возвращает сколько строчек в таблице chemical_compounds
    // QSqlQuery    m_queryReadHowManyRecordsSystem;               // -- возвращает сколько строчек в таблице systems
    // QSqlQuery    m_queryReadHowManyRecordsVersion;              // -- возвращает сколько строчек в таблице db_version

    std::unique_ptr<QSqlDatabase> m_connectionDB;
    std::unique_ptr<QSqlQuery>  m_queryInsertChemicalCompounds;                // -- вставка данных в таблицу chemical_compounds
    std::unique_ptr<QSqlQuery>  m_queryInsertRecordSystem;                     // -- вставка данных в таблицу systems
    std::unique_ptr<QSqlQuery>  m_queryInsertVersion;                          // -- вставка данных в таблицу db_version
    std::unique_ptr<QSqlQuery>  m_queryCreateTable;                            // -- создание таблиц
    std::unique_ptr<QSqlQuery>  m_queryDeleteRecord;                           // -- удалить запись
    std::unique_ptr<QSqlQuery>  m_queryDeleteTableVersion;                     // -- удалить таблицу db_version
    std::unique_ptr<QSqlQuery>  m_queryDeleteTableSystem;                      // -- удалить таблицу systems
    std::unique_ptr<QSqlQuery>  m_queryDeleteTableChemicalCompounds;           // -- удалить таблицу chemical_compounds
    std::unique_ptr<QSqlQuery>  m_queryReadRecordVersion;                      // -- прочитать запись из таблицы db_version, версия БД
    std::unique_ptr<QSqlQuery>  m_queryReadRecordSystem;                       // -- прочитать строчку из таблицы systems
    std::unique_ptr<QSqlQuery>  m_queryReadRecordsSystem;                      // -- прочитать все записи из таблицы systems
    std::unique_ptr<QSqlQuery>  m_queryReadRecordsChemicalCompounds;           // -- прочитать все записи из бд chemical_compounds
    std::unique_ptr<QSqlQuery>  m_queryReadRecordChemicalCompounds;            // -- прочитать одну запись из бд chemical_compounds
    std::unique_ptr<QSqlQuery>  m_queryReadHowManyRecordsChemicalCompounds;    // -- возвращает сколько строчек в таблице chemical_compounds
    std::unique_ptr<QSqlQuery>  m_queryReadHowManyRecordsSystem;               // -- возвращает сколько строчек в таблице systems
    std::unique_ptr<QSqlQuery>  m_queryReadHowManyRecordsVersion;              // -- возвращает сколько строчек в таблице db_version


    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();

    std::atomic_flag  transaction_flag;



    int Error = 0;                                              // -- хранит код ошибки

public:
    DatabaseSQLite();
    ~DatabaseSQLite();
    virtual void connectToDataBase(const QString& fullpath) override; // -- Подключение к базе данных, path - полный путь до базы данных
    virtual bool openDataBase() override;                             // -- Открытие базы данных
    virtual bool createDataBase() override;                           // -- создание базы данных с нуля, если ее нет
    virtual void closeDataBase() override;                            // -- Закрытие базы данных

    virtual bool executionQuery(QSqlQuery& query,const QString& queryForExecution) override;   // -- выполнить запрос
    virtual void setupDB() override;

    virtual bool createTableVersion(const QString& tabName) override;           // -- Создание базы таблицы версий в базе данных
    virtual bool createTableChemicalCompounds(const QString& tabName) override; // -- Создание базы таблицы химических элементов  в базе данных
    virtual bool createTableSystems(const QString& tabName) override;           // -- Создание базы таблицы  Systems
    virtual bool createTables();

    virtual bool removeRecord(const QString& nameTab, const int id) override;   // -- Удаление записи из таблицы по её id
    virtual bool fillTableVersion(const VersionData& version) override;         // -- заполнение таблицы версий
    virtual bool fillTableSystems();                                            // -- заполнение таблицы systems
    virtual bool fillTableChemicalCompounds() override;                         // -- заполнение таблицы компонентов

    bool deleteTabVersion();                                                    //-- удаление таблицы
    bool deleteTabSystems();                                                    //-- удаление таблицы
    bool deleteTabChemicalCompounds();                                          //-- удаление таблицы

    bool deleteTabs();                                                          // -- удаление всех таблиц
    void createDefaultDB();                                                     // -- создание DB  по умолчанию



    bool makePrepared(QSqlQuery& query,QString& commandQuery);
    void makePreparedforDB();                                                   // -- запускает подготовку для всех prepared

    virtual bool insertRecordVersion(const VersionData& version);
    virtual bool insertRecordSystem(const SystemData& systemData);
    virtual bool insertChemicalCompounds(const ComponentData& componentData);


    void bindPreparedToDB();
    void testIsOpenDB(const QString& msg);


    bool isDatabaseNew(const QString& fullpathDB);               // -- проверка существует ли уже такая база данных
    void setPath(const QString& fullpath);  // -- устанавливает m_filename, m_shortpath, m_fullpath
    void setPath(const QString &fullpath, const QString &shortpath, const QString &filename);  // -- устанавливает m_filename, m_shortpath, m_fullpath
    void init(const QString& fullpath);
    QString getNameDB();       // -- получить имя базы данных
    QString getShortpathDB();  // -- получить полный путь до базы данных без имени базы данных
    QString getFullpathDB();   // -- получить полный путь до базы данных


    QVector<ComponentData> readRecordsChemicalCompounds();
    ComponentData          readRecordChemicalCompounds(int id_ReadRecord);
    SystemData             readRecordSystem(int id_ReadRecord);
    QVector<SystemData>    readRecordsSystem();
    VersionData            readRecordVersion(int id_ReadRecord);

    int howManyRecordsInChemicalCompounds();  // -- сколько строчек в таблице chemical_compounds
    int howManyRecordsInSystem();             // -- сколько строчек в таблице systems
    int howManyRecordsInVersion();            // -- сколько строчек в таблице db_version

    QString     m_fullpath;
    QString     m_shortpath;
    QString     m_filename;
};


} // -- end namespace db
} // -- end namespace mapRS
} // -- end namespace bur

#endif // DATABASESQLITE_H
