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
    wchar_t* address = nullptr;

    if (argc > 1)
    {
        address = argv[1];
    }

    RPC_WSTR stringBinding = nullptr;
    RPC_STATUS status = RpcStringBindingCompose(
        nullptr,
        (RPC_WSTR)protseq,
        (RPC_WSTR)address,
        (RPC_WSTR)endpoint,
        nullptr,
        &stringBinding);

    CheckStatus(status, L"RpcStringBindingCompose");

    handle_t clientBindingHandle = nullptr;

    status = RpcBindingFromStringBinding(
        stringBinding,
        &clientBindingHandle);

    CheckStatus(status, L"RpcBindingFromStringBinding");

    __try
    {
        long a = 10;
        long b = 20;
        long result = 0;

        HRESULT hr = c_Add(clientBindingHandle, a, b, &result);
        CheckHResult(hr, L"c_Add");
        wprintf(L"c_Add(%d, %d) = %d\n", a, b, result);

        hr = c_Subtract(clientBindingHandle, a, b, &result);
        CheckHResult(hr, L"c_Subtract");
        wprintf(L"c_Subtract(%d, %d) = %d\n", a, b, result);
        
        hr = c_Multiply(clientBindingHandle, a, b, &result);
        CheckHResult(hr, L"c_Multiply");
        wprintf(L"c_Multiply(%d, %d) = %d\n", a, b, result);

        hr = c_Divide(clientBindingHandle, a, b, &result);
        CheckHResult(hr, L"c_Divide");
        wprintf(L"c_Divide(%d, %d) = %d\n", a, b, result);

    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        wprintf(L"RPC exception: %d\n", GetExceptionCode());
        exit(1);
    }

    status = RpcStringFree(&stringBinding);
    CheckStatus(status, L"RpcStringFree");

    status = RpcBindingFree(&clientBindingHandle);
    CheckStatus(status, L"RpcBindingFree");
}

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR* ptr)
{
    free(ptr);
}
