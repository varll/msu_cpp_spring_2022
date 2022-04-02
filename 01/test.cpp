#include "allocator.hpp"
#include "gtest/gtest.h"

TEST(TestMakeAllocator, TestValidCreation) {
	Allocator allocator;
	allocator.makeAllocator(30);

	ASSERT_TRUE(allocator.get_pointer() != nullptr);
	ASSERT_EQ(allocator.get_size(), 30);
	ASSERT_EQ(allocator.get_offset(), 0);

	allocator.makeAllocator(1);
	ASSERT_TRUE(allocator.get_pointer() != nullptr);
	ASSERT_EQ(allocator.get_size(), 1);
	ASSERT_EQ(allocator.get_offset(), 0);
}

TEST(TestMakeAllocator, TestMakeZero){
	Allocator allocator;
	allocator.makeAllocator(0);

	ASSERT_TRUE(allocator.get_pointer() == nullptr);
	ASSERT_EQ(allocator.get_size(), 0);
	ASSERT_EQ(allocator.get_offset(), 0);
}

TEST(TestMakeAllocator, TestMultipleMake) {
	Allocator allocator;
	allocator.makeAllocator(10);
	allocator.makeAllocator(24);
	allocator.makeAllocator(12);

	ASSERT_TRUE(allocator.get_pointer() != nullptr);
	ASSERT_EQ(allocator.get_size(), 12);
	ASSERT_EQ(allocator.get_offset(), 0);
}

TEST(TestAlloc, TestValidAlloc) {
	Allocator allocator;
	allocator.makeAllocator(80);

	ASSERT_TRUE(allocator.alloc(40) != nullptr);
	ASSERT_EQ(allocator.get_offset(), 40);

}

TEST(TestAlloc, TestAllocBeforeMake) {
	Allocator allocator;

	ASSERT_TRUE(allocator.alloc(40) == nullptr);
	ASSERT_EQ(allocator.get_size(), 0);
	ASSERT_EQ(allocator.get_offset(), 0);
}

TEST(TestAlloc, TestAllocZero) {
	Allocator allocator;
	allocator.makeAllocator(20);
	
	ASSERT_TRUE(allocator.alloc(0) == nullptr);
	ASSERT_EQ(allocator.get_offset(), 0);
}

TEST(TestAlloc, TestMultipleAlloc) {
	Allocator allocator;;
	allocator.makeAllocator(40);

	char* p1 = allocator.alloc(10);
	char* p2 = allocator.alloc(30);

	ASSERT_TRUE(p1 != nullptr);
	ASSERT_TRUE(p2 != nullptr);
	ASSERT_EQ(p2 - p1, 10);
	ASSERT_EQ(allocator.get_offset(), 40);

	char* p3 = allocator.alloc(1);
	ASSERT_TRUE(p3 == nullptr);
	ASSERT_EQ(allocator.get_offset(), 40);
}

TEST(TestReset, TestValidReset) {
	Allocator allocator;
	allocator.makeAllocator(40);

	allocator.alloc(35);
	allocator.reset();

	ASSERT_EQ(allocator.get_size(), 40);
	ASSERT_TRUE(allocator.get_offset() == 0);

	allocator.reset();

	ASSERT_EQ(allocator.get_size(), 40);
	ASSERT_TRUE(allocator.get_offset() == 0);
}

TEST(TestALL, TestSmth){
	Allocator allocator;

	allocator.makeAllocator(100);
	char* p1 = allocator.alloc(50);
	char* p2 = allocator.alloc(50);
	ASSERT_EQ(p2-p1, 50);

	char* p3 = allocator.alloc(1);
	ASSERT_TRUE(p3 == nullptr);
	ASSERT_EQ(allocator.get_offset(), 100);

	allocator.reset();

	ASSERT_EQ(allocator.get_offset(), 0);
	ASSERT_EQ(allocator.get_size(), 100);

	p1 = allocator.alloc(100);

	ASSERT_TRUE(p1 != nullptr);
	ASSERT_EQ(allocator.get_offset(), 100);

	allocator.makeAllocator(1);

	ASSERT_TRUE(allocator.get_pointer() != nullptr);
	ASSERT_EQ(allocator.get_offset(), 0);
	ASSERT_EQ(allocator.get_size(), 1);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}