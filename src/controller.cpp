#include "controller.hpp"

Controller::Controller(size_t bulkSize) {
  push(SingleWorker::createWorker(this, bulkSize));
  push(MultipleWorker::createWorker(this));
}

void Controller::push(PublisherPtr subscriber) {
  mSubscribers.push_back(subscriber);
}

void Controller::execute(std::string line) {
  lock_guard lock(m);

  for (const auto &subscriber : mSubscribers)
    subscriber->parse(line);
}

void Controller::flush() {
  lock_guard lock(m);

  for (const auto &subscriber : mSubscribers)
    subscriber->dump();
}
