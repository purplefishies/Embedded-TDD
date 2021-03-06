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

TEST_F(SetupTest, AllOn)
{
    LedDriver_TurnAllOn();
    EXPECT_EQ( 0xffff, virtualLeds);
}

TEST_F(SetupTest, TurnOffAnyLed)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(8);
    EXPECT_EQ(0xff7f, virtualLeds);
}

TEST_F(SetupTest, LedMemoryIsNotReadable)
{
    virtualLeds = 0xffff;
    LedDriver_TurnOn(8);
    EXPECT_EQ(0x80, virtualLeds);
}

TEST_F(SetupTest, UpperAndLowerBounds)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    EXPECT_EQ(0x8001, virtualLeds);
}

TEST_F(SetupTest, OutOfBoundsChangesNothing2)
{
    LedDriver_TurnOn(-1);
    EXPECT_EQ(0, virtualLeds);
    LedDriver_TurnOn(0);
    EXPECT_EQ(0, virtualLeds);
    LedDriver_TurnOn(17);
    EXPECT_EQ(0, virtualLeds);
    LedDriver_TurnOn(33);
    EXPECT_EQ(0, virtualLeds);
    LedDriver_TurnOn(3141);
    EXPECT_EQ(0, virtualLeds);
}

TEST_F(SetupTest, OutOfBoundsTurnOffDoesNoHarm)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);
    EXPECT_EQ(0xffff, virtualLeds);
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
