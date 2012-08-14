/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/


#include "unity_fixture.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

TEST_GROUP(sprintf);

//static char output[100];
static char *output = NULL;
//static char *output_new = NULL;
static const char *expected;
enum { MIN_OUTPUT_DIM=(2 * sizeof(char)) };

TEST_SETUP(sprintf)
{
	output = (char *)malloc(MIN_OUTPUT_DIM);
	memset(output, 0xaa, MIN_OUTPUT_DIM);
	expected = "";
}

TEST_TEAR_DOWN(sprintf)
{
    free(output);
}

static void expect(const char * s)
{
	int length = strlen(s)+2; // string + terminator + overflow detection

	if (MIN_OUTPUT_DIM < length)
	{
		char *output_new = realloc(output, length);
		if (output_new)
		{
			output = output_new;
			memset(output, 0xaa, length);
			expected = "";
		}
	}

    expected = s;
}

static void given(int charsWritten)
{
    TEST_ASSERT_EQUAL(strlen(expected), charsWritten);
    TEST_ASSERT_EQUAL_STRING(expected, output);
    TEST_ASSERT_BYTES_EQUAL(0xaa, output[strlen(expected) + 1]);
}


#if 1 
TEST(sprintf, NoFormatOperations)
{
    expect("hey");
    given(sprintf(output, "hey"));
}

TEST(sprintf, InsertString)
{
    expect("Hello World\n");
    given(sprintf(output, "Hello %s\n", "World"));
}
#endif  

TEST(sprintf, StringWithSpace)
{
    expect("space ");
    given(sprintf(output, "space "));
}

#pragma GCC diagnostic ignored "-Wformat-zero-length"
TEST(sprintf, EmptyString)
{
  //TEST_FAIL_MESSAGE(__func__);
  expect("");
  given(sprintf(output, ""));
}
#pragma GCC diagnostic warning "-Wformat-zero-length"

TEST(sprintf, StringWithHexFormat)
{
  int test = 255;
  expect("0xff");
  given(sprintf(output, "0x%x", test));
}

/* to run this also change in SprintfTestRunner.c */
#if 0 
TEST(sprintf, NoFormatOperations)
{
    char output[5];

    TEST_ASSERT_EQUAL(4, sprintf(output, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", output);
}
#endif

#if 0 
TEST(sprintf, NoFormatOperations)
{
    char output[5];
    memset(output, 0xaa, sizeof output);

    TEST_ASSERT_EQUAL(3, sprintf(output, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", output);
    TEST_ASSERT_BYTES_EQUAL(0xaa, output[4]);
}

TEST(sprintf, InsertString)
{
    char output[20];
    memset(output, 0xaa, sizeof output);

    TEST_ASSERT_EQUAL(12, sprintf(output, "Hello %s\n", "World"));
    TEST_ASSERT_EQUAL_STRING("Hello World\n", output);
    TEST_ASSERT_BYTES_EQUAL(0xaa, output[13]);
}
#endif

#if 0 
TEST(sprintf, NoFormatOperations)
{
    char output[5];

    TEST_ASSERT_EQUAL(3, sprintf(output, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", output);
}
#endif

#if 0 
TEST(sprintf, NoFormatOperations)
{
    char output[5] = "";
    TEST_ASSERT_EQUAL(3, sprintf(output, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", output);
}
#endif

#if 0 
TEST(sprintf, NoFormatOperations)
{
    char output[5];
    memset(output, 0xaa, sizeof output);

    TEST_ASSERT_EQUAL(3, sprintf(output, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", output);
}
#endif


#if 0 
TEST(sprintf, InsertString)
{
    char output[20] = "";

    TEST_ASSERT_EQUAL(12, sprintf(output, "Hello %s\n", "World"));
    TEST_ASSERT_EQUAL_STRING("Hello World\n", output);
}
#endif
