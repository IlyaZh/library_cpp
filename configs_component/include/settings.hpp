#pragma once

#include <functional>
#include <variant>

LIBRARY_NAMESPACE_BEGIN

namespace CONFIGS {

namespace GROUPS {
struct Value {
  std::string group_name;
  std::vector<std::string> names;
};
struct Settings {
  constexpr static const std::string_view kName = "name";
  constexpr static const std::string_view kFilePath = "name.txt";
  using Type = Value;
  constexpr static const auto Parse = [](std::string&& name) {
    return Type{
        .group_name = std::move(name),
        .names = std::vector<std::string>{"v1", "v2", "v3"}};
  };
};

}  // namespace GROUPS
}  // namespace CONFIGS

namespace components::configs {

namespace settings {
using DataTypes = std::variant<CONFIGS::GROUPS::Value>;
}

}  // namespace components::configs

LIBRARY_NAMESPACE_END
