/*
 * UserLoadKbdDll
 *
 * Loads keyboard layout DLL and gets address to KbdTables
 */
static BOOL
UserLoadKbdDll(WCHAR *pwszLayoutPath,
               HANDLE *phModule,
               PKBDTABLES *pKbdTables)
{
    PFN_KBDLAYERDESCRIPTOR pfnKbdLayerDescriptor;

    /* Load keyboard layout DLL */
    TRACE("Loading Keyboard DLL %ws\n", pwszLayoutPath);
    *phModule = EngLoadImage(pwszLayoutPath);
    if (!(*phModule))
    {
        ERR("Failed to load dll %ws\n", pwszLayoutPath);
        return FALSE;
    }

    /* Find KbdLayerDescriptor function and get layout tables */
    TRACE("Loaded %ws\n", pwszLayoutPath);
    pfnKbdLayerDescriptor = EngFindImageProcAddress(*phModule, "KbdLayerDescriptor");

    /* FIXME: Windows reads file instead of executing!
              It's not safe to kbdlayout DLL in kernel mode! */

    if (pfnKbdLayerDescriptor)
        *pKbdTables = pfnKbdLayerDescriptor();
    else
        ERR("Error: %ws has no KbdLayerDescriptor()\n", pwszLayoutPath);

    if (!pfnKbdLayerDescriptor || !*pKbdTables)
    {
        ERR("Failed to load the keyboard layout.\n");
        EngUnloadImage(*phModule);
        return FALSE;
    }

#if 0 /* Dump keyboard layout */
    {
        unsigned i;
        PVK_TO_BIT pVkToBit = (*pKbdTables)->pCharModifiers->pVkToBit;
        PVK_TO_WCHAR_TABLE pVkToWchTbl = (*pKbdTables)->pVkToWcharTable;
        PVSC_VK pVscVk = (*pKbdTables)->pVSCtoVK_E0;
        DbgPrint("Kbd layout: fLocaleFlags %x bMaxVSCtoVK %x\n", (*pKbdTables)->fLocaleFlags, (*pKbdTables)->bMaxVSCtoVK);
        DbgPrint("wMaxModBits %x\n", (*pKbdTables)->pCharModifiers->wMaxModBits);
        while (pVkToBit->Vk)
        {
            DbgPrint("VkToBit %x -> %x\n", pVkToBit->Vk, pVkToBit->ModBits);
            ++pVkToBit;
        }
        for (i = 0; i <= (*pKbdTables)->pCharModifiers->wMaxModBits; ++i)
            DbgPrint("ModNumber %x -> %x\n", i, (*pKbdTables)->pCharModifiers->ModNumber[i]);
        while (pVkToWchTbl->pVkToWchars)
        {
            PVK_TO_WCHARS1 pVkToWch = pVkToWchTbl->pVkToWchars;
            DbgPrint("pVkToWchTbl nModifications %x cbSize %x\n", pVkToWchTbl->nModifications, pVkToWchTbl->cbSize);
            while (pVkToWch->VirtualKey)
            {
                DbgPrint("pVkToWch VirtualKey %x Attributes %x wc { ", pVkToWch->VirtualKey, pVkToWch->Attributes);
                for (i = 0; i < pVkToWchTbl->nModifications; ++i)
                    DbgPrint("%x ", pVkToWch->wch[i]);
                DbgPrint("}\n");
                pVkToWch = (PVK_TO_WCHARS1)(((PBYTE)pVkToWch) + pVkToWchTbl->cbSize);
            }
            ++pVkToWchTbl;
        }
        DbgPrint("pusVSCtoVK: { ");
        for (i = 0; i < (*pKbdTables)->bMaxVSCtoVK; ++i)
        DbgPrint("%x -> %x, ", i, (*pKbdTables)->pusVSCtoVK[i]);
        DbgPrint("}\n");
        DbgPrint("pVSCtoVK_E0: { ");
        while (pVscVk->Vsc)
        {
            DbgPrint("%x -> %x, ", pVscVk->Vsc, pVscVk->Vk);
            ++pVscVk;
        }
        DbgPrint("}\n");
        pVscVk = (*pKbdTables)->pVSCtoVK_E1;
        DbgPrint("pVSCtoVK_E1: { ");
        while (pVscVk->Vsc)
        {
            DbgPrint("%x -> %x, ", pVscVk->Vsc, pVscVk->Vk);
            ++pVscVk;
        }
        DbgPrint("}\n");
        DbgBreakPoint();
    }
#endif

    return TRUE;
}