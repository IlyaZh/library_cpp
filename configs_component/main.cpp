#include <iostream>

#include "include/component.hpp"
#include "include/settings.hpp"

int main() {

  const auto config = components::configs::GetPtr();
  config->Load<CONFIGS::GROUPS::Settings>();

  const auto group = config->Get<CONFIGS::GROUPS::Settings>();
  std::cout << "name: " << group.group_name << std::endl;
  for (const auto& i : group.names) {
    std::cout << i << std::endl;
  }

  return 0;
}
