#include <gtest/gtest.h>
#include <iostream>

#include "BigInt.h"



class TestFoo : public ::testing::Test
{
    protected:
        void SetUp() {}
        void TearDown() {}
};

TEST(Constructors, DefaultConstructor)
{
	BigInt number;
	EXPECT_EQ(number, 0);
}

TEST(Constructors, NumberConstructor)
{
	BigInt number1(0);
	EXPECT_EQ(number1, 0);

	BigInt number2(5);
	EXPECT_EQ(number2, 5);

	BigInt number3(1234);
	EXPECT_EQ(number3, 1234);

	BigInt number4(-1099);
	EXPECT_EQ(number4, -1099);

	BigInt number5(-123456);
	EXPECT_EQ(number5, -123456);
}

TEST(Constructors, StringConstructor)
{
	BigInt number1("");
	EXPECT_EQ(number1, 0);

	BigInt number2("0");
	EXPECT_EQ(number2, 0);

	BigInt number3("+0");
	EXPECT_EQ(number3, 0);

	BigInt number4("-0");
	EXPECT_EQ(number4, 0);

	BigInt number5("12345");
	EXPECT_EQ(number5, 12345);

	BigInt number6("-12345");
	EXPECT_EQ(number6, -12345);

	BigInt number7("1234567890");
	EXPECT_EQ(number7, 1234567890);

	BigInt number8("-1234567890");
	EXPECT_EQ(number8, -1234567890);
}

TEST(CopySemantic, CopyConstructor)
{
	BigInt number1("-0");
	BigInt number2(number1);
	EXPECT_EQ(number1, 0);
	EXPECT_EQ(number2, 0);

	BigInt number3("-1234567890");
	BigInt number4(number3);
	EXPECT_EQ(number3, -1234567890);
	EXPECT_EQ(number4, -1234567890);
}

TEST(CopySemantic, AssignmentOperator)
{
	BigInt number1("-0");
	BigInt number2;
	number2 = number1;
	EXPECT_EQ(number1, 0);
	EXPECT_EQ(number2, 0);

	BigInt number3("-1234567890");
	BigInt number4;
	number4 = number3;
	EXPECT_EQ(number3, -1234567890);
	EXPECT_EQ(number4, -1234567890);
}

TEST(MoveSemantic, MoveConstructor)
{
	BigInt number1("-0");
	BigInt number2(std::move(number1));
	EXPECT_EQ(number1, 0);
	EXPECT_EQ(number2, 0);

	BigInt number3("-1234567890");
	BigInt number4(std::move(number3));
	EXPECT_EQ(number3, 0);
	EXPECT_EQ(number4, -1234567890);
}

TEST(MoveSemantic, AssignmentOperator)
{
	BigInt number1("-0");
	BigInt number2;
	number2 = std::move(number1);
	EXPECT_EQ(number1, 0);
	EXPECT_EQ(number2, 0);

	BigInt number3("-1234567890");
	BigInt number4;
	number4 = std::move(number3);
	EXPECT_EQ(number3, 0);
	EXPECT_EQ(number4, -1234567890);
}

TEST(FreeOperators, OutputOperator)
{
	std::stringstream stream;
	int32_t integer;

	BigInt number1("");
	stream << number1;
	stream >> integer;
	stream.clear();
	EXPECT_EQ(number1, integer);

	BigInt number2("0");
	stream << number2;
	stream >> integer;
	stream.clear();
	EXPECT_EQ(number2, integer);

	BigInt number3("+0");
	stream << number3;
	stream >> integer;
	stream.clear();
	EXPECT_EQ(number3, integer);

	BigInt number4("-0");
	stream << number4;
	stream >> integer;
	stream.clear();
	EXPECT_EQ(number4, integer);

	BigInt number5("12345");
	stream << number5;
	stream >> integer;
	stream.clear();
	EXPECT_EQ(number5, integer);

	BigInt number6("-12345");
	stream << number6;
	stream >> integer;
	stream.clear();
	EXPECT_EQ(number6, integer);

	BigInt number7("1234567890");
	stream << number7;
	stream >> integer;
	stream.clear();
	EXPECT_EQ(number7, integer);

	BigInt number8("-1234567890");
	stream << number8;
	stream >> integer;
	stream.clear();
	EXPECT_EQ(number8, integer);
}

