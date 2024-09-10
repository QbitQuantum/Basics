void CPythonEngine::backpipeMsgTick()
{
    init();
    enterCriticalSection();
    long int tm = GetTickCount();
    CMemReader& reader = CMemReader::getMemReader();
    CIpcMessage mess;

    if (CIPCBackPipe::readFromPipe(&mess, 1006))
    {
        int infoType;
        int chanType;
        int nickLen;
        int msgLen;
        char nickBuf[16384];
        char msgBuf[16384];
        char chanBuf[16384];

        memset(nickBuf, 0, 16384);
        memset(msgBuf, 0, 16384);
        memcpy(&infoType, mess.payload, sizeof(int));
        memcpy(&chanType, mess.payload + 4, sizeof(int));
        memcpy(&nickLen, mess.payload + 8, sizeof(int));
        memcpy(&msgLen, mess.payload + 12, sizeof(int));
        memcpy(nickBuf, mess.payload + 16, nickLen);
        memcpy(msgBuf, mess.payload + 16 + nickLen, msgLen);
        switch (infoType)
        {
        case 1:
            sprintf(chanBuf, "say");
            break;
        case 2:
            sprintf(chanBuf, "whisper");
            break;
        case 3:
            sprintf(chanBuf, "yell");
            break;
        case 11:
            sprintf(chanBuf, "NPC");
            break;
        case 6:
            sprintf(chanBuf, "private");
            break;
        case 7:
            sprintf(chanBuf, "channel");
            break;
        default:
            sprintf(chanBuf, "other[%d]", infoType);
            break;
        }
        //Channel IDs
        //1-Party
        //2-Own Chat Channel(premium)
        //3-Game Chat
        //4-English Channel
        //5-Trade
        //6-Rook Trade
        //7-Help

        int scriptNr;
        for (scriptNr = 0;; scriptNr++)
        {
            CPythonScript *pythonScript = CPythonScript::getScriptByNr(scriptNr);
            if (!pythonScript)
                break;
            if (!pythonScript->isEnabled())
                continue;
            int funNr;
            for (funNr = 0;; funNr++)
            {
                struct funType *fun = pythonScript->getFunDef(funNr);
                if (!fun)
                    break;

                if (fun->type == FUNTYPE_MSG)
                {
                    PyGILState_STATE gstate;
                    gstate = PyGILState_Ensure();
                    PyObject *params = pythonScript->getParamsDic();
                    PyObject *result = PyObject_CallMethod(pythonScript->getPluginObject(), fun->name, "(O(isss))", params, infoType, chanBuf, nickBuf, msgBuf);
                    Py_XDECREF(params);
                    Py_XDECREF(result);
                    fun->call();
                    PyGILState_Release(gstate);
                }
            }
        }
    }
    leaveCriticalSection();
}