#include "aux_class.h"

#include <QDir>
#include <QApplication>

QString aux_class::projectSourceDirectory(const QString &subdir)
{
    // Start from the directory where the executable is located
    QDir dir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    // If building in a subdirectory (e.g., debug, release), move up one level
    if (dir.dirName().toLower() == "debug"
        || dir.dirName().toLower() == "release"
        || dir.dirName().toLower() == "bin")
    {
        dir.cdUp();
    }
#elif defined(Q_OS_MAC)
    // Handle the specific bundle structure on macOS
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    // Navigate into the desired subdirectory (e.g., "doc", "resources")
    dir.cd(subdir);
    return dir.absolutePath();
}

QString aux_class::getExecutablePath() {
    return QApplication::applicationDirPath();
}

QString aux_class::getCurrentPath() {
    return QDir::currentPath();
}

