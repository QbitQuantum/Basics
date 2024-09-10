VOID
NTAPI
EBRUSHOBJ_vCleanup(EBRUSHOBJ *pebo)
{
    /* Check if there's a GDI realisation */
    if (pebo->pengbrush)
    {
        /* Unlock the bitmap again */
        SURFACE_ShareUnlockSurface(pebo->pengbrush);
        pebo->pengbrush = NULL;
    }

    /* Check if there's a driver's realisation */
    if (pebo->BrushObject.pvRbrush)
    {
        /* Free allocated driver memory */
        EngFreeMem(pebo->BrushObject.pvRbrush);
        pebo->BrushObject.pvRbrush = NULL;
    }

    if (pebo->psoMask != NULL)
    {
        SURFACE_ShareUnlockSurface(pebo->psoMask);
        pebo->psoMask = NULL;
    }

    /* Dereference the palettes */
    PALETTE_ShareUnlockPalette(pebo->ppalSurf);
    PALETTE_ShareUnlockPalette(pebo->ppalDC);
    if (pebo->ppalDIB) PALETTE_ShareUnlockPalette(pebo->ppalDIB);
}