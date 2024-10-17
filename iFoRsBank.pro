QT += quick

# win32:LIBS += -lDbgHelp
# win32: DEFINES += _WIN32

SOURCES += \
    main.cpp \
    src/client/client.cpp \
    src/main/core.cpp \
    src/main/eventdispatcher.cpp \
    src/user/user.cpp \
    src/utils/parameterhandler.cpp

RESOURCES += \
    assets.qrc \
    qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/api/def.h \
    src/api/external/serverAuthorization.h \
    src/api/internal/clientAuthorization.h \
    src/api/internal/internalId.h \
    src/api/internal/serverInfo.h \
    src/client/client.h \
    src/main/core.h \
    src/main/eventdispatcher.h \
    src/user/user.h \
    src/enums.h \
    src/utils/parameterhandler.h
