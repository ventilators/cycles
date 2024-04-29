#include <cycles/cycles.hpp>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

using Cycle         = cycles::Cycle<float>;
using Expiration    = cycles::Expiration<float>;
using Inspiration   = cycles::Inspiration<float>;
using Time          = cycles::Time<float>;

namespace inspiratory {
    using Pause = cycles::inspiratory::Pause<float>;
} // namespace inspiratory
namespace expiratory {
    using Pause = cycles::expiratory::Pause<float>;
} // namespace expiratory

TEST(MARKS, SANS_PAUSE) {
    Inspiration inspiration(1.0f);
    Expiration  expiration(1.0f);
    Cycle c(inspiration, expiration);

    std::size_t count = 100;
    Time step(1.0f / static_cast<float>(count));

    for (std::size_t i = 0; i <= 2 * count; i++) {
        std::optional<cycles::Mark> mark = c(step);
        if (i == count) {
            EXPECT_TRUE(mark);
            EXPECT_EQ(cycles::Mark::START_OF_EXPIRATION, *mark);
        } else if (i == 2 * count) {
            EXPECT_TRUE(mark);
            EXPECT_EQ(cycles::Mark::START_OF_INSPIRATION, *mark);
        } else {
            EXPECT_FALSE(mark);
        }
    }
}

TEST(MARKS, INSPIRATORY_PAUSE) {
    Inspiration inspiration(1.0f);
    Expiration  expiration(1.0f);

    inspiratory::Pause p(1.0f);
    Cycle c(inspiration, p, expiration, {});

    std::size_t count = 100;
    Time step(1.0f / static_cast<float>(count));

    for (std::size_t i = 0; i <= 3 * count; i++) {
        std::optional<cycles::Mark> mark = c(step);
        if (i == 2 * count) {
            EXPECT_TRUE(mark);
            EXPECT_EQ(cycles::Mark::START_OF_EXPIRATION, *mark);
        } else if (i == 3 * count) {
            EXPECT_TRUE(mark);
            EXPECT_EQ(cycles::Mark::START_OF_INSPIRATION, *mark);
        } else {
            EXPECT_FALSE(mark);
        }
    }
}

TEST(MARKS, EXPIRATORY_PAUSE) {
    Inspiration inspiration(1.0f);
    Expiration  expiration(1.0f);

    expiratory::Pause p(1.0f);
    Cycle c(inspiration, {}, expiration, p);

    std::size_t count = 100;
    Time step(1.0f / static_cast<float>(count));

    for (std::size_t i = 0; i <= 3 * count; i++) {
        std::optional<cycles::Mark> mark = c(step);
        if (i == count) {
            EXPECT_TRUE(mark);
            EXPECT_EQ(cycles::Mark::START_OF_EXPIRATION, *mark);
        } else if (i == 3 * count) {
            EXPECT_TRUE(mark);
            EXPECT_EQ(cycles::Mark::START_OF_INSPIRATION, *mark);
        } else {
            EXPECT_FALSE(mark);
        }
    }
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
