#include "LFSR.hpp"
#include <iostream>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// ================================================ very short string
// tap at bit 0 (rightmost edge case)
// call 6 steps
// 001110 in binary = 14 in decimal

BOOST_AUTO_TEST_CASE(threeBitsTapAtZero)
{
	LFSR lfsr0("101", 0);
	BOOST_REQUIRE(lfsr0.step() == 0);
	BOOST_REQUIRE(lfsr0.step() == 0);
	BOOST_REQUIRE(lfsr0.step() == 1);
	BOOST_REQUIRE(lfsr0.step() == 1);
	BOOST_REQUIRE(lfsr0.step() == 1);
	BOOST_REQUIRE(lfsr0.step() == 0);

	LFSR lfsr1("101", 0);
	BOOST_REQUIRE(lfsr1.generate(6) == 14);
}

// ============================================= medium length string
// tap at bit 2 (somewhere in the middle)
// call 8 steps
// 11000110 in binary = 198 in decimal

BOOST_AUTO_TEST_CASE(fiveBitsTapAtTwo) 
{
	LFSR lfsr2("00111", 2);
	BOOST_REQUIRE(lfsr2.step() == 1);
	BOOST_REQUIRE(lfsr2.step() == 1);
	BOOST_REQUIRE(lfsr2.step() == 0);
	BOOST_REQUIRE(lfsr2.step() == 0);
	BOOST_REQUIRE(lfsr2.step() == 0);
	BOOST_REQUIRE(lfsr2.step() == 1);
	BOOST_REQUIRE(lfsr2.step() == 1);
	BOOST_REQUIRE(lfsr2.step() == 0);
	
	LFSR lfsr3("00111", 2);
	BOOST_REQUIRE(lfsr3.generate(8) == 198);
}

// ================================================= very long string
// tap at bit 0 (rightmost edge case)
// call 6 steps
// 100010 in binary = 34

BOOST_AUTO_TEST_CASE(thirtyTwoBitsTapAtZero)
{
	LFSR lfsr4("11001100110011001100110011001100", 0);
	BOOST_REQUIRE(lfsr4.step() == 1);
	BOOST_REQUIRE(lfsr4.step() == 0);
	BOOST_REQUIRE(lfsr4.step() == 0);
	BOOST_REQUIRE(lfsr4.step() == 0);
	BOOST_REQUIRE(lfsr4.step() == 1);
	BOOST_REQUIRE(lfsr4.step() == 0);
	
	LFSR lfsr5("11001100110011001100110011001100", 0);
	BOOST_REQUIRE(lfsr7.generate(6) == 34);
}



