    void disturbMidpoint(ofVec3f & midPoint, ofVec3f const & bottomLeft, ofVec3f const & topLeft, ofVec3f const & topRight, ofVec3f const & bottomRight) {
      //if (std::rand() % 2 == 0) {
      //  return;
      //}
        midPoint[2] += (topLeft.distance(bottomRight) + topRight.distance(bottomLeft)) * randomValue();
        
        if (midPoint[2] < minHeight) {
            minHeight = midPoint[2];
        }
        if (midPoint[2] > maxHeight) {
            maxHeight = midPoint[2];
        }

    }