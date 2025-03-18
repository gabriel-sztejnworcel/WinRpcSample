#pragma comment(lib, "Rpcrt4.lib")
#pragma comment(lib, "RpcStubs.lib")

#include "Calculator.h"
#include <iostream>

void CheckStatus(RPC_STATUS status, const wchar_t* function)
{
    if (status != RPC_S_OK)
    {
        wprintf(L"%s failed with status code: %d\n", function, status);
        exit(1);
    }
}

void CheckHResult(HRESULT hr, const wchar_t* function)
{
    if (hr != S_OK)
    {
        wprintf(L"%s failed with status code: %d\n", function, hr);
        exit(1);
    }
}

int wmain(int argc, wchar_t* argv[])
{
    auto protseq = L"ncacn_np";
    auto endpoint = L"\\pipe\\RpcDemo";

    RPC_STATUS status = RpcServerUseProtseqEp(
        (RPC_WSTR)protseq,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        (RPC_WSTR)endpoint,
        nullptr);

    CheckStatus(status, L"RpcServerUseProtseqEp");

    status = RpcServerRegisterIf(
        s_Calculator_v1_0_s_ifspec,
        nullptr,
        nullptr);

    CheckStatus(status, L"RpcServerRegisterIf");

    status = RpcServerListen(
        1,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        FALSE);

    CheckStatus(status, L"RpcServerListen");
}

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR* ptr)
{
    free(ptr);
}

HRESULT s_Add(
    /* [in] */ handle_t IDL_handle,
    /* [in] */ long a,
    /* [in] */ long b,
    /* [retval][out] */ long* result)
{
    wprintf(L"Client called s_Add\n");
    *result = a + b;
    return 0;
}

HRESULT s_Subtract(
    /* [in] */ handle_t IDL_handle,
    /* [in] */ long a,
    /* [in] */ long b,
    /* [retval][out] */ long* result)
{
    wprintf(L"Client called s_Subtract\n");
    *result = a - b;
    return 0;
}

HRESULT s_Multiply(
    /* [in] */ handle_t IDL_handle,
    /* [in] */ long a,
    /* [in] */ long b,
    /* [retval][out] */ long* result)
{
    wprintf(L"Client called s_Multiply\n");
    *result = a * b;
    return 0;
}

HRESULT s_Divide(
    /* [in] */ handle_t IDL_handle,
    /* [in] */ long a,
    /* [in] */ long b,
    /* [retval][out] */ long* result)
{
    wprintf(L"Client called s_Divide\n");
    *result = a / b;
    return 0;
}
