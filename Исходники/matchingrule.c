// This is NOT RFC 4518 compliance.
static
DWORD
normalizeCaseExact(
    PVDIR_BERVALUE     pBerv
    )
{
    return normalizeString(FALSE, pBerv);
}