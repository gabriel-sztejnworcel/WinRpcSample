#pragma comment(lib, "Rpcrt4.lib")
#pragma comment(lib, "RpcStubs.lib")

#include "Calculator.h"

int wmain(int argc, wchar_t* argv[])
{
    auto protseq = L"ncacn_np";
    auto endpoint = L"\\pipe\\RpcDemo";
    wchar_t* address = nullptr;

    RPC_WSTR stringBinding = nullptr;
    RPC_STATUS status = RpcStringBindingCompose(
        nullptr,
        (RPC_WSTR)protseq,
        (RPC_WSTR)address,
        (RPC_WSTR)endpoint,
        nullptr,
        &stringBinding);

    // Error handling

    handle_t clientBindingHandle = nullptr;
    status = RpcBindingFromStringBinding(stringBinding, &clientBindingHandle);
    // Error handling

    RpcTryExcept
    {
        long a = 10;
        long b = 20;
        long result = 0;

        HRESULT hr = c_Add(clientBindingHandle, a, b, &result);
        // Error handling
        // Print result

        hr = c_Subtract(clientBindingHandle, a, b, &result);
        // Error handling
        // Print result

        hr = c_Multiply(clientBindingHandle, a, b, &result);
        // Error handling
        // Print result

        hr = c_Divide(clientBindingHandle, a, b, &result);
        // Error handling
        // Print result

    }
    RpcExcept(1)
    {
        // Error handling
    }
    RpcEndExcept

    status = RpcStringFree(&stringBinding);
    // Error handling

    status = RpcBindingFree(&clientBindingHandle);
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
