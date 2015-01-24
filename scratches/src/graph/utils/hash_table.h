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
	uint8_t* ptr;
	uint32_t version_number;  // Hash table version information
	uint32_t num_hash_buckets; // Number of hash buckets
	uint32_t hash_bucket_size_bytes; // The size of hash buckets in bytes

	explicit HashTableHeader(uint8_t* ptr, uint8_t offset) {
		this->ptr = ptr;
		offset = Decode4BytesField(&version_number, offset);
		offset = Decode4BytesField(&num_hash_buckets, offset);
		offset = Decode4BytesField(&hash_bucket_size_bytes, offset);
	}

	HashTableHeader(uint8_t* ptr, uint32_t version_number,
			uint32_t num_hash_buckets, uint32_t hash_bucket_size_bytes) {
		this->ptr = ptr;
		this->version_number = version_number;
		this->num_hash_buckets = num_hash_buckets;
		this->hash_bucket_size_bytes = hash_bucket_size_bytes;
		EncodeHeader();
	}

	uint8_t EncodeHeader() {
		uint8_t offset = 0;
		offset = Encode4BytesField(version_number, offset);
		offset = Encode4BytesField(num_hash_buckets, offset);
		offset = Encode4BytesField(hash_bucket_size_bytes, offset);
		return offset;
	}

	uint32_t GetHeaderSize() {
		return sizeof(HashTableHeader);
	}

private:
	uint8_t Encode4BytesField(uint32_t field, uint8_t offset) {
		*reinterpret_cast<uint32_t *>(this->ptr + offset) = field;
		return offset + sizeof field;
	}

	uint8_t Decode4BytesField(uint32_t* field_ptr, uint8_t offset) {
		*field_ptr = *reinterpret_cast<uint32_t *>(this->ptr + offset);
		return offset + sizeof *field_ptr;
	}
};

}
}

#endif /* HASH_TABLE_H_ */
