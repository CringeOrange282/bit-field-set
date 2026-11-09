#include "pch.h"
#include <stdexcept>
#include "Bitfield.h"

TEST(BitfieldTest, CreateEmptyOrWithSize) {
    Bitfield b1;

    Bitfield b2(40);
    for (size_t i = 0; i < 40; ++i) {
        EXPECT_FALSE(b2.get_bit(i));
    }
}

TEST(BitfieldTest, TurnBitsOnAndOff) {
    Bitfield b(50);

    b.set_bit(0);
    b.set_bit(31);
    b.set_bit(49);

    EXPECT_TRUE(b.get_bit(0));
    EXPECT_TRUE(b.get_bit(31));
    EXPECT_TRUE(b.get_bit(49));
    EXPECT_FALSE(b.get_bit(14));

    b.reset_bit(31);
    EXPECT_FALSE(b.get_bit(31));
    EXPECT_TRUE(b.get_bit(0));

    Bitfield b_mask(8);
    b_mask.set_bit(0);
    EXPECT_TRUE(b_mask.get_bit(0));
}

TEST(BitfieldTest, FailsOnWrongIndex) {
    Bitfield b(10);

    EXPECT_THROW(b.set_bit(10), std::invalid_argument);
    EXPECT_THROW(b.set_bit(11), std::invalid_argument);
}

TEST(BitfieldTest, CompareTwoBitfields) {
    Bitfield b1(32);
    Bitfield b2(32);
    Bitfield b3(40);

    EXPECT_EQ(b1, b2);
    EXPECT_NE(b1, b3);

    b1.set_bit(4);
    EXPECT_NE(b1, b2);

    b2.set_bit(4);
    EXPECT_EQ(b1, b2);
}

TEST(BitfieldTest, CopyAndAssignIndependent) {
    Bitfield b1(20);
    b1.set_bit(9);

    Bitfield b2 = b1;
    EXPECT_EQ(b2, b1);

    b2.set_bit(14);
    EXPECT_FALSE(b1.get_bit(14));

    Bitfield b3(5);
    b3 = b1;
    EXPECT_EQ(b3, b1);

    b3 = *&b3;
    EXPECT_EQ(b3, b1);
}

TEST(BitfieldTest, LogicalOrAndAndInvert) {
    Bitfield b1(15);
    Bitfield b2(15);

    b1.set_bit(2);
    b1.set_bit(6);

    b2.set_bit(6);
    b2.set_bit(11);

    Bitfield res_or = b1 | b2;
    EXPECT_TRUE(res_or.get_bit(2));
    EXPECT_TRUE(res_or.get_bit(6));
    EXPECT_TRUE(res_or.get_bit(11));
    EXPECT_FALSE(res_or.get_bit(0));

    Bitfield res_and = b1 & b2;
    EXPECT_TRUE(res_and.get_bit(6));
    EXPECT_FALSE(res_and.get_bit(2));
    EXPECT_FALSE(res_and.get_bit(11));

    Bitfield b1_copy = b1;
    b1_copy |= b2;
    EXPECT_EQ(b1_copy, res_or);

    b1 &= b2;
    EXPECT_EQ(b1, res_and);

    Bitfield b_inv(5);
    b_inv.set_bit(1);
    Bitfield inv = ~b_inv;
    EXPECT_FALSE(inv.get_bit(1));
    EXPECT_TRUE(inv.get_bit(0));
    EXPECT_TRUE(inv.get_bit(4));
}
