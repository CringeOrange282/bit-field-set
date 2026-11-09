#include "pch.h"
#include "Set.h"
#include <stdexcept>

TEST(SetTest, CreateWithCorrectSize) {
    Set s(10);
    EXPECT_EQ(s.max_power(), 10);
}

TEST(SetTest, CopyCreatesIndependentSet) {
    Set a(5);
    a.insert(2);

    Set b(a);
    b.insert(4);

    Bitfield bf_a = static_cast<Bitfield>(a);
    Bitfield bf_b = static_cast<Bitfield>(b);

    EXPECT_FALSE(bf_a.get_bit(3));
    EXPECT_TRUE(bf_b.get_bit(3));
}

TEST(SetTest, MoveTransfersData) {
    Set a(5);
    a.insert(2);

    Set c(std::move(a));
    Bitfield bf_c = static_cast<Bitfield>(c);

    EXPECT_TRUE(bf_c.get_bit(1));
}

TEST(SetTest, AssignCopiesData) {
    Set a(5);
    a.insert(1);
    Set b(5);

    b = a;
    Bitfield bf_b = static_cast<Bitfield>(b);

    EXPECT_TRUE(bf_b.get_bit(0));
}

TEST(SetTest, InsertAddsElement) {
    Set s(5);
    s.insert(1);
    s.insert(3);

    Bitfield bf = static_cast<Bitfield>(s);
    EXPECT_TRUE(bf.get_bit(0));
    EXPECT_FALSE(bf.get_bit(1));
    EXPECT_TRUE(bf.get_bit(2));
}

TEST(SetTest, InsertFailsOutOffBounds) {
    Set s(10);
    EXPECT_THROW(s.insert(0), std::out_of_range);
    EXPECT_THROW(s.insert(11), std::out_of_range);
}

TEST(SetTest, EraseRemovesElement) {
    Set s(5);
    s.insert(3);
    s.erase(3);

    Bitfield bf = static_cast<Bitfield>(s);
    EXPECT_FALSE(bf.get_bit(2));
}

TEST(SetTest, EraseFailsOutOffBounds) {
    Set s(10);
    EXPECT_THROW(s.erase(0), std::out_of_range);
    EXPECT_THROW(s.erase(11), std::out_of_range);
}

TEST(SetTest, CheckIsMember) {
    Set s(5);
    s.insert(3);

    EXPECT_TRUE(s.is_member(3));
    EXPECT_FALSE(s.is_member(1));
    EXPECT_FALSE(s.is_member(0));
    EXPECT_FALSE(s.is_member(6));
}

TEST(SetTest, PlusEqualWithNumber) {
    Set s(10);
    s += 5;

    Bitfield bf = static_cast<Bitfield>(s);
    EXPECT_TRUE(bf.get_bit(4));
}

TEST(SetTest, PlusWithNumber) {
    Set s(10);
    Set s2 = s + 3;

    Bitfield bf1 = static_cast<Bitfield>(s);
    Bitfield bf2 = static_cast<Bitfield>(s2);

    EXPECT_FALSE(bf1.get_bit(2));
    EXPECT_TRUE(bf2.get_bit(2));
}

TEST(SetTest, MinusEqualWithNumber) {
    Set s(10);
    s.insert(5);
    s -= 5;

    Bitfield bf = static_cast<Bitfield>(s);
    EXPECT_FALSE(bf.get_bit(4));
}

TEST(SetTest, MinusWithNumber) {
    Set s(10);
    s.insert(3);
    Set s2 = s - 3;

    Bitfield bf1 = static_cast<Bitfield>(s);
    Bitfield bf2 = static_cast<Bitfield>(s2);

    EXPECT_TRUE(bf1.get_bit(2));
    EXPECT_FALSE(bf2.get_bit(2));
}

TEST(SetTest, PlusEqualWithSet) {
    Set a(5); Set b(5);
    a.insert(1);
    b.insert(2);

    a += b;
    Bitfield bf_a = static_cast<Bitfield>(a);

    EXPECT_TRUE(bf_a.get_bit(0));
    EXPECT_TRUE(bf_a.get_bit(1));
}

TEST(SetTest, PlusWithSet) {
    Set a(5); Set b(5);
    a.insert(1); a.insert(2);
    b.insert(2); b.insert(4);

    Set c = a + b;
    Bitfield bf_c = static_cast<Bitfield>(c);

    EXPECT_TRUE(bf_c.get_bit(0));
    EXPECT_TRUE(bf_c.get_bit(1));
    EXPECT_FALSE(bf_c.get_bit(2));
    EXPECT_TRUE(bf_c.get_bit(3));
}

TEST(SetTest, PlusWithDifferentSizesFails) {
    Set a(5);
    Set d(10);
    EXPECT_THROW(a + d, std::logic_error);
}

TEST(SetTest, MinusEqualWithSet) {
    Set a(5); Set b(5);
    a.insert(1); a.insert(2);
    b.insert(2);

    a -= b;
    Bitfield bf_a = static_cast<Bitfield>(a);

    EXPECT_TRUE(bf_a.get_bit(0));
    EXPECT_FALSE(bf_a.get_bit(1));
}

TEST(SetTest, MinusWithSet) {
    Set a(5); Set b(5);
    a.insert(1); a.insert(2); a.insert(3);
    b.insert(2); b.insert(4);

    Set c = a - b;
    Bitfield bf_c = static_cast<Bitfield>(c);

    EXPECT_TRUE(bf_c.get_bit(0));
    EXPECT_FALSE(bf_c.get_bit(1));
    EXPECT_TRUE(bf_c.get_bit(2));
    EXPECT_FALSE(bf_c.get_bit(3));
}

TEST(SetTest, MinusWithDifferentSizesFails) {
    Set a(5);
    Set d(10);
    EXPECT_THROW(a - d, std::logic_error);
}

TEST(SetTest, MultiplyEqualWithSet) {
    Set a(5); Set b(5);
    a.insert(1); a.insert(2);
    b.insert(2); b.insert(3);

    a *= b;
    Bitfield bf_a = static_cast<Bitfield>(a);

    EXPECT_FALSE(bf_a.get_bit(0));
    EXPECT_TRUE(bf_a.get_bit(1));
    EXPECT_FALSE(bf_a.get_bit(2));
}

TEST(SetTest, MultiplyWithSet) {
    Set a(5); Set b(5);
    a.insert(1); a.insert(2);
    b.insert(2); b.insert(3);

    Set c = a * b;
    Bitfield bf_c = static_cast<Bitfield>(c);

    EXPECT_FALSE(bf_c.get_bit(0));
    EXPECT_TRUE(bf_c.get_bit(1));
    EXPECT_FALSE(bf_c.get_bit(2));
}

TEST(SetTest, MultiplyWithDifferentSizesFails) {
    Set a(5);
    Set d(10);
    EXPECT_THROW(a * d, std::logic_error);
}

TEST(SetTest, InvertAllBits) {
    Set a(4);
    a.insert(1);
    a.insert(3);

    Set b = -a;
    Bitfield bf_b = static_cast<Bitfield>(b);

    EXPECT_FALSE(bf_b.get_bit(0));
    EXPECT_TRUE(bf_b.get_bit(1));
    EXPECT_FALSE(bf_b.get_bit(2));
    EXPECT_TRUE(bf_b.get_bit(3));
}
