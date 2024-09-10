    void
AlignerContext::printStats()
{
    double usefulReads = max((double) stats->usefulReads, 1.0);
    char errorRate[16];
    if (options->computeError) {
        _int64 numSingle = max(stats->singleHits, (_int64) 1);
        snprintf(errorRate, sizeof(errorRate), "%0.3f%%", (100.0 * stats->errors) / numSingle);
    } else {
        snprintf(errorRate, sizeof(errorRate), "-");
    }
    printf("%d\t%d\t%0.2f%%\t%0.2f%%\t%0.2f%%\t%0.2f%%\t%s\t%0.2f%%\t%lld\t%lld\t%.0f (at: %lld)\n",
            maxHits_, maxDist_, 
            100.0 * usefulReads / max(stats->totalReads, (_int64) 1),
            100.0 * stats->singleHits / usefulReads,
            100.0 * stats->multiHits / usefulReads,
            100.0 * stats->notFound / usefulReads,
            errorRate,
            100.0 * stats->alignedAsPairs / usefulReads,
            stats->lvCalls,
            stats->totalReads,
            (1000.0 * usefulReads) / max(alignTime, (_int64) 1), 
            alignTime);
    if (NULL != perfFile) {
        fprintf(perfFile, "%d\t%d\t%0.2f%%\t%0.2f%%\t%0.2f%%\t%0.2f%%\t%s\t%0.2f%%\t%lld\t%lld\tt%.0f\n",
                maxHits_, maxDist_, 
                100.0 * usefulReads / max(stats->totalReads, (_int64) 1),
                100.0 * stats->singleHits / usefulReads,
                100.0 * stats->multiHits / usefulReads,
                100.0 * stats->notFound / usefulReads,
                stats->lvCalls,
                errorRate,
                100.0 * stats->alignedAsPairs / usefulReads,
                stats->totalReads,
                (1000.0 * usefulReads) / max(alignTime, (_int64) 1));

        fprintf(perfFile,"\n");
    }
    // Running counts to compute a ROC curve (with error rate and %aligned above a given MAPQ)
    double totalAligned = 0;
    double totalErrors = 0;
    for (int i = AlignerStats::maxMapq; i >= 0; i--) {
        totalAligned += stats->mapqHistogram[i];
        totalErrors += stats->mapqErrors[i];
        double truePositives = (totalAligned - totalErrors) / max(stats->totalReads, (_int64) 1);
        double falsePositives = totalErrors / totalAligned;
        if (i <= 10 || i % 2 == 0 || i == 69) {
//            printf("%d\t%d\t%d\t%.3f\t%.2E\n", i, stats->mapqHistogram[i], stats->mapqErrors[i], truePositives, falsePositives);
        }
    }

    stats->printHistograms(stdout);

#ifdef  TIME_STRING_DISTANCE
    printf("%llds, %lld calls in BSD noneClose, not -1\n",  stats->nanosTimeInBSD[0][1]/1000000000, stats->BSDCounts[0][1]);
    printf("%llds, %lld calls in BSD noneClose, -1\n",      stats->nanosTimeInBSD[0][0]/1000000000, stats->BSDCounts[0][0]);
    printf("%llds, %lld calls in BSD close, not -1\n",      stats->nanosTimeInBSD[1][1]/1000000000, stats->BSDCounts[1][1]);
    printf("%llds, %lld calls in BSD close, -1\n",          stats->nanosTimeInBSD[1][0]/1000000000, stats->BSDCounts[1][0]);
    printf("%llds, %lld calls in Hamming\n",                stats->hammingNanos/1000000000,         stats->hammingCount);
#endif  // TIME_STRING_DISTANCE

    extension->printStats();
}