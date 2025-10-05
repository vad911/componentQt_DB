#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QDir currentProjectPath = QCoreApplication::applicationDirPath();
    QString dirStr          = currentProjectPath.absolutePath();
    QString fullPathDB      = dirStr + "/" + db::ConstDB::NameDB;

    QString fullpath  = fullPathDB;
    QString shortpath = QFileInfo(fullpath).path();
    QString filename  = QFileInfo(fullpath).fileName();


    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "componentQt_DB_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w(fullpath, shortpath, filename);
    w.show();
    return a.exec();
}
