double CScript::LocalVar(const char* CmdStr, char* retStr)
{
    // 取第一个参数： 变量名字符串, 该脚本系统仅支持数组下标为$var变量,不支持[]嵌套
    // 如 $Var[$Var1],#strVar[$Var1];
    char* firstVarName = (char*)CmdStr;

    // 先循环到第一个参数处
    long cmdStrLen = strlen(CmdStr);
    long tCurPos = 0;
    while(*firstVarName != '(' && tCurPos < cmdStrLen && *firstVarName != '\0')
    {
        tCurPos++;
        firstVarName++;
    }

    if(*firstVarName == '(') // 跳过'('
        firstVarName++;

    if(firstVarName)
    {
        char MainVarName[1024];  // 变量
        char InnVarName[1024];   // 下标变量

        // 分解字符串第一个参数及下标
        long tempPos = 0;
        char* tMainPtr = MainVarName;
        char* tInnPtr = InnVarName;
        CheckParamStringForArray(firstVarName, cmdStrLen-tCurPos, &tMainPtr, 1024, &tInnPtr, 1024, tempPos);

        // 读取字符串值
        if(MainVarName[0] == '#') // 字符串
        {
            char* strValue = NULL;
            strValue = GetStringParam(CmdStr, 1);

            if(m_pVariableList && strValue)
            {
                if(InnVarName[0] == '\0') // 不是数组变量
                {
                    if(strValue[0] != '#') // 第二个参数不是变量
                        m_pVariableList->AddVar(MainVarName, strValue);
                    else
                    {
                        char* str2ndValue = (char*)m_pVariableList->GetVarValue(strValue);
                        if(str2ndValue)
                            m_pVariableList->AddVar(MainVarName, str2ndValue);
                    }
                }
                else// 是数组变量
                {
                    int lArray = 0;
                    if(InnVarName[0] == '$') // 下标是普通变量而非数组变量
                    {
                        lArray = GetScriptVarValue((CMoveShape*)p_SrcShape, InnVarName, 0);
                    }
                    else if(InnVarName[0] != '$' && InnVarName[0] != '#') // 下标是常量
                    {
                        lArray = atoi(InnVarName);
                    }

                    // 去掉'[' ']'
                    for(int i=0; i < lArray; i++)
                    {
                        char tNum[32];
                        char name[1024];
                        strcpy_s(name, 1024, MainVarName);
                        itoa(i, tNum, 10);
                        strcat(name, tNum);
                        m_pVariableList->AddVar(name, strValue);
                    }
                }
            }

            M_FREE( strValue, sizeof(char)*MAX_VAR_LEN );
        }
        else if(MainVarName[0] == '$') // 第一个参数是数字变量
        {
            double value = GetIntParam(CmdStr, 1);

            if(m_pVariableList && (value != ERROR_CODE) )
            {
                if(InnVarName[0] == '\0') // 不是数组变量
                {
                    m_pVariableList->AddVar(MainVarName, value);
                }
                else // 是数组变量
                {
                    int lArray = 0;
                    if(InnVarName[0] == '$') // 下标是普通变量
                    {
                        lArray = GetScriptVarValue((CMoveShape*)p_SrcShape, InnVarName, 0);

                    }
                    else if(InnVarName[0] != '$' && InnVarName[0] != '#') // 下标是常量
                    {
                        lArray = atoi(InnVarName);
                    }

                    // 去掉'[' ']'
                    m_pVariableList->AddVar(MainVarName, lArray, value);
                }
            }
        }

        else if(MainVarName[0] == '@') // 定义GUID
        {
            double value = GetIntParam(CmdStr, 1);

            if(m_pVariableList && (value != ERROR_CODE) )
            {
                if(InnVarName[0] == '\0') // 不是数组变量
                {
                    m_pVariableList->AddGuid(MainVarName, NULL_GUID);
                }
                else // 是数组变量
                {
                    int lArray = 0;
                    if(InnVarName[0] == '$') // 下标是普通变量
                    {
                        lArray = GetScriptVarValue((CMoveShape*)p_SrcShape, InnVarName, 0);
                    }
                    else if(InnVarName[0] != '$' && InnVarName[0] != '#') // 下标是常量
                    {
                        lArray = atoi(InnVarName);
                    }

                    // 去掉'[' ']'
                    for(int i=0; i < lArray; i++)
                    {
                        char tNum[32];
                        char name[1024];
                        strcpy_s(name, 1024, MainVarName);
                        itoa(i, tNum, 10);
                        strcat(name, tNum);
                        m_pVariableList->AddGuid(name, NULL_GUID);
                    }
                }
            }
        }

        //	SAFE_DELETE_ARRAY(firstVarName);
    }
    return 1;
}