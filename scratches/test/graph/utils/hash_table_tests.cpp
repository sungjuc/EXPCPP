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
	uint32_t h_hash_bucket_size_bytes = *reinterpret_cast<uint32_t *>(block + sizeof version_number + sizeof num_hash_buckets);

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
}
