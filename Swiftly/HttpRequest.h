#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "HttpHeader.h"

class TcpSocket;

class HttpRequest:public QObject
{
    Q_OBJECT

    HttpHeader header;
    QByteArray rawData;
    QHash<QString, QSharedPointer<QString>> formData;
    bool hasSetFormData;

    unsigned int totalBytes;
    unsigned int bytesHaveRead;

    QString rawHeader;
public:
    TcpSocket *socket;

public:
    HttpRequest(TcpSocket *_socket=0);
    HttpRequest(const HttpRequest &in);
    void operator=(const HttpRequest &in);

    void setFormData(const QHash<QString, QSharedPointer<QString>> &_formData)
    {
        formData=_formData;
        hasSetFormData=true;
    }

    HttpHeader & getHeader()
    {
        return header;
    }

    QString getFromIPAddress() const;

    QWeakPointer<QString> getFormData(const QString &fieldName)
    {
        if (formData.contains(fieldName))
        {
            return formData[fieldName].toWeakRef();
        }
        else
        {
            return QWeakPointer<QString>();
        }
    }

    const QHash<QString, QSharedPointer<QString>> & getFormData() const
    {
        return formData;
    }

    QByteArray & getRawData()
    {
        return rawData;
    }

    bool hasFormData()
    {
        return hasSetFormData;
    }

    void parseFormData();
    void processCookies();

    ~HttpRequest();

    void appendData(const char*,unsigned int);
    void appendData(const QByteArray &ba);

    void setRawHeader(const QString &_rh);

    QString & getRawHeader()
    {
        return rawHeader;
    }

    unsigned int getTotalBytes()
    {
        return totalBytes;
    }

    unsigned int getBytesHaveRead()
    {
        return bytesHaveRead;
    }

    void setTotalBytes(unsigned _totalBytes)
    {
        totalBytes=_totalBytes;
    }
};

#endif // HTTPREQUEST_H
