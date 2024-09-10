ofVec2f Simple3DTracker::_predictNextPosition(ofVec2f currentPosition, float* minCost)
{
    int bestx = currentPosition.x, besty = currentPosition.y;
    float bestcost = 9999999, cost, distance;
    const float alpha = _weightedMatchingCoefficient;

    if(!_template || !_tmp || !_tmp2)
        return currentPosition;

    // template matching
    IplImage* haystack = _cameraImage();
    cvMatchTemplate(haystack, _template->getCvImage(), _tmp2, CV_TM_CCOEFF);
    cvNormalize(_tmp2, _tmp2, 1.0, 0.0, CV_MINMAX);

    // find the best match
    for(int y = 0; y < _tmp2->height; y++) {
        const float *src = (const float*)(_tmp2->imageData + y * _tmp2->widthStep);
        unsigned char *dst = (unsigned char*)(_tmp->getCvImage()->imageData + y * _tmp->getCvImage()->widthStep);
        for(int x = 0; x < _tmp2->width; x++) {
            dst[x] = (unsigned char)(src[x] * 255.0f);
            distance = currentPosition.distance(ofVec2f(x, y));
            if(distance <= _lookupRadius) {
                cost = (alpha * (1.0f - src[x])) + ((1.0f - alpha) * distance / _lookupRadius);
                if(cost <= bestcost) { // weighted matching
                    bestx = x;
                    besty = y;
                    bestcost = cost;
                }
            }
        }
    }
    _tmp->flagImageChanged();

    // get the resulting position...
    ofVec2f result(bestx + _template->width/2, besty + _template->height/2);

    // return the min cost?
    if(minCost)
        *minCost = bestcost;

    // update the template?
    if(result.distance(currentPosition) >= UPDATETPL_MINDIST)
        _setTemplate(result);

    // done!
    return result;
}