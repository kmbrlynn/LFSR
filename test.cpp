#include "LFSR.hpp"
#include <iostream>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// ================================================ very short string
// edge case: tap at the rightmost bit
BOOST_AUTO_TEST_CASE(threeBitsTapAtZero)
{
	LFSR lfsr0("101", 0);
	// test step function
	// ...

	LFSR lfsr1("011", 0);
	// test genrate functoin
	// ...
}

// edge case: tap at the leftmost bit
BOOST_AUTO_TEST_CASE(threeBitsTapAtTwo)
{
	LFSR lfsr2("000", 2);
	// test step function
	// ...

	LFSR lfsr3("111", 2);
	// test generat function
	// ... 
}

// ============================================= medium length string
// tap bit somewhere in the middle
// (this test provided in starter file for test.cpp)
BOOST_AUTO_TEST_CASE(fiveBitsTapAtTwo) 
{
	LFSR lfsr4("00111", 2);
	BOOST_REQUIRE(lfsr4.step() == 1);
	BOOST_REQUIRE(lfsr4.step() == 1);
	BOOST_REQUIRE(lfsr4.step() == 0);
	BOOST_REQUIRE(lfsr4.step() == 0);
	BOOST_REQUIRE(lfsr4.step() == 0);
	BOOST_REQUIRE(lfsr4.step() == 1);
	BOOST_REQUIRE(lfsr4.step() == 1);
	BOOST_REQUIRE(lfsr4.step() == 0);

//  LFSR lfsr5("00111", 2);
//  BOOST_REQUIRE(lfsr5.generate(8) == 198);
}

// ================================================= very long string
// edge case: tap at the rightmost bit
BOOST_AUTO_TEST_CASE(thirtyTwoBitsTapAtZero)
{
	LFSR lfsr6("10101010101010101010101010101010", 0);
	// test step function
	// ...

	LFSR lfsr7("0001111000011110000111100001111", 0);
	// test genrate functoin
	// ...
}

// edge case: tap at the leftmost bit
BOOST_AUTO_TEST_CASE(thirtyTwoBitsTapAtThirtyOne)
{
	LFSR lfsr8("11001100110011001100110011001100", 31);
	// test step function
	// ...

	LFSR lfsr9("11010010110100101101000011110101", 31);
	// test genrate functoin
	// ...

}















