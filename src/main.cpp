#include "controller.hpp"
#include "multiple_worker.hpp"
#include "server.hpp"
#include "single_worker.hpp"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Error: bulk_server <port> <bulk_size>" << std::endl;
    return -1;
  }

  {
    size_t port = std::stoi(argv[1]);
    size_t bulkSize = std::stoi(argv[2]);

    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
    boost::asio::io_service service;
    Server host(service, ep, std::make_shared<Controller>(bulkSize));

    service.run();
  }

  return 0;
}
