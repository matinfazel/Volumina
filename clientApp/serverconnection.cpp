#include "serverconnection.h"
#define PORT 1234

ServerConnection::ServerConnection()
{

}

int ServerConnection::connectToServer(QString ip)
{

    connectToHost(ip, 1234);
    if (!waitForConnected(5000)) return -1;
    if (isOpen()){
        QByteArray msg = "";
        msg.append("VOLUMINA\r\n");
        write(msg);
        if (waitForBytesWritten(5000))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}
