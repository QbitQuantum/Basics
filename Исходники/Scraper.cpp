bool Scraper::FindAllBMPs(const searchType type, HBITMAP hBmp, const double threshold, const int maxMatch, vector<MATCHPOINTS> &matches)
{
    // Convert HBITMAP to Mat
    unique_ptr<Gdiplus::Bitmap> pBitmap;
    pBitmap.reset(Gdiplus::Bitmap::FromHBITMAP(hBmp, NULL));
    Mat img = CGdiPlus::CopyBmpToMat(pBitmap.get());
    pBitmap.reset();

    cvtColor( img, img, CV_BGRA2BGR );

    // Find right image group
    imageType iType =
        type==searchGoldStorage ? goldStorage :
        type==searchElixStorage ? elixStorage :
        type==searchDarkStorage ? darkStorage :
        type==searchLootCollector ? collector :
        type==searchLootBubble ? lootBubble :
        type==searchDonateButton ? donateButton : (imageType) 0;

    int iTypeIndex = -1;
    for (int i = 0; i < (int) imageGroups.size(); i++)
        if (imageGroups[i].iType == iType)
            iTypeIndex = i;
    if (iTypeIndex == -1)
        return false;

    // Scan through each Mat in this image group
    int count = 0;

    for (int i = 0; i < (int) imageGroups[iTypeIndex].mats.size(); i++)
    {
        // Get matches for this image
        Mat result( FindMatch(img, imageGroups[iTypeIndex].mats[i]) );

        // Parse through matches in result set
        while (count < maxMatch)
        {
            double minVal, maxVal;
            Point minLoc, maxLoc;
            minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

            // Fill haystack with pure green so we don't match this same location
            rectangle(img, maxLoc, cv::Point(maxLoc.x + imageGroups[iTypeIndex].mats[i].cols, maxLoc.y + imageGroups[iTypeIndex].mats[i].rows), CV_RGB(0,255,0), 2);

            // Fill results array with lo vals, so we don't match this same location
            floodFill(result, maxLoc, 0, 0, Scalar(0.1), Scalar(1.0));

            if (maxVal >= threshold && maxVal > 0)
            {
                // Check if this point is within 10 pixels of an existing match to avoid dupes
                bool alreadyFound = false;

                for (int k=0; k<count; k++)
                {
                    if (DistanceBetweenTwoPoints((double) maxLoc.x, (double) maxLoc.y, (double) matches.at(k).x, (double) matches.at(k).y) < 10.0)
                    {
                        alreadyFound = true;
                        break;
                    }
                }

                // Add matched location to the vector
                if (alreadyFound == false)
                {
                    MATCHPOINTS match;
                    match.val = maxVal;
                    match.x = maxLoc.x;
                    match.y = maxLoc.y;
                    matches.push_back(match);
                    count++;
                }
            }
            else
            {
                break;
            }
        }

        if (count >= maxMatch)
            break;
    }

    return true;
}