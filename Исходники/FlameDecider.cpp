bool FlameDecider::judge(map<int, Target>& targets)
{
    bool flameDetected = false;
    
    Mat temp;
    mFrame.copyTo(temp);
    
    for (map<int, Target>::iterator it = targets.begin(); it != targets.end(); it++) {
        bool isFlame = svmPredict(it->second.feature);
        it->second.isFlame = isFlame;
        if (isFlame) {
            flameDetected = true;
            rectangle(temp, it->second.region.rect, Scalar(0, 255, 0));
        }
    }
    
    namedWindow("result");
    moveWindow("result", 350, 400);
    imshow("result", temp);
    return flameDetected;
}