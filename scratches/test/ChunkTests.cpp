/*
 * ChunkTests.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: scho
 */
# include "gtest/gtest.h"
# include "Chunk.h"

typedef uint32_t offset_t;

TEST(ConstructorTest, negative) {
	Chunk<uint32_t, offset_t> chunk(1);

	uint32_t sample = 1;
	uint32_t* sample1 = (uint32_t *)malloc(sizeof(uint32_t*));

	//EXPECT_EQ(chunk.Size(), 0);
	//EXPECT_EQ(chunk.offset_, 123);
	EXPECT_EQ(sizeof(sample), 4);
	EXPECT_EQ(sizeof(*sample1), 4);

}

TEST(IntegerFunctionTest, negative) {
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_GT(1, 0);
}
