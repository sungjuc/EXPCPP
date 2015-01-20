/*
 * chunk.h
 *
 *  Created on: Jan 19, 2015
 *      Author: scho
 */
#include <queue>

#ifndef CHUNK_H_
#define CHUNK_H_

template<class Value>
struct ChunkIter {
private:
public:
	Value next();
	bool hasNext();
};

template<class Value>
struct Chunk {
private:
	uint32_t offset_;
	uint32_t size_;
	uint32_t first_;
	std::priority_queue<Value> delta_set_;
	Chunk* next_;

public:
	Chunk(uint32_t offset);
	Chunk(uint32_t offset, std::priority_queue<Value> set);

	/**
	 * Returns the number of elements in the chunk.
	 * @return the number of elements in the chunk.
	 */
	uint32_t Size();

	/**
	 * Returns the chunk iterator. The iterator should be lazy iterator.
	 * @return the chunk iterator.
	 */
	ChunkIter<Value> Iterator();

	bool Encode();

	bool Encode(Value value);
};

template<class Value>
Chunk<Value>::Chunk(uint32_t offset) {
	Chunk::offset_ = offset;
	Chunk::size_ = 0;
}

template<class Value>
uint32_t Chunk<Value>::Size() {
	return Chunk::size_;
}


#endif /* CHUNK_H_ */
