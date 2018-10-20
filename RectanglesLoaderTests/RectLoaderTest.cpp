//
// Created by Joao Henriques David Dos Reis on 14/10/2018.
//


#include "gtest/gtest.h"
#include "Rect.h"
#include "RectanglesList.h"
#include "RectLoader.h"


class RectLoaderTest : public ::testing::Test {
public:
    RectLoaderTest(){}

    void SetUp( ) {
        // code here will execute just before the test ensues
    }

    void TearDown( ) {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~RectLoaderTest( )  {
        // cleanup any pending stuff, but no exceptions allowed
    }
    const std::string _test1file = "../../Files/RectangleTest1.txt";
    const std::string _test2file = "../../Files/RectangleTest2.txt";
    const std::string _test3file = "../../Files/RectangleTest3.txt";
};


TEST_F(RectLoaderTest, rectLoader) {
   //set
   RectLoader rl(_test1file);

   //assert
   ASSERT_EQ(_test1file, rl.get_file_path());
}

TEST_F(RectLoaderTest, file_exists) {
    //set
    RectLoader rl(_test1file);

    //assert
    ASSERT_TRUE(rl.is_valid_file());
}

TEST_F(RectLoaderTest, file_does_not_exist) {
    //set
    RectLoader rl("fail_test.txt");

    //assert
    ASSERT_FALSE(rl.is_valid_file());
}

TEST_F(RectLoaderTest, read_file) {
    //prepare
    RectLoader rl(_test1file);

    //set
    auto result = rl.load();

    //assert
    ASSERT_EQ(result.size(), 6);
}

TEST_F(RectLoaderTest, read_file_have_negatives) {
    //prepare
    RectLoader rl(_test2file);

    //set
    auto result = rl.load();

    //assert
    ASSERT_EQ(result.size(), 4);
}

TEST_F(RectLoaderTest, read_file_consecutive_values) {
    //prepare
    RectLoader rl(_test3file);

    //set
    auto result = rl.load();

    //assert
    ASSERT_EQ(result.size(), 6);
}

TEST_F(RectLoaderTest, get_random_of_size_8) {
    auto v = RectLoader::load_rand(8);
    EXPECT_EQ(v.size(), 8);

    EXPECT_LE(biggest_width(v), 100);
    EXPECT_LE(biggest_height(v), 100);
}