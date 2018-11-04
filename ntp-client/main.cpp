#include <iostream>
#include <Poco/Net/NTPClient.h>
#include <Poco/Net/NTPEventArgs.h>
#include <Poco/Net/NTPPacket.h>
#include <Poco/Delegate.h>
#include <ctime>

class NTPDelegate {
public:
    void onNTPEvent(const void *pSender, Poco::Net::NTPEventArgs &arg) {
        packet = arg.packet();
        std::cout << "on asd " << arg.packet().receiveTime().epochTime() << std::endl;
    }

    Poco::Net::NTPPacket getPacket() {
        this->packet;
    }
private:
    Poco::Net::NTPPacket packet;
};

int main() {
    Poco::Net::SocketAddress::Family family;
    Poco::Net::NTPClient ntpClient(family);
    Poco::Net::SocketAddress socketAddress("172.17.0.2",123);

    NTPDelegate ntpDelegate;
    ntpClient.response += Poco::delegate(&ntpDelegate,&NTPDelegate::onNTPEvent);

    ntpClient.request(socketAddress);

    std::cout << ntpClient.response.hasDelegates() << std::endl;

    ntpClient.response -= Poco::delegate(&ntpDelegate,&NTPDelegate::onNTPEvent);

    time_t t = ntpDelegate.getPacket().receiveTime().epochTime();
    std:: cout << std::asctime(std::localtime(&t)) << std::endl;
    std::cout << ntpClient.response.hasDelegates() << std::endl;
    return 0;
}
