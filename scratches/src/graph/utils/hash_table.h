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

/**
 * Hash Table Header
 */
struct HashTableHeader {
	uint8_t** base_ptr;
	uint32_t version_number;  // Hash table version information
	uint32_t num_hash_buckets; // Number of hash buckets
	uint32_t hash_bucket_size_bytes; // The size of hash buckets in bytes

	explicit HashTableHeader(uint8_t** base_ptr, uint8_t offset) {
		this->base_ptr = base_ptr;
		offset = Decode4BytesField(&version_number, offset);
		offset = Decode4BytesField(&num_hash_buckets, offset);
		offset = Decode4BytesField(&hash_bucket_size_bytes, offset);
	}

	HashTableHeader(uint8_t** base_ptr, uint32_t version_number, uint32_t num_hash_buckets,
			uint32_t hash_bucket_size_bytes) {
		this->base_ptr = base_ptr;
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
		*reinterpret_cast<uint32_t *>(*this->base_ptr + offset) = field;
		return offset + sizeof field;
	}

	uint8_t Decode4BytesField(uint32_t* field_ptr, uint8_t offset) {
		*field_ptr = *reinterpret_cast<uint32_t *>(*this->base_ptr + offset);
		return offset + sizeof *field_ptr;
	}
};

/**
 * Generic key object
 */
struct Key {
	uint16_t size;
	uint8_t* bytes;

	Key(uint16_t size, uint8_t* bytes) :
			size(size), bytes(bytes) {
	}
};

/**
 * Generic value object
 */
struct Value {
	uint16_t size;
	uint8_t* bytes;

	Value(uint16_t size, uint8_t* bytes) :
			size(size), bytes(bytes) {
	}
};

/**
 * Hash Table entry object
 */
struct Entry {
	uint8_t** base_ptr;
	uint8_t* header;
	uint16_t key_size;
	uint8_t* key_bytes;
	uint16_t value_size;
	uint8_t* value_bytes;
	uint32_t offset;

	Entry(uint8_t** base_ptr, uint32_t offset) {
		this->base_ptr = base_ptr;
		header = reinterpret_cast<uint8_t *>(*this->base_ptr + offset);
		uint32_t cursor_offset = offset + sizeof *header;
		key_size = *reinterpret_cast<uint16_t *>(*this->base_ptr + cursor_offset);
		cursor_offset += sizeof key_size;
		key_bytes = reinterpret_cast<uint8_t *>(*this->base_ptr + cursor_offset);
		cursor_offset += key_size;
		value_size = *(reinterpret_cast<uint16_t *>(*this->base_ptr + cursor_offset));
		cursor_offset += sizeof value_size;
		value_bytes = reinterpret_cast<uint8_t *>(*this->base_ptr + cursor_offset);
	}

	uint32_t GetNextOffset() {
		if (this->HasNext())
			return offset + *header | 0x80;

		return 0;
	}

	bool HasNext() {
		return *header & 0x80;
	}
};

/**
 * Hash Table object
 */
class HashTable {
public:
	const bool Find(const Key& key, Value* value) {
		// Compute hash bucket
		uint32_t entry_offset = Hash(key) * header_.hash_bucket_size_bytes + header_.GetHeaderSize();
		Entry first_entry(this->base_ptr, entry_offset);

		// Iterate over every key
		for (Entry entry = first_entry; entry.HasNext();) {
			Entry next_entry(this->base_ptr, entry.GetNextOffset());
			entry = next_entry;
		}

		return false;
	}

private:
	uint8_t** base_ptr;
	HashTableHeader header_;
	uint32_t Hash(const Key& key) {
		uint32_t sum = 0;
		for (uint16_t i = 0; i < key.size; ++i) {
			sum += key.bytes[i];
		}

		return sum % header_.num_hash_buckets;
	}
};
}
}

#endif /* HASH_TABLE_H_ */
