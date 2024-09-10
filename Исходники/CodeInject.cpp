//-----------------------------------------------------------------------------
// Name: FreeRemoteAllocatedMemory
// Object: Free remote process allocated memory of members pDataRemote and pCodeRemote
// Parameters :
//     in  : 
//     out : 
//     return : 
//-----------------------------------------------------------------------------
void CCodeInject::FreeRemoteAllocatedMemory()
{
    if (this->pDataRemote)
        VirtualFreeEx( this->hProcess, this->pDataRemote, 0, MEM_RELEASE );

    if (this->pCodeRemote)
        VirtualFreeEx( this->hProcess, this->pCodeRemote, 0, MEM_RELEASE );
}