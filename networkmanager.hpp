#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <iostream>

//Asio lib
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <thread>

 
namespace bahiart 
{
    namespace NetworkManager
    {
        class SocketException : std::exception
        {
        private:
            const char *description{};

        public:
            SocketException(const char *description) : description(description) {}

            const char *what()
            {
                return description;
            }
        };


        class Socket
        {   
            public:
                
                virtual void setupAddress(std::string HOST_NAME, unsigned short PORT) = 0;

                virtual void openConnection() = 0;

                virtual void sendMessage(std::string message) = 0;

                virtual ~Socket() = 0;
        };

        class SyncTcpSocket : public bahiart::NetworkManager::Socket
        {
            private:
                std::shared_ptr<boost::asio::ip::tcp::endpoint> endPoint;
                std::shared_ptr<boost::asio::ip::tcp::socket> socket;
            public:

                void setupAddress(std::string HOST_NAME, unsigned short PORT) override;

                void openConnection() override;

                void sendMessage(std::string message) override;

                ~SyncTcpSocket() override;

        };

        class SyncUdpSocket : public bahiart::NetworkManager::Socket
        {
            private:
                std::shared_ptr<boost::asio::ip::udp::endpoint> endPoint;
                std::shared_ptr<boost::asio::ip::udp::socket> socket;
                
            public:

                void setupAddress(std::string HOST_NAME, unsigned short PORT) override;
                void openConnection() override;
                void sendMessage(std::string message) override;
                void handle_receiver(std::size_t errConsValue, const boost::system::error_code& error, size_t bytes_transferred);
                void wait();
                void receiver();

                ~SyncUdpSocket() override;
        };
    }
}



#endif
