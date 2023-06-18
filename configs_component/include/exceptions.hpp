#pragma once

#include <string>
#include <stdexcept>


namespace components::configs::exceptions {

struct NotRegistered final : protected std::runtime_error {
  NotRegistered(std::string_view name)
      : std::runtime_error(std::string("Config '") + std::string(name.data()) + std::string("' is not registred")) {}
};

struct ReadingFile final : protected std::runtime_error {
  ReadingFile(const std::string& file_name, const std::string& error)
      : std::runtime_error("Error while reading file ('" + file_name +
                           "'): " + error) {}
};

struct InvalidType final : protected std::runtime_error {
  InvalidType(std::string_view name, const std::string& error)
      : std::runtime_error(std::string("Invalid struct type for config (") + name.data() +
                           "): " + error) {}
};

struct AlreadyLoaded final : protected std::runtime_error {
  AlreadyLoaded(std::string_view name)
      : std::runtime_error(std::string("Config already loaded: ") + name.data()) {}
};

}  // namespace components::configs::exceptions
