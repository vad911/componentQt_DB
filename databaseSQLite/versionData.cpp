#include <databaseSQLite/versionData.h>


namespace bur {
namespace mapRS {
namespace db {



VersionData::VersionData() : VersionData(-1,-1,-1)
{
}

VersionData::VersionData(int t_versionMajor, int t_versionMinor, int t_versionPatch)
    :      m_versionMajor(t_versionMajor),
           m_versionMinor(t_versionMinor),
           m_versionPatch(t_versionPatch)
{
}

} // -- end namespace db
} // -- end namespace mapRS
} // -- end namespace bur
