#pragma once

#pragma warning(push)
#pragma warning(disable: 4100)
#include "FastDelegate.h"
#pragma warning(pop)

#include "../shared/SharedMemory.h"
#include "../shared/Structures.h"

//////////////////////////////////////////////////////////////////////////////

typedef fastdelegate::FastDelegate1<bool>	ConsoleChangeDelegate;
typedef fastdelegate::FastDelegate0<>		ConsoleCloseDelegate;

//////////////////////////////////////////////////////////////////////////////

class ConsoleHandler {

	public:
		ConsoleHandler();
		~ConsoleHandler();

	public:

		void SetupDelegates(ConsoleChangeDelegate consoleChangeDelegate, ConsoleCloseDelegate consoleCloseDelegate);
		bool StartShellProcess();

		DWORD StartMonitorThread();
		void StopMonitorThread();

		SharedMemory<ConsoleParams>& GetConsoleParams() { return m_consoleParams; }
		SharedMemory<CONSOLE_SCREEN_BUFFER_INFO>& GetConsoleInfo() { return m_consoleInfo; }
		SharedMemory<CHAR_INFO>& GetConsoleBuffer() { return m_consoleBuffer; }
		SharedMemory<ConsoleSize>& GetNewConsoleSize() { return m_newConsoleSize; }

	private:

		bool CreateSharedMemory(DWORD dwConsoleProcessId);

		bool InjectHookDLL();

	private:
		
		static DWORD WINAPI MonitorThreadStatic(LPVOID lpParameter);
		DWORD MonitorThread();


	private:
		
		wstring GetModulePath(HMODULE hModule);


	private:

		ConsoleChangeDelegate						m_consoleChangeDelegate;
		ConsoleCloseDelegate						m_consoleCloseDelegate;

		shared_ptr<void>							m_hConsoleProcess;

		SharedMemory<ConsoleParams>					m_consoleParams;
		SharedMemory<CONSOLE_SCREEN_BUFFER_INFO>	m_consoleInfo;
		SharedMemory<CHAR_INFO>						m_consoleBuffer;

		SharedMemory<ConsoleSize>					m_newConsoleSize;

		shared_ptr<void>							m_hMonitorThread;
		shared_ptr<void>							m_hMonitorThreadExit;
};

//////////////////////////////////////////////////////////////////////////////
