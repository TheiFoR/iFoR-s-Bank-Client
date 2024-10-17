#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(double rate READ rate WRITE setRate NOTIFY rateChanged FINAL)

public:
    explicit User(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

    double rate() const;
    void setRate(double newRate);

signals:
    void nameChanged();
    void rateChanged();

private:
    QString _name = "Unknow";
    double _rate = -1;
};

#endif // USER_H
