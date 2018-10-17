//
// Created by Joao Henriques David Dos Reis on 13/10/2018.
//
#include "gtest/gtest.h"
#include "Rect.h"


class RectClassTesting : public ::testing::Test {
protected:
    RectClassTesting() {
        Rect d(2,4);
        _rect = d;
    }

    void SetUp( ) {
        // code here will execute just before the test ensues
    }

    void TearDown( ) {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~RectClassTesting( )  {
        // cleanup any pending stuff, but no exceptions allowed
    }

    Rect _rect;
};


TEST_F(RectClassTesting, default_constructor_values) {
    Rect r;
    ASSERT_EQ(r.height(), 0);
    ASSERT_EQ(r.width(), 0);
    ASSERT_EQ(r.x(), 0);
    ASSERT_EQ(r.y(), 0);
}


TEST_F(RectClassTesting, height_is_2) {
    Rect r(0,2);
    ASSERT_EQ(r.height(), 2);
}


TEST_F(RectClassTesting, width_is_4) {
    Rect r(4,0);
    ASSERT_EQ(r.width(), 4);
}


TEST_F(RectClassTesting, change_dimensions) {
    _rect.set_dimension(10, 5);
    ASSERT_EQ(_rect.width(), 10);
    ASSERT_EQ(_rect.height(), 5);
}


TEST_F(RectClassTesting, set_x_0_y_0) {
    _rect.set_position(0, 0);
    ASSERT_EQ(_rect.x(), 0);
    ASSERT_EQ(_rect.x(), 0);
}


TEST_F(RectClassTesting, reset_rectangle) {
    _rect.reset(2,1,1,1);
    ASSERT_EQ(_rect.width(), 2);
    ASSERT_EQ(_rect.height(), 1);
    ASSERT_EQ(_rect.x(), 1);
    ASSERT_EQ(_rect.x(), 1);
}


TEST_F(RectClassTesting, rectangle_is_not_overlapped_test1) {
    //prepare
    Rect a(2,1);
    Rect b(2,1);

    //set same axis x
    a.set_position(0, 0);
    b.set_position(2, 0);
    //assert
    ASSERT_FALSE(a.overlaps(b));
}


TEST_F(RectClassTesting, rectangle_is_not_overlapped_test2) {
    //prepare
    Rect a(2,1);
    Rect b(2,1);

    //set same axis y
    a.set_position(0, 0);
    b.set_position(0, 1);
    //assert
    ASSERT_FALSE(a.overlaps(b));
}


TEST_F(RectClassTesting, rectangle_is_overlaps_same_position) {
    //prepare
    Rect a(2,1);
    Rect b(2,1);

    //set same position
    a.set_position(0, 0);
    b.set_position(0, 0);
    //assert
    ASSERT_TRUE(a.overlaps(b));
}


TEST_F(RectClassTesting, rectangle_is_overlaps_in_the_x) {
    //prepare
    Rect a(2,1);
    Rect b(2,1);

    //set same position
    a.set_position(0, 0);
    b.set_position(1, 0);
    //assert
    ASSERT_TRUE(a.overlaps(b));
}


TEST_F(RectClassTesting, rectangle_is_overlaps_in_the_y) {
    //prepare
    Rect a(1,2);
    Rect b(1,2);

    //set same position
    a.set_position(0, 0);
    b.set_position(0, 1);
    //assert
    ASSERT_TRUE(a.overlaps(b));
}


TEST_F(RectClassTesting, rectangle_is_contained_same) {
    //prepare
    Rect a(1,2);
    Rect b(1,2);

    //set same position
    a.set_position(0, 0);
    b.set_position(0, 0);
    //assert
    ASSERT_TRUE(a.is_contained(b));
}


TEST_F(RectClassTesting, rectangle_a_is_contained_in_b) {
    //prepare
    Rect a(2,1);
    Rect b(5,3);

    //set same position
    a.set_position(1, 1);
    b.set_position(0, 0);
    //assert
    ASSERT_TRUE(a.is_contained(b));
}


TEST_F(RectClassTesting, rectangle_b_is_not_contained_in_a) {
    //prepare
    Rect a(2,1);
    Rect b(5,3);

    //set same position
    a.set_position(1, 1);
    b.set_position(0, 0);
    //assert
    ASSERT_FALSE(b.is_contained(a));
}







