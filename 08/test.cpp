#include "ThreadPool.hpp"
#include "gtest/gtest.h"

struct A {};

void foo(const A&) {}


TEST(TestThreadPool, TestFromHomework){
    ThreadPool pool(8);
	auto task1 = pool.exec(foo, A());
	task1.get();
	auto task2 = pool.exec([]() { return 1; });
	ASSERT_EQ(task2.get(), 1);
}

TEST(TestThreadPool, TestRandom){
	ThreadPool pool(5);
	for (size_t i = 0; i < 5; ++i){
		auto result = pool.exec([](){return 42;});
		ASSERT_EQ(result.get(), 42);
	}
	
}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
