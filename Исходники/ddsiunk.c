/*
 * DestroySurface
 *
 * destroys a DirectDraw surface.   does not unlink or free the surface struct.
 * The driver object MUST be locked while making this call
 */
void DestroySurface( LPDDRAWI_DDRAWSURFACE_LCL this_lcl )
{
    LPDDRAWI_DDRAWSURFACE_GBL		this;
    DDHAL_DESTROYSURFACEDATA		dsd;
    DWORD				rc;
    BOOL				free_vmem;
    LPDDHALSURFCB_DESTROYSURFACE	dsfn;
    LPDDHALSURFCB_DESTROYSURFACE	dshalfn;
    BOOL				emulation;
    DWORD                               caps;
    LPDDRAWI_DIRECTDRAW_LCL		pdrv_lcl;

    this = this_lcl->lpGbl;
    caps = this_lcl->ddsCaps.dwCaps;
    pdrv_lcl = this_lcl->lpSurfMore->lpDD_lcl;

    /*
     * see if we need to free video memory
     */
    if((this->dwGlobalFlags & DDRAWISURFGBL_MEMFREE) ||
       ((this->dwGlobalFlags & DDRAWISURFGBL_ISGDISURFACE) &&         //((this->fpVidMem == this->lpDD->fpPrimaryOrig) &&
	(this_lcl->ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) ) )
    {
	free_vmem = FALSE;
    }
    else
    {
	free_vmem = TRUE;
    }

    if( free_vmem )
    {
	/*
	 * ask the driver to free its video memory...
	 */
	if( this_lcl->ddsCaps.dwCaps & DDSCAPS_SYSTEMMEMORY )
	{
            if( caps & DDSCAPS_EXECUTEBUFFER )
	        dsfn = pdrv_lcl->lpDDCB->HELDDExeBuf.DestroyExecuteBuffer;
            else
	        dsfn = pdrv_lcl->lpDDCB->HELDDSurface.DestroySurface;
	    dshalfn = dsfn;
	    emulation = TRUE;
	}
	else
	{
            if( caps & DDSCAPS_EXECUTEBUFFER )
            {
	        dsfn = pdrv_lcl->lpDDCB->HALDDExeBuf.DestroyExecuteBuffer;
	        dshalfn = pdrv_lcl->lpDDCB->cbDDExeBufCallbacks.DestroyExecuteBuffer;
            }
            else
            {
	        dsfn = pdrv_lcl->lpDDCB->HALDDSurface.DestroySurface;
	        dshalfn = pdrv_lcl->lpDDCB->cbDDSurfaceCallbacks.DestroySurface;
            }
	    emulation = FALSE;
	}
	rc = DDHAL_DRIVER_NOTHANDLED;
	if( dshalfn != NULL )
	{
	    dsd.DestroySurface = dshalfn;
	    dsd.lpDD = this->lpDD;
	    dsd.lpDDSurface = this_lcl;
    
	    /*
	     * NOTE: THE DRIVER _CANNOT_ FAIL THIS CALL. ddrval is ignored.
	     */
            if( caps & DDSCAPS_EXECUTEBUFFER )
            {
	        DOHALCALL( DestroyExecuteBuffer, dsfn, dsd, rc, emulation );
            }
            else
            {
	        DOHALCALL( DestroySurface, dsfn, dsd, rc, emulation );
            }
	}
    
	/*
	 * free the video memory ourselves
	 */
	if( rc == DDHAL_DRIVER_NOTHANDLED )
	{
	    if( this_lcl->ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY )
	    {
		if( this->lpVidMemHeap != NULL )
		{
		    VidMemFree( this->lpVidMemHeap, this->fpVidMem );
		}
	    }
	}
	this->lpVidMemHeap = NULL;
	this->fpVidMem = 0;
	this->dwGlobalFlags |= DDRAWISURFGBL_MEMFREE;
    }

    #ifdef WINNT
    {
        /*
         * Free the associated NT kernel-mode object only if it is a vram surface, it is not
         * an execute buffer, and it has not yet been freed in the kernel
         */
        DWORD pid = GetCurrentProcessId();
        if (!(caps & (DDSCAPS_EXECUTEBUFFER|DDSCAPS_SYSTEMMEMORY) ) && this_lcl->hDDSurface && this_lcl->dwProcessId == pid)
        {
            DPF(9,"Deleting NT kernel-mode object handle %08x",this_lcl->hDDSurface);
            if (!DdDeleteSurfaceObject(this_lcl))
                DPF(9,"DdDeleteSurfaceObject failed");
        }
    }
    #endif

} /* DestroySurface */