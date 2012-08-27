//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved         
//-    For use by owners of Test-Driven Development for Embedded C,   
//-    and attendees of Renaissance Software Consulting, Co. training 
//-    classes.                                                       
//-                                                                   
//-    Available at http://pragprog.com/titles/jgade/                 
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3               
//-                                                                   
//-    Authorized users may use this source code in your own          
//-    projects, however the source code may not be used to           
//-    create training material, courses, books, articles, and        
//-    the like. We make no guarantees that this source code is       
//-    fit for any purpose.                                           
//-                                                                   
//-    www.renaissancesoftware.net james@renaissancesoftware.net      
//- ------------------------------------------------------------------
#include <stdio.h>
extern "C"
{
#include "CircularBuffer.h"
}

#include "CppUTest/TestHarness.h"

enum { CIRCULAR_BUFFER_DIM = 10 };

TEST_GROUP(CircularBuffer)
{
    void setup()
    {
      CircularBuffer_Create(CIRCULAR_BUFFER_DIM);
    }

    void teardown()
    {
       CircularBuffer_Destroy();
    }
};

TEST(CircularBuffer, CreateIsEmpty)
{
	CHECK_TRUE(CircularBuffer_IsEmpty());
	CHECK_FALSE(CircularBuffer_IsFull());
	CHECK_EQUAL(0, CircularBuffer_Size());
}

TEST(CircularBuffer, QueueOneSizeOne)
{
	CHECK_EQUAL(0, CircularBuffer_Size());
	CHECK_TRUE(CircularBuffer_Queue(1));
	CHECK_EQUAL(1, CircularBuffer_Size());
}

TEST(CircularBuffer, Fill)
{
	CHECK_FALSE(CircularBuffer_IsFull());
	for (int i = 0; !CircularBuffer_IsFull(); ++i)
		CHECK_TRUE(CircularBuffer_Queue(i));
	CHECK_EQUAL(CIRCULAR_BUFFER_DIM, CircularBuffer_Size());
}

IGNORE_TEST(CircularBuffer, CannotOverflow)
{
	// @TODO to test this need to pad buffer with start and end flag
	//       and check them for overflow after writes
}

TEST(CircularBuffer, QueueFull)
{
	for (int i = 0; !CircularBuffer_IsFull(); ++i)
		CHECK_TRUE(CircularBuffer_Queue(i));
	CHECK_FALSE(CircularBuffer_Queue(1));
}

TEST(CircularBuffer, DestroyIsEmpty)
{
	CHECK_TRUE(CircularBuffer_Queue(1));
	CHECK_FALSE(CircularBuffer_IsEmpty());
	CircularBuffer_Destroy();
	CHECK_TRUE(CircularBuffer_IsEmpty());
	CHECK_EQUAL(0, CircularBuffer_Size());
}

TEST(CircularBuffer, DequeueIfNotEmpty)
{
	CHECK_TRUE(CircularBuffer_Queue(1));
	CHECK_TRUE(CircularBuffer_Dequeue(NULL));
}

TEST(CircularBuffer, QueueDequeueOne)
{
	int test_value = 1;
	CHECK_TRUE(CircularBuffer_Queue(test_value));
	test_value = -1;
	CHECK_TRUE(CircularBuffer_Dequeue(&test_value));
	CHECK_EQUAL(1, test_value);
}

TEST(CircularBuffer, QueueDequeueAll)
{
	int test_value = -1;

	// fill with test pattern
	for (int i = 0; !CircularBuffer_IsFull(); ++i)
			CHECK_TRUE(CircularBuffer_Queue(i));

	// read back
	for (int i = 0; !CircularBuffer_IsEmpty(); ++i)
	{
		test_value = -1;
		CHECK_TRUE(CircularBuffer_Dequeue(&test_value));
		CHECK_EQUAL(i, test_value);
	}
}

TEST(CircularBuffer, DequeueIfEmpty)
{
	CHECK_FALSE(CircularBuffer_Dequeue(NULL));
}

TEST(CircularBuffer, CannotQueueIfFull)
{
	int test_value = 0;

	// fill
	for (test_value = 0; !CircularBuffer_IsFull(); ++test_value)
		CHECK_TRUE(CircularBuffer_Queue(test_value));

	// verify cannot queue new values
	CHECK_FALSE(CircularBuffer_Queue(test_value));
}

TEST(CircularBuffer, QueueWrapAround)
{
	int test_value = 0;

	// fill
	for (test_value = 0; !CircularBuffer_IsFull(); ++test_value)
		CHECK_TRUE(CircularBuffer_Queue(test_value));

	// free a slot
	CHECK_TRUE(CircularBuffer_Dequeue(NULL));
	// queue new value
	CHECK_TRUE(CircularBuffer_Queue(test_value));

	// verify correct values are read back
	for (int i = 1; !CircularBuffer_IsEmpty(); ++i)
	{
		test_value = -1;
		CHECK_TRUE(CircularBuffer_Dequeue(&test_value));
		CHECK_EQUAL(i, test_value);
	}
}

IGNORE_TEST(CircularBuffer, Print)
{
	for (int i = 0; !CircularBuffer_IsFull(); ++i)
		CHECK_TRUE(CircularBuffer_Queue(i));
	CircularBuffer_Print();
}
