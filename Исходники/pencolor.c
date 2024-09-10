LONG
GetColor(
    PPDEV       pPDev,
    BRUSHOBJ    *pbo,
    LPDWORD     pColorFG,
    PDEVBRUSH   *ppDevBrush,
    ROP4        Rop4
    )

/*++

Routine Description:

    Realize the brush color and return the color


Arguments:

    pPDev       - Pointer to our DEV

    pbo         - Engine brush object

    pColorFG    - pointer to the ULONG to received forground color, NULL if
                  not needed

    ppDevBrush  - Pointer to the location to received brush, NULL if not
                  needed

    Rop4        - Rop4 to be used, this function looks at this in order to
                  determine if the brush can be used with the HPGL2 cmds or
                  that the brush will have to be simulated.

Return Value:

    LONG    > 0     The Brush is compatible with device format (Fill command)
            = 0     Failed
            < 0     The brush must send to device via a bitblt

Author:

    13-Jan-1994 Thu 20:18:49 created  

    15-Jan-1994 Sat 06:58:56 updated  
        Change parameters and return value

    16-May-1994 Mon 15:59:45 updated  
        Adding PDEV

Revision History:


--*/

{
    PDEVBRUSH   pDevBrush = NULL;
    LONG        RetVal    = 1;
    DWORD       SolidColor = 0xFFFFFF;
    DWORD       RopBG;
    DWORD       RopFG;


    //
    // Get the ROP for the foureground and background. This information is
    // used to determine if the brush has to be simulated, or can be
    // used with selectable pens in the target device.

    RopBG = ROP4_BG_ROP(Rop4);
    RopFG = ROP4_FG_ROP(Rop4);

    //
    // Get the current color and select the appropriate pen, this should
    // ONLY be a solid color as we don't support stroking with arbitrary
    // brushes.
    //

    if (pbo) {

        //
        // get the brush realization, and select a pen.
        // If the BRUSHOBJ's iSolidColor field is a valid color, then
        // we must do a solid fill with that pen.  Otherwise, we must
        // check the realization of the brush to do a pattern fill.
        //
        // To return a Fillable pattern by DoFill, one of the following conditions
        // must be true and in this sequence
        //
        //  1. SOLID COLOR
        //  2. STANDARD PATTERN
        //  3. Device compatible bitmap
        //

        if ((SolidColor = (DWORD)pbo->iSolidColor) == CLR_INVALID) {

            PLOTDBG(DBG_GETCLR, ("iSolodColor == CLR_INVALID, pBrush=%08lx",
                                                                pbo->pvRbrush));

            //
            // This is a pattern brush, but we will just use its
            // foreground color.
            //

            if ((pDevBrush = (PDEVBRUSH)pbo->pvRbrush) ||
                (pDevBrush = BRUSHOBJ_pvGetRbrush(pbo))) {


                //
                // Grab the foreground color and use it.
                //

                SolidColor = pDevBrush->ColorFG;


                if ((pDevBrush->PatIndex < HS_DDI_MAX) ||
                    (pDevBrush->pbgr24)) {

                    ;

                } else {

                    PLOTDBG(DBG_GETCLR, ("GETColor: NOT DEVICE_PAT"));

                    RetVal = -1;
                }

            } else {

                RetVal = 0;
                PLOTDBG(DBG_GETCLR, ("GetColor(): couldn't realize brush!"));
            }

        } else {

            PLOTDBG(DBG_GETCLR,
                    ("GETColor: is a SOLID COLOR=%08lx", pbo->iSolidColor));
        }

    } else if ((RopFG == 0x00) || (RopBG == 0x00)) {

        if (IS_RASTER(pPDev)) {

            SolidColor = 0x0;

        } else {

            //
            // If we are not a raster device (which supports overprint)
            // match the best non-white pen, in order to fill with.
            //

            SolidColor = (DWORD)BestMatchNonWhitePen(pPDev, 0, 0, 0);

            PLOTDBG(DBG_GETCLR,
                    ("GETColor: pbo=NULL, BLACK Pen Idx=%ld", SolidColor));

        }
    }

    if ((!IS_RASTER(pPDev)) && (SolidColor == 0x00FFFFFF)) {

        SolidColor = WHITE_INDEX;

        PLOTDBG(DBG_GETCLR,
                ("GETColor: Pen plotter using WHITE COLOR Idx=%ld", SolidColor));
    }

    if (pColorFG) {

        *pColorFG = SolidColor;
    }

    if (ppDevBrush) {

        *ppDevBrush = pDevBrush;
    }

    return(RetVal);
}