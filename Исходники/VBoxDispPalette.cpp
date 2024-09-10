void VBoxDispDestroyPalette(PVBOXDISPDEV pDev)
{
    if (pDev->hDefaultPalette)
    {
        EngDeletePalette(pDev->hDefaultPalette);
        pDev->hDefaultPalette = 0;
    }

    if (pDev->pPalette)
    {
        EngFreeMem(pDev->pPalette);
    }
}