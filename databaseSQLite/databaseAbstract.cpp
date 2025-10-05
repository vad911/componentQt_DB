#include <databaseSQLite/databaseAbstract.h>

namespace bur {
namespace mapRS {
namespace db {




// void DatabaseAbstract::init(const QString& fullpath)
// {
//     // setPath(fullpath);
// }

DatabaseAbstract::DatabaseAbstract()
{
    m_VersionMajor = -1;  // -- version DB major   - new algorithms
    m_VersionMinor = -1;  // -- version DB minor   - new func
    m_VersionPatch = -1;  // -- version DB patch   - fix error
}

// bool DatabaseAbstract::isDatabaseNew(const QString &fullpathDB)
// {
//     return !QFile::exists(fullpathDB); // Если файл не существует, база новая
// }

// void DatabaseAbstract::connectToDataBase(const QString &fullpath)
// {
//
// }

QString DatabaseAbstract::get_strVersionDB()
{
    return m_strVersionDB;
}

VersionData DatabaseAbstract::get_versionDB()
{
    return m_versionDB;
}

int DatabaseAbstract::get_versionMajor()
{
    return m_versionDB.m_versionMajor;
}

int DatabaseAbstract::get_versionMinor()
{
    return m_versionDB.m_versionMinor;
}

int DatabaseAbstract::get_versionPatch()
{
    return m_versionDB.m_versionPatch;
}

void DatabaseAbstract::set_versionDB(const QString &version)
{
    m_strVersionDB = version;
}

bool DatabaseAbstract::versionDB_isOK()
{
    // Регулярное выражение для проверки формата [число.число.число]
    QRegularExpression regex("^\\d+\\.\\d+\\.\\d+$");

    // Проверяем, соответствует ли строка регулярному выражению
    QRegularExpressionMatch match = regex.match(m_strVersionDB);

    // Если соответствует, возвращаем true, иначе false
    return match.hasMatch();
}

bool DatabaseAbstract::versionDB_isOK(QString version)
{
    // Регулярное выражение для проверки формата [число.число.число]
    QRegularExpression regex("^\\d+\\.\\d+\\.\\d+$");

    // Проверяем, соответствует ли строка регулярному выражению
    QRegularExpressionMatch match = regex.match(version);

    // Если соответствует, возвращаем true, иначе false
    return match.hasMatch();
}

void DatabaseAbstract::splitStrVersion2NumberVersion(QString &version)
{
    // Разделяем строку по точкам
    QStringList parts = version.split('.');

    // Проверяем, что строка разделилась на 3 части
    if (parts.size() == 3) {
        // Преобразуем каждую часть в число и сохраняем в переменные
        bool ok1, ok2, ok3;
        m_VersionMajor = parts[0].toInt(&ok1);
        m_VersionMinor = parts[1].toInt(&ok2);
        m_VersionPatch = parts[2].toInt(&ok3);

        // Проверяем, что преобразование прошло успешно
        if (!ok1 || !ok2 || !ok3) {
            qDebug() << "Ошибка: неверный формат версии!";
            // resetVersion();
            m_VersionMajor = m_VersionMinor = m_VersionPatch = -1; // Сбрасываем значения
        }
    } else {
        qDebug() << "Ошибка: неверный формат версии!";
        m_VersionMajor = m_VersionMinor = m_VersionPatch = -1; // Сбрасываем значения
    }
}

void DatabaseAbstract::resetVersion()
{
    // Сбрасываем значения
    m_VersionMajor = -1;
    m_VersionMinor = -1;
    m_VersionPatch = -1;
}

//    void DatabaseAbstract::setPath(const QString &fullpath)
//    {
//        // m_fullpath  = fullpath;
//        // m_shortpath = QFileInfo(fullpath).path();
//        // m_filename  = QFileInfo(fullpath).fileName();
//    }
//
//    QString DatabaseAbstract::getNameDB()
//    {
//        return m_filename;
//    }
//
//    QString DatabaseAbstract::getShortpathDB()
//    {
//        return m_shortpath;
//    }
//
//    QString DatabaseAbstract::getFullpathDB()
//    {
//        return m_fullpath;
//    }

} // -- end namespace db
} // -- end namespace mapRS
} // -- end namespace bur
