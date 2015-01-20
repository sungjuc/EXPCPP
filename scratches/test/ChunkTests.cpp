/*
 * ChunkTests.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: scho
 */
# include "gtest/gtest.h"
# include "Chunk.h"

TEST(ConstructorTest, negative) {
	Chunk<int> chunk(123);

	EXPECT_EQ(chunk.Size(), 0);
	//EXPECT_EQ(chunk.offset_, 123);

}

TEST(IntegerFunctionTest, negative) {
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_GT(1, 0);
}
