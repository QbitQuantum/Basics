static NTSTATUS PhNetworkPingThreadStart(
    _In_ PVOID Parameter
    )
{
    HANDLE icmpHandle = INVALID_HANDLE_VALUE;
    ULONG icmpCurrentPingMs = 0;
    ULONG icmpCurrentPingTtl = 0;
    ULONG icmpReplyCount = 0;
    ULONG icmpReplyLength = 0;
    PVOID icmpReplyBuffer = NULL;
    PPH_STRING phVersion = NULL;
    PPH_BYTES icmpEchoBuffer = NULL;
    IP_OPTION_INFORMATION pingOptions =
    {
        255,         // Time To Live
        0,           // Type Of Service
        IP_FLAG_DF,  // IP header flags
        0            // Size of options data
    };

    PNETWORK_OUTPUT_CONTEXT context = (PNETWORK_OUTPUT_CONTEXT)Parameter;

    __try
    {
        // Query PH version.
        if ((phVersion = PhGetPhVersion()) == NULL)
            __leave;

        // Create ICMP echo buffer.
        if ((icmpEchoBuffer = PhFormatAnsiString("processhacker_%S_0x0D06F00D_x1", phVersion->Buffer)) == NULL)
            __leave;

        if (context->IpAddress.Type == PH_IPV6_NETWORK_TYPE)
        {
            SOCKADDR_IN6 icmp6LocalAddr = { 0 };
            SOCKADDR_IN6 icmp6RemoteAddr = { 0 };
            PICMPV6_ECHO_REPLY icmp6ReplyStruct = NULL;

            // Create ICMPv6 handle.
            if ((icmpHandle = Icmp6CreateFile()) == INVALID_HANDLE_VALUE)
                __leave;

            // Set Local IPv6-ANY address.
            icmp6LocalAddr.sin6_addr = in6addr_any;
            icmp6LocalAddr.sin6_family = AF_INET6;

            // Set Remote IPv6 address.
            icmp6RemoteAddr.sin6_addr = context->IpAddress.In6Addr;
            icmp6RemoteAddr.sin6_port = _byteswap_ushort((USHORT)context->NetworkItem->RemoteEndpoint.Port);

            // Allocate ICMPv6 message.
            icmpReplyLength = ICMP_BUFFER_SIZE(sizeof(ICMPV6_ECHO_REPLY), icmpEchoBuffer);
            icmpReplyBuffer = PhAllocate(icmpReplyLength);
            memset(icmpReplyBuffer, 0, icmpReplyLength);

            InterlockedIncrement(&context->PingSentCount);

            // Send ICMPv6 ping...
            icmpReplyCount = Icmp6SendEcho2(
                icmpHandle,
                NULL,
                NULL,
                NULL,
                &icmp6LocalAddr,
                &icmp6RemoteAddr,
                icmpEchoBuffer->Buffer,
                (USHORT)icmpEchoBuffer->Length,
                &pingOptions,
                icmpReplyBuffer,
                icmpReplyLength,
                context->MaxPingTimeout
                );

            icmp6ReplyStruct = (PICMPV6_ECHO_REPLY)icmpReplyBuffer;
            if (icmpReplyCount > 0 && icmp6ReplyStruct)
            {
                BOOLEAN icmpPacketSignature = FALSE;

                if (icmp6ReplyStruct->Status != IP_SUCCESS)
                {
                    InterlockedIncrement(&context->PingLossCount);
                }

                if (_memicmp(
                    icmp6ReplyStruct->Address.sin6_addr,
                    context->IpAddress.In6Addr.u.Word,
                    sizeof(icmp6ReplyStruct->Address.sin6_addr)
                    ) != 0)
                {
                    InterlockedIncrement(&context->UnknownAddrCount);
                }

                //if (icmp6ReplyStruct->DataSize == icmpEchoBuffer->MaximumLength)
                //{
                //    icmpPacketSignature = (_memicmp(
                //        icmpEchoBuffer->Buffer,
                //        icmp6ReplyStruct->Data,
                //        icmp6ReplyStruct->DataSize
                //        ) == 0);
                //}

                //if (icmpPacketSignature != TRUE)
                //{
                //    InterlockedIncrement(&context->HashFailCount);
                //}

                icmpCurrentPingMs = icmp6ReplyStruct->RoundTripTime;
                //icmpCurrentPingTtl = icmp6ReplyStruct->Options.Ttl;
            }
            else
            {
                InterlockedIncrement(&context->PingLossCount);
            }
        }
        else
        {
            IPAddr icmpLocalAddr = 0;
            IPAddr icmpRemoteAddr = 0;
            PICMP_ECHO_REPLY icmpReplyStruct = NULL;

            // Create ICMPv4 handle.
            if ((icmpHandle = IcmpCreateFile()) == INVALID_HANDLE_VALUE)
                __leave;

            // Set Local IPv4-ANY address.
            icmpLocalAddr = in4addr_any.s_addr;

            // Set Remote IPv4 address.
            icmpRemoteAddr = context->IpAddress.InAddr.s_addr;

            // Allocate ICMPv4 message.
            icmpReplyLength = ICMP_BUFFER_SIZE(sizeof(ICMP_ECHO_REPLY), icmpEchoBuffer);
            icmpReplyBuffer = PhAllocate(icmpReplyLength);
            memset(icmpReplyBuffer, 0, icmpReplyLength);

            InterlockedIncrement(&context->PingSentCount);

            // Send ICMPv4 ping...
            //if (WindowsVersion > WINDOWS_VISTA)
            //{
            //    // Vista SP1 and up we can specify the source address:
            //    icmpReplyCount = IcmpSendEcho2Ex(
            //        icmpHandle,
            //        NULL,
            //        NULL,
            //        NULL,
            //        icmpLocalAddr,
            //        icmpRemoteAddr,
            //        icmpEchoBuffer->Buffer,
            //        icmpEchoBuffer->MaximumLength,
            //        &pingOptions,
            //        icmpReplyBuffer,
            //        icmpReplyLength,
            //        context->MaxPingTimeout
            //        );
            //}

            icmpReplyCount = IcmpSendEcho2(
                icmpHandle,
                NULL,
                NULL,
                NULL,
                icmpRemoteAddr,
                icmpEchoBuffer->Buffer,
                (USHORT)icmpEchoBuffer->Length,
                &pingOptions,
                icmpReplyBuffer,
                icmpReplyLength,
                context->MaxPingTimeout
                );

            icmpReplyStruct = (PICMP_ECHO_REPLY)icmpReplyBuffer;

            if (icmpReplyStruct && icmpReplyCount > 0)
            {
                BOOLEAN icmpPacketSignature = FALSE;

                if (icmpReplyStruct->Status != IP_SUCCESS)
                {
                    InterlockedIncrement(&context->PingLossCount);
                }

                if (icmpReplyStruct->Address != context->IpAddress.InAddr.s_addr)
                {
                    InterlockedIncrement(&context->UnknownAddrCount);
                }

                if (icmpReplyStruct->DataSize == icmpEchoBuffer->Length)
                {
                    icmpPacketSignature = (_memicmp(
                        icmpEchoBuffer->Buffer,
                        icmpReplyStruct->Data,
                        icmpReplyStruct->DataSize
                        ) == 0);
                }

                icmpCurrentPingMs = icmpReplyStruct->RoundTripTime;
                icmpCurrentPingTtl = icmpReplyStruct->Options.Ttl;

                if (!icmpPacketSignature)
                {
                    InterlockedIncrement(&context->HashFailCount);
                }
            }
            else
            {
                InterlockedIncrement(&context->PingLossCount);
            }
        }

        InterlockedIncrement(&context->PingRecvCount);

        if (context->PingMinMs == 0 || icmpCurrentPingMs < context->PingMinMs)
            context->PingMinMs = icmpCurrentPingMs;
        if (icmpCurrentPingMs > context->PingMaxMs)
            context->PingMaxMs = icmpCurrentPingMs;

        context->CurrentPingMs = icmpCurrentPingMs;

        PhAddItemCircularBuffer_ULONG(&context->PingHistory, icmpCurrentPingMs);
    }
    __finally
    {
        if (phVersion)
        {
            PhDereferenceObject(phVersion);
        }

        if (icmpEchoBuffer)
        {
            PhDereferenceObject(icmpEchoBuffer);
        }

        if (icmpHandle != INVALID_HANDLE_VALUE)
        {
            IcmpCloseHandle(icmpHandle);
        }

        if (icmpReplyBuffer)
        {
            PhFree(icmpReplyBuffer);
        }
    }

    PostMessage(context->WindowHandle, WM_PING_UPDATE, 0, 0);

    return STATUS_SUCCESS;
}