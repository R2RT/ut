//
// Copyright (c) 2019-2020 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/ut.hpp>

#include "test.hpp"

static test::suite<"failing tests"> _ = [] {
  using namespace test;

  "printing test"_test = [] {
    std::cerr << "\ntest cerr to be captured" << std::endl;
    expect(false);
  };
  skip / "skipped test"_test = [] {};
  "equality"_test = [] {
    "should be equal"_test = [] { expect(42_i == 42); };
    "should not be equal"_test = [] { expect(1_i != 2); };
    "throws"_test = [] { throw std::runtime_error("throws explicitly"); };
    skip / "skipped nested test"_test = [] { expect(false); };
  };
};

int main() {}
