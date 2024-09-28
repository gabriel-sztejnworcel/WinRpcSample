#pragma comment(lib, "Rpcrt4.lib")
#pragma comment(lib, "RpcStubs.lib")

#include "Calculator.h"

int wmain(int argc, wchar_t* argv[])
{
    auto protseq = L"ncacn_np";
    auto endpoint = L"\\pipe\\RpcDemo";

    RPC_STATUS status = RpcServerUseProtseqEp(
        (RPC_WSTR)protseq,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        (RPC_WSTR)endpoint,
        nullptr);

    // Error handling

    status = RpcServerRegisterIf(
        s_Calculator_v1_0_s_ifspec,
        nullptr,
        nullptr);

    // Error handling

    status = RpcServerListen(
        1,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        FALSE);

    // Error handling
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
    *result = a + b;
    return 0;
}

HRESULT s_Subtract(
    /* [in] */ handle_t IDL_handle,
    /* [in] */ long a,
    /* [in] */ long b,
    /* [retval][out] */ long* result)
{
    *result = a - b;
    return 0;
}

HRESULT s_Multiply(
    /* [in] */ handle_t IDL_handle,
    /* [in] */ long a,
    /* [in] */ long b,
    /* [retval][out] */ long* result)
{
    *result = a * b;
    return 0;
}

HRESULT s_Divide(
    /* [in] */ handle_t IDL_handle,
    /* [in] */ long a,
    /* [in] */ long b,
    /* [retval][out] */ long* result)
{
    *result = a / b;
    return 0;
}
