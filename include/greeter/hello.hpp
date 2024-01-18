#pragma once

#include <greeter/export_greeter.hpp>
#include <string>

namespace Greeter {
/// Example class that is explicitly exported into a dll
class GREETER_EXPORT Hello {
public:
  Hello(const std::string &name) : name_{name} {}

  void greet() const;

private:
  const std::string name_;
};
} // namespace Greeter