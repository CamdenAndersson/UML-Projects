// Copyright 2023 Camden Andersson

#include <iostream>
#include <string>
#include <sstream>
#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using PhotoMagic::FibLFSR;


BOOST_AUTO_TEST_CASE(testDifferentSeed) {
  FibLFSR l("1011010000000001");
  BOOST_REQUIRE_EQUAL(l.generate(6), 17);
}
