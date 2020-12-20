#include "session.hpp"

Session::Session(boost::asio::ip::tcp::socket socket,
                 std::set<std::shared_ptr<Session>> &sessions,
                 std::shared_ptr<Controller> controller)
    : mBuffer(""), mSocket(std::move(socket)), mSessions(sessions),
      mController(controller) {}

void Session::begin() { read(); }

void Session::read() {
  auto session(shared_from_this());

  boost::asio::async_read(
      mSocket, boost::asio::buffer(&mData, 1),
      [this, session](boost::system::error_code errorCode, std::size_t length) {
        if (!errorCode) {
          if ('\n' != mData) {
            mBuffer += mData;
          } else {
            if ('\r' == mBuffer.back()) {
              mBuffer.pop_back();
            }

            mController->execute(mBuffer);
            mBuffer.clear();
          }
          read();

        } else {
          mSessions.erase(session);
          mSocket.close();

          if (mSessions.empty())
            mController->flush();
        }
      });
}
