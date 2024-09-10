static void test_endpoint_mapper(RPC_CSTR protseq, RPC_CSTR address)
{
    static unsigned char annotation[] = "Test annotation string.";
    RPC_STATUS status;
    RPC_BINDING_VECTOR *binding_vector;
    handle_t handle;
    unsigned char *binding;

    status = RpcServerRegisterIf(IFoo_v0_0_s_ifspec, NULL, NULL);
    ok(status == RPC_S_OK, "%s: RpcServerRegisterIf failed (%u)\n", protseq, status);

    status = RpcServerInqBindings(&binding_vector);
    ok(status == RPC_S_OK, "%s: RpcServerInqBindings failed with error %u\n", protseq, status);

    /* register endpoints created in test_RpcServerUseProtseq */
    status = RpcEpRegisterA(IFoo_v0_0_s_ifspec, binding_vector, NULL, annotation);
    ok(status == RPC_S_OK, "%s: RpcEpRegisterA failed with error %u\n", protseq, status);
    /* reregister the same endpoint with no annotation */
    status = RpcEpRegisterA(IFoo_v0_0_s_ifspec, binding_vector, NULL, NULL);
    ok(status == RPC_S_OK, "%s: RpcEpRegisterA failed with error %u\n", protseq, status);

    status = RpcStringBindingComposeA(NULL, protseq, address,
                                     NULL, NULL, &binding);
    ok(status == RPC_S_OK, "%s: RpcStringBindingCompose failed (%u)\n", protseq, status);

    status = RpcBindingFromStringBindingA(binding, &handle);
    ok(status == RPC_S_OK, "%s: RpcBindingFromStringBinding failed (%u)\n", protseq, status);

    RpcStringFreeA(&binding);

    status = RpcBindingReset(handle);
    ok(status == RPC_S_OK, "%s: RpcBindingReset failed with error %u\n", protseq, status);

    status = RpcEpResolveBinding(handle, IFoo_v0_0_s_ifspec);
    ok(status == RPC_S_OK || broken(status == RPC_S_SERVER_UNAVAILABLE), /* win9x */
       "%s: RpcEpResolveBinding failed with error %u\n", protseq, status);

    status = RpcBindingReset(handle);
    ok(status == RPC_S_OK, "%s: RpcBindingReset failed with error %u\n", protseq, status);

    status = RpcBindingFree(&handle);
    ok(status == RPC_S_OK, "%s: RpcBindingFree failed with error %u\n", protseq, status);

    status = RpcServerUnregisterIf(NULL, NULL, FALSE);
    ok(status == RPC_S_OK, "%s: RpcServerUnregisterIf failed (%u)\n", protseq, status);

    status = RpcEpUnregister(IFoo_v0_0_s_ifspec, binding_vector, NULL);
    ok(status == RPC_S_OK, "%s: RpcEpUnregisterA failed with error %u\n", protseq, status);

    status = RpcBindingVectorFree(&binding_vector);
    ok(status == RPC_S_OK, "%s: RpcBindingVectorFree failed with error %u\n", protseq, status);
}