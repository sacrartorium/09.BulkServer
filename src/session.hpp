#pragma once

#include "controller.hpp"

#include <boost/asio.hpp>

struct Session : public std::enable_shared_from_this<Session> {
  Session(boost::asio::ip::tcp::socket socket,
          std::set<std::shared_ptr<Session>> &sessions,
          std::shared_ptr<Controller> controller);

  void begin();

private:
  void read();

  char mData;
  std::string mBuffer;

  boost::asio::ip::tcp::socket mSocket;
  std::set<std::shared_ptr<Session>> &mSessions;
  std::shared_ptr<Controller> mController;
};
