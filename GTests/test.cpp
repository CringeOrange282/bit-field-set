#include "pch.h"
#include <stdexcept>
#include "Bitfield.h"

TEST(BitfieldTest, Construction) {
    Bitfield b1;

    Bitfield b2(40);
    for (size_t i = 1; i <= 40; ++i) {
        EXPECT_FALSE(b2.get_bit(i));
    }
}

TEST(BitfieldTest, SetGetReset) {
    Bitfield b(50);

    b.set_bit(1);
    b.set_bit(32);
    b.set_bit(50);

    EXPECT_TRUE(b.get_bit(1));
    EXPECT_TRUE(b.get_bit(32));
    EXPECT_TRUE(b.get_bit(50));
    EXPECT_FALSE(b.get_bit(15));

    b.reset_bit(32);
    EXPECT_FALSE(b.get_bit(32));
    EXPECT_TRUE(b.get_bit(1));

    Bitfield b_mask(8);
    b_mask.set_bit(1);
    EXPECT_TRUE(b_mask.get_bit(1));
}

TEST(BitfieldTest, Exceptions) {
    Bitfield b(10);

    EXPECT_THROW(b.set_bit(0), std::invalid_argument);
    EXPECT_THROW(b.set_bit(11), std::invalid_argument);
}

TEST(BitfieldTest, Equality) {
    Bitfield b1(32);
    Bitfield b2(32);
    Bitfield b3(40);

    EXPECT_EQ(b1, b2);
    EXPECT_NE(b1, b3);

    b1.set_bit(5);
    EXPECT_NE(b1, b2);

    b2.set_bit(5);
    EXPECT_EQ(b1, b2);
}

TEST(BitfieldTest, CopyAndAssignment) {
    Bitfield b1(20);
    b1.set_bit(10);

    Bitfield b2 = b1;
    EXPECT_EQ(b2, b1);

    b2.set_bit(15);
    EXPECT_FALSE(b1.get_bit(15));

    Bitfield b3(5);
    b3 = b1;
    EXPECT_EQ(b3, b1);

    b3 = *&b3;
    EXPECT_EQ(b3, b1);
}

TEST(BitfieldTest, BitwiseOperations) {
    Bitfield b1(15);
    Bitfield b2(15);

    b1.set_bit(3);
    b1.set_bit(7);

    b2.set_bit(7);
    b2.set_bit(12);

    Bitfield res_or = b1 | b2;
    EXPECT_TRUE(res_or.get_bit(3));
    EXPECT_TRUE(res_or.get_bit(7));
    EXPECT_TRUE(res_or.get_bit(12));
    EXPECT_FALSE(res_or.get_bit(1));

    Bitfield res_and = b1 & b2;
    EXPECT_TRUE(res_and.get_bit(7));
    EXPECT_FALSE(res_and.get_bit(3));
    EXPECT_FALSE(res_and.get_bit(12));

    Bitfield b1_copy = b1;
    b1_copy |= b2;
    EXPECT_EQ(b1_copy, res_or);

    b1 &= b2;
    EXPECT_EQ(b1, res_and);

    Bitfield b_inv(5);
    b_inv.set_bit(2);
    Bitfield inv = ~b_inv;
    EXPECT_FALSE(inv.get_bit(2));
    EXPECT_TRUE(inv.get_bit(1));
    EXPECT_TRUE(inv.get_bit(5));
}
