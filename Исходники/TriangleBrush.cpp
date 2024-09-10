bool TriangleBrush::isDistanceBigger(ofVec2f a, ofVec2f b, float distance){
            return a.distance(b) > distance? true : false;
}