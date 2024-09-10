UBool 
DateIntervalFormat::setSeparateDateTimePtn(
                                 const UnicodeString& dateSkeleton,
                                 const UnicodeString& timeSkeleton) {
    const UnicodeString* skeleton;
    // if both date and time skeleton present,
    // the final interval pattern might include time interval patterns
    // ( when, am_pm, hour, minute differ ),
    // but not date interval patterns ( when year, month, day differ ).
    // For year/month/day differ, it falls back to fall-back pattern.
    if ( timeSkeleton.length() != 0  ) {
        skeleton = &timeSkeleton;
    } else {
        skeleton = &dateSkeleton;
    }

    /* interval patterns for skeleton "dMMMy" (but not "dMMMMy") 
     * are defined in resource,
     * interval patterns for skeleton "dMMMMy" are calculated by
     * 1. get the best match skeleton for "dMMMMy", which is "dMMMy"
     * 2. get the interval patterns for "dMMMy",
     * 3. extend "MMM" to "MMMM" in above interval patterns for "dMMMMy" 
     * getBestSkeleton() is step 1.
     */
    // best skeleton, and the difference information
    int8_t differenceInfo = 0;
    const UnicodeString* bestSkeleton = fInfo->getBestSkeleton(*skeleton, 
                                                               differenceInfo);
    /* best skeleton could be NULL.
       For example: in "ca" resource file,
       interval format is defined as following
           intervalFormats{
                fallback{"{0} - {1}"}
            }
       there is no skeletons/interval patterns defined,
       and the best skeleton match could be NULL
     */
    if ( bestSkeleton == NULL ) {
        return false; 
    } 
   
    // difference:
    // 0 means the best matched skeleton is the same as input skeleton
    // 1 means the fields are the same, but field width are different
    // 2 means the only difference between fields are v/z,
    // -1 means there are other fields difference 
    if ( differenceInfo == -1 ) { 
        // skeleton has different fields, not only  v/z difference
        return false;
    }

    if ( timeSkeleton.length() == 0 ) {
        UnicodeString extendedSkeleton;
        UnicodeString extendedBestSkeleton;
        // only has date skeleton
        setIntervalPattern(UCAL_DATE, skeleton, bestSkeleton, differenceInfo,
                           &extendedSkeleton, &extendedBestSkeleton);

        UBool extended = setIntervalPattern(UCAL_MONTH, skeleton, bestSkeleton, 
                                     differenceInfo,
                                     &extendedSkeleton, &extendedBestSkeleton);
                                              
        if ( extended ) {
            bestSkeleton = &extendedBestSkeleton;
            skeleton = &extendedSkeleton;
        }
        setIntervalPattern(UCAL_YEAR, skeleton, bestSkeleton, differenceInfo,
                           &extendedSkeleton, &extendedBestSkeleton);
    } else {
        setIntervalPattern(UCAL_MINUTE, skeleton, bestSkeleton, differenceInfo);
        setIntervalPattern(UCAL_HOUR, skeleton, bestSkeleton, differenceInfo);
        setIntervalPattern(UCAL_AM_PM, skeleton, bestSkeleton, differenceInfo);
    }
    return true;
}