Mat TargetExtractor::extract(const Mat& frame, map<int, Target>& targets, bool track)
{
    mFrame = frame;

    /* for 2.avi:
     *     movement:   0.008;
     *     color:      120, 0.2;
     *     regionGrow: enable;
     * for 6.avi:
     *     movement:   0.012;
     *     color:      150, 0.4;
     *     regionGrow: disable;
     */

    movementDetect(0.012);
    colorDetect(150, 0.4);

    denoise(7, 5);
    fill(7, 5);
    medianBlur(mMask, mMask, 3);

    // TODO: make use of accumulate result

    //regionGrow();
    //fill(7, 6);
    //medianBlur(mMask, mMask, 3);

    //Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
    //erode(mMask, mMask, element);
    //dilate(mMask, mMask, element);

    smallAreaFilter(12, 8);
#ifdef DEBUG_OUTPUT
    namedWindow("mask");
    moveWindow("mask", 350, 120);
    imshow("mask", mMask);
#endif
    if (track) {
        blobTrack(targets);
    }
    return mMask;
}