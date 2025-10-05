#ifndef DATABASEABSTRACT_H
#define DATABASEABSTRACT_H

#include "databaseTypes.h"
#include "versionData.h"

#include <QString>
#include <QFileInfo>
#include <QRegularExpression>
#include <QtSql/QSqlQuery>

namespace bur {
namespace mapRS {
namespace db {


class DatabaseAbstract
{
private:
    // QString     m_fullpath;
    // QString     m_shortpath;
    // QString     m_filename;
    QString     m_strVersionDB; // -- версияDB
    VersionData m_versionDB;

    int m_VersionMajor;  // -- version DB major   - new algorithms
    int m_VersionMinor;  // -- version DB minor   - new func
    int m_VersionPatch;  // -- version DB patch   - fix error

public:
    DatabaseAbstract();
    virtual ~DatabaseAbstract(){};

    DatabaseAbstract(const DatabaseAbstract&)            = delete;
    DatabaseAbstract(DatabaseAbstract&&)                 = delete;
    DatabaseAbstract& operator=(const DatabaseAbstract&) = delete;
    DatabaseAbstract& operator=(DatabaseAbstract&&)      = delete;

    // -- common interface
    virtual void connectToDataBase(const QString& fullpathDB) = 0;                      // -- Подключение к базе данных, path - полный путь до базы данных
    virtual bool openDataBase()   = 0;                                                  // -- Открытие базы данных
    virtual bool createDataBase() = 0;                                                  // -- создание базы данных с нуля, если ее нет
    virtual void closeDataBase()  = 0;                                                  // -- Закрытие базы данных
    virtual bool executionQuery(QSqlQuery& query,const QString& queryForExecution) = 0; // -- выполнить запрос
    virtual void setupDB() = 0;

    virtual bool createTableVersion(const QString& tabName)           = 0; // -- Создание базы таблицы версий в базе данных
    virtual bool createTableChemicalCompounds(const QString& tabName) = 0; // -- Создание базы таблицы химических элементов  в базе данных
    virtual bool createTableSystems(const QString& tabName)           = 0; // -- Создание базы таблицы  Systems
    virtual bool createTables() = 0;
    virtual bool removeRecord(const QString& nameTab, const int id)   = 0; // -- Удаление записи из таблицы по её id из таблицы с именем nameTab

    virtual bool fillTableVersion(const VersionData& version) = 0;         // -- заполнение таблицы версий
    virtual bool fillTableChemicalCompounds() = 0;                         // -- заполнение таблицы компонентов
    virtual bool fillTableSystems() = 0;                                   // -- заполнение таблицы systems

    virtual bool insertRecordVersion(const VersionData& version) = 0;
    virtual bool insertRecordSystem(const SystemData& systemData) = 0;
    virtual bool insertChemicalCompounds(const ComponentData& componentData) = 0;



    // bool isDatabaseNew(const QString& fullpathDB);               // -- проверка существует ли уже такая база данных
    QString get_strVersionDB();                                  // -- получение версии DB
    VersionData get_versionDB();
    int get_versionMajor();
    int get_versionMinor();
    int get_versionPatch();
    void set_versionDB(const QString& version);                  // -- установить версию DB
    // void init(const QString& fullpath);
    bool versionDB_isOK();                                       // -- проверяет что версия записана в формате [число.число.число]
    bool versionDB_isOK(QString version);                        // -- проверяет что версия записана в формате [число.число.число]
    void splitStrVersion2NumberVersion(QString& version);        // -- разделяет QString версию в числовую  [число.число.число]

    void resetVersion(); // -- сброс значений номера версий до -1


    // void setPath(const QString& fullpath);  // -- устанавливает m_filename, m_shortpath, m_fullpath
    // QString getNameDB();       // -- получить имя базы данных
    // QString getShortpathDB();  // -- получить полный путь до базы данных без имени базы данных
    // QString getFullpathDB();   // -- получить полный путь до базы данных
};

} // -- end namespace db
} // -- end namespace mapRS
} // -- end namespace bur

#endif // DATABASEABSTRACT_H
