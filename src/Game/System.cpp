#include <STDInclude.hpp>

namespace Game
{
	Sys_FreeFileList_t Sys_FreeFileList = Sys_FreeFileList_t(0x4D8580);
	Sys_IsDatabaseReady_t Sys_IsDatabaseReady = Sys_IsDatabaseReady_t(0x4CA4A0);
	Sys_IsDatabaseReady2_t Sys_IsDatabaseReady2 = Sys_IsDatabaseReady2_t(0x441280);
	Sys_IsMainThread_t Sys_IsMainThread = Sys_IsMainThread_t(0x4C37D0);
	Sys_IsRenderThread_t Sys_IsRenderThread = Sys_IsRenderThread_t(0x4B20E0);
	Sys_IsServerThread_t Sys_IsServerThread = Sys_IsServerThread_t(0x4B0270);
	Sys_IsDatabaseThread_t Sys_IsDatabaseThread = Sys_IsDatabaseThread_t(0x4C6020);
	Sys_ListFiles_t Sys_ListFiles = Sys_ListFiles_t(0x45A660);
	Sys_Milliseconds_t Sys_Milliseconds = Sys_Milliseconds_t(0x42A660);
	Sys_Error_t Sys_Error = Sys_Error_t(0x43D570);
	Sys_LockWrite_t Sys_LockWrite = Sys_LockWrite_t(0x435880);
	Sys_TempPriorityAtLeastNormalBegin_t Sys_TempPriorityAtLeastNormalBegin = Sys_TempPriorityAtLeastNormalBegin_t(0x478680);
	Sys_TempPriorityEnd_t Sys_TempPriorityEnd = Sys_TempPriorityEnd_t(0x4DCF00);
	Sys_EnterCriticalSection_t Sys_EnterCriticalSection = Sys_EnterCriticalSection_t(0x4FC200);
	Sys_LeaveCriticalSection_t Sys_LeaveCriticalSection = Sys_LeaveCriticalSection_t(0x41B8C0);
	Sys_DefaultInstallPath_t Sys_DefaultInstallPath = Sys_DefaultInstallPath_t(0x4326E0);
	Sys_SendPacket_t Sys_SendPacket = Sys_SendPacket_t(0x60FDC0);
	Sys_ShowConsole_t Sys_ShowConsole = Sys_ShowConsole_t(0x4305E0);
	Sys_SuspendOtherThreads_t Sys_SuspendOtherThreads = Sys_SuspendOtherThreads_t(0x45A190);

	char(*sys_exitCmdLine)[1024] = reinterpret_cast<char(*)[1024]>(0x649FB68);

	void Sys_LockRead(FastCriticalSection* critSect)
	{
		InterlockedIncrement(&critSect->readCount);
		while (critSect->writeCount) std::this_thread::sleep_for(1ms);
	}

	void Sys_UnlockRead(FastCriticalSection* critSect)
	{
		assert(critSect->readCount > 0);
		InterlockedDecrement(&critSect->readCount);
	}
}
