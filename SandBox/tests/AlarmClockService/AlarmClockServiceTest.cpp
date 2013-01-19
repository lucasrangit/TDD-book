#include <stdio.h>
extern "C"
{
#include "AlarmClockService.h"
}

#include "CppUTest/TestHarness.h"


TEST_GROUP(AlarmClockService)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(AlarmClockService, ScheduleActionEvery100NotTimeYet)
{
	//int action_id = ACTION_ID_UNKNOWN;
	//action_id = AlarmClockService_SchedulePeriodic(NULL, 1);
	AlarmClockService_SchedulePeriodic(NULL, 1);
	FakeTimeMsService_SetTimeMs(99);

	AlarmClockService_WakeUp();

	LONGS_EQUAL(ACTION_ID_UNKNOWN, ActionSpy_GetLasId());
	LONGS_EQUAL(ACTION_STATE_UNKNOWN, ActionSpy_GetLastState());
}
