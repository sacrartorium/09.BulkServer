#include "server.hpp"

Server::Server(boost::asio::io_service &service,
               const boost::asio::ip::tcp::endpoint &ep,
               std::shared_ptr<Controller> controller)
    : mAcceptor(service, ep), mSocket(service), mSessions(),
      mController(controller) {
  accept();
}

void Server::accept() {
  mAcceptor.async_accept(mSocket, [this](boost::system::error_code errorCode) {
    if (!errorCode) {
      auto session =
          std::make_shared<Session>(std::move(mSocket), mSessions, mController);
      mSessions.insert(session);
      session->begin();
    }
    accept();
  });
}
