#include <gtest/gtest.h>
#include "format.h" 

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST_F(TestFoo, Test1){
    auto text= format("{1}+{1} = {0}", 2, "one");
    ASSERT_EQ(text, "one+one = 2");
}

TEST_F(TestFoo, Test2){
    auto text = format("{0}*{1} = {0}", 0, "one");
    ASSERT_EQ(text, "0*one = 0");
}

TEST_F(TestFoo, Test3){
    auto text = format("{0}", 100500);
    ASSERT_EQ(text, "100500");
}

TEST_F(TestFoo, Test4){
    auto text = format("technosphere");
    ASSERT_EQ(text, "technosphere");
}

TEST_F(TestFoo, Test5){
    auto text = format("И {1} меня, и {1} меня В звенящую снежную даль {0} {3} коня, эх, {2} {3} коня Декабрь, {4}февраль{5}", "Три","уносят", "3", "белых", "январь и ", "!");
    ASSERT_EQ(text, "И уносят меня, и уносят меня В звенящую снежную даль Три белых коня, эх, 3 белых коня Декабрь, январь и февраль!");
}

TEST_F(TestFoo, Test8){
    try{
        auto text = format("{0} + {1} = {2}", 10, 5, 15, 16);
    } catch(FormatError& error){
        std::string a = error.what();
        ASSERT_EQ(a, "invalid format");
    }
}

TEST_F(TestFoo, Test10){
    try{
        auto text = format("0 + 1 = 2{");
    } catch (FormatError& error){
        std::string a = error.what();
        ASSERT_EQ(a, "invalid format");
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
