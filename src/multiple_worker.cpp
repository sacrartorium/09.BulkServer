#include "multiple_worker.hpp"
MultipleWorker::MultipleWorker(handle_t id) : Publisher(id) {}

void MultipleWorker::job(const std::string &command) {
  // Add if open block only.
  if (mBlockCount)
    mCommands.add(command);
}

void MultipleWorker::openBrace() {
  if (!mBlockCount)
    mTime = std::time(nullptr);
  mBlockCount++;
}

void MultipleWorker::closeBrace() {
  if (mBlockCount)
    mBlockCount--;

  // Dump if end the block.
  if (!mBlockCount)
    dump();
}

PublisherPtr MultipleWorker::createWorker(handle_t id) {
  return std::make_shared<MultipleWorker>(id);
}
