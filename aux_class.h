#ifndef AUX_CLASS_H
#define AUX_CLASS_H

#include <databaseSQLite/databaseSQlite.h>


namespace db  = bur::mapRS::db;

class aux_class
{
public:


static QString projectSourceDirectory(const QString &subdir);
static QString getExecutablePath();
static QString getCurrentPath();




};

#endif // AUX_CLASS_H
