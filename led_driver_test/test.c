#include <stdint.h>
#include "LedDriver.h"
#include "gtest/gtest.h"
#include <queue>

static uint16_t virtualLeds;

class SetupTest : public testing::Test  {
 protected:
    virtual void SetUp() {
        /* std::cout << "Here !" << std::endl; */
        /* q0.push(1); */
        LedDriver_Create( &virtualLeds );
    }
    /* std::queue<int16_t> q0; */
};

TEST(FirstTestGroup, LedsOffAfterCreate)
{
    uint16_t virtualLeds = 0xffff;
    LedDriver_Create( &virtualLeds );

    EXPECT_EQ( virtualLeds, 0x0 );
    LedDriver_TurnOn( 1 );
    EXPECT_EQ( virtualLeds, 0x1 );
    LedDriver_TurnOff( 1 );
    EXPECT_EQ( virtualLeds, 0x0 );

}

TEST(LedDriver, LedsOffAfterCreate)
{
    uint16_t virtualLeds = 0xffff;
    LedDriver_Create(&virtualLeds);
    EXPECT_EQ(0, virtualLeds);
}

TEST_F(SetupTest, TurnOnLedOne)
{
    LedDriver_TurnOn(1);
    EXPECT_EQ( 1, virtualLeds);
}

TEST_F(SetupTest, TurnOffLedOne)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    EXPECT_EQ(0, virtualLeds);
}

TEST_F(SetupTest, TurnOnMultipleLeds)
{
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    EXPECT_EQ(0x180, virtualLeds);
}



int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::TestEventListeners & listeners = testing::UnitTest::GetInstance()->listeners();
#ifdef GTEST_TAP_PRINT_TO_STDOUT
    delete listeners.Release(listeners.default_result_printer());
    listeners.Append( new tap::TapListener() );
#endif

#ifdef TAP
    listeners.Append( new tap::TapListener() );
#endif

    return RUN_ALL_TESTS();  

}
