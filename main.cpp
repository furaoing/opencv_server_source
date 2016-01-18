#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>

#include "config.h"
#include "score.h"

using boost::asio::ip::tcp;

int main() {
    try
    {
        boost::system::error_code error;
        boost::asio::io_service io_service;
        // create an io_server object

        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), MY_PORT));
        // bind a host:port to this io_service object, an implicit socket is created

        std::string port_str = std::to_string(MY_PORT);
        std::cout << "Serving HTTP on port: " + port_str << std::endl;

        while(1) {
            char buffer[BUFF_SIZE];
            // buffer is a string representing the path of image path

            tcp::socket socket(io_service);
            acceptor.accept(socket);
            // accept one connection

            std::cout << "Tcp Connection Established" << std::endl;

            while (1) {
                size_t len = socket.read_some(boost::asio::buffer(buffer), error);
                if (error == boost::asio::error::eof) {
                    std::cout << "Connection Closed" << std::endl;
                    break;
                }
                else if (error) {
                    throw boost::system::system_error(error);
                }
                std::cout << "Message Received: " << buffer << "##" << std::endl;

                roy_opencv::roy_memset((int)len, BUFF_SIZE, buffer);
                // Strip unwanted chars based on the len of msg received

                std::cout << "Image Path: " << buffer << "##" << std::endl;
                std::cout << "Image Processing Started" << std::endl;

                boost::asio::write(socket, boost::asio::buffer(score(buffer)), error);
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}