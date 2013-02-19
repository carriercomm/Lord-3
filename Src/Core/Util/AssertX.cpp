#include "CoreStd.h"
#include "StringUtil.h"
#include "AssertX.h"

// Platform head file including
#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
#	define WIN32_LEAN_AND_MEAN
#	define _CRT_SECURE_NO_WARNINGS
#	include <Windows.h>
#	undef _T
#	include <tchar.h>
#endif

LORD_NAMESPACE_BEGIN

ErrRet DisplayError(const tchar *errorTitle,
					const tchar *errorText,
					const tchar *errorDescription,
					const tchar *fileName,
					int lineNumber)
{
#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	const int MODULE_NAME_SIZE = 255;
	tchar moduleName[MODULE_NAME_SIZE];
	
	// attempt to get the module name
	if (!GetModuleFileName(NULL, moduleName, MODULE_NAME_SIZE))
	{
		tchar *msg = _T("<unknown application>");
		_tcscpy_s(moduleName, _tcsclen(msg), msg);
	}
	
	// build a collosal string containing the entire asster message
	const	int		MAX_BUFFER_SIZE = 1024;
	tchar	buffer[MAX_BUFFER_SIZE];
	
	int Size = _sntprintf_s(buffer,
							MAX_BUFFER_SIZE,
							_T(	"%s\n\nProgram : %s\nFile : %s\nLine : %d\nError: %s\nComment: %s\n")
							_T("Abort to exit (or debug), Retry to continue,\n")
							_T("Ignore to disregard all occurances of this error\n"),
							errorTitle,
							moduleName,
							fileName,
							lineNumber,
							errorText,
							errorDescription);
	
	
	// place a copy of the message into the clipboard
	if (OpenClipboard(NULL))
	{
		size_t bufferLength = _tcsclen(buffer);
		HGLOBAL hMem = GlobalAlloc(GHND|GMEM_DDESHARE, bufferLength+1);
		
		if (hMem)
		{
			Byte* pMem = (Byte*)GlobalLock(hMem);
			memcpy(pMem, buffer, bufferLength);
			GlobalUnlock(hMem);
			EmptyClipboard();
			SetClipboardData(CF_TEXT, hMem);
		}
		
		CloseClipboard();
	}
	
	
	// find the top most window of the current application
	HWND hWndParent = GetActiveWindow();
	if (NULL != hWndParent)
	{
		hWndParent = GetLastActivePopup(hWndParent);
	}
	
	// put up a message box with the error
	int iRet = MessageBox ( hWndParent,
						   buffer,
						   _T( "ERROR NOTIFICATION..." ),
						   MB_TASKMODAL|MB_SETFOREGROUND|MB_ABORTRETRYIGNORE|MB_ICONERROR);
	
	// Figure out what to do on the return.
	if (iRet == IDRETRY)
	{
		// ignore this error and continue
		return (ERRRET_CONTINUE);
	}
	if (iRet == IDIGNORE)
	{
		// ignore this error and continue,
		// plus never stop on this error again (handled by the caller)
		return (ERRRET_IGNORE);
	}
	
	// The return has to be IDABORT, but does the user want to enter the debugger
	// or just exit the application?
	iRet = MessageBox(	hWndParent,
					  _T("Do you wish to debug the last error?"),
					  _T( "DEBUG OR EXIT?" ),
					  MB_TASKMODAL|MB_SETFOREGROUND|MB_YESNO|MB_ICONQUESTION);
	
	if (iRet == IDYES)
	{
		// inform the caller to break on the current line of execution
		return (ERRRET_BREAKPOINT);
	}
	
	// must be a full-on termination of the app
	ExitProcess ( (UINT)-1 ) ;
	return (ERRRET_ABORT);

#else
	
	return (ERRRET_BREAKPOINT);
#endif
}

ErrRet NotifyAssert(const tchar *condition, const char *fileName, int lineNumber, const tchar *formats, ...)
{
	va_list args;
	va_start(args, formats);
	String msg = StringUtil::Format(formats, va_pass(args));
	va_end(args);
	
	String filenameStr = StringUtil::ConvStr(fileName);
	
	// pass the data on to the message box
	ErrRet result = DisplayError(_T("Assert Failed!"),
								 condition,
								 msg.c_str(),
								 filenameStr.c_str(),
								 lineNumber);
	return result;
}

LORD_NAMESPACE_END