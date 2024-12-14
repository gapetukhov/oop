#include <gtest/gtest.h>
#include "max_multiple.h"

TEST(MaxMultipleTest, 2_7) {
    EXPECT_EQ(maxMultiple(2, 7), 6);
}

TEST(MaxMultipleTest, 10_50) {
    EXPECT_EQ(maxMultiple(10, 50), 50);
}

TEST(MaxMultipleTest, Overfulfilment) {
    EXPECT_EQ(maxMultiple(5, 3), 0);
}

TEST(MaxMultipleTest, limit) {
    EXPECT_EQ(maxMultiple(1, 100), 100);  }

TEST(MaxMultipleTest, draw) {
    EXPECT_EQ(maxMultiple(1, 1), 1); 
}
  
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
