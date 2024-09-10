bool SubreadConverter::ConvertFile(HDFBasReader* reader,
                                   PacBio::BAM::BamWriter* writer,
                                   PacBio::BAM::BamWriter* scrapsWriter) 
{
    assert(reader);

    // initialize with default values (shared across all unmapped subreads)
    BamRecordImpl bamRecord;

    // read region table info
    std::unique_ptr<HDFRegionTableReader> const regionTableReader(new HDFRegionTableReader);
    RegionTable regionTable;
    string fn = filenameForReader_[reader];
    assert(!fn.empty());
    if (regionTableReader->Initialize(fn) == 0) {
        AddErrorMessage("could not read region table on "+fn);
        return false;
    }
    regionTable.Reset();
    regionTableReader->ReadTable(regionTable);
    regionTableReader->Close();

    // initialize read scores
    InitReadScores(reader);

    // fetch records from HDF5 file
    SMRTSequence smrtRecord;
    while (reader->GetNext(smrtRecord)) {

        // compute subread & adapter intervals
        SubreadInterval hqInterval;
        deque<SubreadInterval> subreadIntervals;
        deque<SubreadInterval> adapterIntervals;
        try {
            hqInterval = ComputeSubreadIntervals(&subreadIntervals,
                                                 &adapterIntervals,
                                                 regionTable,
                                                 smrtRecord.zmwData.holeNumber,
                                                 smrtRecord.length);
        } catch (runtime_error& e) {
            AddErrorMessage(string(e.what()));
            smrtRecord.Free();
            return false;
        }

        // sequencing ZMW
        if (IsSequencingZmw(smrtRecord))
        {
            // write subreads to main BAM file
            for (const SubreadInterval& interval : subreadIntervals)
            {
                // skip invalid or 0-sized intervals
                if (interval.End <= interval.Start)
                    continue;

                if (!WriteSubreadRecord(smrtRecord,
                                        interval.Start,
                                        interval.End,
                                        ReadGroupId(),
                                        static_cast<uint8_t>(interval.LocalContextFlags),
                                        writer))
                {
                    smrtRecord.Free();
                    return false;
                }
            }

            // if scraps BAM file present
            if (scrapsWriter)
            {
                // write 5-end LQ sequence
                if (hqInterval.Start > 0)
                {
                    if (!WriteLowQualityRecord(smrtRecord,
                                               0,
                                               hqInterval.Start,
                                               ScrapsReadGroupId(),
                                               scrapsWriter))
                    {
                        smrtRecord.Free();
                        return false;
                    }
                }

                // write adapters
                for (const SubreadInterval& interval : adapterIntervals) {

                    // skip invalid or 0-sized adapters
                    if (interval.End <= interval.Start)
                        continue;

                    if (!WriteAdapterRecord(smrtRecord,
                                            interval.Start,
                                            interval.End,
                                            ScrapsReadGroupId(),
                                            scrapsWriter))
                    {
                        smrtRecord.Free();
                        return false;
                    }
                }

                // write 3'-end LQ sequence
                if (hqInterval.End < smrtRecord.length)
                {
                    if (!WriteLowQualityRecord(smrtRecord,
                                               hqInterval.End,
                                               smrtRecord.length,
                                               ScrapsReadGroupId(),
                                               scrapsWriter))
                    {
                        smrtRecord.Free();
                        return false;
                    }
                }
            }
        } // sequencing ZMW

        // non-sequencing ZMW
        else
        {
            assert(!IsSequencingZmw(smrtRecord));

            // only write these if scraps BAM present & we are in 'internal mode'
            if (settings_.isInternal && scrapsWriter)
            {
                // write 5-end LQ sequence to scraps BAM
                if (hqInterval.Start > 0)
                {
                    if (!WriteLowQualityRecord(smrtRecord,
                                               0,
                                               hqInterval.Start,
                                               ScrapsReadGroupId(),
                                               scrapsWriter))
                    {
                        smrtRecord.Free();
                        return false;
                    }
                }

                // write subreads & adapters to scraps BAM, sorted by query start
                while (!subreadIntervals.empty() && !adapterIntervals.empty()) {

                    const SubreadInterval& subread = subreadIntervals.front();
                    const SubreadInterval& adapter = adapterIntervals.front();
                    assert(subread.Start != adapter.Start);

                    if (subread.Start < adapter.Start)
                    {
                        if (!WriteFilteredRecord(smrtRecord,
                                                 subread.Start,
                                                 subread.End,
                                                 ScrapsReadGroupId(),
                                                 static_cast<uint8_t>(subread.LocalContextFlags),
                                                 scrapsWriter))
                        {
                            smrtRecord.Free();
                            return false;
                        }

                        subreadIntervals.pop_front();
                    }
                    else
                    {
                        if (!WriteAdapterRecord(smrtRecord,
                                                adapter.Start,
                                                adapter.End,
                                                ScrapsReadGroupId(),
                                                scrapsWriter))
                        {
                            smrtRecord.Free();
                            return false;
                        }
                        adapterIntervals.pop_front();
                    }
                }

                // flush any traling subread intervals
                while (!subreadIntervals.empty())
                {
                    assert(adapterIntervals.empty());
                    const SubreadInterval& subread = subreadIntervals.front();
                    if (!WriteFilteredRecord(smrtRecord,
                                             subread.Start,
                                             subread.End,
                                             ScrapsReadGroupId(),
                                             static_cast<uint8_t>(subread.LocalContextFlags),
                                             scrapsWriter))
                    {
                        smrtRecord.Free();
                        return false;
                    }

                    subreadIntervals.pop_front();
                }

                // flush any remaining adapter intervals
                while (!adapterIntervals.empty())
                {
                    assert(subreadIntervals.empty());
                    const SubreadInterval& adapter = adapterIntervals.front();
                    if (!WriteAdapterRecord(smrtRecord,
                                            adapter.Start,
                                            adapter.End,
                                            ScrapsReadGroupId(),
                                            scrapsWriter))
                    {
                        smrtRecord.Free();
                        return false;
                    }
                    adapterIntervals.pop_front();
                }

                // write 3'-end LQ sequence to scraps BAM
                if (hqInterval.End < smrtRecord.length)
                {
                    if (!WriteLowQualityRecord(smrtRecord,
                                               hqInterval.End,
                                               smrtRecord.length,
                                               ScrapsReadGroupId(),
                                               scrapsWriter))
                    {
                        smrtRecord.Free();
                        return false;
                    }
                }
            }
        } // non-sequencing ZMW

        smrtRecord.Free();
    }

    // if we get here, all OK
    return true; 
} 