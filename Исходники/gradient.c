BOOL
APIENTRY
IntEngGradientFill(
    IN SURFOBJ *psoDest,
    IN CLIPOBJ *pco,
    IN XLATEOBJ *pxlo,
    IN TRIVERTEX *pVertex,
    IN ULONG nVertex,
    IN PVOID pMesh,
    IN ULONG nMesh,
    IN RECTL *prclExtents,
    IN POINTL *pptlDitherOrg,
    IN ULONG ulMode)
{
    BOOL Ret;
    SURFACE *psurf;
    ASSERT(psoDest);

    psurf = CONTAINING_RECORD(psoDest, SURFACE, SurfObj);
    ASSERT(psurf);

    if (psurf->flags & HOOK_GRADIENTFILL)
    {
        Ret = GDIDEVFUNCS(psoDest).GradientFill(psoDest,
                                                pco,
                                                pxlo,
                                                pVertex,
                                                nVertex,
                                                pMesh,
                                                nMesh,
                                                prclExtents,
                                                pptlDitherOrg,
                                                ulMode);
    }
    else
    {
        Ret = EngGradientFill(psoDest,
                              pco,
                              pxlo,
                              pVertex,
                              nVertex,
                              pMesh,
                              nMesh,
                              prclExtents,
                              pptlDitherOrg,
                              ulMode);
    }

    return Ret;
}