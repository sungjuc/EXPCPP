/*
 * hash_table_tests.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: scho
 */

# include "gtest/gtest.h"
# include "graph/utils/hash_table.h"
# include <stdio.h>

using namespace graph::utils;

TEST(HashTableHeader, constructor) {
	// Prepare memory, test data and create header instance.
	uint8_t* block = reinterpret_cast<uint8_t *>(malloc(1024));

	uint32_t version_number = 100;  // Hash table version information
	uint32_t num_hash_buckets = 10; // Number of hash buckets
	uint32_t hash_bucket_size_bytes = 16; // The size of hash buckets in bytes

	HashTableHeader header(&block, version_number, num_hash_buckets, hash_bucket_size_bytes);

	// Get the header entries directly from underlying memory and validate them.
	uint32_t h_version_number = *reinterpret_cast<uint32_t *>(block);
	uint32_t h_num_hash_buckets = *reinterpret_cast<uint32_t *>(block + sizeof version_number);
	uint32_t h_hash_bucket_size_bytes = *reinterpret_cast<uint32_t *>(block + sizeof version_number
			+ sizeof num_hash_buckets);

	EXPECT_EQ(header.version_number, version_number);
	EXPECT_EQ(header.num_hash_buckets, num_hash_buckets);
	EXPECT_EQ(header.hash_bucket_size_bytes, hash_bucket_size_bytes);

	EXPECT_EQ(h_version_number, version_number);
	EXPECT_EQ(h_num_hash_buckets, num_hash_buckets);
	EXPECT_EQ(h_hash_bucket_size_bytes, hash_bucket_size_bytes);

	// Create another header using underlying memory to parse.
	HashTableHeader readHeader(&block, 0);
	EXPECT_EQ(readHeader.version_number, version_number);
	EXPECT_EQ(readHeader.num_hash_buckets, num_hash_buckets);
	EXPECT_EQ(readHeader.hash_bucket_size_bytes, hash_bucket_size_bytes);

	// Free memory.
	free(block);
}

TEST(Key, basic) {
	uint32_t subject = 1;
	uint8_t* key_bytes = reinterpret_cast<uint8_t *>(&subject);

	Key key(sizeof subject, key_bytes);

	EXPECT_EQ(key.size, sizeof subject);
	EXPECT_EQ(key.bytes, key_bytes);

	uint16_t double_key_size = 9;
	uint32_t predicate = 2;
	uint8_t* double_key_bytes = reinterpret_cast<uint8_t *>(malloc(double_key_size));
	*double_key_bytes = subject;
	*(double_key_bytes + sizeof subject) = '|';
	*(double_key_bytes + sizeof subject + 1) = predicate;

	Key doubleKey(double_key_size, double_key_bytes);

	EXPECT_EQ(doubleKey.size, double_key_size);
	EXPECT_EQ(doubleKey.bytes, double_key_bytes);

	free(double_key_bytes);
}

TEST(Value, basic) {
	uint32_t offset = 1024;
	uint8_t* value_bytes = reinterpret_cast<uint8_t *>(&offset);

	Value value(sizeof offset, value_bytes);

	EXPECT_EQ(value.size, sizeof offset);
	EXPECT_EQ(value.bytes, value_bytes);
}

TEST(Entry, basic) {
	// Prepare memory, test data and create header instance.
	uint8_t* block = reinterpret_cast<uint8_t *>(malloc(1024));

	// Key setup
	uint16_t key_size = 9;
	uint32_t subject = 1;
	uint32_t predicate = 2;

	uint8_t* key_bytes = reinterpret_cast<uint8_t *>(malloc(key_size));
	*key_bytes = subject;
	*(key_bytes + sizeof subject) = '|';
	*(key_bytes + sizeof subject + 1) = predicate;

	// Value setup
	uint32_t value = 2048;
	uint16_t value_size = sizeof value;

	// Entry size
	uint8_t entry_size = static_cast<uint8_t>(sizeof(uint8_t) + sizeof key_size + key_size + sizeof value_size
			+ value_size);

	// Set up arbitrary offset
	uint32_t offset = 100;

	// Write data in block.
	uint32_t cursor_offset = offset;

	*reinterpret_cast<uint8_t *>(block + cursor_offset) = entry_size;
	cursor_offset += sizeof entry_size;

	*reinterpret_cast<uint16_t *>(block + cursor_offset) = key_size;
	cursor_offset += sizeof key_size;

	uint8_t key_offset = cursor_offset;
	uint8_t* key_bytes_offset = key_bytes;

	for (uint16_t i = 0; i < key_size; i++) {
		*reinterpret_cast<uint8_t *>(block + key_offset) = *key_bytes_offset;
		key_bytes_offset++;
		key_offset++;
	}

	cursor_offset += key_size;

	*reinterpret_cast<uint16_t *>(block + cursor_offset) = value_size;
	cursor_offset += sizeof value_size;

	*reinterpret_cast<uint32_t *>(block + cursor_offset) = value;

	// Move to new entry position.
	cursor_offset += value_size;

	Entry entry(&block, offset);

	EXPECT_EQ((uint8_t )*entry.header, entry_size);
	EXPECT_EQ(entry.key_size, key_size);
	EXPECT_EQ(*entry.key_bytes, *key_bytes);
	EXPECT_EQ(entry.value_size, value_size);
	EXPECT_EQ(*(uint32_t * )entry.value_bytes, value);

	EXPECT_EQ(entry.HasNext(), false);
	EXPECT_EQ(entry.GetNextOffset(), 0);

	// Free memory.
	free(block);
	free(key_bytes);
}
