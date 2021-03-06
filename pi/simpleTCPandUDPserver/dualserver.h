#ifndef DUALSERVER_H
#define DUALSERVER_H


#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QStringList>
#include <QTime>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QProcess>
#include <QTimer>
#include <QStringList>

//#define QDEBUG() QTextStream(stdout) << "\n" << __FILE__ << " / " <<__LINE__  <<" (" << __FUNCTION__ << "): "
#define QDEBUG() QTextStream(stdout) << "\n" <<"(" << __FUNCTION__ << "): "
#define QDEBUGVAR(var)  QDEBUG() << # var <<  var;

#define DATETIMEFORMAT "h:mm:ss.zzz ap"

#ifdef Q_OS_MAC
#define MPG123PATH "/Applications/VLC.app/Contents/MacOS/VLC"
#define MP3PATH1 "/Users/dannagle/github/PiPlayer/pi/music/fastmoving.mp3"
#define MP3PATH2 "/Users/dannagle/github/PiPlayer/pi/music/instrumental.mp3"
#define NMAPPATH "/Users/dannagle/nmapresults.txt"

#endif
#ifdef Q_OS_WIN

#define MPG123PATH "C:/Users/danie/github/PiPlayer/pi/music/mpg123/mpg123.exe"
#define MP3PATH1 "C:/Users/danie/github/PiPlayer/pi/music/mpg123/fastmoving.mp3"
#define MP3PATH2 "C:/Users/danie/github/PiPlayer/pi/music/mpg123/instrumental.mp3"
#define NMAPPATH "C:/Users/danie/nmapresults.txt"
#endif

#ifdef Q_OS_LINUX
#define MPG123PATH "/usr/bin/mpg123"
#define MP3PATH1 "/home/pi/fastmoving.mp3"
#define MP3PATH2 "/home/pi/instrumental.mp3"
#define NMAPPATH "/home/pi/nmapresults.txt"
#endif



class DualServer : public QObject
{
    Q_OBJECT
public:
    explicit DualServer(QObject *parent = nullptr);
    void init();
    QString debugQByteArray(QByteArray debugArray);
    void kill();


    static QByteArray tcpSend(QString ip, quint16 port, QByteArray tcpSend);
    static QString myIPs();
    static QByteArray tcpSingle(QString ip, quint16 port, QByteArray tcpSend);


public slots:
    void readPendingDatagrams();
    void disconnected();

    void processDone();
    void timerTimeout();
private slots:
     void newSession();

private:

     int listenPort;

     QByteArray nmapData;

     QProcess *mpg123;
     QUdpSocket *udpSocket;
     QTcpSocket *tcpSocket;
     QTcpServer * tcpServer;

     QTimer *timer;

     QStringList mp3Paths;
     int mp3Index;
};

#endif // DUALSERVER_H
