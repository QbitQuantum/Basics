void text_itemizer::itemize_direction(unsigned start, unsigned end)
{
    direction_runs_.clear();
    UErrorCode error = U_ZERO_ERROR;
    int32_t length = end - start;
    UBiDi *bidi = ubidi_openSized(length, 0, &error);
    if (!bidi || U_FAILURE(error))
    {
        MAPNIK_LOG_ERROR(text_itemizer) << "Failed to create bidi object: " << u_errorName(error) << "\n";
        return;
    }
    ubidi_setPara(bidi, text_.getBuffer() + start, length, UBIDI_DEFAULT_LTR, 0, &error);
    if (U_SUCCESS(error))
    {
        UBiDiDirection direction = ubidi_getDirection(bidi);
        if (direction != UBIDI_MIXED)
        {
            direction_runs_.emplace_back(direction, start, end);
        }
        else
        {
            // mixed-directional
            int32_t count = ubidi_countRuns(bidi, &error);
            if(U_SUCCESS(error))
            {
                for(int i=0; i<count; ++i)
                {
                    int32_t vis_length;
                    int32_t run_start;
                    direction = ubidi_getVisualRun(bidi, i, &run_start, &vis_length);
                    run_start += start; //Add offset to compensate offset in setPara
                    direction_runs_.emplace_back(direction, run_start, run_start+vis_length);
                }
            }
        }
    }
    else
    {
        MAPNIK_LOG_ERROR(text_itemizer) << "ICU error: " << u_errorName(error) << "\n"; //TODO: Exception
    }
    ubidi_close(bidi);
}