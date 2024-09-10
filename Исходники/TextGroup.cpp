TextGroup::TextGroup(const std::string &input, hb_script_t script, const std::string &lang, hb_direction_t overallDirection)
    :script_(script)
     ,lang_(lang)
     ,overallDirection_(overallDirection)
{
    if(hb_script_get_horizontal_direction(script_) == HB_DIRECTION_LTR)
    {
        addRun(input, HB_DIRECTION_LTR);
    }
    else
    {
        auto text = UnicodeString::fromUTF8(input);
        auto length = text.length();
        printf("Hominlinx-->TextGroup::TextGroup str unicodelen[%d] ====text[0x%x]\n",length, text.charAt(0) );

        UErrorCode err = U_ZERO_ERROR;
        UBiDi *bidi = ubidi_openSized(length, 0, &err);//Bidrectional text
        ubidi_setPara(bidi, text.getBuffer(), length, hbDirectionToUBIDILevel(overallDirection_), 0, &err);
        auto direction = ubidi_getDirection(bidi);

        if(direction != UBIDI_MIXED)
        {
            addRun(input, uciDirectionToHB(direction));
        }
        else
        {
            auto count = ubidi_countRuns(bidi, &err);

            for(int i=0; i < count; ++i)
            {
                int32_t start, length;
                direction = ubidi_getVisualRun(bidi, i, &start, &length);
                addRun(text, direction, start, start + length);
            }

        }

        ubidi_close(bidi);
    }
}