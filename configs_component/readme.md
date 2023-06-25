# Config component

## Features

- Load at startup
- Strong typed interface
- Singleton

## Using example

How to add new config source to component?

Define `LIBRARY_NAMESPACE_BEGIN` and `LIBRARY_NAMESPACE_END` either `separated_namespace` to put library's components to separated namespace or empty string

Define config struct at settings.hpp or at another file. It should be defined at `CONFIGS` namespace.

Example:

```c++
namespace CONFIGS {

struct NEW_CONFIG {
  constexpr static const std::string_view kName = "new_config"; // name of config
  constexpr static const std::string_view kFilePath = "new_config.json"; // path to configs data file

  // The structure into which the file will be parse
  struct Value { 
    std::string group_name;
    std::vector<std::string> names;
  };

  using Type = Value;
  // Parsing function. args 
  constexpr static const auto Parse = [](std::string&& content) {
    return Type{.group_name = std::move(content),
                .names = std::vector<std::string>{"v1", "v2", "v3"}};
  };
};

}
```

Extend `DataTypes` at settings.hpp by adding a new Value structure

```c++
using DataTypes = std::variant<CONFIGS::GROUPS::Value, CONFIGS::NEW_CONFIG::Value>;
```

Create a config component instance and use Get method templated by config's name

```c++
auto configs = components::configs::GetPtr();
const auto value = configs->Get<Configs::NEW_CONIG>();
```