U_DRAFT uint32_t U_EXPORT2
ubiditransform_transform(UBiDiTransform *pBiDiTransform,
            const UChar *src, int32_t srcLength,
            UChar *dest, int32_t destSize,
            UBiDiLevel inParaLevel, UBiDiOrder inOrder,
            UBiDiLevel outParaLevel, UBiDiOrder outOrder,
            UBiDiMirroring doMirroring, uint32_t shapingOptions,
            UErrorCode *pErrorCode)
{
    uint32_t destLength = 0;
    UBool textChanged = FALSE;
    const UBiDiTransform *pOrigTransform = pBiDiTransform;
    const UBiDiAction *action = NULL;

    if (U_FAILURE(*pErrorCode)) {
        return 0;
    }
    if (src == NULL || dest == NULL) {
        *pErrorCode = U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }
    CHECK_LEN(src, srcLength, pErrorCode);
    CHECK_LEN(dest, destSize, pErrorCode);

    if (pBiDiTransform == NULL) {
        pBiDiTransform = ubiditransform_open(pErrorCode);
        if (U_FAILURE(*pErrorCode)) {
            return 0;
        }
    }
    /* Current limitation: in multiple paragraphs will be resolved according
       to the 1st paragraph */
    resolveBaseDirection(src, srcLength, &inParaLevel, &outParaLevel);

    pBiDiTransform->pActiveScheme = findMatchingScheme(inParaLevel, outParaLevel,
            inOrder, outOrder);
    if (pBiDiTransform->pActiveScheme == NULL) {
        goto cleanup;
    }
    pBiDiTransform->reorderingOptions = doMirroring ? UBIDI_DO_MIRRORING
            : UBIDI_REORDER_DEFAULT;

    /* Ignore TEXT_DIRECTION_* flags, as we apply our own depending on the text
       scheme at the time shaping is invoked. */
    shapingOptions &= ~U_SHAPE_TEXT_DIRECTION_MASK;
    pBiDiTransform->digits = shapingOptions & ~U_SHAPE_LETTERS_MASK;
    pBiDiTransform->letters = shapingOptions & ~U_SHAPE_DIGITS_MASK;

    updateSrc(pBiDiTransform, src, srcLength, destSize > srcLength ? destSize : srcLength, pErrorCode);
    if (U_FAILURE(*pErrorCode)) {
        goto cleanup;
    }
    if (pBiDiTransform->pBidi == NULL) {
        pBiDiTransform->pBidi = ubidi_openSized(0, 0, pErrorCode);
        if (U_FAILURE(*pErrorCode)) {
            goto cleanup;
        }
    }
    pBiDiTransform->dest = dest;
    pBiDiTransform->destSize = destSize;
    pBiDiTransform->pDestLength = &destLength;

    /* Checking for U_SUCCESS() within the loop to bail out on first failure. */
    for (action = pBiDiTransform->pActiveScheme->actions; *action && U_SUCCESS(*pErrorCode); action++) {
        if ((*action)(pBiDiTransform, pErrorCode)) {
            if (action + 1) {
                updateSrc(pBiDiTransform, pBiDiTransform->dest, *pBiDiTransform->pDestLength,
                        *pBiDiTransform->pDestLength, pErrorCode);
            }
            textChanged = TRUE;
        }
    }
    ubidi_setInverse(pBiDiTransform->pBidi, FALSE);

    if (!textChanged && U_SUCCESS(*pErrorCode)) {
        /* Text was not changed - just copy src to dest */
        if (destSize < srcLength) {
            *pErrorCode = U_BUFFER_OVERFLOW_ERROR;
        } else {
            u_strncpy(dest, src, srcLength);
            destLength = srcLength;
        }
    }
cleanup:
    if (pOrigTransform != pBiDiTransform) {
        ubiditransform_close(pBiDiTransform);
    } else {
        pBiDiTransform->dest = NULL;
        pBiDiTransform->pDestLength = NULL;
        pBiDiTransform->srcLength = 0;
        pBiDiTransform->destSize = 0;
    }
    return U_FAILURE(*pErrorCode) ? 0 : destLength;
}