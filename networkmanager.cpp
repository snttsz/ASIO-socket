#include "networkmanager.hpp"
 


void bahiart::NetworkManager::SyncTcpSocket::setupAddress(std::string HOST_NAME, unsigned short PORT)
{

    try {
        this->endPoint = std::make_shared<boost::asio::ip::tcp::endpoint>(boost::asio::ip::address::from_string(HOST_NAME),  PORT);
    }
    catch (boost::system::system_error &e) {
        std::cout 
        << "Error occured! Error code = " << e.code()
        << ". Message " << e.what() <<std::endl;

        return;
    }
}

void bahiart::NetworkManager::SyncTcpSocket::openConnection()
{
    try {
        
        boost::asio::io_service ios;

        this->socket = std::make_shared<boost::asio::ip::tcp::socket>(ios, this->endPoint->protocol());
        this->socket->connect(*(this->endPoint));
    }
    catch (boost::system::system_error &e) {
        std::cout 
        << "Error occured! Error code = " << e.code()
        << ". Message " << e.what() <<std::endl;

        return;
    }
}

void bahiart::NetworkManager::SyncTcpSocket::sendMessage(std::string message)
{
    std::size_t bytesWritten {};
    try{
        while( bytesWritten != message.length()){

            bytesWritten += this->socket->write_some(boost::asio::buffer(message.c_str()+bytesWritten, message.length() - bytesWritten));
        }
    }
      catch (boost::system::system_error &e) {
        std::cout 
        << "Error occured! Error code = " << e.code()
        << ". Message " << e.what() <<std::endl;

        return;
      }

}

bahiart::NetworkManager::SyncTcpSocket::~SyncTcpSocket(){
    this->socket->close();

}

void bahiart::NetworkManager::SyncUdpSocket::setupAddress(std::string HOST_NAME, unsigned short PORT)
{   
    
    try{

    this->endPoint = std::make_shared<boost::asio::ip::udp::endpoint>(boost::asio::ip::address::from_string(HOST_NAME), PORT);
    }
    catch (boost::system::system_error &e) {
        std::cout 
        << "Error occured! Error code = " << e.code()
        << ". Message " << e.what() <<std::endl;

        return;
      }

}

void bahiart::NetworkManager::SyncUdpSocket::openConnection()
{   
    try{


        boost::asio::io_service io_service;
        this->socket = std::make_shared<boost::asio::ip::udp::socket>(io_service);
        this->socket->open(boost::asio::ip::udp::v4());

        



    }
   catch (boost::system::system_error &e) {
        std::cout 
        << "Error occured! Error code = " << e.code()
        << ". Message " << e.what() <<std::endl;

        return;
   }

}

void bahiart::NetworkManager::SyncUdpSocket::sendMessage(std::string message)
{
    try{
        boost::system::error_code err;
        
        auto sent = this->socket->send_to(boost::asio::buffer(message), *(this->endPoint), 0, err);

        
    }
      catch (boost::system::system_error &e) {
        std::cout
        << "Error occured! Error code = " << e.code()
        << ". Message " << e.what() <<std::endl;

        return;
      }


}

void bahiart::NetworkManager::SyncUdpSocket::handle_receiver(size_t errConstValue, const boost::system::error_code &error, size_t bytes_transferred)
{
    std::vector<int> arr (errConstValue);
    

}

bahiart::NetworkManager::SyncUdpSocket::~SyncUdpSocket(){
    this->socket->close();
    std::cout << "Destrutor"; 
}

bahiart::NetworkManager::Socket::~Socket(){}

