    // Produce the pseudo-random set of records.
    static void createRecords (HeapBlock <Record>& records,
                               int numRecords,
                               int maxBytes,
                               std::int64_t seedValue)
    {
        using namespace UnitTestUtilities;

        Random r (seedValue);

        records.malloc (numRecords);

        int offset = 0;

        for (int i = 0; i < numRecords; ++i)
        {
            int const bytes = r.nextInt (maxBytes) + 1;

            records [i].index = i;
            records [i].bytes = bytes;
            records [i].offset = offset;

            offset += bytes;
        }

        repeatableShuffle (numRecords, records, seedValue);
    }