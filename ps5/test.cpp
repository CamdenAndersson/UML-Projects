// Copyright Camden Andersson 2024

#include <sstream>
#include "EDistance.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string.hpp>

// example10 and check output
BOOST_AUTO_TEST_CASE(testOutput) {
    std::string x, y;
    // example10
    x = "AACAGTTACC";
    y = "TAAGGTCA";
    EDistance ed(x, y);
    ed.optDistance();
    std::string alignment = ed.alignment();
    std::stringstream ss;
    std::stringstream s;
    boost::erase_all(alignment, "\n");
    ss << alignment;
    s << "A T 1";
    s << "A A 0";
    s << "C - 2";
    s << "A A 0";
    s << "G G 0";
    s << "T G 1";
    s << "T T 0";
    s << "A - 2";
    s << "C C 0";
    s << "C A 1";
    BOOST_REQUIRE_EQUAL(ss.str(), s.str());
}
// check if the cost = 7
BOOST_AUTO_TEST_CASE(testDistance) {
    std::string x, y;
    // example10
    x = "AACAGTTACC";
    y = "TAAGGTCA";
    EDistance ed(x, y);
    int distance = ed.optDistance();
    BOOST_REQUIRE_EQUAL(7, distance);
}
