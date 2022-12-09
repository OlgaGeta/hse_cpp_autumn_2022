#ifndef ALLOCATOR_HPP_

#define ALLOCATOR_HPP_

class Allocator
{
private:
	char* data = nullptr;
	size_t capacity = 0;

	size_t offset = 0;
public:
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~Allocator();
};

#endif
