#include <ntifs.h>
#include <intrin.h>
#include "..\Includes\ByePg.h"

#define Log(...) DbgPrintEx( DPFLTR_SYSTEM_ID, DPFLTR_ERROR_LEVEL, "[ByePg] " __VA_ARGS__ )

void EntryPoint()
{
	BOOLEAN Hypervisor = false;

		NTSTATUS Status = ByePgInitialize([](CONTEXT* ContextRecord, EXCEPTION_RECORD* ExceptionRecord) -> LONG
		{
			if ( ExceptionRecord->ExceptionCode == STATUS_BREAKPOINT )
			//if(ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION)
			{
				Log("DESCARTANDO #BP en RIP = %p, ID Procesador: %d!\n", ContextRecord->Rip, KeGetCurrentProcessorIndex() );

				// Continue execution
				ContextRecord->Rip++;

				return EXCEPTION_CONTINUE_EXECUTION;
			}
			return EXCEPTION_EXECUTE_HANDLER;
		}, TRUE );

		if (NT_SUCCESS(Status))
		{
			//BIT 0->VME [VIRTUAL MODE EXTENSION 8086]

			__writecr4(__readcr4() | (0 << 13));
			__debugbreak();

	 }
	   else
	   {
		   Log("FALLO: %x\n", Status );
	   } 
   }
