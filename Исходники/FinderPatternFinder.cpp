bool FinderPatternFinder::haveMultiplyConfirmedCenters() {
    int confirmedCount = 0;
    float totalModuleSize = 0.0f;
    size_t max = possibleCenters_.size();
    for (size_t i = 0; i < max; i++) {
        Ref<FinderPattern> pattern = possibleCenters_[i];
        if (pattern->getCount() >= CENTER_QUORUM) {
            confirmedCount++;
            totalModuleSize += pattern->getEstimatedModuleSize();
        }
    }
    if (confirmedCount < 3) {
        return false;
    }
    // OK, we have at least 3 confirmed centers, but, it's possible that one is a "false positive"
    // and that we need to keep looking. We detect this by asking if the estimated module sizes
    // vary too much. We arbitrarily say that when the total deviation from average exceeds
    // 5% of the total module size estimates, it's too much.
    float average = totalModuleSize / max;
    float totalDeviation = 0.0f;
    for (size_t i = 0; i < max; i++) {
        Ref<FinderPattern> pattern = possibleCenters_[i];
        totalDeviation += abs(pattern->getEstimatedModuleSize() - average);
    }
    return totalDeviation <= 0.05f * totalModuleSize;
}