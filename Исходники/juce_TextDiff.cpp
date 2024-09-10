    static int findLongestCommonSubstring (String::CharPointerType a, const int lenA,
                                           const String::CharPointerType b, const int lenB,
                                           int& indexInA, int& indexInB)
    {
        if (lenA == 0 || lenB == 0)
            return 0;

        HeapBlock<int> lines;
        lines.calloc (2 + 2 * (size_t) lenB);

        int* l0 = lines;
        int* l1 = l0 + lenB + 1;

        int loopsWithoutImprovement = 0;
        int bestLength = 0;
        indexInA = indexInB = 0;

        for (int i = 0; i < lenA; ++i)
        {
            const juce_wchar ca = a.getAndAdvance();
            String::CharPointerType b2 (b);

            for (int j = 0; j < lenB; ++j)
            {
                if (ca != b2.getAndAdvance())
                {
                    l1[j + 1] = 0;
                }
                else
                {
                    const int len = l0[j] + 1;
                    l1[j + 1] = len;

                    if (len > bestLength)
                    {
                        loopsWithoutImprovement = 0;
                        bestLength = len;
                        indexInA = i;
                        indexInB = j;
                    }
                }
            }

            if (++loopsWithoutImprovement > 100)
                break;

            std::swap (l0, l1);
        }

        indexInA -= bestLength - 1;
        indexInB -= bestLength - 1;
        return bestLength;
    }