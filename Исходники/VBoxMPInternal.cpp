int VBoxVbvaEnable(PVBOXMP_DEVEXT pExt, BOOLEAN bEnable, VBVAENABLERESULT *pResult)
{
    int rc = VINF_SUCCESS;
    LOGF_ENTER();

    VMMDevMemory *pVMMDevMemory = NULL;

    rc = VbglQueryVMMDevMemory (&pVMMDevMemory);
    if (RT_FAILURE(rc))
    {
        WARN(("VbglQueryVMMDevMemory rc = %#xrc", rc));
        LOGF_LEAVE();
        return rc;
    }

    if (pExt->iDevice>0)
    {
        PVBOXMP_DEVEXT pPrimary = pExt->pPrimary;
        LOGF(("skipping non-primary display %d", pExt->iDevice));

        if (bEnable && pPrimary->u.primary.ulVbvaEnabled && pVMMDevMemory)
        {
            pResult->pVbvaMemory = &pVMMDevMemory->vbvaMemory;
            pResult->pfnFlush    = VBoxVbvaFlush;
            pResult->pvFlush     = pExt;
        }
        else
        {
            VideoPortZeroMemory(&pResult, sizeof(VBVAENABLERESULT));
        }

        LOGF_LEAVE();
        return rc;
    }

    /* Allocate the memory block for VMMDevReq_VideoAccelFlush request. */
    if (pExt->u.primary.pvReqFlush == NULL)
    {
        VMMDevVideoAccelFlush *req = NULL;

        rc = VbglGRAlloc((VMMDevRequestHeader **)&req, sizeof(VMMDevVideoAccelFlush), VMMDevReq_VideoAccelFlush);

        if (RT_SUCCESS(rc))
        {
            pExt->u.primary.pvReqFlush = req;
        }
        else
        {
            WARN(("VbglGRAlloc(VMMDevVideoAccelFlush) rc = %#xrc", rc));
            LOGF_LEAVE();
            return rc;
        }
    }

    ULONG ulEnabled = 0;

    VMMDevVideoAccelEnable *req = NULL;
    rc = VbglGRAlloc((VMMDevRequestHeader **)&req, sizeof(VMMDevVideoAccelEnable), VMMDevReq_VideoAccelEnable);

    if (RT_SUCCESS(rc))
    {
        req->u32Enable    = bEnable;
        req->cbRingBuffer = VBVA_RING_BUFFER_SIZE;
        req->fu32Status   = 0;

        rc = VbglGRPerform(&req->header);
        if (RT_SUCCESS(rc))
        {
            if (req->fu32Status & VBVA_F_STATUS_ACCEPTED)
            {
                LOG(("accepted"));

                /* Initialize the result information and VBVA memory. */
                if (req->fu32Status & VBVA_F_STATUS_ENABLED)
                {
                    pResult->pVbvaMemory = &pVMMDevMemory->vbvaMemory;
                    pResult->pfnFlush    = VBoxVbvaFlush;
                    pResult->pvFlush     = pExt;
                    ulEnabled = 1;
                }
                else
                {
                    VideoPortZeroMemory(&pResult, sizeof(VBVAENABLERESULT));
                }
            }
            else
            {
                LOG(("rejected"));

                /* Disable VBVA for old hosts. */
                req->u32Enable = 0;
                req->cbRingBuffer = VBVA_RING_BUFFER_SIZE;
                req->fu32Status = 0;

                VbglGRPerform(&req->header);

                rc = VERR_NOT_SUPPORTED;
            }
        }
        else
        {
            WARN(("rc = %#xrc", rc));
        }

        VbglGRFree(&req->header);
    }
    else
    {
        WARN(("VbglGRAlloc(VMMDevVideoAccelEnable) rc = %#xrc", rc));
    }

    pExt->u.primary.ulVbvaEnabled = ulEnabled;

    LOGF_LEAVE();
    return rc;
}