#include "libkrbn/impl/libkrbn_log_monitor.hpp"

size_t libkrbn_log_lines_get_size(libkrbn_log_lines* p) {
  auto log_lines = reinterpret_cast<libkrbn_log_lines_class*>(p);
  if (!log_lines) {
    return 0;
  }

  auto lines = log_lines->get_lines();
  if (!lines) {
    return 0;
  }

  return lines->size();
}

bool libkrbn_log_lines_get_line(libkrbn_log_lines* p,
                                size_t index,
                                char* buffer,
                                size_t length) {
  if (buffer && length > 0) {
    buffer[0] = '\0';
  }

  auto log_lines = reinterpret_cast<libkrbn_log_lines_class*>(p);
  if (!log_lines) {
    return false;
  }

  auto lines = log_lines->get_lines();
  if (!lines) {
    return false;
  }

  if (index >= lines->size()) {
    return false;
  }

  strlcpy(buffer, (*lines)[index].c_str(), length);
  return true;
}

bool libkrbn_log_lines_is_warn_line(const char* line) {
  return pqrs::spdlog::find_level(line) == spdlog::level::warn;
}

bool libkrbn_log_lines_is_error_line(const char* line) {
  return pqrs::spdlog::find_level(line) == spdlog::level::err;
}

uint64_t libkrbn_log_lines_get_date_number(const char* line) {
  if (auto n = pqrs::spdlog::find_date_number(line)) {
    return *n;
  }
  return 0;
}
