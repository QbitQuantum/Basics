int main()
{
    RPC_STATUS status;

    // Uses the protocol combined with the endpoint for receiving
    // remote procedure calls.
    status = RpcServerUseProtseqEp(
                 reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // Use TCP/IP protocol.
                 RPC_C_PROTSEQ_MAX_REQS_DEFAULT, // Backlog queue length for TCP/IP.
                 reinterpret_cast<unsigned char*>("4747"), // TCP/IP port to use.
                 NULL); // No security.

    if (status)
        exit(status);

    // Registers the Example1Explicit interface.
    status = RpcServerRegisterIf2(
                 Example1Explicit_v1_0_s_ifspec, // Interface to register.
                 NULL, // Use the MIDL generated entry-point vector.
                 NULL, // Use the MIDL generated entry-point vector.
                 RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH, // Forces use of security callback.
                 RPC_C_LISTEN_MAX_CALLS_DEFAULT, // Use default number of concurrent calls.
                 (unsigned)-1, // Infinite max size of incoming data blocks.
                 SecurityCallback); // Naive security callback.

    if (status)
        exit(status);

    // Start to listen for remote procedure calls for all registered interfaces.
    // This call will not return until RpcMgmtStopServerListening is called.
    status = RpcServerListen(
                 1, // Recommended minimum number of threads.
                 RPC_C_LISTEN_MAX_CALLS_DEFAULT, // Recommended maximum number of threads.
                 FALSE); // Start listening now.

    if (status)
        exit(status);
}