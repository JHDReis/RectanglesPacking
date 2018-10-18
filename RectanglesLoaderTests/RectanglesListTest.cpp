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

TEST_F(RectanglesListTest, calculate_max_width) {
    int maxwidth = sum_width(_rectangle1);
    EXPECT_EQ(maxwidth, 9);
}


TEST_F(RectanglesListTest, calculate_max_height) {
    int maxHeight = sum_height(_rectangle1);
    EXPECT_EQ(maxHeight, 3);
}

TEST_F(RectanglesListTest, calculate_max_right) {
    int maxRight = max_right(_rectangle1);
    EXPECT_EQ(maxRight, 4);
}

TEST_F(RectanglesListTest, calculate_max_right2) {
    _rectangle1.push_back( Rect(2,1,5,0));
    int maxRight = max_right(_rectangle1);
    EXPECT_EQ(maxRight, 7);
}


TEST_F(RectanglesListTest, calculate_max_bottom) {
    int maxBottom = max_bottom(_rectangle1);
    EXPECT_EQ(maxBottom, 1);
}

TEST_F(RectanglesListTest, calculate_max_bottom2) {
    _rectangle1.push_back( Rect(2,1,0,5));
    int maxBottom = max_bottom(_rectangle1);
    EXPECT_EQ(maxBottom, 6);
}


TEST_F(RectanglesListTest, calculate_area_is_4) {
    int a = area(_rectangle1);
    EXPECT_EQ(a, 4);
}

TEST_F(RectanglesListTest, calculate_max_bottom_is_24) {
    _rectangle1.push_back( Rect(2,1,0,5));
    int a = area(_rectangle1);
    EXPECT_EQ(a, 24);
}

TEST_F(RectanglesListTest, sorting_area_dec) {
    sort_area_dec(_rectangle1);
    EXPECT_EQ(_rectangle1[0].area(), 4);
    EXPECT_EQ(_rectangle1[1].area(), 3);
    EXPECT_EQ(_rectangle1[2].area(), 2);
}

TEST_F(RectanglesListTest, get_smallest_area){
    std::vector<Rect> rectangle;           //   _  _ _
    rectangle.emplace_back(Rect(2,1,1,0)); //  |_||_|_| 3x3
    rectangle.emplace_back(Rect(1,3,0,0)); //  |_||_|_|
    rectangle.emplace_back(Rect(2,1,1,1)); //  |_|

    int side = square_side(rectangle);
    ASSERT_EQ(side*side, 9);
}

