#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QShortcut>
#include <QWidgetAction>
#include <QSettings>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QPoint>



// -- namespace bur::mapRS::types
namespace bur   {
namespace mapRS {
namespace types {


struct  conv {

    static constexpr const double from_kx      =      1000.0;
    static constexpr const double from_mx      =          0.001;
    static constexpr const double from_ux      =          0.000001;
    static constexpr const double from_nx      =          0.000000001;
    static constexpr const double to_kx        =          0.001;
    static constexpr const double to_mx        =       1000.0;
    static constexpr const double to_ux        =    1000000.0;
    static constexpr const double to_nx        = 1000000000.0;
    static constexpr const double pct_to_parts =          0.01;
};


// -- свойство кривой
struct PropertyCurve {
    int idx; // -- индекс кривой

};


// -- используется для подсчета количества пиков в контейнере по типам ( например в analytics.h -  m_selectedPeaks)
struct NumberSelectedPeaksByTypes {
    int oscil;  // -- количество пиков осциляции в контейнере (синие пики)
    int sub;    // -- количество пиков подложки  в контейнере (зеленые пики)
    int normal; // -- количество пиков обычных  в контейнере  (черные пунктирной линией)
};


// -- в комплексном контейнере QVector<QVector<double>> data
// -- в каждом четном контейнере QVector<double> systemData (data[0], data[2], ...) хранится QVector<double> systemData
// -- в каждом четном контейнере QVector<double> Intencities  - контенейнере хранятся интенсивности
// -- описание формата header DSC
enum class headerDscFile : int {
    indNotDefine         = -1,
    ind2ThetaMin         =  0,
    ind2ThetaMax         =  1,
    ind2ThetaStep        =  2,
    indOmegaMin          =  3,
    indOmegaMax          =  4,
    indOmegaStep         =  5,
    indExposition        =  6,     // -- Exposition - экспозиция,
    // indCount             =  7,  // -- count счет
    // indStatusMeasurement =  8,  // -- статус измерения, 1 - частичное измерение, 2 полное, 0 - неопределено
    // indExternal          =  9,  // -- расширение файла откуда брать данные
    indScanCount     = 7,          // number of scans (LINE COUNT ? REPEAT COUNT?)
    indScanStatus    = 8,          // = MeasureIntervalStatus, -- StatusMeasurement
    indFileExtension = 9,          // determined of data file extension for scanned interval (D01, D02, etc.)
    indScanType      = 10,         // Type 1 – measured intensities are equal to count rate (counts of impulses divided by exposition).
    // Type 2 – measured intensities are equal the number of counts. (unit = impulse count)
    indLength                      // should be the last element of this enum
};

enum MeasMethodId {
    MEAS_METHOD_USER          = 0,
    MEAS_METHOD_THETA_F_THETA_D = 1,
    MEAS_METHOD_THETA_D       = 2,
    MEAS_METHOD_THETA_F       = 6,
    MEAS_METHOD_OMEGA         = 3,
    MEAS_METHOD_THETA_F_THETA_D_OMEGA = 9,
    MEAS_METHOD_MACRO_KSI     = 4,
    MEAS_METHOD_MACRO_SIN_KSI = 5,
    MEAS_METHOD_PPF_KSI       = 7,
    MEAS_METHOD_PPF_SIN_KSI   = 8,
    MEAS_METHOD_LAUE_KSI      = 17,
    MEAS_METHOD_LAUE_SIN_KSI  = 18,
    MEAS_METHOD_ORI_KSI       = 27,
    MEAS_METHOD_ORI_SIN_KSI   = 28,
    MEAS_METHOD_MACRO         = 101,
    MEAS_METHOD_MACRO_SIN     = 102,
    MEAS_METHOD_HI            = 110,
    MEAS_METHOD_XY            = 111,
    MEAS_METHOD_PHI           = 112
    //MEAS_METHOD_BASE        = 103
};

enum class TypeCompare : int {
    notDefine    = -10,
    equalOrLess  = -2,
    less         = -1,
    equal        =  0,
    great        =  1,
    greatOrEqual =  2,
};



enum class CollisionResolution {
    AddOnlyIfNotEists,
    Overwrite,
};


// -- для state maschine
enum PeakState : int {
    StateUnDefine   = 0,
    Peak_Normal     = 1,     // -- установить новый пик как normal  обычный, без цветового выделения
    Peak_Oscil      = 2,     // -- выбранный пик окрашивается как oscil peak , пик слоя   - синего цвета
    Peak_Sub        = 3,     // -- выбранный пик окрашивается как sub peak - пие подложки - зеленого цвета
    Peak_Ghost      = 4,     // -- выбранный пик окрашивается как normal   - пик перед удалением
    deletePeak      = 5      // -- удалить пик
};


// -- поддерживаемые типы файлов
enum class FileTypes {
    notDefine  = -1,
    DSC        =  0,
    TXT        =  1,
    DBW        =  2
};


enum TypeExist: int{
    notExist       = -1,   // -- задается в коде
    notDefineExist =  0,   // -- пока не используется
    Exist          =  1    // -- пока не используется
};

// -- typefile - расширение файла с точкой в начале : ".txt"
FileTypes convertQString2FileTypes(const QString& strTypeFile);
QString convertFileTypes2QString(const FileTypes typefile);

// -- расчет по 2-м пикам или по группе пиков
enum class TypeCalculateThickness  : int {
    notDefine = -1,
    CalculateByTwoPeaks   = 0,  // -- простой расчет по 2 выделенным пикам
    CalculateByGroupPeaks = 1,  // -- расчет по выбранной группе пиков
};


// -- тип пространства - прямое, обратное
enum TypeSpace : int {
    SpaceNotDefine  = -100,// -- пространство не определено
    ReciprocalSpace = -1,  // -- обратное (взаимное, двустороннее) пространство
    DirectSpace     =  1,  // -- прямое пространство
};

enum Type_nMark : int {
    notDefine            = -1,  // -- не определено
    noMarker             =  0,  // -- нет маркера
    verticalLine          =  1,  // -- вертикальная линия
    horizontalLine       =  2,  // -- горизонтальная линия
    arbitraryPositions   =  4,  // -- произвольные положения
};


enum class TypeProject : int {
    NotDefine,       // -- проект не определен
    ProjectSimple,   // -- проект с 1 экспериментом
    ProjectComplex,  // -- проект с несколькоми экспериментами
};


// -- тип данных, 2Theta, Omega, Intencity
enum class TypeData : int {
    dataNotDefined = -1,
    dataOmega      =  2,  // -- тип данных, данные омега
};


enum class TypeWidget : int{
    notDefine   = -1,
    TabComplex =  1,  // -- виджет с разделителем
    TabSimple   =  2,  // -- простой виджет QWidget* widget;
};


// -- единицы измерения
enum class UnitsMeasurement : int {
    notDefine = -1,
    Anstrem   =  0,  // -- 1e-10 m   (=10^-10 m )
    nanometer =  1,  // -- 1e-9 m    (=10^-9 m)
    micrometer = 2,  // -- 1e-6 m    (=10^-6 m)
};

enum class TypeUsedFormula : int {
    notDefine = -1,
    formula1  =  0,  // -- формула из наследства
    formula2  =  1,  // --
    formula3  =  2,
    formula4  =  4,
};


QString UnitsMeasurement2QString(UnitsMeasurement init);
UnitsMeasurement QString2UnitsMeasurement (QString strUnit);


enum TypeParam : int
{
    notDefineParam   = -1,
    typeLambda       =  0, // -- длина волны, лямбда
    typeH            =  1, // h
    typeK            =  2, // k
    typeL            =  3, // l
    typeLog          =  4, // -- преобразовать в логрифм
    typeSdvigOm      =  5, // -- смещение "омега"
    typeLoadInOneTab =  6, // -- загрузить в один таб
}; // -- end enum class TypeParam


// -- тип пика
enum TypePeak : int {
    notDefinePeak = -1,
    normalPeak    =  0,  // -- обычный тип пика
    subPeak       =  1,  // -- пик подложки - gNSub
    oscilPeak     =  2   // -- осциляции
};

TypePeak convertQString2TypePeak(QString strTypePeak);
QString  convertTypePeak2QString(TypePeak typePeak);


struct PeakInfo{
    QPointF  point;      // -- координата пика на графике
    QString  gtypePeak;  // -- тип пика : "sub" - подложка, "normal" - обычный не выделенный пик(не участвует в расчете),  "oscil" - обычный пик, который участвует в расчете
    int      idxPeak;    // -- индекс пика в контейнере m_PosPeaks
    TypePeak typePeak;   // -- тип пика
    PeakState peakState; // -- режим пика
};


// -- сборник данных которые используются в создании нового DSC
struct DataDSC {
    QVector <double> data_int;
    QVector <double> g_param;
};


struct PersonalData {
    QString nameOrganization;
    QString addressOrganization;

