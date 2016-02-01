/*
Cuckoo Sandbox - Automated Malware Analysis
Copyright (C) 2010-2014 Cuckoo Sandbox Developers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <windows.h>

#ifndef __NTAPI_H__
#define __NTAPI_H__

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation, // 0 Y N
	SystemProcessorInformation, // 1 Y N
	SystemPerformanceInformation, // 2 Y N
	SystemTimeOfDayInformation, // 3 Y N
	SystemNotImplemented1, // 4 Y N
	SystemProcessesAndThreadsInformation, // 5 Y N
	SystemCallCounts, // 6 Y N
	SystemConfigurationInformation, // 7 Y N
	SystemProcessorTimes, // 8 Y N
	SystemGlobalFlag, // 9 Y Y
	SystemNotImplemented2, // 10 Y N
	SystemModuleInformation, // 11 Y N
	SystemLockInformation, // 12 Y N
	SystemNotImplemented3, // 13 Y N
	SystemNotImplemented4, // 14 Y N
	SystemNotImplemented5, // 15 Y N
	SystemHandleInformation, // 16 Y N
	SystemObjectInformation, // 17 Y N
	SystemPagefileInformation, // 18 Y N
	SystemInstructionEmulationCounts, // 19 Y N
	SystemInvalidInfoClass1, // 20
	SystemCacheInformation, // 21 Y Y
	SystemPoolTagInformation, // 22 Y N
	SystemProcessorStatistics, // 23 Y N
	SystemDpcInformation, // 24 Y Y
	SystemNotImplemented6, // 25 Y N
	SystemLoadImage, // 26 N Y
	SystemUnloadImage, // 27 N Y
	SystemTimeAdjustment, // 28 Y Y
	SystemNotImplemented7, // 29 Y N
	SystemNotImplemented8, // 30 Y N
	SystemNotImplemented9, // 31 Y N
	SystemCrashDumpInformation, // 32 Y N
	SystemExceptionInformation, // 33 Y N
	SystemCrashDumpStateInformation, // 34 Y Y/N
	SystemKernelDebuggerInformation, // 35 Y N
	SystemContextSwitchInformation, // 36 Y N
	SystemRegistryQuotaInformation, // 37 Y Y
	SystemLoadAndCallImage, // 38 N Y
	SystemPrioritySeparation, // 39 N Y
	SystemNotImplemented10, // 40 Y N
	SystemNotImplemented11, // 41 Y N
	SystemInvalidInfoClass2, // 42
	SystemInvalidInfoClass3, // 43
	SystemTimeZoneInformation, // 44 Y N
	SystemLookasideInformation, // 45 Y N
	SystemSetTimeSlipEvent, // 46 N Y
	SystemCreateSession, // 47 N Y
	SystemDeleteSession, // 48 N Y
	SystemInvalidInfoClass4, // 49
	SystemRangeStartInformation, // 50 Y N
	SystemVerifierInformation, // 51 Y Y
	SystemAddVerifier, // 52 N Y
	SystemSessionProcessesInformation // 53 Y N
} SYSTEM_INFORMATION_CLASS;

typedef enum _PROCESSINFOCLASS {
	ProcessBasicInformation,
	ProcessQuotaLimits,
	ProcessIoCounters,
	ProcessVmCounters,
	ProcessTimes,
	ProcessBasePriority,
	ProcessRaisePriority,
	ProcessDebugPort,
	ProcessExceptionPort,
	ProcessAccessToken,
	ProcessLdtInformation,
	ProcessLdtSize,
	ProcessDefaultHardErrorMode,
	ProcessIoPortHandlers,          // Note: this is kernel mode only
	ProcessPooledUsageAndLimits,
	ProcessWorkingSetWatch,
	ProcessUserModeIOPL,
	ProcessEnableAlignmentFaultFixup,
	ProcessPriorityClass,
	ProcessWx86Information,
	ProcessHandleCount,
	ProcessAffinityMask,
	ProcessPriorityBoost,
	ProcessDeviceMap,
	ProcessSessionInformation,
	ProcessForegroundInformation,
	ProcessWow64Information,
	ProcessImageFileName,
	ProcessLUIDDeviceMapsEnabled,
	ProcessBreakOnTermination,
	ProcessDebugObjectHandle,
	ProcessDebugFlags,
	ProcessHandleTracing,
	ProcessIoPriority,
	ProcessExecuteFlags,
	ProcessTlsInformation,
	ProcessCookie,
	ProcessImageInformation,
	ProcessCycleTime,
	ProcessPagePriority,
	ProcessInstrumentationCallback,
	ProcessThreadStackAllocation,
	ProcessWorkingSetWatchEx,
	ProcessImageFileNameWin32,
	ProcessImageFileMapping,
	ProcessAffinityUpdateMode,
	ProcessMemoryAllocationMode,
	ProcessGroupInformation,
	ProcessTokenVirtualizationEnabled,
	ProcessConsoleHostProcess,
	ProcessWindowInformation,
	MaxProcessInfoClass             // MaxProcessInfoClass should always be the last enum
} PROCESSINFOCLASS;

#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT * Buffer;
#else // MIDL_PASS
	__field_bcount_part(MaximumLength, Length) PWCH   Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef LONG KPRIORITY;
typedef struct _CLIENT_ID {
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID;
typedef CLIENT_ID *PCLIENT_ID;
typedef struct _VM_COUNTERS {
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
} VM_COUNTERS;
typedef VM_COUNTERS *PVM_COUNTERS;

//structs about processes
typedef enum _KWAIT_REASON {
	Executive,
	FreePage,
	PageIn,
	PoolAllocation,
	DelayExecution,
	Suspended,
	UserRequest,
	WrExecutive,
	WrFreePage,
	WrPageIn,
	WrPoolAllocation,
	WrDelayExecution,
	WrSuspended,
	WrUserRequest,
	WrEventPair,
	WrQueue,
	WrLpcReceive,
	WrLpcReply,
	WrVirtualMemory,
	WrPageOut,
	WrRendezvous,
	WrKeyedEvent,
	WrTerminated,
	WrProcessInSwap,
	WrCpuRateControl,
	WrCalloutStack,
	WrKernel,
	WrResource,
	WrPushLock,
	WrMutex,
	WrQuantumEnd,
	WrDispatchInt,
	WrPreempted,
	WrYieldExecution,
	WrFastMutex,
	WrGuardedMutex,
	WrRundown,
	MaximumWaitReason
} KWAIT_REASON;
typedef struct _SYSTEM_THREADS {
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PVOID StartAddress;
	CLIENT_ID ClientId;
	KPRIORITY Priority;
	KPRIORITY BasePriority;
	ULONG ContextSwitchCount;
	ULONG State;
	KWAIT_REASON WaitReason;
} SYSTEM_THREADS, *PSYSTEM_THREADS; 
typedef struct _SYSTEM_PROCESSES { // Information Class 5
	ULONG NextEntryDelta;
	ULONG ThreadCount;
	ULONG Reserved1[6];
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ProcessName; 
	KPRIORITY BasePriority;
	ULONG ProcessId;
	ULONG InheritedFromProcessId;
	ULONG HandleCount;
	ULONG Reserved2[2];
	VM_COUNTERS VmCounters;
	IO_COUNTERS IoCounters; // Windows 2000 only
	SYSTEM_THREADS Threads[1];
} SYSTEM_PROCESSES, *PSYSTEM_PROCESSES;
typedef struct _SYSTEM_THREAD_INFORMATION {
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG         WaitTime;
	PVOID         StartAddress;
	CLIENT_ID     ClientId;
	KPRIORITY     Priority;
	KPRIORITY     BasePriority;
	ULONG         ContextSwitchCount;
	LONG          State;
	LONG          WaitReason;
} SYSTEM_THREAD_INFORMATION, * PSYSTEM_THREAD_INFORMATION;
typedef struct _SYSTEM_PROCESS_INFORMATION {
	ULONG             NextEntryDelta;
	ULONG             ThreadCount;
	ULONG             Reserved1[6];
	LARGE_INTEGER     CreateTime;
	LARGE_INTEGER     UserTime;
	LARGE_INTEGER     KernelTime;
	UNICODE_STRING    ProcessName;
	KPRIORITY         BasePriority;
	ULONG             ProcessId;
	ULONG             InheritedFromProcessId;
	ULONG             HandleCount;
	ULONG             Reserved2[2];
	VM_COUNTERS       VmCounters;
#if _WIN32_WINNT >= 0x500
	IO_COUNTERS       IoCounters;
#endif
	SYSTEM_THREAD_INFORMATION Threads[1];
} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;

typedef __success(return >= 0) LONG NTSTATUS, *PNTSTATUS;


typedef struct _PEB_LDR_DATA
 {
     ULONG Length;
     BOOLEAN Initialized;
     HANDLE SsHandle;
     LIST_ENTRY InLoadOrderModuleList;
     LIST_ENTRY InMemoryOrderModuleList;
     LIST_ENTRY InInitializationOrderModuleList;
     PVOID EntryInProgress;
     BOOLEAN ShutdownInProgress;
     HANDLE ShutdownThreadId;
 } PEB_LDR_DATA, *PPEB_LDR_DATA;
typedef struct _LSA_UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength/2), length_is(Length/2)]
#endif // MIDL_PASS
	PWSTR  Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING;
typedef struct _LSA_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PCHAR Buffer;
} LSA_STRING, *PLSA_STRING;
#ifndef _NTDEF_
typedef LSA_STRING STRING, *PSTRING ;
#endif
#define RTL_MAX_DRIVE_LETTERS 32
#define RTL_DRIVE_LETTER_VALID (USHORT)0x0001
typedef struct _CURDIR
{
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURDIR, *PCURDIR; 
typedef struct _RTL_DRIVE_LETTER_CURDIR
{
     USHORT Flags;
     USHORT Length;
     ULONG TimeStamp;
     STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;
typedef struct _RTL_USER_PROCESS_PARAMETERS
{
     ULONG MaximumLength;
     ULONG Length;
 
     ULONG Flags;
     ULONG DebugFlags;
 
     HANDLE ConsoleHandle;
     ULONG ConsoleFlags;
	 HANDLE StandardInput;
     HANDLE StandardOutput;
     HANDLE StandardError;
 
     CURDIR CurrentDirectory;
     UNICODE_STRING DllPath;
     UNICODE_STRING ImagePathName;
     UNICODE_STRING CommandLine;
     PVOID Environment;
 
     ULONG StartingX;
     ULONG StartingY;
     ULONG CountX;
     ULONG CountY;
     ULONG CountCharsX;
     ULONG CountCharsY;
     ULONG FillAttribute;
 
     ULONG WindowFlags;
     ULONG ShowWindowFlags;
     UNICODE_STRING WindowTitle;
     UNICODE_STRING DesktopInfo;
     UNICODE_STRING ShellInfo;
     UNICODE_STRING RuntimeData;
     RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];
 
     ULONG EnvironmentSize;
     ULONG EnvironmentVersion;
     PVOID PackageDependencyData;
     ULONG ProcessGroupId;
     ULONG LoaderThreads;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _RTL_USER_PROCESS_PARAMETERS *PRTL_USER_PROCESS_PARAMETERS;
typedef struct _RTL_CRITICAL_SECTION *PRTL_CRITICAL_SECTION;

#define GDI_HANDLE_BUFFER_SIZE32 34
#define GDI_HANDLE_BUFFER_SIZE64 60

#ifndef _WIN64
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#else
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#endif
 
typedef ULONG GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];
 
typedef ULONG GDI_HANDLE_BUFFER32[GDI_HANDLE_BUFFER_SIZE32];
typedef ULONG GDI_HANDLE_BUFFER64[GDI_HANDLE_BUFFER_SIZE64];
// symbols
typedef struct _PEB
{
     BOOLEAN InheritedAddressSpace;
     BOOLEAN ReadImageFileExecOptions;
     BOOLEAN BeingDebugged;
     union
     {
         BOOLEAN BitField;
         struct
         {
             BOOLEAN ImageUsesLargePages : 1;
             BOOLEAN IsProtectedProcess : 1;
             BOOLEAN IsImageDynamicallyRelocated : 1;
             BOOLEAN SkipPatchingUser32Forwarders : 1;
             BOOLEAN IsPackagedProcess : 1;
             BOOLEAN IsAppContainer : 1;
             BOOLEAN IsProtectedProcessLight : 1;
             BOOLEAN SpareBits : 1;
         };
     };
     HANDLE Mutant;
 
     PVOID ImageBaseAddress;
     PPEB_LDR_DATA Ldr;
     PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
     PVOID SubSystemData;
     PVOID ProcessHeap;
     PRTL_CRITICAL_SECTION FastPebLock;
     PVOID AtlThunkSListPtr;
     PVOID IFEOKey;
     union
     {
         ULONG CrossProcessFlags;
         struct
         {
             ULONG ProcessInJob : 1;
             ULONG ProcessInitializing : 1;
             ULONG ProcessUsingVEH : 1;
             ULONG ProcessUsingVCH : 1;
             ULONG ProcessUsingFTH : 1;
             ULONG ReservedBits0 : 27;
         };
         ULONG EnvironmentUpdateCount;
     };
     union
     {
         PVOID KernelCallbackTable;
         PVOID UserSharedInfoPtr;
     };
     ULONG SystemReserved[1];
     ULONG AtlThunkSListPtr32;
     PVOID ApiSetMap;
     ULONG TlsExpansionCounter;
     PVOID TlsBitmap;
     ULONG TlsBitmapBits[2];
     PVOID ReadOnlySharedMemoryBase;
     PVOID HotpatchInformation;
     PVOID *ReadOnlyStaticServerData;
     PVOID AnsiCodePageData;
     PVOID OemCodePageData;
     PVOID UnicodeCaseTableData;
 
     ULONG NumberOfProcessors;
     ULONG NtGlobalFlag;
 
     LARGE_INTEGER CriticalSectionTimeout;
     SIZE_T HeapSegmentReserve;
     SIZE_T HeapSegmentCommit;
     SIZE_T HeapDeCommitTotalFreeThreshold;
     SIZE_T HeapDeCommitFreeBlockThreshold;
 
     ULONG NumberOfHeaps;
     ULONG MaximumNumberOfHeaps;
     PVOID *ProcessHeaps;
 
     PVOID GdiSharedHandleTable;
     PVOID ProcessStarterHelper;
     ULONG GdiDCAttributeList;
 
     PRTL_CRITICAL_SECTION LoaderLock;
 
     ULONG OSMajorVersion;
     ULONG OSMinorVersion;
     USHORT OSBuildNumber;
     USHORT OSCSDVersion;
     ULONG OSPlatformId;
     ULONG ImageSubsystem;
     ULONG ImageSubsystemMajorVersion;
     ULONG ImageSubsystemMinorVersion;
     ULONG_PTR ImageProcessAffinityMask;
     GDI_HANDLE_BUFFER GdiHandleBuffer;
     PVOID PostProcessInitRoutine;
 
     PVOID TlsExpansionBitmap;
     ULONG TlsExpansionBitmapBits[32];
 
     ULONG SessionId;
 
     ULARGE_INTEGER AppCompatFlags;
     ULARGE_INTEGER AppCompatFlagsUser;
     PVOID pShimData;
     PVOID AppCompatInfo;
 
     UNICODE_STRING CSDVersion;
 
     PVOID ActivationContextData;
     PVOID ProcessAssemblyStorageMap;
     PVOID SystemDefaultActivationContextData;
     PVOID SystemAssemblyStorageMap;
 
     SIZE_T MinimumStackCommit;
 
     PVOID *FlsCallback;
     LIST_ENTRY FlsListHead;
     PVOID FlsBitmap;
     ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
     ULONG FlsHighIndex;
 
     PVOID WerRegistrationData;
     PVOID WerShipAssertPtr;
     PVOID pContextData;
     PVOID pImageHeaderHash;
     union
     {
         ULONG TracingFlags;
         struct
         {
             ULONG HeapTracingEnabled : 1;
             ULONG CritSecTracingEnabled : 1;
             ULONG LibLoaderTracingEnabled : 1;
             ULONG SpareTracingBits : 29;
         };
     };
     ULONGLONG CsrServerReadOnlySharedMemoryBase;
 } PEB, *PPEB;
 
 #define GDI_BATCH_BUFFER_SIZE 310
 
 typedef struct _GDI_TEB_BATCH
 {
     ULONG Offset;
     ULONG_PTR HDC;
     ULONG Buffer[GDI_BATCH_BUFFER_SIZE];
 } GDI_TEB_BATCH, *PGDI_TEB_BATCH;

 typedef struct _TEB_ACTIVE_FRAME_CONTEXT
 {
     ULONG Flags;
     PSTR FrameName;
 } TEB_ACTIVE_FRAME_CONTEXT, *PTEB_ACTIVE_FRAME_CONTEXT;
 
 typedef struct _TEB_ACTIVE_FRAME
 {
     ULONG Flags;
     struct _TEB_ACTIVE_FRAME *Previous;
     PTEB_ACTIVE_FRAME_CONTEXT Context;
 } TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;
 typedef struct _PROCESSOR_NUMBER {
	 WORD Group;
	 BYTE Number;
	 BYTE Reserved;
 } PROCESSOR_NUMBER, *PPROCESSOR_NUMBER;
 typedef struct _TEB
 {
     NT_TIB NtTib;
 
     PVOID EnvironmentPointer;
     CLIENT_ID ClientId;
     PVOID ActiveRpcHandle;
     PVOID ThreadLocalStoragePointer;
     PPEB ProcessEnvironmentBlock;
 
     ULONG LastErrorValue;
     ULONG CountOfOwnedCriticalSections;
     PVOID CsrClientThread;
     PVOID Win32ThreadInfo;
     ULONG User32Reserved[26];
     ULONG UserReserved[5];
     PVOID WOW32Reserved;
     LCID CurrentLocale;
     ULONG FpSoftwareStatusRegister;
     PVOID SystemReserved1[54];
     NTSTATUS ExceptionCode;
     PVOID ActivationContextStackPointer;
 #ifdef _WIN64
     UCHAR SpareBytes[24];
 #else
     UCHAR SpareBytes[36];
 #endif
     ULONG TxFsContext;
 
     GDI_TEB_BATCH GdiTebBatch;
     CLIENT_ID RealClientId;
     HANDLE GdiCachedProcessHandle;
     ULONG GdiClientPID;
     ULONG GdiClientTID;
     PVOID GdiThreadLocalInfo;
     ULONG_PTR Win32ClientInfo[62];
     PVOID glDispatchTable[233];
     ULONG_PTR glReserved1[29];
     PVOID glReserved2;
     PVOID glSectionInfo;
     PVOID glSection;
     PVOID glTable;
     PVOID glCurrentRC;
     PVOID glContext;
 
     NTSTATUS LastStatusValue;
     UNICODE_STRING StaticUnicodeString;
     WCHAR StaticUnicodeBuffer[261];
 
     PVOID DeallocationStack;
     PVOID TlsSlots[64];
     LIST_ENTRY TlsLinks;
 
     PVOID Vdm;
     PVOID ReservedForNtRpc;
     PVOID DbgSsReserved[2];
 
     ULONG HardErrorMode;
 #ifdef _WIN64
     PVOID Instrumentation[11];
 #else
     PVOID Instrumentation[9];
 #endif
     GUID ActivityId;
 
     PVOID SubProcessTag;
     PVOID EtwLocalData;
     PVOID EtwTraceData;
     PVOID WinSockData;
     ULONG GdiBatchCount;
 
     union
     {
         PROCESSOR_NUMBER CurrentIdealProcessor;
         ULONG IdealProcessorValue;
         struct
         {
             UCHAR ReservedPad0;
             UCHAR ReservedPad1;
             UCHAR ReservedPad2;
             UCHAR IdealProcessor;
         };
     };
 
     ULONG GuaranteedStackBytes;
     PVOID ReservedForPerf;
     PVOID ReservedForOle;
     ULONG WaitingOnLoaderLock;
     PVOID SavedPriorityState;
     ULONG_PTR SoftPatchPtr1;
     PVOID ThreadPoolData;
     PVOID *TlsExpansionSlots;
 #ifdef _WIN64
     PVOID DeallocationBStore;
     PVOID BStoreLimit;
 #endif
     ULONG MuiGeneration;
     ULONG IsImpersonating;
     PVOID NlsCache;
     PVOID pShimData;
     ULONG HeapVirtualAffinity;
     HANDLE CurrentTransactionHandle;
     PTEB_ACTIVE_FRAME ActiveFrame;
     PVOID FlsData;
 
     PVOID PreferredLanguages;
     PVOID UserPrefLanguages;
     PVOID MergedPrefLanguages;
     ULONG MuiImpersonation;
 
     union
     {
         USHORT CrossTebFlags;
         USHORT SpareCrossTebBits : 16;
     };
     union
     {
         USHORT SameTebFlags;
         struct
         {
             USHORT SafeThunkCall : 1;
             USHORT InDebugPrint : 1;
             USHORT HasFiberData : 1;
             USHORT SkipThreadAttach : 1;
             USHORT WerInShipAssertCode : 1;
             USHORT RanProcessInit : 1;
             USHORT ClonedThread : 1;
             USHORT SuppressDebugMsg : 1;
             USHORT DisableUserStackWalk : 1;
             USHORT RtlExceptionAttached : 1;
             USHORT InitialThread : 1;
             USHORT SessionAware : 1;
             USHORT SpareSameTebBits : 4;
         };
     };
 
     PVOID TxnScopeEnterCallback;
     PVOID TxnScopeExitCallback;
     PVOID TxnScopeContext;
     ULONG LockCount;
     ULONG SpareUlong0;
     PVOID ResourceRetValue;
     PVOID ReservedForWdf;
} TEB, *PTEB;

typedef struct _PROCESS_BASIC_INFORMATION { // Information Class 0
	NTSTATUS ExitStatus;
	PPEB PebBaseAddress;
	KAFFINITY AffinityMask;
	KPRIORITY BasePriority;
	ULONG UniqueProcessId;
	ULONG InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION, *PPROCESS_BASIC_INFORMATION;
//funcs

typedef 
NTSYSAPI
NTSTATUS
(NTAPI *ZwQuerySystemInformation_ptr)(
									  IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
									  IN OUT PVOID SystemInformation,
									  IN ULONG SystemInformationLength,
									  OUT PULONG ReturnLength OPTIONAL
									  );
typedef
NTSYSAPI
NTSTATUS
(NTAPI *ZwQueryInformationProcess_ptr)(
						  IN HANDLE ProcessHandle,
						  IN PROCESSINFOCLASS ProcessInformationClass,
						  OUT PVOID ProcessInformation,
						  IN ULONG ProcessInformationLength,
						  OUT PULONG ReturnLength OPTIONAL
						  );
#endif