#include "Globals.h"
#include "Debug.h"

Debug db;

const Debug& operator<<(const Debug& debug,LPCTSTR string)
{
	debug.Trace(TEXT("%s"),string);
	return debug;
}

const Debug& operator<<(const Debug& debug,const Vector2& vector)
{
	debug.Trace(TEXT("Vector2: {%f,%f}"),vector.x,vector.y);
	return debug;
}

BOOL Debug::EvaluateAssert(BOOL expression,LPCSTR expressionString,LPCSTR function,LPCSTR file,LONG line)
{
	if(expression)
		return FALSE;

	static TCHAR message[4096];

	wsprintf(message,TEXT("Function: %s\n\nExpression: %s\n\nFile: %s (Line %d)\n\nDo you want to break into the debugger? Selecting No will exit the application."),function,expressionString,file,line);

	switch(MessageBox(NULL,message,TEXT("Assertion Failed"),MB_YESNOCANCEL|MB_ICONEXCLAMATION|MB_TASKMODAL))
	{
	case IDYES:
		return TRUE;

	case IDCANCEL:
		return FALSE;
	}

	exit(2);
}

VOID Debug::Trace(LPCTSTR format,...)
{
	ASSERT(format);

	static TCHAR buffer[4096];

    va_list args;
    va_start(args,format);
	wvsprintf(buffer,format,args);
    va_end(args);

	OutputDebugString(buffer);
}

typedef enum _MINIDUMP_TYPE {
    MiniDumpNormal                         = 0x00000000,
    MiniDumpWithDataSegs                   = 0x00000001,
    MiniDumpWithFullMemory                 = 0x00000002,
    MiniDumpWithHandleData                 = 0x00000004,
    MiniDumpFilterMemory                   = 0x00000008,
    MiniDumpScanMemory                     = 0x00000010,
    MiniDumpWithUnloadedModules            = 0x00000020,
    MiniDumpWithIndirectlyReferencedMemory = 0x00000040,
    MiniDumpFilterModulePaths              = 0x00000080,
    MiniDumpWithProcessThreadData          = 0x00000100,
    MiniDumpWithPrivateReadWriteMemory     = 0x00000200,
    MiniDumpWithoutOptionalData            = 0x00000400,
    MiniDumpWithFullMemoryInfo             = 0x00000800,
    MiniDumpWithThreadInfo                 = 0x00001000,
    MiniDumpWithCodeSegs                   = 0x00002000,
    MiniDumpWithoutAuxiliaryState          = 0x00004000,
    MiniDumpWithFullAuxiliaryState         = 0x00008000,
    
    MiniDumpValidTypeFlags                 = 0x0000ffff,
} MINIDUMP_TYPE;

typedef struct _MINIDUMP_EXCEPTION_INFORMATION {
    DWORD ThreadId;
    PEXCEPTION_POINTERS ExceptionPointers;
    BOOL ClientPointers;
} MINIDUMP_EXCEPTION_INFORMATION, *PMINIDUMP_EXCEPTION_INFORMATION;

typedef
BOOL
(WINAPI * LPMINIDUMPWRITEDUMP) (
	IN HANDLE hProcess,
	IN DWORD ProcessId,
	IN HANDLE hFile,
	IN MINIDUMP_TYPE DumpType,
	IN CONST LPVOID NotUsed1,	// IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
	IN CONST LPVOID NotUsed2,	// IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
	IN CONST LPVOID NotUsed3	// IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL
	);

LONG WINAPI Debug::DumpException(LPEXCEPTION_POINTERS exceptionInfo)
{
	HMODULE hLibrary = LoadLibrary(TEXT("dbghelp.dll"));
	LPMINIDUMPWRITEDUMP miniDumpWriteDump = (LPMINIDUMPWRITEDUMP)GetProcAddress(hLibrary,"MiniDumpWriteDump");
	if(!hLibrary || !miniDumpWriteDump)
	{
		FreeLibrary(hLibrary);

		TCHAR message[512];
		wsprintf(message,TEXT("The program needs to close because of a unhandled 0x%08lX exception which occurred at 0x%08lX.\n")\
						 TEXT("No additional information about the problem could be stored. We apologize for the inconvenience."),exceptionInfo->ExceptionRecord->ExceptionCode,exceptionInfo->ExceptionRecord->ExceptionAddress);

		MessageBox(GetDesktopWindow(),message,TEXT("Unhandled Exception"),MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);

		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Just create the dump file in the current working directory
	TCHAR dump[MAX_PATH] = {TEXT("Dump.dmp")};

	HANDLE hFile = CreateFile(dump,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,NULL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		FreeLibrary(hLibrary);

		TCHAR message[512];
		wsprintf(message,TEXT("The program needs to close because of a unhandled 0x%08lX exception which occurred at 0x%08lX.\n")\
						 TEXT("A file '%s' containing more information about the ")\
						 TEXT("exception could not be written to the current directory.\nPlease ")\
						 TEXT("check if you have write permissions in the current directory. We apologize for the inconvenience."),exceptionInfo->ExceptionRecord->ExceptionCode,exceptionInfo->ExceptionRecord->ExceptionAddress,dump);

		MessageBox(GetDesktopWindow(),message,TEXT("Unhandled Exception"),MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);

		return EXCEPTION_EXECUTE_HANDLER;
	}

	MINIDUMP_EXCEPTION_INFORMATION info = {0};
	info.ClientPointers = TRUE;
	info.ExceptionPointers = exceptionInfo;
	info.ThreadId = GetCurrentThreadId();

	miniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(),hFile,MiniDumpWithFullMemory,&info,NULL,NULL);
	
	FlushFileBuffers(hFile);
	CloseHandle(hFile);
	FreeLibrary(hLibrary);

	TCHAR message[512];
	wsprintf(message,TEXT("The program needs to close because of a unhandled 0x%08lX exception which occurred at 0x%08lX.\n")\
					 TEXT("A file '%s' containing more information about the ")\
					 TEXT("exception has been written to the current directory.\nPlease ")\
					 TEXT("send us this file to help us in finding and repairing ")\
					 TEXT("the problem. We apologize for the inconvenience."),exceptionInfo->ExceptionRecord->ExceptionCode,exceptionInfo->ExceptionRecord->ExceptionAddress,dump);

	MessageBox(GetDesktopWindow(),message,TEXT("Unhandled Exception"),MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);

	return EXCEPTION_EXECUTE_HANDLER;
}