#ifndef AUX_TABLE_H
#define AUX_TABLE_H

#include <databaseSQLite/databaseSQlite.h>
class QTableWidget;
class QString;

namespace db  = bur::mapRS::db;

class aux_table
{
public:



    static void insertInTableWidget(QTableWidget *tableWidget, QString data, int& counter_row, int &counter_col);
    static void populateTableWidget(QTableWidget* tableWidget, const QVector<db::ComponentData>& vecComponentData);

};

#endif // AUX_TABLE_H
