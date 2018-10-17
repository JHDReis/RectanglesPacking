//
// Created by Joao Henriques David Dos Reis on 15/10/2018.
//

#include "gtest/gtest.h"
#include "RectanglesList.h"
#include "Rect.h"


class RectanglesListTest : public ::testing::Test {
public:
    RectanglesListTest(){}

    void SetUp( ) {
        _rectangle1.emplace_back(Rect(2,1)); //moves
        _rectangle1.emplace_back(Rect(3,1));
        _rectangle1.emplace_back(Rect(4,1));
    }

    void TearDown( ) {
        _rectangle1.clear();
    }

    ~RectanglesListTest( )  {
        // cleanup any pending stuff, but no exceptions allowed
    }

    std::vector<Rect> _rectangle1;
};


TEST_F(RectanglesListTest, rectangles_is_moving) {
    //prepare
    RectanglesList rList;

    //act
    rList.load(_rectangle1);

    //assert
    EXPECT_EQ(_rectangle1.size(), 3);
}


TEST_F(RectanglesListTest, rectangles_size_is_3) {
    //prepare
    RectanglesList rList;

    //act
    rList.load(_rectangle1);
    auto result = rList.size();

    //assert
    EXPECT_EQ(result, 3);
}


TEST_F(RectanglesListTest, rectangles_max_width_is_9) {
    //prepare
    RectanglesList rList;

    //act
    rList.load(_rectangle1);
    auto result = rList.max_width();

    //assert
    EXPECT_EQ(result, 9);
}


TEST_F(RectanglesListTest, rectangles_max_width_is_3) {
    //prepare
    RectanglesList rList;

    //act
    rList.load(_rectangle1);
    auto result = rList.max_height();

    //assert
    EXPECT_EQ(result, 3);
}
