﻿#pragma once

#include "session.hpp"

struct Server {
  Server(boost::asio::io_service &service,
         const boost::asio::ip::tcp::endpoint &ep,
         std::shared_ptr<Controller> controller);

private:
  void accept();

  boost::asio::ip::tcp::acceptor mAcceptor;
  boost::asio::ip::tcp::socket mSocket;

  std::set<std::shared_ptr<Session>> mSessions;
  std::shared_ptr<Controller> mController;
};
