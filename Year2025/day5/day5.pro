TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        inputparsing.cpp \
        integerinterval.cpp \
        integerintervalunion.cpp \
        main.cpp \
        parsedinput.cpp \
        part1.cpp \
        part2.cpp

HEADERS += \
    inputparsing.hh \
    integerinterval.hh \
    integerintervalunion.hh \
    parsedinput.hh \
    part1.hh \
    part2.hh \
    typealiases.hh