    QString operatorName;
    QString operatorMiddleName;
    QString operatorFamily;
};


// -- хранит коэффициенты уравнения y = kx +b
struct LineKoefficient {
    double k; // -- k - коэффициент, y = kx +b
    double b; // -- b - свободный член
};


// -- индексы для информации которая будет в PDF отчете
enum class idxDocument : int {
    notDefine               = -1,
    nameOrganization        =  0, // -- имя организации
    nameAuthor              =  1, // -- автор отчета
    filename                =  2, // -- название файла
    dateExperiment          =  3, // -- дата эксперимента
    dateReport              =  4, // -- дата отчета
    nameSystem              =  5, // -- имя системы
    nameSub                 =  6, // -- название элемента подложки
    nameEpitaxialCopmponent =  7, // -- название элемента покрывающего слоя
    value_procentSub        =  8, // -- значение толщины
    value_procentEpitaxial  =  9, // -- значение толщины
    value_Th                = 10, // -- значение толщины
    unitMeasurement         = 11, // -- единица измерения
    typeSpace               = 12, // -- тип пространства
    idxDocumentSize               // -- последний элемент для расчета размера контейнера

};


enum class QtDateMode : int {
    notDefine         = 0,
    StandartDate      = 1, // -- Стандартный формат даты
    ISOformateDate    = 2,
    CustomFormateDate = 3, // -- yyyy-MM-dd HH:mm:ss
    OnlyDate          = 4,
    OnlyTime          = 5,

