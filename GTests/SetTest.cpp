#include "pch.h"
#include "Set.h"

TEST(SetTest, ConstructionAndLimits) {
    Set s(10);
    EXPECT_EQ(s.max_power(), 10);
    EXPECT_THROW(s.insert(0), std::out_of_range);
    EXPECT_THROW(s.insert(11), std::out_of_range);
}

TEST(SetTest, InsertAndErase) {
    Set s(5);
    s.insert(1);
    s.insert(3);
    s.insert(5);

    Bitfield bf = static_cast<Bitfield>(s);
    EXPECT_TRUE(bf.get_bit(1));
    EXPECT_FALSE(bf.get_bit(2));
    EXPECT_TRUE(bf.get_bit(3));
    EXPECT_TRUE(bf.get_bit(5));

    s.erase(3);
    bf = static_cast<Bitfield>(s);
    EXPECT_FALSE(bf.get_bit(3));
}

TEST(SetTest, SingleElementOperators) {
    Set s(10);
    s += 5;
    Set s2 = s + 3;

    Bitfield bf1 = static_cast<Bitfield>(s);
    Bitfield bf2 = static_cast<Bitfield>(s2);

    EXPECT_TRUE(bf1.get_bit(5));
    EXPECT_FALSE(bf1.get_bit(3));
    EXPECT_TRUE(bf2.get_bit(5));
    EXPECT_TRUE(bf2.get_bit(3));

    s2 -= 5;
    Bitfield bf3 = static_cast<Bitfield>(s2);
    EXPECT_FALSE(bf3.get_bit(5));
}

TEST(SetTest, UnionOperators) {
    Set a(5);
    Set b(5);
    a += 1; a += 2;
    b += 2; b += 4;

    Set c = a + b;
    Bitfield bf_c = static_cast<Bitfield>(c);

    EXPECT_TRUE(bf_c.get_bit(1));
    EXPECT_TRUE(bf_c.get_bit(2));
    EXPECT_FALSE(bf_c.get_bit(3));
    EXPECT_TRUE(bf_c.get_bit(4));

    Set d(10);
    EXPECT_THROW(a + d, std::logic_error);
}

TEST(SetTest, DifferenceOperators) {
    Set a(5);
    Set b(5);
    a += 1; a += 2; a += 3;
    b += 2; b += 4;

    Set c = a - b;
    Bitfield bf_c = static_cast<Bitfield>(c);

    EXPECT_TRUE(bf_c.get_bit(1));
    EXPECT_FALSE(bf_c.get_bit(2));
    EXPECT_TRUE(bf_c.get_bit(3));
}

TEST(SetTest, UnaryMinus) {
    Set a(4);
    a += 1; a += 3;

    Set b = -a;
    Bitfield bf_b = static_cast<Bitfield>(b);

    EXPECT_FALSE(bf_b.get_bit(1));
    EXPECT_TRUE(bf_b.get_bit(2));
    EXPECT_FALSE(bf_b.get_bit(3));
    EXPECT_TRUE(bf_b.get_bit(4));
}

TEST(SetTest, CopyAndMoveSemantics) {
    Set a(5);
    a += 2;

    Set b(a);
    b += 4;

    Bitfield bf_a = static_cast<Bitfield>(a);
    Bitfield bf_b = static_cast<Bitfield>(b);

    EXPECT_FALSE(bf_a.get_bit(4));
    EXPECT_TRUE(bf_b.get_bit(4));

    Set c(std::move(a));
    Bitfield bf_c = static_cast<Bitfield>(c);
    EXPECT_TRUE(bf_c.get_bit(2));
}
