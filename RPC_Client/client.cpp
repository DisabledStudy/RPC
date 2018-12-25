#include <cstdlib>
#include <cstdio>
#include <cctype>

#include <windows.h>

#include "../CustomFunction/CustomFunction.h" 

void main()
{
	RPC_STATUS status;
	RPC_WSTR pszStringBinding = NULL;
	unsigned long ulCode;
	RPC_WSTR protocol = reinterpret_cast<RPC_WSTR>(const_cast<LPWSTR>(L"ncacn_np"));
	RPC_WSTR endPoint = reinterpret_cast<RPC_WSTR>(const_cast<LPWSTR>(L"\\pipe\\hello"));
	const char* message = "hello world!";

	status = RpcStringBindingCompose(NULL,
		protocol,
		NULL,
		endPoint,
		NULL,
		&pszStringBinding);

	if (status){
		exit(status);
	}

	status = RpcBindingFromStringBinding(pszStringBinding, &customFunction_IfHandle);

	if (status){
		exit(status);
	}
	
	RpcTryExcept
	{
		PrintMessage(message);
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

	status = RpcBindingFree(&customFunction_IfHandle);
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
