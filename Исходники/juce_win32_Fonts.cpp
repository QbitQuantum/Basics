    void createKerningPairs (HDC dc, const float height)
    {
        HeapBlock<KERNINGPAIR> rawKerning;
        const DWORD numKPs = GetKerningPairs (dc, 0, 0);
        rawKerning.calloc (numKPs);
        GetKerningPairs (dc, numKPs, rawKerning);

        kerningPairs.ensureStorageAllocated ((int) numKPs);

        for (DWORD i = 0; i < numKPs; ++i)
        {
            KerningPair kp;
            kp.glyph1 = getGlyphForChar (dc, rawKerning[i].wFirst);
            kp.glyph2 = getGlyphForChar (dc, rawKerning[i].wSecond);

            const int standardWidth = getGlyphWidth (dc, kp.glyph1);
            kp.kerning = (standardWidth + rawKerning[i].iKernAmount) / height;
            kerningPairs.add (kp);

            kp.glyph2 = -1;  // add another entry for the standard width version..
            kp.kerning = standardWidth / height;
            kerningPairs.add (kp);
        }
    }