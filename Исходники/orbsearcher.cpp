/**
 * @brief Processed a search request.
 * @param request the request to proceed.
 */
u_int32_t ORBSearcher::searchImage(SearchRequest &request)
{
    timeval t[5];
    gettimeofday(&t[0], NULL);

    cout << "Loading the image and extracting the ORBs." << endl;

    Mat img;
    u_int32_t i_ret = ImageLoader::loadImage(request.imageData.size(),
                                             request.imageData.data(), img);
    if (i_ret != OK)
        return i_ret;

    vector<KeyPoint> keypoints;
    Mat descriptors;

    ORB(1000, 1.02, 100)(img, noArray(), keypoints, descriptors);

    gettimeofday(&t[1], NULL);

    cout << "time: " << getTimeDiff(t[0], t[1]) << " ms." << endl;
    cout << "Looking for the visual words. " << endl;

    unordered_map<u_int32_t, list<Hit> > imageReqHits; // key: visual word, value: the found angles
    for (unsigned i = 0; i < keypoints.size(); ++i)
    {
        #define NB_NEIGHBORS 1

        vector<int> indices(NB_NEIGHBORS);
        vector<int> dists(NB_NEIGHBORS);
        wordIndex->knnSearch(descriptors.row(i), indices,
                           dists, NB_NEIGHBORS);

        for (unsigned j = 0; j < indices.size(); ++j)
        {
            const unsigned i_wordId = indices[j];
            if (imageReqHits.find(i_wordId) == imageReqHits.end())
            {
                // Convert the angle to a 16 bit integer.
                Hit hit;
                hit.i_imageId = 0;
                hit.i_angle = keypoints[i].angle / 360 * (1 << 16);
                hit.x = keypoints[i].pt.x;
                hit.y = keypoints[i].pt.y;

                imageReqHits[i_wordId].push_back(hit);
            }
        }
    }

    cout << imageReqHits.size() << " visual words kept for the request." << endl;

    const unsigned i_nbTotalIndexedImages = index->getTotalNbIndexedImages();
    cout << i_nbTotalIndexedImages << " images indexed in the index." << endl;

    unordered_map<u_int32_t, vector<Hit> > indexHits; // key: visual word id, values: index hits.
    index->getImagesWithVisualWords(imageReqHits, indexHits);

    gettimeofday(&t[2], NULL);
    cout << "time: " << getTimeDiff(t[1], t[2]) << " ms." << endl;
    cout << "Ranking the images." << endl;

    unordered_map<u_int32_t, float> weights; // key: image id, value: image score.

    for (unordered_map<u_int32_t, vector<Hit> >::const_iterator it = indexHits.begin();
        it != indexHits.end(); ++it)
    {
        const vector<Hit> &hits = it->second;

        const float f_weight = log((float)i_nbTotalIndexedImages / hits.size());

        for (vector<Hit>::const_iterator it2 = hits.begin();
             it2 != hits.end(); ++it2)
        {
            /* TF-IDF according to the paper "Video Google:
             * A Text Retrieval Approach to Object Matching in Videos" */
            unsigned i_totalNbWords = index->countTotalNbWord(it2->i_imageId);
            weights[it2->i_imageId] += f_weight / i_totalNbWords;
        }
    }

    priority_queue<SearchResult> rankedResults;
    for (tr1::unordered_map<unsigned, float>::const_iterator it = weights.begin();
         it != weights.end(); ++it)
        rankedResults.push(SearchResult(it->second, it->first));

    gettimeofday(&t[3], NULL);
    cout << "time: " << getTimeDiff(t[2], t[3]) << " ms." << endl;
    cout << "Reranking 300 among " << rankedResults.size() << " images." << endl;

    priority_queue<SearchResult> rerankedResults;
    reranker.rerank(imageReqHits, indexHits,
                    rankedResults, rerankedResults, 300);

    gettimeofday(&t[4], NULL);
    cout << "time: " << getTimeDiff(t[3], t[4]) << " ms." << endl;
    cout << "Returning the results. " << endl;

    returnResults(rerankedResults, request, 100);

#if 0
    // Draw keypoints and ellipses.
    Mat img_res;
    drawKeypoints(img, cleanKeypoints, img_res, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    for (unsigned i = 0; i < ellipses.size(); ++i)
        ellipse( img_res, ellipses[i], Scalar(0, 0, 255), 1);

    // Show the image.
    imshow("Keypoints 1", img_res);
#endif

    return SEARCH_RESULTS;
}