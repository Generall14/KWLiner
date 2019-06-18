TEMPLATE = app
CONFIG += console c++14 core qt
CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += \
    utests/SetUtest.cpp \
    src/set.cpp \
    src/sets/setCpp.cpp \
    src/sets/setJava.cpp \
    src/sets/setMSP.cpp \
    src/sets/setPIC.cpp \
    src/sets/setPython.cpp \
    utests/DyskryminatorSMUtest.cpp \
    src/dyskryminatorSM.cpp \
    utests/ResFileUtest.cpp \
    src/resFile.cpp

LIBS += -lgmock_main -lgtest -lgmock -lpthread

HEADERS += \
    src/set.hpp \
    src/sets/setCpp.hpp \
    src/sets/setJava.hpp \
    src/sets/setMSP.hpp \
    src/sets/setPIC.hpp \
    src/sets/setPython.hpp \
    src/dyskryminatorSM.hpp \
    src/resFile.hpp
