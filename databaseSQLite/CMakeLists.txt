cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME databaseSQLite)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT REQUIRED COMPONENTS Qt6::Widgets Qt6::Sql)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Sql)

set(HEADERS
        include/databaseSQLite/databaseAbstract.h
        include/databaseSQLite/databaseSQlite.h
        include/databaseSQLite/databaseTypes.h
        include/databaseSQLite/versionData.h
)

set(SOURCES
        databaseAbstract.cpp
        databaseSQlite.cpp
        databaseTypes.cpp
        versionData.cpp
)



add_library(${PROJECT_NAME} SHARED   ${SOURCES} ${HEADERS})

# Указываем, где искать заголовочные файлы
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)


# -- stage install 
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)
