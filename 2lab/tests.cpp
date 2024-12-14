#include <gtest/gtest.h>
#include "BitString.h"

// Тесты для логических операций

TEST(BitStringTest, LogicalAnd_3Bits) {
    BitString bs1 = {1, 0, 1};
    BitString bs2 = {1, 1, 0};
    EXPECT_EQ((bs1 & bs2), BitString({1, 0, 0}));
}

TEST(BitStringTest, LogicalOr_3Bits) {
    BitString bs1 = {1, 0, 1};
    BitString bs2 = {1, 1, 0};
    EXPECT_EQ((bs1 | bs2), BitString({1, 1, 1}));
}

TEST(BitStringTest, LogicalXor_3Bits) {
    BitString bs1 = {1, 0, 1};
    BitString bs2 = {1, 1, 0};
    EXPECT_EQ((bs1 ^ bs2), BitString({0, 1, 1}));
}

// Тесты для сравнения

TEST(BitStringTest, Equality_3Bits) {
    BitString bs1 = {1, 0, 1};
    BitString bs2 = {1, 0, 1};
    EXPECT_EQ(bs1, bs2);
}

TEST(BitStringTest, Equality_3Bits_False) {
    BitString bs1 = {1, 0, 1};
    BitString bs2 = {0, 1, 0};
    EXPECT_NE(bs1, bs2);
}

TEST(BitStringTest, LessThan_3Bits) {
    BitString bs1 = {1, 0, 1};
    BitString bs2 = {1, 1, 0};
    EXPECT_LT(bs1, bs2);
}

TEST(BitStringTest, GreaterThan_3Bits) {
    BitString bs1 = {1, 1, 0};
    BitString bs2 = {1, 0, 1};
    EXPECT_GT(bs1, bs2);
}

// Тесты для присваивания

TEST(BitStringTest, Assignment_3Bits) {
    BitString bs1 = {1, 0, 1};
    BitString bs2 = {0, 1, 0};
    bs1 = bs2;
    EXPECT_EQ(bs1, bs2);
}

TEST(BitStringTest, MoveAssignment_3Bits) {
    BitString bs1 = {1, 0, 1};
    BitString bs2 = {0, 1, 0};
    bs1 = std::move(bs2);
    EXPECT_EQ(bs1, BitString({0, 1, 0}));
    EXPECT_EQ(bs2.size(), 0);
}

// Тесты для изменения размера

TEST(BitStringTest, Resize_3Bits_To_5Bits) {
    BitString bs1 = {1, 0, 1};
    bs1.resize(5, 0);
    EXPECT_EQ(bs1, BitString({1, 0, 1, 0, 0}));
}

TEST(BitStringTest, Resize_3Bits_To_2Bits) {
    BitString bs1 = {1, 0, 1};
    bs1.resize(2, 0);
    EXPECT_EQ(bs1, BitString({1, 0}));
}

// Тесты для работы с разными размерами

TEST(BitStringTest, LogicalAnd_2Bits) {
    BitString bs1 = {1, 0};
    BitString bs2 = {0, 1};
    EXPECT_EQ((bs1 & bs2), BitString({0, 0}));
}

TEST(BitStringTest, LogicalOr_2Bits) {
    BitString bs1 = {1, 0};
    BitString bs2 = {0, 1};
    EXPECT_EQ((bs1 | bs2), BitString({1, 1}));
}

TEST(BitStringTest, LogicalXor_2Bits) {
    BitString bs1 = {1, 0};
    BitString bs2 = {0, 1};
    EXPECT_EQ((bs1 ^ bs2), BitString({1, 1}));
}

TEST(BitStringTest, Resize_2Bits_To_4Bits) {
    BitString bs1 = {1, 0};
    bs1.resize(4, 1);
    EXPECT_EQ(bs1, BitString({1, 0, 1, 1}));
}

TEST(BitStringTest, LogicalAnd_4Bits) {
    BitString bs1 = {1, 0, 1, 0};
    BitString bs2 = {0, 1, 0, 1};
    EXPECT_EQ((bs1 & bs2), BitString({0, 0, 0, 0}));
}

TEST(BitStringTest, LogicalOr_4Bits) {
    BitString bs1 = {1, 0, 1, 0};
    BitString bs2 = {0, 1, 0, 1};
    EXPECT_EQ((bs1 | bs2), BitString({1, 1, 1, 1}));
}

TEST(BitStringTest, LogicalXor_4Bits) {
    BitString bs1 = {1, 0, 1, 0};
    BitString bs2 = {0, 1, 0, 1};
    EXPECT_EQ((bs1 ^ bs2), BitString({1, 1, 1, 1}));
}

TEST(BitStringTest, Resize_4Bits_To_8Bits) {
    BitString bs1 = {1, 0, 1, 0};
    bs1.resize(8, 1);
    EXPECT_EQ(bs1, BitString({1, 0, 1, 0, 1, 1, 1, 1}));
}

TEST(BitStringTest, LogicalAnd_8Bits) {
    BitString bs1 = {1, 0, 1, 0, 1, 0, 1, 0};
    BitString bs2 = {0, 1, 0, 1, 0, 1, 0, 1};
    EXPECT_EQ((bs1 & bs2), BitString({0, 0, 0, 0, 0, 0, 0, 0}));
}

TEST(BitStringTest, LogicalOr_8Bits) {
    BitString bs1 = {1, 0, 1, 0, 1, 0, 1, 0};
    BitString bs2 = {0, 1, 0, 1, 0, 1, 0, 1};
    EXPECT_EQ((bs1 | bs2), BitString({1, 1, 1, 1, 1, 1, 1, 1}));
}

TEST(BitStringTest, LogicalXor_8Bits) {
    BitString bs1 = {1, 0, 1, 0, 1, 0, 1, 0};
    BitString bs2 = {0, 1, 0, 1, 0, 1, 0, 1};
    EXPECT_EQ((bs1 ^ bs2), BitString({1, 1, 1, 1, 1, 1, 1, 1}));
}

TEST(BitStringTest, Resize_8Bits_To_16Bits) {
    BitString bs1 = {1, 0, 1, 0, 1, 0, 1, 0};
    bs1.resize(16, 1);
    EXPECT_EQ(bs1, BitString({1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1}));
}

TEST(BitStringTest, LogicalAnd_16Bits) {
    BitString bs1 = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    BitString bs2 = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    EXPECT_EQ((bs1 & bs2), BitString({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
}

TEST(BitStringTest, LogicalOr_16Bits) {
    BitString bs1 = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    BitString bs2 = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    EXPECT_EQ((bs1 | bs2), BitString({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
}

TEST(BitStringTest, LogicalXor_16Bits) {
    BitString bs1 = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    BitString bs2 = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    EXPECT_EQ((bs1 ^ bs2), BitString({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
