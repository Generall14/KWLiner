TEMPLATE = app
CONFIG += console c++11 core
CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += \
    utests/SetUtest.cpp \
    src/set.cpp \
    src/sets/setCpp.cpp \
    src/sets/setJava.cpp \
    src/sets/setMSP.cpp \
    src/sets/setPIC.cpp \
    src/sets/setPython.cpp

LIBS += -lgmock_main -lgtest -lgmock -lpthread

HEADERS += \
    src/set.hpp \
    src/sets/setCpp.hpp \
    src/sets/setJava.hpp \
    src/sets/setMSP.hpp \
    src/sets/setPIC.hpp \
    src/sets/setPython.hpp