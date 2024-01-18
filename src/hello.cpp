#include <greeter/hello.hpp>

#include "internal.hpp"

namespace Greeter {
void Hello::greet() const { details::print_impl(name_); }
} // namespace Greeter