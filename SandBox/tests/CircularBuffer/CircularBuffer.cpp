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

extern "C"
{
#include "CircularBuffer.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(CircularBuffer)
{
    void setup()
    {
      CircularBuffer_Create();
    }

    void teardown()
    {
       CircularBuffer_Destroy();
    }
};

TEST(CircularBuffer, CreateIsEmpty)
{
	// Create() CircularBuffer is called from setup()
	// check that it's empty
	CHECK_TRUE(CircularBuffer_IsEmpty());
	CHECK_FALSE(CircularBuffer_IsFull());
}

TEST(CircularBuffer, DestroyIsEmpty)
{
	// Destroy() CircularBuffer is called from teardown()
	CHECK_TRUE(CircularBuffer_IsEmpty());
	CHECK_FALSE(CircularBuffer_IsFull());
}

TEST(CircularBuffer, InsertIfEmpty)
{
	CHECK_TRUE(CircularBuffer_Insert(1));
}

TEST(CircularBuffer, InsertIfFull)
{
	for (int i = 0; i < 10; ++i)
		CHECK_TRUE(CircularBuffer_Insert(i));
	//CHECK_FALSE(CircularBuffer_Insert(10));
}

TEST(CircularBuffer, DeleteIfNotEmpty)
{
	//CHECK_TRUE(CircularBuffer_Delete(NULL));
}

TEST(CircularBuffer, DeleteIfEmpty)
{
	CHECK_FALSE(CircularBuffer_Delete(NULL));
}

TEST(CircularBuffer, IntialSizeEmpty)
{
	//CHECK_EQUAL(0, CircularBuffer_Size());
}

TEST(CircularBuffer, InsertOneSizeOne)
{
	CHECK_TRUE(CircularBuffer_Insert(1));
	//CHECK_EQUAL(1, CircularBuffer_Size());
}
 TEST(CircularBuffer, FullSize)
 {
	 for (int i = 0; i < 10; ++i)
		 CircularBuffer_Insert(i);
	 CHECK_EQUAL(10, CircularBuffer_Size());
 }
