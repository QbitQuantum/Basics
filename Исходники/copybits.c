BOOL APIENTRY
IntEngCopyBits(
    SURFOBJ *psoDest,
    SURFOBJ *psoSource,
    CLIPOBJ *pco,
    XLATEOBJ *pxlo,
    RECTL *prclDest,
    POINTL *ptlSource)
{
    return EngCopyBits(psoDest, psoSource, pco, pxlo, prclDest, ptlSource);
}