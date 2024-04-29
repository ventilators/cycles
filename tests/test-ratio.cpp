#include <cycles/cycles.hpp>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

TEST(RATIO, PERIOD) {
    cycles::Period<double> period(2.0);
    {
        cycles::Ratio<double> ratio(1.0, 1.0);
        EXPECT_EQ(ratio.inspiration(period), period * 0.5);
        EXPECT_EQ( ratio.expiration(period), period * 0.5);
    }
    {
        cycles::Ratio<double> ratio(1.0, 3.0);
        EXPECT_EQ(ratio.inspiration(period), period * 0.25);
        EXPECT_EQ( ratio.expiration(period), period * 0.75);
    }
    {
        cycles::Ratio<double> ratio(3.0, 1.0);
        EXPECT_EQ(ratio.inspiration(period), period * 0.75);
        EXPECT_EQ( ratio.expiration(period), period * 0.25);
    }
}

TEST(RATIO, FREQUENCY) {
    cycles::Frequency<double> frequency(0.5);
    cycles::Period<double> period   = static_cast<cycles::Period<double>>(frequency);
    {
        cycles::Ratio<double> ratio(1.0, 1.0);
        EXPECT_EQ(ratio.inspiration(frequency), period * 0.5);
        EXPECT_EQ( ratio.expiration(frequency), period * 0.5);
    }
    {
        cycles::Ratio<double> ratio(1.0, 3.0);
        EXPECT_EQ(ratio.inspiration(period), period * 0.25);
        EXPECT_EQ( ratio.expiration(period), period * 0.75);
    }
    {
        cycles::Ratio<double> ratio(3.0, 1.0);
        EXPECT_EQ(ratio.inspiration(period), period * 0.75);
        EXPECT_EQ( ratio.expiration(period), period * 0.25);
    }
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