    OnlyYear          = 6,
    OnlyMonth         = 7,
    OnlyDay           = 8,
    OnlyHour          = 9,
    OnlyMin           = 10,
    OnlySec           = 11,
};



struct  CurrentDate {
    int Year;
    int Month;
    int Day;
    int Hour;
    int Min;
    int Sec;
    int dayOfWeak;
    int dayOfYear;
};



struct BundleMainWindow {
    // // -- common action
    // QShortcut*       copyBif;      // -- действие "сохранить в буфер PNG - toClipboardPNG"
    // QAction*         saveMapD;     // -- действие "сохранить\карту(данные)"
    // QAction*         saveMapG;     // -- действие "сохранить\nкарту(PNG)"
    // QAction*         savePrD;      // -- действие "сохранить\профиль(данные)"
    // QAction*         savePrG;      // -- действие "сохранить\nпрофиль(PNG)"

    // QAction*         invAct;       // -- действие "смена типа пространства : "Обратное <-> Прямое""
    // QAction*         printAct;     // -- печать на принтер
    // QAction*         circuitAct;   // -- показать контур
    // QAction*         Tools;        // -- Параметры
    // QAction*         wAnalyt;      // -- Анализ
    // QMenu*           PrMap;        // -- меню Профиль
    // QMenu*           menuSave;     // -- меню Сохранить

    QDoubleSpinBox*  Lamda_tools;  // -- QDoubleSpinBox,  "λ:", setValue(g_param[3]) = ParamL = 1.5406, NoButtons, setDecimals(4)
    QDoubleSpinBox*  Shift_tools;  // -- QDoubleSpinBox,  "ΔΩ", (g_param[5] = ParamSdvigOm =  0, NoButtons, setDecimals(4)
    QCheckBox*       Check_tools;  // -- QCheckBox, Логарфим, g_param[4], g_param[4]=Check_tools->isChecked()
    QSpinBox*        H_tools;      // -- QSpinBox, "h: ",  g_param[0] = ParamLambda = 1 ???, g_param[0] = H_tools->value()  (TODO : check_  H_tools == ParamH ??? ) перепутаны параметры, setMaximumWidth(20) ???
    QSpinBox*        K_tools;      // -- QSpinBox ,"k: ",  g_param[1] =  (g_param[1] =  ParamH ???,  g_param[1] = K_tools->value() ??? TODO : find error why g_param[1] =  ParamH  ), NoButtons, setMaximumWidth(20)  (TODO : check_ )
    QSpinBox*        L_tools;      // -- QSpinBox, "l: ",  g_param[2] =  (g_param[2] =  ParamK ???   g_param[2] = L_tools->value())


    // QWidgetAction*   ToolsWA;      // -- видимость констант, логарифма
    // QWidgetAction*   CountStWA;    // -- связано с "видимость конутра на текущем графике"
    // QWidgetAction*   CountNWA;     // -- связано с "видимость конутра на текущем графике"

