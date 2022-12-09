#include "pch.h"
#include "Allocator.cpp"

TEST(Allocator, makeAllocator)
{
	Allocator a;
	a.makeAllocator(10);
	char* ptr1 = a.alloc(1);

	a.makeAllocator(20);
	char* ptr2 = a.alloc(1);

	EXPECT_NE(ptr1, ptr2);
}

TEST(Allocator, alloc)
{
	Allocator a;
	a.makeAllocator(sizeof(int) + 1);

	int* ptr1 = (int*)a.alloc(sizeof(int));
	int* ptr2 = (int*)a.alloc(sizeof(int));

	EXPECT_NE(ptr1, nullptr);
	EXPECT_EQ(ptr2, nullptr);

	a.makeAllocator(1000);

	ptr1 = (int*)a.alloc(sizeof(int));
	ptr2 = (int*)a.alloc(sizeof(int));

	EXPECT_EQ((size_t)ptr2 - (size_t)ptr1, sizeof(int));

	char* ptr3 = (char*)a.alloc(sizeof(char));
	float* ptr4 = (float*)a.alloc(sizeof(float));

	EXPECT_EQ((size_t)ptr4 - (size_t)ptr3, sizeof(char));
}

TEST(Allocator, reset)
{
	Allocator a;
	a.makeAllocator(1000);

	int* ptr1 = (int*)a.alloc(sizeof(int));
	int* ptr2 = (int*)a.alloc(sizeof(int));

	a.reset();

	char* ptr3 = (char*)a.alloc(sizeof(char));

	EXPECT_EQ((size_t)ptr1, (size_t)ptr3);
}