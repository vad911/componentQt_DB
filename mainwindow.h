#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <databaseSQLite/databaseSQlite.h>
#include "types.h"

#include <QMainWindow>



namespace fs  = std::filesystem;
namespace bmt = bur::mapRS::types;
namespace bm  = bur::mapRS;
namespace db  = bur::mapRS::db;


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString fullpath,
               QString shortpath,
               QString filename,
               QWidget *parent = nullptr);
    ~MainWindow();

    void readDB();
    void set_rowDB(int id);

private:
    Ui::MainWindow*            ui;
    db::DatabaseSQLite*        m_dbSqlite;         // -- класс работает с базой данных
    QVector<db::ComponentData> m_vecComponentData; // -- контейнер с строками из базы данных
    db::ComponentData          m_cur_rowDB;        // -- текущая строчка базы данных


    QString m_fullpathDB ;
    QString m_shortpathDB;
    QString m_filenameDB ;
};
#endif // MAINWINDOW_H
