#include "LFSR.hpp"
#include <iostream>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// ========================================================== very short string
// tap at bit 0 (rightmost edge case)
// test step() - call 6 steps, should produce 001110 bit sequence
// test generate() - does 001110 in binary == 14 in decimal?

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

// ======================================================= medium length string
// tap at bit 2 (somewhere in the middle)
// test step() - call 8 steps, should produce 11000110 bit sequence
// test generate() - does 11000110 in binary == 198 in decimal?

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

// =========================================================== very long string
// tap at bit 0 (rightmost edge case)
// test step() - call 6 steps, should produce a 100010 bit sequence
// test generate() - does 100010 in binary == 34 in decimal?

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
	BOOST_REQUIRE(lfsr5.generate(6) == 34);
}

// ================================ check that only ASCII 0s and 1s were passed

// runs stringToVector() - part of which is to inspect string characters
// returns 0 if all characters in the string are 0 and 1 characters
// returns 1 if it finds a rogue character

BOOST_AUTO_TEST_CASE(verifyStringParameter)
{
	LFSR lfsr5("101010010", 8);
	BOOST_REQUIRE(lfsr5.stringToVector() == 0);
}



