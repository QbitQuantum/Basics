/* Finishes a blit for one or two DCs */
VOID
FASTCALL
DC_vFinishBlit(PDC pdc1, PDC pdc2)
{
    if(pdc1->dctype == DCTYPE_DIRECT)
    {
        MouseSafetyOnDrawEnd(pdc1->ppdev);
        EngReleaseSemaphore(pdc1->ppdev->hsemDevLock);
    }

    if(pdc2)
    {
        if(pdc2->dctype == DCTYPE_DIRECT)
        {
            MouseSafetyOnDrawEnd(pdc2->ppdev);
            EngReleaseSemaphore(pdc2->ppdev->hsemDevLock);
        }
    }
}