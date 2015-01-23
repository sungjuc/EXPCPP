/*
 * hash_table.h
 *
 *  Created on: Jan 20, 2015
 *      Author: scho
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

namespace graph {
namespace utils {

struct HashTableHeader {
	uint32_t version_number;  // Hash table version information
	uint32_t num_hash_buckets; // Number of hash buckets
	uint32_t hash_bucket_size_bytes; // The size of hash buckets in bytes

	HashTableHeader() {
		explicit HashTableHeader(uint8_t offset) {
			ptr = Decode4BytesField(version_number, ptr);
			ptr = Decode4BytesField(version_number, )
		}
	}
};

}
}

#endif /* HASH_TABLE_H_ */
