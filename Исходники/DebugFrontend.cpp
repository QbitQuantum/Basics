bool DebugFrontend::GetExeInfo(LPCSTR fileName, ExeInfo& info) const
{
    
    LOADED_IMAGE loadedImage;
    if (!MapAndLoad(const_cast<PSTR>(fileName), NULL, &loadedImage, FALSE, TRUE))
    {
        return false;
    }

    // Check if this is a managed application.
    // http://www.codeguru.com/cpp/w-p/system/misc/print.php/c14001

    info.managed = false;
    if (loadedImage.FileHeader->Signature == IMAGE_NT_SIGNATURE)
    {
       
        DWORD netHeaderAddress =
            loadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress;

        if (netHeaderAddress)
        {
            info.managed = true;
        }
    
    }
    
    info.entryPoint = loadedImage.FileHeader->OptionalHeader.AddressOfEntryPoint;
    info.i386       = loadedImage.FileHeader->FileHeader.Machine == IMAGE_FILE_MACHINE_I386;

    UnMapAndLoad(&loadedImage);

    return true;

}