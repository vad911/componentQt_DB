#include "types.h"


// -- namespace bur::mapRS::types
namespace bur   {
namespace mapRS {
namespace types {

const QString Constant::symbolAngstrem = "\u00C5";           //   "\u00C5\u207B\u00B9";
const QString Constant::negativeDegree = "\u207B\u00B9";

const QString Constant::symbolOmega = QString::fromUtf8(u8"\u03A9");
const QString Constant::symbol2Teta = QString::fromUtf8(u8"2\u03B8"); // 2θ
const QString Constant::symbolIntencity = "Intencity";



const QString Constant::nameAxis_X_Angstrem ="qX, " + Constant::symbolAngstrem + Constant::negativeDegree;
const QString Constant::nameAxis_Y_Angstrem ="qZ, " + Constant::symbolAngstrem + Constant::negativeDegree;
const QString Constant::nameAxis_X_nm  = "qX, nm" + Constant::negativeDegree;
const QString Constant::nameAxis_Y_nm  = "qZ, nm" + Constant::negativeDegree;
const QString Constant::nameAxis_X_mkm = "qX, mkm" + Constant::negativeDegree;
const QString Constant::nameAxis_Y_mkm = "qZ, mkm" + Constant::negativeDegree;

// const QString Constant::nameAxis_X_Angstrem ="qX, " + Constant::symbolAngstrem;
// const QString Constant::nameAxis_Y_Angstrem ="qZ, " + Constant::symbolAngstrem;
//
// const QString Constant::nameAxis_X_nm  = "qX, nm";
// const QString Constant::nameAxis_Y_nm  = "qZ, nm";
//
// const QString Constant::nameAxis_X_mkm = "qX, mkm";
// const QString Constant::nameAxis_Y_mkm = "qZ, mkm";


QString UnitsMeasurement2QString(UnitsMeasurement init)
{
    QString result = "notDefine";
    switch(init)
    {
    case UnitsMeasurement::notDefine : { result = "notDefine";  break;}
    case UnitsMeasurement::Anstrem   : { result = "Anstrem";    break;}
    case UnitsMeasurement::nanometer : { result = "nanometer";  break;}
    case UnitsMeasurement::micrometer: { result = "micrometer"; break;}
    default                          : { result = "notDefine";  break;}
    }
    return result;
}

UnitsMeasurement QString2UnitsMeasurement(QString strUnit)
{
    UnitsMeasurement result = UnitsMeasurement::notDefine;

    if(strUnit == "notDefine") {
        result = UnitsMeasurement::notDefine;
    }

    if(strUnit == "Anstrem") {
        result = UnitsMeasurement::Anstrem;
    }

    if(strUnit == "nanometer") {
        result = UnitsMeasurement::nanometer;
    }

    if(strUnit == "micrometer") {
        result = UnitsMeasurement::micrometer;
    }
    return result;
}

FileTypes convertQString2FileTypes(const QString &strTypeFile)
{
    FileTypes typeFile = FileTypes::notDefine;
    if(strTypeFile == ".txt") {
        typeFile = FileTypes::TXT;
    }

    if(strTypeFile == ".dsc") {
        typeFile = FileTypes::DSC;
    }

    if(strTypeFile == ".dbw") {
        typeFile = FileTypes::DBW;
    }
    return typeFile;
}

QString convertFileTypes2QString(const FileTypes typefile)
{
    QString strTypeFile = "notDefine";
    switch(typefile)
    {
    case FileTypes::TXT :       {strTypeFile = ".txt";      break;}
    case FileTypes::DBW :       {strTypeFile = ".dbw";      break;}
    case FileTypes::DSC :       {strTypeFile = ".dsc";      break;}
    case FileTypes::notDefine : {strTypeFile = "notDefine"; break;}
    default :                   {strTypeFile = "notDefine"; break;}
    }
    return strTypeFile;
}

// // -- тип пика
// enum TypePeak : int {
//     notDefinePeak = -1,
//     normalPeak    =  0,  // -- обычный тип пика
//     subPeak       =  1,  // -- пик подложки - gNSub
//     oscilPeak     =  2   // -- осциляции
// };


TypePeak convertQString2TypePeak(QString strTypePeak)
{
    const QMap<QString, TypePeak> mapConvertTypePeak =
        {
         { "notDefinePeak", notDefinePeak},
         { "normalPeak"   , normalPeak   },
         { "subPeak"      , subPeak      },
         { "oscilPeak"    , oscilPeak    },
         };

    if (!mapConvertTypePeak.contains(strTypePeak)) {
        throw std::invalid_argument("Unknown peak type: " + strTypePeak.toStdString());
    }
    return mapConvertTypePeak.value(strTypePeak);

}

QString convertTypePeak2QString(TypePeak typePeak)
{
    const QMap<TypePeak, QString> mapConvertTypePeak =
        {
         { notDefinePeak , "notDefinePeak" },
         { normalPeak    , "normalPeak"    },
         { subPeak       , "subPeak"       },
         { oscilPeak     , "oscilPeak"     },
         };
    if (!mapConvertTypePeak.contains(typePeak)) {
        std::string unknownType =  QString::number(typePeak).toStdString();
        throw std::invalid_argument("Unknown peak type: " + unknownType);
    }
    return mapConvertTypePeak.value(typePeak);

}

}  // -- end namespace bur
}  // -- end namespace types
}  // -- end namespace mapRS
