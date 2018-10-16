//
// Created by Joao Henriques David Dos Reis on 15/10/2018.
//

#include "gtest/gtest.h"
#include "Rect.h"
#include "TerminalPrint.h"


class TerminalPrintTest : public ::testing::Test {
public:
    void SetUp( ) {
        // code here will execute just before the test ensues
    }

    void TearDown( ) {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~TerminalPrintTest( )  {
        // cleanup any pending stuff, but no exceptions allowed
    }
};
