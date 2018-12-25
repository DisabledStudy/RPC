/* file: hellos.c */
#include <cstdlib>
#include <cstdio>

#include <windows.h>

#include "../CustomFunction/CustomFunction.h" 

void main()
{
	RPC_STATUS status;
	RPC_WSTR protocol = reinterpret_cast<RPC_WSTR>(const_cast<LPWSTR>(L"ncacn_np"));
	RPC_WSTR endPoint = reinterpret_cast<RPC_WSTR>(const_cast<LPWSTR>(L"\\pipe\\hello"));
	unsigned char * pszSecurity = NULL;
	unsigned int    cMinCalls = 1;
	unsigned int    fDontWait = FALSE;

	status = RpcServerUseProtseqEp(protocol,
		RPC_C_LISTEN_MAX_CALLS_DEFAULT,
		endPoint,
		pszSecurity);

	if (status) {
		exit(status);
	}

	status = RpcServerRegisterIf(CustomFunction_v1_0_s_ifspec,
		NULL,
		NULL);

	if (status) {
		exit(status);
	}

	status = RpcServerListen(cMinCalls,
		RPC_C_LISTEN_MAX_CALLS_DEFAULT,
		fDontWait);

	if (status) {
		exit(status);
	}
}

/******************************************************/
/*         MIDL allocate and free                     */
/******************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
	return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
	free(ptr);
}