#include <iostream>

#include "gtest/gtest.h"

#include "Bimap/bimap.h"

constexpr auto cycles_count = 1000;

TEST(Bimap, add_values)
{
    container::bimap<std::string, int> bimap;

    EXPECT_TRUE(bimap.isEmpty());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind), ind);
        EXPECT_TRUE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind), ind);
        EXPECT_FALSE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());

    EXPECT_FALSE(bimap.isEmpty());
}

TEST(Bimap, add_and_erase_by_key)
{
    container::bimap<std::string, int> bimap;

    EXPECT_TRUE(bimap.isEmpty());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind), ind);
        EXPECT_TRUE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());

    const auto half = cycles_count/2;
    for(auto ind = 0; ind < half; ++ind) {
        bimap.keyErase(std::to_string(ind));
    }
    EXPECT_EQ(cycles_count - half, bimap.size());

    for(auto ind = half; ind < cycles_count; ++ind) {
        EXPECT_TRUE(bimap.checkKey(std::to_string(ind)));
        EXPECT_TRUE(bimap.checkVal(ind));
    }
    for(auto ind = 0; ind < half; ++ind) {
        EXPECT_FALSE(bimap.checkKey(std::to_string(ind)));
        EXPECT_FALSE(bimap.checkVal(ind));

        bool will_except = false;
        try {
            bimap.keyGet(std::to_string(ind));
        } catch (const std::exception&) {
            will_except = true;
        }
        EXPECT_TRUE(will_except);

        will_except = false;
        try {
            bimap.keyGet(std::to_string(ind));
        } catch (const std::exception&) {
            will_except = true;
        }
        EXPECT_TRUE(will_except);
    }
}

TEST(Bimap, add_and_erase_by_value)
{
    container::bimap<std::string, int> bimap;

    EXPECT_TRUE(bimap.isEmpty());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind), ind);
        EXPECT_TRUE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());

    const auto half = cycles_count/2;
    for(auto ind = 0; ind < half; ++ind) {
        bimap.valErase(ind);
    }
    EXPECT_EQ(cycles_count - half, bimap.size());

    for(auto ind = half; ind < cycles_count; ++ind) {
        EXPECT_TRUE(bimap.checkKey(std::to_string(ind)));
        EXPECT_TRUE(bimap.checkVal(ind));
    }
    for(auto ind = 0; ind < half; ++ind) {
        EXPECT_FALSE(bimap.checkKey(std::to_string(ind)));
        EXPECT_FALSE(bimap.checkVal(ind));
    }
}

TEST(Bimap, check_key_unique)
{
    container::bimap<std::string, int> bimap;

    EXPECT_TRUE(bimap.isEmpty());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind), ind);
        EXPECT_TRUE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind), ind + cycles_count);
        EXPECT_FALSE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());
}

TEST(Bimap, check_val_unique)
{
    container::bimap<std::string, int> bimap;

    EXPECT_TRUE(bimap.isEmpty());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind), ind);
        EXPECT_TRUE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind + cycles_count), ind);
        EXPECT_FALSE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());
}

TEST(Bimap, compare_ret_data_by_key)
{
    container::bimap<std::string, int> bimap;

    EXPECT_TRUE(bimap.isEmpty());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind), ind);
        EXPECT_TRUE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const auto ret = bimap.keyGet(std::to_string(ind));
        EXPECT_EQ(std::to_string(ind), ret.first.get());
        EXPECT_EQ(ind, ret.second.get());
    }
}

TEST(Bimap, compare_ret_data_by_val)
{
    container::bimap<std::string, int> bimap;

    EXPECT_TRUE(bimap.isEmpty());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const bool res = bimap.insert(std::to_string(ind), ind);
        EXPECT_TRUE(res);
    }
    EXPECT_EQ(cycles_count, bimap.size());

    for(auto ind = 0; ind < cycles_count; ++ind) {
        const auto ret = bimap.valGet(ind);
        EXPECT_EQ(std::to_string(ind), ret.first.get());
        EXPECT_EQ(ind, ret.second.get());
    }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
