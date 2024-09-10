extern "C" DLL_EXPORT uint _dbg_sendmessage(DBGMSG type, void* param1, void* param2)
{
    if(dbgisstopped())
    {
        switch(type)  //ignore win events
        {
        //these functions are safe to call when we did not initialize yet
        case DBG_DEINITIALIZE_LOCKS:
        case DBG_INITIALIZE_LOCKS:
        case DBG_GET_FUNCTIONS:
        case DBG_SETTINGS_UPDATED:
        case DBG_GET_THREAD_LIST:
        case DBG_WIN_EVENT:
        case DBG_WIN_EVENT_GLOBAL:
            break;
        //the rest is unsafe -> throw an exception when people try to call them
        default:
            __debugbreak(); //we cannot process messages when the debugger is stopped, this must be a bug
        }
    }
    switch(type)
    {
    case DBG_SCRIPT_LOAD:
    {
        scriptload((const char*)param1);
    }
    break;

    case DBG_SCRIPT_UNLOAD:
    {
        scriptunload();
    }
    break;

    case DBG_SCRIPT_RUN:
    {
        scriptrun((int)(duint)param1);
    }
    break;

    case DBG_SCRIPT_STEP:
    {
        scriptstep();
    }
    break;

    case DBG_SCRIPT_BPTOGGLE:
    {
        return scriptbptoggle((int)(duint)param1);
    }
    break;

    case DBG_SCRIPT_BPGET:
    {
        return scriptbpget((int)(duint)param1);
    }
    break;

    case DBG_SCRIPT_CMDEXEC:
    {
        return scriptcmdexec((const char*)param1);
    }
    break;

    case DBG_SCRIPT_ABORT:
    {
        scriptabort();
    }
    break;

    case DBG_SCRIPT_GETLINETYPE:
    {
        return (duint)scriptgetlinetype((int)(duint)param1);
    }
    break;

    case DBG_SCRIPT_SETIP:
    {
        scriptsetip((int)(duint)param1);
    }
    break;

    case DBG_SCRIPT_GETBRANCHINFO:
    {
        return (duint)scriptgetbranchinfo((int)(duint)param1, (SCRIPTBRANCH*)param2);
    }
    break;

    case DBG_SYMBOL_ENUM:
    {
        SYMBOLCBINFO* cbInfo = (SYMBOLCBINFO*)param1;
        SymEnum(cbInfo->base, cbInfo->cbSymbolEnum, cbInfo->user);
    }
    break;

    case DBG_ASSEMBLE_AT:
    {
        return assembleat((duint)param1, (const char*)param2, 0, 0, false);
    }
    break;

    case DBG_MODBASE_FROM_NAME:
    {
        return ModBaseFromName((const char*)param1);
    }
    break;

    case DBG_DISASM_AT:
    {
        disasmget((uint)param1, (DISASM_INSTR*)param2);
    }
    break;

    case DBG_STACK_COMMENT_GET:
    {
        return stackcommentget((uint)param1, (STACK_COMMENT*)param2);
    }
    break;

    case DBG_GET_THREAD_LIST:
    {
        ThreadGetList((THREADLIST*)param1);
    }
    break;

    case DBG_SETTINGS_UPDATED:
    {
        valuesetsignedcalc(!settingboolget("Engine", "CalculationType")); //0:signed, 1:unsigned
        SetEngineVariable(UE_ENGINE_SET_DEBUG_PRIVILEGE, settingboolget("Engine", "EnableDebugPrivilege"));
        bOnlyCipAutoComments = settingboolget("Disassembler", "OnlyCipAutoComments");
        bListAllPages = settingboolget("Engine", "ListAllPages");
        bUndecorateSymbolNames = settingboolget("Engine", "UndecorateSymbolNames");
        bEnableSourceDebugging = settingboolget("Engine", "EnableSourceDebugging");

        uint setting;
        if(BridgeSettingGetUint("Engine", "BreakpointType", &setting))
        {
            switch(setting)
            {
            case 0: //break_int3short
                SetBPXOptions(UE_BREAKPOINT_INT3);
                break;
            case 1: //break_int3long
                SetBPXOptions(UE_BREAKPOINT_LONG_INT3);
                break;
            case 2: //break_ud2
                SetBPXOptions(UE_BREAKPOINT_UD2);
                break;
            }
        }

        char exceptionRange[MAX_SETTING_SIZE] = "";
        dbgclearignoredexceptions();
        if(BridgeSettingGet("Exceptions", "IgnoreRange", exceptionRange))
        {
            char* entry = strtok(exceptionRange, ",");
            while(entry)
            {
                unsigned long start;
                unsigned long end;
                if(sscanf(entry, "%08X-%08X", &start, &end) == 2 && start <= end)
                {
                    ExceptionRange range;
                    range.start = start;
                    range.end = end;
                    dbgaddignoredexception(range);
                }
                entry = strtok(0, ",");
            }
        }

        char cachePath[MAX_SETTING_SIZE];
        if(BridgeSettingGet("Symbols", "CachePath", cachePath))
        {
            // Trim the buffer to fit inside MAX_PATH
            strncpy_s(szSymbolCachePath, cachePath, _TRUNCATE);
        }
    }
    break;

    case DBG_DISASM_FAST_AT:
    {
        if(!param1 || !param2)
            return 0;
        BASIC_INSTRUCTION_INFO* basicinfo = (BASIC_INSTRUCTION_INFO*)param2;
        if(!disasmfast((uint)param1, basicinfo))
            basicinfo->size = 1;
        return 0;
    }
    break;

    case DBG_MENU_ENTRY_CLICKED:
    {
        int hEntry = (int)(uint)param1;
        pluginmenucall(hEntry);
    }
    break;

    case DBG_FUNCTION_GET:
    {
        FUNCTION_LOOP_INFO* info = (FUNCTION_LOOP_INFO*)param1;
        return (uint)FunctionGet(info->addr, &info->start, &info->end);
    }
    break;

    case DBG_FUNCTION_OVERLAPS:
    {
        FUNCTION_LOOP_INFO* info = (FUNCTION_LOOP_INFO*)param1;
        return (uint)FunctionOverlaps(info->start, info->end);
    }
    break;

    case DBG_FUNCTION_ADD:
    {
        FUNCTION_LOOP_INFO* info = (FUNCTION_LOOP_INFO*)param1;
        return (uint)FunctionAdd(info->start, info->end, info->manual);
    }
    break;

    case DBG_FUNCTION_DEL:
    {
        FUNCTION_LOOP_INFO* info = (FUNCTION_LOOP_INFO*)param1;
        return (uint)FunctionDelete(info->addr);
    }
    break;

    case DBG_LOOP_GET:
    {
        FUNCTION_LOOP_INFO* info = (FUNCTION_LOOP_INFO*)param1;
        return (uint)LoopGet(info->depth, info->addr, &info->start, &info->end);
    }
    break;

    case DBG_LOOP_OVERLAPS:
    {
        FUNCTION_LOOP_INFO* info = (FUNCTION_LOOP_INFO*)param1;
        return (uint)LoopOverlaps(info->depth, info->start, info->end, 0);
    }
    break;

    case DBG_LOOP_ADD:
    {
        FUNCTION_LOOP_INFO* info = (FUNCTION_LOOP_INFO*)param1;
        return (uint)LoopAdd(info->start, info->end, info->manual);
    }
    break;

    case DBG_LOOP_DEL:
    {
        FUNCTION_LOOP_INFO* info = (FUNCTION_LOOP_INFO*)param1;
        return (uint)LoopDelete(info->depth, info->addr);
    }
    break;

    case DBG_IS_RUN_LOCKED:
    {
        return (uint)waitislocked(WAITID_RUN);
    }
    break;

    case DBG_IS_BP_DISABLED:
    {
        BREAKPOINT bp;
        if(BpGet((uint)param1, BPNORMAL, 0, &bp))
            return !(uint)bp.enabled;
        return (uint)false;
    }
    break;

    case DBG_SET_AUTO_COMMENT_AT:
    {
        return (uint)CommentSet((uint)param1, (const char*)param2, false);
    }
    break;

    case DBG_DELETE_AUTO_COMMENT_RANGE:
    {
        CommentDelRange((uint)param1, (uint)param2);
    }
    break;

    case DBG_SET_AUTO_LABEL_AT:
    {
        return (uint)LabelSet((uint)param1, (const char*)param2, false);
    }
    break;

    case DBG_DELETE_AUTO_LABEL_RANGE:
    {
        LabelDelRange((uint)param1, (uint)param2);
    }
    break;

    case DBG_SET_AUTO_BOOKMARK_AT:
    {
        return (uint)BookmarkSet((uint)param1, false);
    }
    break;

    case DBG_DELETE_AUTO_BOOKMARK_RANGE:
    {
        BookmarkDelRange((uint)param1, (uint)param2);
    }
    break;

    case DBG_SET_AUTO_FUNCTION_AT:
    {
        return (uint)FunctionAdd((uint)param1, (uint)param2, false);
    }
    break;

    case DBG_DELETE_AUTO_FUNCTION_RANGE:
    {
        FunctionDelRange((uint)param1, (uint)param2);
    }
    break;

    case DBG_GET_STRING_AT:
    {
        STRING_TYPE strtype;
        char string[MAX_STRING_SIZE];
        if(disasmgetstringat((uint)param1, &strtype, string, string, MAX_STRING_SIZE-3))
        {
            if(strtype == str_ascii)
                sprintf((char*)param2, "\"%s\"", string);
            else //unicode
                sprintf((char*)param2, "L\"%s\"", string);
            return true;
        }
        return false;
    }
    break;

    case DBG_GET_FUNCTIONS:
    {
        return (uint)dbgfunctionsget();
    }
    break;

    case DBG_WIN_EVENT:
    {
        return (uint)pluginwinevent((MSG*)param1, (long*)param2);
    }
    break;

    case DBG_WIN_EVENT_GLOBAL:
    {
        return (uint)pluginwineventglobal((MSG*)param1);
    }
    break;

    case DBG_INITIALIZE_LOCKS:
    {
        SectionLockerGlobal::Initialize();
    }
    break;

    case DBG_DEINITIALIZE_LOCKS:
    {
        SectionLockerGlobal::Deinitialize();
    }
    break;

    case DBG_GET_TIME_WASTED_COUNTER:
        return dbggettimewastedcounter();
    }
    return 0;
}