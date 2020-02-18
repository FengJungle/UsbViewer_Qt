#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <TCHAR.H>
#include <mutex>

using namespace std;

enum LOGLEVEL
{
	LOG_LEVEL_NONE,
	LOG_LEVEL_ERROR,     // error
	LOG_LEVEL_WARNING,   // warning
	LOG_LEVEL_DEBUG,     // debug
	LOG_LEVEL_INFO,      // info	
};

enum LOGTARGET
{
	LOG_TARGET_NONE      = 0x00,
	LOG_TARGET_CONSOLE   = 0x01,
	LOG_TARGET_FILE      = 0x10
};

#define FILENAME(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#define LOG_DEBUG(...)    LOG::writeLog(LOG_LEVEL_DEBUG, (unsigned char*)(FILENAME(__FILE__)), (unsigned char*)(__FUNCTION__), (int)(__LINE__), __VA_ARGS__)
#define LOG_INFO(...)     LOG::writeLog(LOG_LEVEL_INFO, (unsigned char*)(FILENAME(__FILE__)), (unsigned char*)(__FUNCTION__), (int)(__LINE__), __VA_ARGS__)
#define LOG_WARNING(...)  LOG::writeLog(LOG_LEVEL_WARNING, (unsigned char*)(FILENAME(__FILE__)), (unsigned char*)(__FUNCTION__), (int)(__LINE__), __VA_ARGS__)
#define LOG_ERROR(...)    LOG::writeLog(LOG_LEVEL_ERROR, (unsigned char*)(FILENAME(__FILE__)), (unsigned char*)(__FUNCTION__), (int)(__LINE__), __VA_ARGS__)

#define ENTER() LOG_INFO("enter")
#define EXIT()  LOG_INFO("exit")
#define FAIL()  LOG_ERROR("fail")

// The maximum size of a single log file
#define MAX_SIZE 2*1024*1024  // 2M

class LOG
{
public:

	// Init
	void init(LOGLEVEL loglevel, LOGTARGET logtarget);

	// 
	void uninit();

	// file
	int createFile();

	static LOG* getInstance();

	// Log level
	LOGLEVEL getLogLevel();
	void setLogLevel(LOGLEVEL loglevel);

	// Log output location
	LOGTARGET getLogTarget();
	void setLogTarget(LOGTARGET logtarget);

	//  Output log
	static int writeLog(
		LOGLEVEL loglevel,         // Log level
		unsigned char* fileName,   // File name which the function locates in
		unsigned char* function,   // Function name
		int lineNumber,            // Line num
		char* format,              // Format
		...);                      // Args

	// Output log
	static void outputToTarget();

private:
	LOG();
	~LOG();
	static LOG* Log;

	// Mutex
	static mutex log_mutex;
	// Critical section
	static CRITICAL_SECTION criticalSection;

	// Buffer saving log
	static string logBuffer;
	// Written size
	static int writtenSize;

	// Log level
	LOGLEVEL logLevel;

	// Log target
	LOGTARGET logTarget;

	// Handle
	static HANDLE mFileHandle;
};

#endif // __LOG_H__