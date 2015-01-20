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

	EXPECT_EQ(chunk.Size(), 0);
	//EXPECT_EQ(chunk.offset_, 123);

}

TEST(IntegerFunctionTest, negative) {
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_GT(1, 0);
}
