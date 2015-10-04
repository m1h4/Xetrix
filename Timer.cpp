#include "Globals.h"
#include "Timer.h"
#include "Debug.h"

ULONGLONG	timerFrequency;
ULONGLONG	timerLast;
DOUBLE		timerElapsed;
DOUBLE		timerAbsolute;

bool InitializeTimer(void)
{
	if(!QueryPerformanceFrequency((PLARGE_INTEGER)&timerFrequency))
		return false;

	TRACE(TEXT("Info: Timer frequency is %ull Hz\n"),timerFrequency);

	if(!QueryPerformanceCounter((PLARGE_INTEGER)&timerLast))
		return false;

	timerElapsed = NULL;
	timerAbsolute = NULL;

	return true;
}

void KillTimer(void)
{
	// Does not do anything at this time
}

bool UpdateTimer(void)
{
	static const double framerate = 60.0;

	ULONGLONG time;

	if(!QueryPerformanceCounter((PLARGE_INTEGER)&time))
		return false;

	timerElapsed = DOUBLE(time - timerLast) / DOUBLE(timerFrequency) * framerate;
	timerAbsolute += timerElapsed;
	timerLast = time;

	if(timerElapsed > 1.5f)
	{
		TRACE(TEXT("Hich warning %u\n"),(unsigned long)(timerElapsed * 1000));
		timerElapsed = 1.5f;
	}

	return true;
}

float GetElapsedTime(void)
{
	return (float)timerElapsed;
}

float GetAbsoluteTime(void)
{
	return (float)timerAbsolute;
}