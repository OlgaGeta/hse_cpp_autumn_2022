#include "Allocator.hpp"

void Allocator::makeAllocator(size_t maxSize)
{
	delete[] data;

	capacity = maxSize;
	data = new char[capacity];
	offset = 0;
}

char* Allocator::alloc(size_t size)
{
	if (capacity - offset < size)
		return nullptr;

	char* memory = data + offset;

	offset += size;

	return memory;
}

void Allocator::reset()
{
	offset = 0;
}

Allocator::~Allocator()
{
	delete[] data;
}