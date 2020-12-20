#include "single_worker.hpp"

SingleWorker::SingleWorker(handle_t id, size_t bulkSize)
    : Publisher(id), mBulkSize(bulkSize) {
  mCommands = Container(bulkSize);
}

SingleWorker::~SingleWorker() { dump(); }

void SingleWorker::addCommand(const std::string &command) {
  mCommands.add(command);
}

void SingleWorker::openBrace() {
  if (!mBlockCount)
    dump();

  mBlockCount++;
}

void SingleWorker::closeBrace() {
  if (mBlockCount)
    mBlockCount--;
}

void SingleWorker::job(const std::string &command) {
  if (!mBlockCount) {
    if (mCommands.isEmpty())
      mTime = std::time(nullptr);
    addCommand(command);

    // The limit has been reached.
    if (mBulkSize == mCommands.size())
      dump();
  }
}

PublisherPtr SingleWorker::createWorker(handle_t id, int bulkSize) {
  return std::make_shared<SingleWorker>(id, bulkSize);
}