TEST(MethodOperators, OperatorUnaryMinus)
{
	BigInt number1;
	EXPECT_EQ(-number1, 0);

	number1 = -1;
	EXPECT_EQ(-number1, +1);

	number1 = +1;
	EXPECT_EQ(-number1, -1);

	number1 = 100;
	EXPECT_EQ(-number1, -100);

	number1 = -13;
	EXPECT_EQ(-number1, +13);

	number1 = BigInt("1000000000000000000000");
	EXPECT_EQ(-number1, BigInt("-1000000000000000000000"));

	number1 = BigInt("-123456789123456789");
	EXPECT_EQ(-number1, BigInt("+123456789123456789"));
}

TEST(MethodOperators, OperatorBinaryPlus)
{
	BigInt number1, number2;
	EXPECT_EQ(number1 + number2, 0);

	number1 = -1, number2 = +1;
	EXPECT_EQ(number1 + number2, 0);

	number1 = 100, number2 = 13;
	EXPECT_EQ(number1 + number2, 113);

	number1 = -100, number2 = 13;
	EXPECT_EQ(number1 + number2, -87);

	number1 = 100, number2 = -13;
	EXPECT_EQ(number1 + number2, +87);

	number1 = 9999, number2 = 1;
	EXPECT_EQ(number1 + number2, 10000);

	number1 = 9999, number2 = 111;
	EXPECT_EQ(number1 + number2, 10110);

	number1 = BigInt("999999999999999999999"), number2 = BigInt("1");
	EXPECT_EQ(number1 + number2, BigInt("1000000000000000000000"));

	number1 = BigInt("123456789123456789"), number2 = BigInt("98765432198765432100000");
	EXPECT_EQ(number1 + number2, BigInt("98765555655554555556789"));
}

TEST(MethodOperators, OperatorBinaryMinus)
{
	BigInt number1, number2;
	EXPECT_EQ(number1 - number2, 0);

	number1 = -1, number2 = -1;
	EXPECT_EQ(number1 - number2, 0);

	number1 = +1, number2 = +1;
	EXPECT_EQ(number1 - number2, 0);

	number1 = -1, number2 = +1;
	EXPECT_EQ(number1 - number2, -2);

	number1 = 100, number2 = 13;
	EXPECT_EQ(number1 - number2, 87);

	number1 = -100, number2 = 13;
	EXPECT_EQ(number1 - number2, -113);

	number1 = 100, number2 = -13;
	EXPECT_EQ(number1 - number2, +113);

	number1 = 1000, number2 = 1;
	EXPECT_EQ(number1 - number2, 999);

	number1 = 1000, number2 = 15;
	EXPECT_EQ(number1 - number2, 985);

	number1 = BigInt("1000000000000000000000"), number2 = BigInt("1");
	EXPECT_EQ(number1 - number2, BigInt("999999999999999999999"));

	number1 = BigInt("98765555655554555556789"), number2 = BigInt("98765432198765432100000");
	EXPECT_EQ(number1 - number2, BigInt("123456789123456789"));
}

