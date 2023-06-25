#pragma once

#include <functional>
#include <variant>

LIBRARY_NAMESPACE_BEGIN

namespace CONFIGS {

struct GROUPS {
  constexpr static const std::string_view kName = "name";
  constexpr static const std::string_view kFilePath = "name.txt";

  struct Value {
    std::string group_name;
    std::vector<std::string> names;
  };

  using Type = Value;
  constexpr static const auto Parse = [](std::string&& content) {
    return Type{.group_name = std::move(content),
                .names = std::vector<std::string>{"v1", "v2", "v3"}};
  };
};
}  // namespace CONFIGS

namespace components::configs {

namespace settings {
using DataTypes = std::variant<CONFIGS::GROUPS::Value>;
}

}  // namespace components::configs

LIBRARY_NAMESPACE_END
