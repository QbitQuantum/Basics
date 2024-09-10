void font_face_set::get_string_info(string_info & info, UnicodeString const& ustr, char_properties *format)
{
    double avg_height = character_dimensions('X').height();
    UErrorCode err = U_ZERO_ERROR;
    UnicodeString reordered;
    UnicodeString shaped;

    int32_t length = ustr.length();

    UBiDi *bidi = ubidi_openSized(length, 0, &err);
    ubidi_setPara(bidi, ustr.getBuffer(), length, UBIDI_DEFAULT_LTR, 0, &err);

    ubidi_writeReordered(bidi, reordered.getBuffer(length),
                         length, UBIDI_DO_MIRRORING, &err);

    reordered.releaseBuffer(length);

    u_shapeArabic(reordered.getBuffer(), length,
                  shaped.getBuffer(length), length,
                  U_SHAPE_LETTERS_SHAPE | U_SHAPE_LENGTH_FIXED_SPACES_NEAR |
                  U_SHAPE_TEXT_DIRECTION_VISUAL_LTR, &err);

    shaped.releaseBuffer(length);

    if (U_SUCCESS(err)) {
        StringCharacterIterator iter(shaped);
        for (iter.setToStart(); iter.hasNext();) {
            UChar ch = iter.nextPostInc();
            char_info char_dim = character_dimensions(ch);
            char_dim.format = format;
            char_dim.avg_height = avg_height;
            info.add_info(char_dim);
        }
    }


#if (U_ICU_VERSION_MAJOR_NUM*100 + U_ICU_VERSION_MINOR_NUM >= 406)
    if (ubidi_getBaseDirection(ustr.getBuffer(), length) == UBIDI_RTL)
    {
        info.set_rtl(true);
    }
#endif

    ubidi_close(bidi);
}