TEST(MethodOperators, OperatorMultiply)
{
	BigInt number1, number2;
	EXPECT_EQ(number1 * number2, 0);

	number1 = -1, number2 = -1;
	EXPECT_EQ(number1 * number2, 1);

	number1 = +1, number2 = +1;
	EXPECT_EQ(number1 * number2, 1);

	number1 = -1, number2 = +1;
	EXPECT_EQ(number1 * number2, -1);

	number1 = 100, number2 = 13;
	EXPECT_EQ(number1 * number2, 1300);

	number1 = -100, number2 = 13;
	EXPECT_EQ(number1 * number2, -1300);

	number1 = 100, number2 = -5;
	EXPECT_EQ(number1 * number2, -500);

	number1 = 1000, number2 = 0;
	EXPECT_EQ(number1 * number2, 0);

	number1 = 1000, number2 = 1;
	EXPECT_EQ(number1 * number2, 1000);

	number1 = BigInt("1000000000000000000000"), number2 = BigInt("1");
	EXPECT_EQ(number1 * number2, BigInt("1000000000000000000000"));

	number1 = BigInt("123456789"), number2 = BigInt("1000000");
	EXPECT_EQ(number1 * number2, BigInt("123456789000000"));

	number1 = BigInt("123456789"), number2 = BigInt("123456789");
	EXPECT_EQ(number1 * number2, BigInt("15241578750190521"));
}

TEST(MethodOperators, OperatorBinaryPlusWithInt32_t)
{
	BigInt number1;
	EXPECT_EQ(number1 + 0, 0);

	number1 = -1;
	EXPECT_EQ(number1 + 1, 0);

	number1 = 100;
	EXPECT_EQ(number1 + 13, 113);

	number1 = -100;
	EXPECT_EQ(number1 + 13, -87);

	number1 = 100;
	EXPECT_EQ(number1 + (-13), +87);

	number1 = 9999;
	EXPECT_EQ(number1 + 1, 10000);

	number1 = 9999;
	EXPECT_EQ(number1 + 111, 10110);

	number1 = BigInt("999999999999999999999");
	EXPECT_EQ(number1 + 1, BigInt("1000000000000000000000"));

	number1 = BigInt("123456789123456789");
	EXPECT_EQ(number1 + 123, BigInt("123456789123456912"));
}

TEST(MethodOperators, OperatorBinaryMinusWithInt32_t)
{
	BigInt number1;
	EXPECT_EQ(number1 - 0, 0);

	number1 = -1;
	EXPECT_EQ(number1 - (-1), 0);

	number1 = +1;
	EXPECT_EQ(number1 - (+1), 0);

	number1 = -1;
	EXPECT_EQ(number1 - (+1), -2);

	number1 = 100;
	EXPECT_EQ(number1 - 13, 87);

	number1 = -100;
	EXPECT_EQ(number1 - 13, -113);

	number1 = 100;
	EXPECT_EQ(number1 - (-13), +113);

	number1 = 1000;
	EXPECT_EQ(number1 - 1, 999);

	number1 = 1000;
	EXPECT_EQ(number1 - 15, 985);

	number1 = BigInt("1000000000000000000000");
	EXPECT_EQ(number1 - 1, BigInt("999999999999999999999"));

	number1 = BigInt("123456789123456789");
	EXPECT_EQ(number1 - 123, BigInt("123456789123456666"));
}

TEST(MethodOperators, OperatorMultiplyWithInt32_t)
{
	BigInt number1;
	EXPECT_EQ(number1 * 0, 0);

	number1 = -1;
	EXPECT_EQ(number1 * (-1), 1);

	number1 = +1;
	EXPECT_EQ(number1 * 1, 1);

	number1 = -1;
	EXPECT_EQ(number1 * 1, -1);

	number1 = 100;
	EXPECT_EQ(number1 * 13, 1300);

	number1 = -100;
	EXPECT_EQ(number1 * 13, -1300);

	number1 = 100;
	EXPECT_EQ(number1 * (-5), -500);

	number1 = 1000;
	EXPECT_EQ(number1 * 0, 0);

	number1 = 1000;
	EXPECT_EQ(number1 * 1, 1000);

	number1 = BigInt("1000000000000000000000");
	EXPECT_EQ(number1 * 1, BigInt("1000000000000000000000"));

	number1 = BigInt("123456789");
	EXPECT_EQ(number1 * 1000000, BigInt("123456789000000"));

	number1 = BigInt("123456789");
	EXPECT_EQ(number1 * 123456789, BigInt("15241578750190521"));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
