
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "aux_table.h"

MainWindow::MainWindow(
    QString fullpathDB,
    QString shortpathDB,
    QString filenameDB,
    QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_fullpathDB(fullpathDB)
    , m_shortpathDB(shortpathDB)
    , m_filenameDB(filenameDB)
{
    ui->setupUi(this);




    m_dbSqlite = new db::DatabaseSQLite();
    m_dbSqlite->setPath(m_fullpathDB, m_shortpathDB, m_filenameDB);
    m_dbSqlite->connectToDataBase(m_fullpathDB);


    readDB();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_dbSqlite;

}

void MainWindow::readDB()
{
    m_vecComponentData = m_dbSqlite->readRecordsChemicalCompounds();
    if (m_vecComponentData.size() > 0) {
        // cur_rowDB = vecComponentData.at(0);
        int id = 0;
        //set_rowDB(id);
    }

    aux_table::populateTableWidget(ui->tableWidget_DB,  m_vecComponentData);

}

void MainWindow::set_rowDB(int id)
{
    if (id < m_vecComponentData.size()) {
        m_cur_rowDB = m_vecComponentData.at(id);
    }
    // m_visualizationCurRowDB();
}
