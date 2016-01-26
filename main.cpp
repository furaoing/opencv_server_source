#include <iostream>
#include <ctime>
#include <boost/asio.hpp>

#include "config.h"
#include "score.h"

using namespace opencv_server;

int main() {
    using boost::asio::ip::tcp;

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
            symbol_handler symbol_detector = symbol_handler();
            shape_handler shape_examiner = shape_handler();
            face_handler face_detector = face_handler();
            // Create three handlers to process image
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

                boost::asio::write(socket, boost::asio::buffer(score(buffer,
                                                                     &symbol_detector,
                                                                     &shape_examiner,
                                                                     &face_detector)), error);
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}