// virtual_void variant of this yomm2 example via virtual_void m_tables
// https://github.com/jll63/yomm2/blob/master/examples/accept_no_visitors.cpp

#include <iostream>
#include <string>


using std::cout;
using std::string;

#include "virtual_void/utillities/unnamed__.hpp"
#include "virtual_void/data/has_m_table/shared_const.hpp"
#include "virtual_void/open_method/via_m_table/declare.hpp"

namespace {

using node = virtual_void::data::has_m_table::shared_const;
template <typename V, typename... ARGS>
auto make_node(ARGS&&... args) {
  return erased<node, V>(std::forward<ARGS>(args)...);
}

struct Plus {
  Plus(node left, node right) : left(left), right(right) {}

  node left, right;
  //    ~Plus() { cout << "~Plus()" << "\n"; } // to show, that
  //    virtual_void::typed_shared_const will call the rigtht destructor
};

struct Times {
  Times(node left, node right) : left(left), right(right) {}

  node left, right;
  //    ~Times() { cout << "~Times()" << "\n"; }
};

struct Integer {
  explicit Integer(int value) : value(value) {}
  int value;
  //    ~Integer() { cout << "~Integer()" << "\n"; }
};

// =============================================================================
// add behavior to existing classes, without changing them

}  // namespace

namespace {
// -----------------------------------------------------------------------------
// evaluate

virtual_void::open_method::via_m_table::domain value_domain;

auto value =
    virtual_void::open_method::via_m_table::declare<int(virtual_void::const_)>{
        value_domain};

auto __ = value.define<Plus>(
    [](auto expr) { return value(expr->left) + value(expr->right); });

auto __ = value.define<Times>(
    [](auto expr) { return value(expr->left) * value(expr->right); });

auto __ = value.define<Integer>([](auto expr) { return expr->value; });

// -----------------------------------------------------------------------------
// render as Forth

virtual_void::open_method::via_m_table::domain generator_domain;

auto as_forth = virtual_void::open_method::via_m_table::declare<string(
    virtual_void::const_)>{generator_domain};

auto __ = as_forth.define<Plus>([](auto expr) {
  return as_forth(expr->left) + " " + as_forth(expr->right) + " +";
});

auto __ = as_forth.define<Times>([](auto expr) {
  return as_forth(expr->left) + " " + as_forth(expr->right) + " *";
});

auto __ = as_forth.define<Integer>(
    [](auto expr) { return std::to_string(expr->value); });

// -----------------------------------------------------------------------------
// render as Lisp

auto as_lisp = virtual_void::open_method::via_m_table::declare<string(
    virtual_void::const_)>{generator_domain};

auto __ = as_lisp.define<Plus>([](auto expr) {
  return "(plus " + as_lisp(expr->left) + " " + as_lisp(expr->right) + ")";
});

auto __ = as_lisp.define<Times>([](auto expr) {
  return "(times " + as_lisp(expr->left) + " " + as_lisp(expr->right) + ")";
});

auto __ = as_lisp.define<Integer>(
    [](auto expr) { return std::to_string(expr->value); });

}  // namespace

// -----------------------------------------------------------------------------

int main() {
  using namespace virtual_void;

  auto expr = erased_in_place<node, Times>(
      erased_in_place<node, Integer>(2),
      erased_in_place<node, Plus>(erased_in_place<node, Integer>(3),
                                  erased_in_place<node, Integer>(4)));

  std::cout << as_forth(expr) << " = " << as_lisp(expr) << " = " << value(expr);
  return 0;
}
