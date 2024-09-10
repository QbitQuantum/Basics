void _tmain(int argc, TCHAR *argv[])
{
	g_hStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);		// WinBash.h
	/*
	CreateEventW (Unicode)
	Creates or opens a named or unnamed event object.

	HANDLE WINAPI CreateEvent(
		_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
		_In_     BOOL                  bManualReset,
		_In_     BOOL                  bInitialState,
		_In_opt_ LPCTSTR               lpName
	);

	*** !LPSECURITY_ATTRIBUTES

	The SECURITY_ATTRIBUTES structure contains the security descriptor for an object and specifies
	whether the handle retrieved by specifying this structure is inheritable.
	This structure provides security settings for objects created by various functions,
	such as CreateFile, CreatePipe, CreateProcess, RegCreateKeyEx, or RegSaveKeyEx.
	
	typedef struct _SECURITY_ATTRIBUTES {
	  DWORD  nLength;
	  LPVOID lpSecurityDescriptor;
	  BOOL   bInheritHandle;
	} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

		*** LPVOID
		http://kspil.tistory.com/6
		Microsoft Playform SDK를 설치하고 그 하위 디렉토리에서 WinDef.h 파일을 찾으면
		아래와 같은 치환어들이 모두 정의되어 있습니다.
		
		#define WINAPI __stdcall
		typedef unsigned char BYTE;
		typedef unsigned long * PDWORD;
		typedef void far * LPVOID;

			*** far * http://egloos.zum.com/jhjang/v/2369128
			far 포인터 형 함수는 unix와 ansi c에서는 제공이 되지 않고 도스와 윈도우에서만 사용하였지만
			최근에는 WIN32로 환경이 바뀌면서 사용하지 않게 되었다.
			좀더 상세히 말하면 near포인터와 far포인터는 windef.h파일에 정의되는데 win32로 바뀌면서 빈 문장열로 처리하도록 변경되었다.

		단순히 Microsoft에서 좀 더 이해하기 쉬우면서 짧은 타입명을 제시한 것이다.

		이름에는 일정한 형식이 있다.

		1. 포인터 타입(*)인 경우에는 P로 시작하며 - PINT, PDWORD 등
		2. far 포인터(far *)인 경우에는 L로 시작합니다 - LPVOID 등
		3. unsigned 타입일 경우 U로 시작합니다. - UINT, ULONG 등
		4. BYTE, WORD, DWORD 등은 어셈블리에서 쓰이던 데이터 형식의 이름을 따왔습니다.
	
	*** LPCTSTR
	http://egloos.zum.com/pelican7/v/1768951

	LP는 long pointer를 나타내는 약어로서 16bit시절의 윈도우의 유산이다.
	현재 LP(long pointer)는 .Net에서는 64bit pointer를,
	VC++6.0과 그 이전 버전에서는 32bit pointer를 나타낸다.

	C는 constant, 즉 함수의 내부에서 인자값을 변경하지 말라는 뜻이다. 
	STR은 말그대로 string자료가 될것이라는 뜻으로 내부적으로는 char형 배열에 null값 종료를 의미한다.

	LPSTR = long pointer string = char * 
	LPCTSTR = long pointer constant t_string = const tchar * 

	컴파일러가 precompile option을 보고 환경에 맞게 동작하는 코드를 작성할 수 있는 새로운 변수 모양의 Macro를 선언하게 되었다. 
	그것이 바로 TCHAR, t_char라는 변수다. 
	즉, 자신의 운영체제가 multi-byte환경이면, char형으로, 
	unicode환경이면, w_char, wide char형으로 type casting된다.
	*/

	

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
	/*
	SetConsoleCtrlHandler :
	Adds or removes an application-defined HandlerRoutine function
	from the list of handler functions for the calling process.
	If no handler function is specified,
	the function sets an inheritable attribute that determines
	whether the calling process ignores CTRL+C signals.
	
	SetConsoleCtrlHandler(
		__in_opt PHANDLER_ROUTINE HandlerRoutine,
		__in BOOL Add);	

	*** PHANDLER_ROUTINE

	// typedef for ctrl-c handler routines
	typedef
	BOOL
	(WINAPI *PHANDLER_ROUTINE)( __in DWORD CtrlType	);
	*/


	g_hFile = CreateFile(_T("RegFsNotify.txt"), 
		GENERIC_WRITE,				// (0x40000000L)
		FILE_SHARE_READ, 0,			// 0x00000001, 0
		CREATE_ALWAYS, 0, NULL);	// 2, 0, NULL
	/*
	https://msdn.microsoft.com/en-us/library/windows/desktop/aa363858(v=vs.85).aspx
	WINBASEAPI
	__out
	HANDLE
	WINAPI
	CreateFileW(
		__in     LPCWSTR lpFileName,
		__in     DWORD dwDesiredAccess,
					// The requested access to the file or device,
					// which can be summarized as read, write, both or neither zero
		__in     DWORD dwShareMode,
					// The requested sharing mode of the file or device,
					// which can be read, write, both, delete, all of these, or none
		__in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
					// A pointer to a SECURITY_ATTRIBUTES structure
					// that contains two separate but related data members
					// INULL : the handle returned
					// by CreateFile cannot be inherited by any child processes the application
		__in     DWORD dwCreationDisposition,
		__in     DWORD dwFlagsAndAttributes,
					// The file or device attributes and flags,
					// FILE_ATTRIBUTE_NORMAL being the most common default value for files.
		__in_opt HANDLE hTemplateFile
		);
	*/


	HANDLE hThread[2];

	hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartFileMonitor, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartRegistryMonitor, NULL, 0, NULL);
	/*
	*** CreateThread
	Creates a thread to execute within the virtual address space of the calling process.
	To create a thread that runs in the virtual address space of another process,
	use the CreateRemoteThread function.

	WINBASEAPI
	__out_opt
	HANDLE
	WINAPI
	CreateThread(
		__in_opt  LPSECURITY_ATTRIBUTES lpThreadAttributes,
						// A pointer to a SECURITY_ATTRIBUTES structure that determines 
						// whether the returned handle can be inherited by child processes.
						// NULL : the handle cannot be inherited.
		__in      SIZE_T dwStackSize,
						// The initial size of the stack, in bytes.
						// 0 : the new thread uses the default size for the executable.
		__in      LPTHREAD_START_ROUTINE lpStartAddress,
		__in_opt __deref __drv_aliasesMem LPVOID lpParameter,
						// A pointer to a variable to be passed to the thread.
		__in      DWORD dwCreationFlags,
						// The flags that control the creation of the thread.
						// 0 : The thread runs immediately after creation.
		__out_opt LPDWORD lpThreadId
						// A pointer to a variable that receives the thread identifier.
						// NULL : the thread identifier is not returned.
		);
	*/


	WaitForMultipleObjects(2, (const HANDLE*)&hThread, TRUE, INFINITE);		// WinBash.h
	/*
	*** WaitForMultipleObjects
	Waits until one or all of the specified objects are
	in the signaled state or the time-out interval elapses.

	WINBASEAPI
	DWORD
	WINAPI
	WaitForMultipleObjects(
		__in DWORD nCount,
		__in_ecount(nCount) CONST HANDLE *lpHandles,
		__in BOOL bWaitAll,
					// TRUE : the function returns when the state of all objects
					// in the lpHandles array is signaled.
		__in DWORD dwMilliseconds
					// The time-out interval, in milliseconds.
					// INFINITE : the function will return only when the specified objects are signaled.
		);
	*/


	TerminateThread(g_hRegWatch[0], 0);
	TerminateThread(g_hRegWatch[1], 0);
	/*
	*** TerminateThread
	WINBASEAPI
	BOOL
	WINAPI
	TerminateThread(
		__in HANDLE hThread,
		__in DWORD dwExitCode
		);

	TerminatedThread를 사용하면 스레드가 제대로 정리되지 않는다.
	대부분 최후의 경우에만 사용해야 하는 위험한 함수다.
	적절하게 종료하기 위한 방법 :
		1. CreateEvent 함수를 사용하여 이벤트 개체를 만든다.
		2. 스레드를 만든다.
		3. 각 스레드는 WaitForSingleObject 함수를 호출하여 이벤트 상태를 모니터링한다.
		4. 각 스레드는 이벤트가 신호를 받는 상태 (WaitForSingleObjtect)가 WAIT_OBJECT_0을 반환)로 설정되었을 때 실행을 종료한다.
	*/


	CloseHandle(g_hStopEvent);
	CloseHandle(g_hFile);
	/*
	WINBASEAPI
	BOOL
	WINAPI
	CloseHandle( __in HANDLE hObject );
	*/

	_tprintf(_T("Program terminating.\n"));
}