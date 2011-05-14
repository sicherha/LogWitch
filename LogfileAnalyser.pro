TEMPLATE = app
TARGET = LogfileAnalyser
QT += core \
    gui
HEADERS += LogData/LogEntryParser_dummy.h \
    Assert.h \
    LogData/LogEntryAttributes.h \
    LogData/LogEntryAttributeFactory.h \
    LogData/LogEntryParser_Logfile.h \
    LogData/LogEntryParser.h \
    LogData/StringCache.h \
    LogData/LogEntryFactory.h \
    LogData/LogEntry.h \
    logfileanalyser.h
SOURCES += LogData/LogEntryParser_dummy.cpp \
    LogData/LogEntryAttributes.cpp \
    LogData/LogEntryAttributeFactory.cpp \
    LogData/LogEntryParser_Logfile.cpp \
    LogData/StringCache.cpp \
    LogData/LogEntryFactory.cpp \
    LogData/LogEntry.cpp \
    main.cpp \
    logfileanalyser.cpp
FORMS += logfileanalyser.ui
RESOURCES += 
