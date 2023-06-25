#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "exceptions.hpp"
#include "settings.hpp"

LIBRARY_NAMESPACE_BEGIN

namespace components::configs {

namespace detail {

template <typename T>
concept HasNameField = requires {
  T::kName;
};

template <typename T>
concept HasFilePath = requires {
  T::kFilePath;
};

template <typename T>
concept ValidSettings = requires {
  HasNameField<T>&& HasFilePath<T>;
};

}  // namespace detail

class Component final {
  using DataMap = std::unordered_map<std::string_view, settings::DataTypes>;

  DataMap map_{};

  std::string ReadFile(std::string_view file_path) {
    try {
      std::ifstream file_stream(file_path.data());
      if (!file_stream.is_open()) {
        throw std::runtime_error("Can't open the file: " +
                                 std::string(file_path.data()));
      }
      return std::string(std::istreambuf_iterator<char>(file_stream),
                         std::istreambuf_iterator<char>());
    } catch (const std::exception& ex) {
      throw exceptions::ReadingFile(file_path.data(), ex.what());
    }
  }

 public:
  Component() { map_.reserve(std::variant_size_v<settings::DataTypes>); }

  template <detail::ValidSettings T>
  Component* Load() {
    if (map_.contains(T::kName)) {
      throw exceptions::AlreadyLoaded(T::kName);
    }
    try {
      std::string content = ReadFile(T::kFilePath);
      map_[T::kName] = T::Parse(std::move(content));
    } catch (const std::exception& ex) {
      std::cout << "File hasn't been readed: " << T::kFilePath << std::endl
                << "error: " << ex.what() << std::endl;
      return this;
    }

    return this;
  }

  template <typename T>
  T::Type Get() const {
    if (auto it = map_.find(T::kName); it != map_.end()) {
      try {
        return std::get<typename T::Type>(it->second);
      } catch (const std::exception& ex) {
        throw exceptions::InvalidType(T::kName, ex.what());
      }
    }
    throw exceptions::NotRegistered(T::kName);
  }
};

using ConfigsPtr = std::shared_ptr<Component>;

ConfigsPtr GetPtr() {
  static ConfigsPtr config_;
  if (!config_) {
    config_ = std::make_shared<Component>();
  }
  return config_;
}

}  // namespace components::configs

LIBRARY_NAMESPACE_END
