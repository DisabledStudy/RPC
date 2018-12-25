#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "hello.h" 
#include <windows.h>

void main()
{
	RPC_STATUS status;
	unsigned char * pszUuid = NULL;
	unsigned char * pszNetworkAddress = NULL;
	unsigned char * pszOptions = NULL;
	RPC_WSTR pszStringBinding = NULL;
	unsigned long ulCode;
	RPC_WSTR protocol = reinterpret_cast<RPC_WSTR>(const_cast<LPWSTR>(L"ncacn_np"));
	RPC_WSTR endPoint = reinterpret_cast<RPC_WSTR>(const_cast<LPWSTR>(L"\\pipe\\hello"));
	unsigned char message = '1';

	status = RpcStringBindingCompose(NULL,
		protocol,
		NULL,
		endPoint,
		NULL,
		&pszStringBinding);

	if (status){
		exit(status);
	}

	RPC_WSTR stringBinding = nullptr;

	status = RpcBindingFromStringBinding(pszStringBinding, &hello_IfHandle);
	//status = RpcBindingFromStringBinding(NULL, &hello_v1_0_c_ifspec);

	if (status){
		exit(status);
	}

	RpcTryExcept
	{
		HelloProc(&message);
		Shutdown();
	}
		RpcExcept(1)
	{
		ulCode = RpcExceptionCode();
		printf("Runtime reported exception 0x%lx = %ld\n", ulCode, ulCode);
	}
	RpcEndExcept

		status = RpcStringFree(&pszStringBinding);
	if (status){
		exit(status);
	}

	status = RpcBindingFree(&hello_IfHandle);
	if (status){
		exit(status);
	}

	exit(0);
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
