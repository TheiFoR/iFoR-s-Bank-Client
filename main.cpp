#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

// #include <windows.h>
// #include <dbghelp.h>
// #pragma comment(lib, "dbghelp.lib")

#include "src/main/core.h"

//#define LOG_TO_FILE
#ifdef LOG_TO_FILE
#define logFilePath "logs.log"
#endif

// QString getStackTrace()
// {
//     const int maxFrames = 64;
//     void *stack[maxFrames];
//     HANDLE process = GetCurrentProcess();
//     SymInitialize(process, NULL, TRUE);

//     // Получаем адреса вызовов
//     USHORT frames = CaptureStackBackTrace(0, maxFrames, stack, NULL);

//     SYMBOL_INFO *symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
//     symbol->MaxNameLen = 255;
//     symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

//     QStringList stackTrace;
//     for (USHORT i = 0; i < frames; i++) {
//         SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
//         stackTrace.append(QString("%1: %2").arg(frames - i - 1).arg(symbol->Name));
//     }

//     free(symbol);
//     return stackTrace.join("\n");
// }

void messageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Information"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Error"}, {QtFatalMsg, "Fatal"}});
    QByteArray localMsg = msg.toLocal8Bit();
    QDateTime time = QDateTime::currentDateTime();
    QString formattedTime = time.toString("hh:mm:ss.zzz");
    QString logLevelName = msgLevelHash[type];
    QByteArray logLevelMsg = logLevelName.toLocal8Bit();

    // QString stackTrace = getStackTrace();
    // fprintf(stderr, "Stack Trace:\n%s\n", stackTrace.toLocal8Bit().constData());

    QString message = QString(localMsg.constData());
    QString messagePath = QString("%1:%2, %3").arg(context.file).arg(context.line).arg(context.function);
    fprintf(stderr, (formattedTime + " " + logLevelMsg + ": " + message + " (" + messagePath + ")\n").toStdString().c_str());

    #ifdef LOG_TO_FILE
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
    QJsonObject jsonObject
        {
         {"@t", time.toOffsetFromUtc(QDateTime::currentDateTime().offsetFromUtc()).toString(Qt::ISODate) },
         {"@m", message },
         {"@l", logLevelName },
         {"@i", messagePath },
         };
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);

    QFile outFile(logFilePath);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << jsonDocument.toJson(QJsonDocument::Compact) << Qt::endl;
    outFile.close();
    #endif

    fflush(stderr);
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageOutput);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    qInfo("Start iFoR's Bank");

    Core core;

    core.registerContext(engine);
    core.start();

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
