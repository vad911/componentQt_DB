#ifndef VERSIONDATA_H
#define VERSIONDATA_H


namespace bur {
namespace mapRS {
namespace db {

// -- версия
struct VersionData
{
    VersionData();

    VersionData(int t_versionMajor,
                int t_versionMinor,
                int t_versionPatch);

    int m_versionMajor;
    int m_versionMinor;
    int m_versionPatch;
};


} // -- end namespace db
} // -- end namespace mapRS
} // -- end namespace bur

#endif // VERSIONDATA_H
