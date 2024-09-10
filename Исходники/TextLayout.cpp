void TextLayout::computeAdvancesWithICU(SkPaint* paint, const UChar* chars,
        size_t start, size_t count, size_t contextCount, int dirFlags,
        jfloat* outAdvances, jfloat* outTotalAdvance) {
    SkAutoSTMalloc<CHAR_BUFFER_SIZE, jchar> tempBuffer(contextCount);
    jchar* buffer = tempBuffer.get();
    SkScalar* scalarArray = (SkScalar*)outAdvances;

    // this is where we'd call harfbuzz
    // for now we just use ushape.c
    size_t widths;
    const jchar* text;
    if (dirFlags & 0x1) { // rtl, call arabic shaping in case
        UErrorCode status = U_ZERO_ERROR;
        // Use fixed length since we need to keep start and count valid
        u_shapeArabic(chars, contextCount, buffer, contextCount,
                U_SHAPE_LENGTH_FIXED_SPACES_NEAR |
                U_SHAPE_TEXT_DIRECTION_LOGICAL | U_SHAPE_LETTERS_SHAPE |
                U_SHAPE_X_LAMALEF_SUB_ALTERNATE, &status);
        // we shouldn't fail unless there's an out of memory condition,
        // in which case we're hosed anyway
        for (int i = start, e = i + count; i < e; ++i) {
            if (buffer[i] == UNICODE_NOT_A_CHAR) {
                buffer[i] = UNICODE_ZWSP; // zero-width-space for skia
            }
        }
        text = buffer + start;
        widths = paint->getTextWidths(text, count << 1, scalarArray);
    } else {
        text = chars + start;
        widths = paint->getTextWidths(text, count << 1, scalarArray);
    }

    jfloat totalAdvance = 0;
    if (widths < count) {
#if DEBUG_ADVANCES
    ALOGD("ICU -- count=%d", widths);
#endif
        // Skia operates on code points, not code units, so surrogate pairs return only
        // one value. Expand the result so we have one value per UTF-16 code unit.

        // Note, skia's getTextWidth gets confused if it encounters a surrogate pair,
        // leaving the remaining widths zero.  Not nice.
        for (size_t i = 0, p = 0; i < widths; ++i) {
            totalAdvance += outAdvances[p++] = SkScalarToFloat(scalarArray[i]);
            if (p < count &&
                    text[p] >= UNICODE_FIRST_LOW_SURROGATE &&
                    text[p] < UNICODE_FIRST_PRIVATE_USE &&
                    text[p-1] >= UNICODE_FIRST_HIGH_SURROGATE &&
                    text[p-1] < UNICODE_FIRST_LOW_SURROGATE) {
                outAdvances[p++] = 0;
            }
#if DEBUG_ADVANCES
            ALOGD("icu-adv = %f - total = %f", outAdvances[i], totalAdvance);
#endif
        }
    } else {
#if DEBUG_ADVANCES
    ALOGD("ICU -- count=%d", count);
#endif
        for (size_t i = 0; i < count; i++) {
            totalAdvance += outAdvances[i] = SkScalarToFloat(scalarArray[i]);
#if DEBUG_ADVANCES
            ALOGD("icu-adv = %f - total = %f", outAdvances[i], totalAdvance);
#endif
        }
    }
    *outTotalAdvance = totalAdvance;
}