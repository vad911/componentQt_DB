#ifndef DATABASETYPES_H
#define DATABASETYPES_H

#include <QString>
#include <QVector>
// #include <QDir>

// -- namespace bur::mapRS::db;

namespace bur {
namespace mapRS {
namespace db {

enum Errors : int {
    notDefine                                    = -1,
    OK                                           =  0,
    ErrorConnectionToDB                          =  10,
    Failed_to_query_the_chemical_compounds_table =  20,
    Failed_to_query_the_systems_table            =  30,
    Failed_to_query_the_db_version_table         =  40,
    Failed_to_execute_query                      =  50
};

enum CrystalStructure : int {
    ShapeNotDefine = 0, // -- не определена
    cubic          = 1, // -- кубическая форма
    hexagonal      = 2, // -- гексагональную кристаллическую структуру
};

QString CrystalStructure2String(CrystalStructure type);
CrystalStructure String2CrystalStructure(QString cristalShapeStr);


struct ComponentData{
    ComponentData();
    ComponentData(int              t_id,
                  QString          t_system,
                  QString          t_component,
                  double           t_TwoTheta,
                  CrystalStructure t_crystalStructure,
                  double           t_lattice_a,
                  double           t_lattice_c,
                  int              t_h,
                  int              t_k,
                  int              t_l,
                  double           t_dhkl,
                  QString          t_description);

    int              id;
    QString          system;               // -- система Si-Ge-C, AlAs-GaAs-InAs итд
    QString          component;            // -- component - компонент - Si,SiC и тд
    double           TwoTheta;             // -- TwoTheta  - 2Theta   бреговский угол
    CrystalStructure crystalStructure; // -- форма кристала ()
    double           lattice_a;            // -- lattice_a - Параметр элементарной ячейки (ПЭЯ) решетки
    double           lattice_c;            // -- lattice_c - Параметр элементарной ячейки (ПЭЯ) решетки
    int              h;                    // -- hkl       - коэффициент h
    int              k;                    // -- hkl       - коэффициент k
    int              l;                    // -- hkl       - коэффициент l
    double           dhkl;                 // -- это межплоскостное расстояние (межплоскостный промежуток) между кристаллографическими плоскостями в кристаллической решётке
    QString          description;          // -- замечание
};

struct SystemData {
    QString system_name;  // -- имя системы
    QString description;  // -- описание системы
};



class ConstDB {
public:
    static const QString nameTableVersion;//  = "db_version";  // -- имя таблицы с версией базы данных
    static const QString nameTableChemicalCompounds;           // -- имя химических соединений с свойствами кристалической решетки
    static const QString nameTableSystems;                      // -- таблица систем

    // -- свойства DB TODO перенести в config

    static const QString NameDB;                               // -- имя базы данных
    static const QString HOST_NAMEDB;                          // -- имя хоста где находится DB
    static const QString pswDB;                                // -- пароль к DB

    static const QVector<ComponentData> vecCompanentData;      // -- исходные данные для базы соединений с свойствами кристалической решетки
    static const QVector<SystemData>    vecSystemData;         // -- исходные данные для базы соединений с свойствами кристалической решетки
};


} // -- end namespace db
} // -- end namespace mapRS
} // -- end namespace bur

#endif // DATABASETYPES_H
