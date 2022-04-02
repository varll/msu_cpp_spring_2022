#include "allocator.h"
#include "gtest/gtest.h"

TEST(TestMakeAllocator, TestValidCreation) {
	Allocator allocator;
	allocator.makeAllocator(30);

	ASSERT_NE(allocator.get_pointer(), nullptr);
	ASSERT_EQ(allocator.get_size(), 30);
	ASSERT_EQ(allocator.get_offset(), 0);
}

TEST(TestMakeAllocator, TestMultipleMake) {
	Allocator allocator;
	allocator.makeAllocator(30);
	allocator.makeAllocator(24);
	allocator.makeAllocator(12);

	ASSERT_TRUE(allocator.get_pointer() != nullptr);
	ASSERT_EQ(allocator.get_size(), 12);
	ASSERT_NE(allocator.get_size(), 30);
	ASSERT_EQ(allocator.get_offset(), 0);

}

TEST(TestAlloc, TestValidAlloc) {
	Allocator allocator;
	allocator.makeAllocator(80);

	ASSERT_TRUE(allocator.alloc(40) != nullptr);
	ASSERT_EQ(allocator.get_offset(), 40);

}

TEST(TestAlloc, TestMultipleAlloc) {
	Allocator allocator;;
	allocator.makeAllocator(80);

	allocator.alloc(10);
	allocator.alloc(30);

	ASSERT_TRUE(allocator.alloc(20) != nullptr);
	ASSERT_EQ(allocator.get_offset(), 60);

	ASSERT_TRUE(allocator.alloc(20) != nullptr);
	ASSERT_EQ(allocator.get_offset(), 80);

	ASSERT_TRUE(allocator.alloc(1) == nullptr);
	ASSERT_EQ(allocator.get_offset(), 80);
}

TEST(TestReset, TestValidReset) {
	Allocator allocator;
	allocator.makeAllocator(40);

	allocator.alloc(35);
	allocator.reset();

	ASSERT_EQ(allocator.get_size(), 40);
	ASSERT_TRUE(allocator.get_offset() == 0);

	allocator.reset();
	allocator.reset();

	ASSERT_EQ(allocator.get_size(), 40);
	ASSERT_TRUE(allocator.get_offset() == 0);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}