#pragma once

#include "Vector.h"

#ifdef _DEBUG
#define ASSERT(expression) if(Debug::EvaluateAssert((BOOL)expression,#expression,__FUNCTION__,__FILE__,__LINE__)) DebugBreak();
#define TRACE Debug::Trace
#else
#define ASSERT __noop
#define TRACE __noop
#endif

class Debug
{
public:
	static VOID Trace(LPCTSTR format,...);
	static BOOL EvaluateAssert(BOOL expression,LPCSTR expressionString,LPCSTR function,LPCSTR file,LONG line);
	// Give this function to SetUnhandledExceptionFilter in a call at the begining of your main function
	static LONG WINAPI DumpException(LPEXCEPTION_POINTERS exceptionInfo);
};

const Debug& operator<<(const Debug& debug,LPCTSTR string);
const Debug& operator<<(const Debug& debug,const Vector2& vector);


extern Debug db;