#include <databaseSQLite/databaseTypes.h>

namespace bur {
namespace mapRS {
namespace db {

const QString ConstDB::nameTableVersion           = "db_version";               // -- имя т
const QString ConstDB::nameTableChemicalCompounds = "chemical_compounds";
const QString ConstDB::nameTableSystems           = "systems";


// -- свойства DB TODO пренести в config
// const QString ConstDB::NameDB      = "d:/db/compaunds.db";
const QString ConstDB::NameDB      = "compaunds.db";
const QString ConstDB::HOST_NAMEDB = "HOST_NAME_LOCALHOST";
const QString ConstDB::pswDB       = "psw";

const QVector<ComponentData> ConstDB::vecCompanentData = {
    // -  system     component  TwoTheta   crystalShape               lattice_a lattice_c  h  k  l    dhkl    description
    {  1,  "Si-Ge-C",            "Si",   69.13,    CrystalStructure::cubic,      0.54310,  0.54310,   0, 0, 4, 0.13578,  ""                        },
    {  2,  "Si-Ge-C",            "Si",   88.03,    CrystalStructure::cubic,      0.54310,  0.54310,   2, 2, 4, 0.11087,  "use for calculate stress"},
    {  3,  "Si-Ge-C",            "Ge",   66.00,    CrystalStructure::cubic,      0.56580,  0.56580,   0, 0, 4, 0.14145,  ""                        },
    {  4,  "Si-Ge-C",            "Ge",   83.67,    CrystalStructure::cubic,      0.56580,  0.56580,   2, 2, 4, 0.11155,  "use for calculate stress"},
    {  5,  "Si-Ge-C",             "C",  119.49,    CrystalStructure::cubic,      0.35670,  0.35670,   0, 0, 4, 0.08918,  ""                        },
    {  6,  "Si-Ge-C",           "SiC",   90.01,    CrystalStructure::cubic,      0.4359,   0.4359,    0, 0, 4, 0.10898,  ""                        },
    {  7,  "Si-Ge-C",           "SiC",  119.99,    CrystalStructure::cubic,      0.4359,   0.4359,    2, 2, 4, 0.08895,  "use for calculate stress"},
    {  8,  "AlAs-GaAs-InAs",   "AlAs",   66.35,    CrystalStructure::cubic,      0.56310,  0.56310,   0, 0, 4, 0.14078,  ""                        },
    {  9,  "AlAs-GaAs-InAs",   "AlAs",   84.16,    CrystalStructure::cubic,      0.56310,  0.56310,   2, 2, 4, 0.11494,  "use for calculate stress"},
    { 10,  "AlAs-GaAs-InAs",   "GaAs",   66.06,    CrystalStructure::cubic,      0.56530,  0.56530,   0, 0, 4, 0.14132,  ""                        },
    { 11,  "AlAs-GaAs-InAs",   "GaAs",   83.75,    CrystalStructure::cubic,      0.56530,  0.56530,   2, 2, 4, 0.11538,  "use for calculate stress"},
    { 12,  "AlAs-GaAs-InAs",   "InAs",   61.14,    CrystalStructure::cubic,      0.60580,  0.60580,   0, 0, 4, 0.15146,  ""                        },
    { 13,  "AlAs-GaAs-InAs",   "InAs",   77.05,    CrystalStructure::cubic,      0.60580,  0.60580,   2, 2, 4, 0.12367,  "use for calculate stress"},
    { 14,  "AlP-GaP-InP",       "AlP",   69.14,    CrystalStructure::cubic,      0.54300,  0.54300,   0, 0, 4, 0.13575,  ""                        },
    { 15,  "AlP-GaP-InP",       "AlP",   88.05,    CrystalStructure::cubic,      0.54300,  0.54300,   2, 2, 4, 0.11084,  "use for calculate stress"},
    { 16,  "AlP-GaP-InP",       "GaP",   68.86,    CrystalStructure::cubic,      0.54500,  0.54500,   0, 0, 4, 0.13625,  ""                        },
    { 17,  "AlP-GaP-InP",       "GaP",   87.64,    CrystalStructure::cubic,      0.54500,  0.54500,   2, 2, 4, 0.11125,  "use for calculate stress"},
    { 18,  "AlP-GaP-InP",       "InP",   63.29,    CrystalStructure::cubic,      0.58730,  0.58730,   0, 0, 4, 0.14683,  ""                        },
    { 19,  "AlP-GaP-InP",       "InP",   79.96,    CrystalStructure::cubic,      0.58730,  0.58730,   2, 2, 4, 0.11988,  "use for calculate stress"},
    { 20,  "AlN-GaN-InN",       "AlN",   36.03,    CrystalStructure::hexagonal,  0.31127,  0.49816,   0, 0, 2, 0.24905,  ""                        },
    { 21,  "AlN-GaN-InN",       "AlN",  111.05,    CrystalStructure::hexagonal,  0.31127,  0.49816,   1, 0, 5, 0.09344,  "use for calculate stress"},
    { 22,  "AlN-GaN-InN",       "GaN",   34.57,    CrystalStructure::hexagonal,  0.31893,  0.51851,   0, 0, 2, 0.25924,  ""                        },
    { 23,  "AlN-GaN-InN",       "GaN",  105.01,    CrystalStructure::hexagonal,  0.31893,  0.51851,   1, 0, 5, 0.09709,  "use for calculate stress"},
    { 24,  "AlN-GaN-InN",       "InN",   31.34,    CrystalStructure::hexagonal,  0.53800,  0.57040,   0, 0, 2, 0.28519,  ""                        },
    { 25,  "AlN-GaN-InN",       "InN",   92.20,    CrystalStructure::hexagonal,  0.53800,  0.57040,   1, 0, 5, 0.10690,  "use for calculate stress"},
};


const QVector<SystemData> ConstDB::vecSystemData
{
    {"Si-Ge-C",        ""},
    {"AlAs-GaAs-InAs", ""},
    {"AlP-GaP-InP",    ""},
    {"AlN-GaN-InN",    ""}
};

QString CrystalStructure2String(CrystalStructure type)
{
    QString result = "ShapeNotDefine";
    switch(type)
    {
        case CrystalStructure::ShapeNotDefine: {result = "ShapeNotDefine"; break;}
        case CrystalStructure::cubic:          {result = "cubic";          break;}
        case CrystalStructure::hexagonal:      {result = "hexagonal";      break;}
        default :                              {result = "ShapeNotDefine"; break;}
    }
    return result;
}

CrystalStructure String2CrystalStructure(QString cristalShapeStr)
{
    CrystalStructure result = CrystalStructure::ShapeNotDefine;

    if (cristalShapeStr == "ShapeNotDefine") {
        result = CrystalStructure::ShapeNotDefine;
    }

    if (cristalShapeStr == "cubic") {
        result = CrystalStructure::cubic;
    }

    if (cristalShapeStr == "hexagonal") {
        result = CrystalStructure::hexagonal;
    }
    return result;
}

ComponentData::ComponentData()
    : ComponentData (0, "", "", 0.0, CrystalStructure::ShapeNotDefine, 0.0, 0.0, 0, 0, 0, 0.0, "")
{
}

ComponentData::ComponentData(int              t_id,
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
                             QString          t_description)
    : id(t_id),
      system(t_system),
      component(t_component),
      TwoTheta(t_TwoTheta),
      crystalStructure(t_crystalStructure),
      lattice_a(t_lattice_a),
      lattice_c(t_lattice_c),
      h(t_h),
      k(t_k),
      l(t_l),
      dhkl(t_dhkl),
      description(t_description)
{
}

// -- end vecCompanentData



} // -- end namespace db
} // -- end namespace mapRS
} // -- end namespace bur

