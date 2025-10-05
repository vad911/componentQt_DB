#include "aux_table.h"


#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QHeaderView>
#include <QTableWidget>


void aux_table::insertInTableWidget(QTableWidget *tableWidget, QString data, int &counter_row, int &counter_col)
{
    QTableWidgetItem* item = new QTableWidgetItem(data);
    tableWidget->setItem(counter_row, counter_col, item);
    ++counter_col;
}

void aux_table::populateTableWidget(QTableWidget *tableWidget, const QVector<db::ComponentData> &vecComponentData)
{
    // -- Заголовки столбцов
    QStringList headers = { "id", "System Name", "Component", "2Theta", "Crystal Structure",
        "Lattice A", "Lattice C", "h", "k", "l", "d_hkl", "Description"
    };

    // -- Очищаем таблицу
    tableWidget->clear();

    int rows  = vecComponentData.size();
    int columns = headers.size();

    // -- Устанавливаем количество строк и столбцов
    tableWidget->setRowCount(rows);
    tableWidget->setColumnCount(columns);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive); // -- изменяемая ширина колонок
    // -- Устанавливаем заголовки столбцов
    tableWidget->setHorizontalHeaderLabels(headers);

    int row = 0;
    int col = 0;
    for (auto& [id, system_name, component, TwoTheta, crystalStructure, lattice_a, lattice_c, h, k, l, dhkl, description ] : vecComponentData )
    {

        // -- convert in QString
        QString str_id = QString::number(id);
        QString str_TwoTheta = QString::number(TwoTheta);
        QString str_crystalStructure = CrystalStructure2String(crystalStructure);

        QString str_lattice_a = QString::number(lattice_a);
        QString str_lattice_c = QString::number(lattice_c);
        QString str_h = QString::number(h);
        QString str_k = QString::number(k);
        QString str_l = QString::number(l);
        QString str_dhkl = QString::number(dhkl);

        insertInTableWidget(tableWidget, str_id,               row, col);
        insertInTableWidget(tableWidget, system_name,          row, col);
        insertInTableWidget(tableWidget, component,            row, col);
        insertInTableWidget(tableWidget, str_TwoTheta,         row, col);
        insertInTableWidget(tableWidget, str_crystalStructure, row, col);
        insertInTableWidget(tableWidget, str_lattice_a,        row, col);
        insertInTableWidget(tableWidget, str_lattice_c,        row, col);
        insertInTableWidget(tableWidget, str_h,                row, col);
        insertInTableWidget(tableWidget, str_k,                row, col);
        insertInTableWidget(tableWidget, str_l,                row, col);
        insertInTableWidget(tableWidget, str_dhkl,             row, col);
        insertInTableWidget(tableWidget, description,          row, col);
        // -- end
        col = 0;
        ++row;

        // Настраиваем отображение таблицы
        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Растягиваем столбцы
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);            // Выделение строк
        // tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);          // Запрет редактирования
    }
}
