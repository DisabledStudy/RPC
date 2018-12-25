#include <rpc.h>
#include <cstdio>

extern "C" void PrintMessage(const char * message)
{
	printf("%s\n", message);
}

/* add this function to hellop.c */
extern "C" void Shutdown(void)
{
	RPC_STATUS status;

	status = RpcMgmtStopServerListening(NULL);

	if (status)
	{
		exit(status);
	}

	status = RpcServerUnregisterIf(NULL, NULL, FALSE);

	if (status)
	{
		exit(status);
	}
} //end Shutdown