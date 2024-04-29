#include <cycles/cycles.hpp>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

using Period    = cycles::Time<double>;
using Frequency = cycles::Frequency<double>;

TEST(FREQUENCY, CONSTRUCTOR_ZERO) {
    ASSERT_THROW(Frequency(0.0), cycles::exception::frequency);
}

TEST(FREQUENCY, PERIOD_ZERO) {
    ASSERT_THROW(Frequency(Period(0.0)), cycles::exception::period);
}

TEST(FREQUENCY, IDENTITY) {
    using namespace cycles::frequency::literals;
    EXPECT_EQ(Frequency(Period(1.0)), 1.0_hz);
}

TEST(FREQUENCY, COMPARISON) {
    using namespace cycles::frequency::literals;

    EXPECT_EQ(1.0_hz, 1.0_hz);
    EXPECT_NE(1.0_hz, 2.0_hz);
    EXPECT_NE(2.0_hz, 1.0_hz);

    EXPECT_GE(1.0_hz, 1.0_hz);
    EXPECT_GE(2.0_hz, 1.0_hz);
    EXPECT_GT(2.0_hz, 1.0_hz);

    EXPECT_LE(1.0_hz, 1.0_hz);
    EXPECT_LE(1.0_hz, 2.0_hz);
    EXPECT_LT(1.0_hz, 2.0_hz);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
