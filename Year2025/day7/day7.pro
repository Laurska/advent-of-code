TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        fileutility.cpp \
        main.cpp \
        parser.cpp \
        part1.cpp \
        part2.cpp \
        token.cpp

HEADERS += \
    fileutility.hh \
    parser.hh \
    part1.hh \
    part2.hh \
    token.hh \
    typealiases.hh
