#pragma once

/**
 @file
 Заголовочный файл, содержащий описание подсистемы, управляющей подписчиками.
 */

#include "multiple_worker.hpp"
#include "single_worker.hpp"

#include <mutex>

struct Controller {
  using lock_guard = std::lock_guard<std::mutex>;

  Controller(size_t bulkSize);

  void push(PublisherPtr subscriber);

  void execute(std::string line);
  void flush();

private:
  std::mutex m;

  std::vector<PublisherPtr> mSubscribers;
};
