void MarkupTextManager::GetVariableValue(StringId name, int index, char* buffer, int bufferSize)
{
    StrCpy(buffer,"");

    const RegisteredVariable* variable=FindRegisteredVariable(name);
    if (!variable)
    {
        return;
    }

    if (variable->intArray)
    {
        if (index>=0 && index<variable->intArray->GetItemCount() && variable->intArray->Get(index)!=0)
        {
            SNPrintF(buffer,bufferSize,"%d",variable->intArray->Get(index));
        }
    }
    else if (variable->stringIdArray)
    {
        if (index>=0 && index<variable->stringIdArray->GetItemCount() && variable->stringIdArray->Get(index)!=0)
        {
            SNPrintF(buffer,bufferSize,"%s",variable->stringIdArray->Get(index).GetString());
        }
    }
}