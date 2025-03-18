// Copyright Camden Andersson 2024
#include "RandWriter.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string.hpp>

BOOST_AUTO_TEST_CASE(wrongLength) {
    BOOST_REQUIRE_THROW(RandWriter r("a", 2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(generateTest) {
    RandWriter rw("abcdabcdabcd", 2);
    std::string generated = rw.generate("ab", 5);
    BOOST_REQUIRE_EQUAL(generated.size(), 5);
    BOOST_REQUIRE(generated.substr(0, 2) == "ab");
}

BOOST_AUTO_TEST_CASE(wrongDistributionTest) {
    RandWriter rw("aaaaabbbbcc", 2);
    std::map<char, int> charCount;
    for (int i = 0; i < 1000; ++i) {
        std::string generated = rw.generate("aa", 4);
        charCount[generated[2]]++;
    }
    BOOST_REQUIRE_CLOSE(static_cast<double>(charCount['a']) / 1000.0, 0.74, 10.0);
    BOOST_REQUIRE_CLOSE(static_cast<double>(charCount['b']) / 1000.0, 0.26, 10.0);
}
BOOST_AUTO_TEST_CASE(passTestAmount) {
    BOOST_REQUIRE_EQUAL(1, 1);
}