    // -- personal
    TypeWidget       type;
    QString          titulTab;
    QRectF           zoom;
    QSettings*       settings;
    QVector <double> g_param;
    QVector<QString> nameIntervals; // -- имена интервалов, если есть лишь один интервал то он будет называться по имени первого интервала или "D00"
    PersonalData     personalData;  // -- персональные данные

};



// -- разные константы
class Constant {
public:
    static const QString symbolOmega;
    static const QString symbol2Teta;
    static const QString symbolAngstrem;
    static const QString symbolIntencity;

    static const QString negativeDegree;
    // -- Angstrem
    static const QString nameAxis_X_Angstrem;  // ="qX, \u00C5\u207B\u00B9";
    static const QString nameAxis_Y_Angstrem;  // ="qZ, \u00C5\u207B\u00B9";

    // -- nanometer
    static const QString nameAxis_X_nm;
    static const QString nameAxis_Y_nm;

    // -- mkm
    static const QString nameAxis_X_mkm;
    static const QString nameAxis_Y_mkm;
    // NameX="qX, nm\u207B\u00B9";
    // NameY="qZ, nm\u207B\u00B9";
}; // -- end class Constant


enum idxSpace : int {
    idx_notDefine = -1,
    idx_xMin      =  0,
    idx_xMax      =  1,
    idx_yMax      =  2,
    idx_yMin      =  3,
    idx_TypeSpace =  4, // -- тип пространства, значение по этому индексу:-1 - обратное 1 - прямое
};

// -- индесы данных в векторе data;  QVector<QVector<double>> data = uniquePtrReader->openFile(fullpath);
// -- чуть изменная схема enum class headerDscFile (добавлены Lambda1, Lambda2, Radius вначало  enum)
enum TypeIndex : int {
    idxNotDefine     =  -1,
    indLambda1       =   0,
    indLambda2       =   1,
    indRadius        =   2,
    idxMinX          =   3,
    idxMaxX          =   4,
    idxStepX         =   5,
    idxMinOm         =   6,
    idxMaxOm         =   7,
    idxStepOm        =   8,
    idxExposition    =   9,
    idxScanCount     =  10,  // number of scans (LINE COUNT ? REPEAT COUNT?)
    idxScanStatus    =  11,  // MeasureIntervalStatus, -- StatusMeasurement
    idxFileExtension =  12,  // determined of data file extension for scanned interval (D01, D02, etc.)
    idxScanType      =  13,  // Type 1 – measured intensities are equal to count rate (counts of impulses divided by exposition).
};

// -- используется только в funFromLib::saveDSC (для вектора data) и в MainWindow::SaveDSC() (для вектора Intervals_data_ex)
enum DataDesc {
    idx_NotDefine         =   -1,
    idx_2ThetaMin         =    0,
    idx_2ThetaMax         =    1,
    idx_2ThetaStep        =    2,
    idx_OmegaMin          =    3,
    idx_OmegaMax          =    4,
    idx_OmegaStep         =    5,
    idx_Exposition        =    6,          // -- Exposition - экспозиция,
    idx_ScanCount         =    7,          // -- number of scans (LINE COUNT ? REPEAT COUNT?)
    idx_ScanStatus        =    8,          // -- = MeasureIntervalStatus, -- StatusMeasurement
    idx_ScanType          =    9,          // -- Type 1 – measured intensities are equal to count rate (counts of impulses divided by exposition).
};


// -- для группировки по одинаковым омега
struct IntervalSystemProperty
{
    // double Lambda1;
    // double Lambda2;
    // double indRadius;
    double minTwoTheta;
    double maxTwoTheta;
    double stepTwoTheta;
    double minOmega;
    double maxOmega;
    double stepOmega;
    // double idxExposition;
    // int    ScanCount;
    // int    ScanStatus;
    // QString idxFileExtension;
    // int    idxScanType;
    int    numberInterval;  // -- индекс (номер) интервала
};


struct IntervalProperty {
    double Lambda1;
    double Lambda2;
    double indRadius;
    double minTwoTheta;
    double maxTwoTheta;
    double stepTwoTheta;
    double minOmega;
    double maxOmega;
    double stepOmega;
    double idxExposition;
    int    ScanCount;
    int    ScanStatus;
    QString idxFileExtension;
    int    idxScanType;
    int    numberInterval;  // -- индекс (номер) интервала
};



struct IntervalData {
    int intervalIdx;
    QString IntervalName;
    QString describe;
    bool checked;  // -- признак что объект выбран
};



}  // -- end namespace bur
}  // -- end namespace types
}  // -- end namespace mapRS


#endif // TYPES_H
