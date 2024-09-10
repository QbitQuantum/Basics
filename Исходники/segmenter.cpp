    /**
     * Generic segmentation method that operates on the substring between
     * the given indices, using the given strategy for segmenting that
     * substring.
     *
     * @param first The index of the beginning of the string to work on
     * @param last The index of the end of the string to work on
     * @param type The type of segmentation to perform
     * @return a vector of segments (whose meaning depends on `type`)
     */
    std::vector<segment> segments(int32_t first, int32_t last,
                                  segment_t type) const
    {
        std::vector<segment> results;
        icu::BreakIterator* iter;
        if (type == segment_t::SENTENCES)
            iter = sentence_iter_.get();
        else if (type == segment_t::WORDS)
            iter = word_iter_.get();
        else
            throw std::runtime_error{"Unknown segmentation type"};

        auto status = U_ZERO_ERROR;
        UText utxt = UTEXT_INITIALIZER;
        utext_openUTF8(&utxt, text_.data() + first, last - first, &status);
        if (!U_SUCCESS(status))
        {
            std::string err = "Failed to open UText: ";
            err += u_errorName(status);
            throw std::runtime_error{err};
        }

        iter->setText(&utxt, status);
        if (!U_SUCCESS(status))
        {
            utext_close(&utxt);
            std::string err = "Failed to setText: ";
            err += u_errorName(status);
            throw std::runtime_error{err};
        }

        auto start = iter->first();
        auto end = iter->next();
        while (end != icu::BreakIterator::DONE)
        {
            results.emplace_back(first + start, first + end);
            start = end;
            end = iter->next();
        }
        utext_close(&utxt);
        return results;
    }