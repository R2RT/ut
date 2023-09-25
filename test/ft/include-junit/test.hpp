//
// Copyright (c) 2019-2020 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <boost/ut.hpp>

namespace test = boost::ut;

#include <iostream>

namespace ft {
template <class TPrinter = test::printer>
struct validate_reporter_junit : test::reporter_junit<TPrinter> {
  constexpr static const auto expectedJunit =
      R"(<?xml version="1.0" encoding="UTF-8"?>
<testsuites name=".*" errors="0" failures="0" tests="11" time=".*">
  <testsuite name="" tests="" disabled="" errors="" failures="" skipped="">
    <properties>
      <property name="version" value=""/>
    </properties>
    <testcase name="" assertions="" classname="" status="">
      <skipped message=""/>
      <error message="" type="">error description</error>
      <failure message="" type="">failure description</failure>
      <system-out>STDOUT text</system-out>
      <system-err>STDERR text</system-err>
    </testcase>
    <testcase name="" assertions="" classname="" status="">
      <skipped message=""/>
      <error message="" type="">error description</error>
      <failure message="" type="">failure description</failure>
      <system-out>STDOUT text</system-out>
      <system-err>STDERR text</system-err>
    </testcase>
    <system-out>STDOUT text</system-out>
    <system-err>STDERR text</system-err>
  </testsuite>
</testsuites>
)";

  auto on(test::events::summary) -> void {
    std::stringstream ss_out_{};
    auto* save = std::cout.rdbuf();
    std::cout.rdbuf(ss_out_.rdbuf());
    test::reporter_junit<TPrinter>::print_junit_summary();
    std::cout.rdbuf(save);
    auto junit = ss_out_.str();
    puts(junit.c_str());
    boost::ut::expect(boost::ut::that % junit == expectedJunit);
  }
  using test::reporter_junit<TPrinter>::on;
};
}  // namespace ft

template <class... Ts>
inline auto test::cfg<test::override, Ts...> =
    test::runner<ft::validate_reporter_junit<>>{};
