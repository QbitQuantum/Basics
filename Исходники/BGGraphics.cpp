/*
    offsetIndex:    [0] skeleton
                    [1] spline
                    [2] offset spline
*/
ofVec2f BGGraphics::calculateInternalTexOffset(float t, bool isSourceSpline, bool isSourceSegment, int offsetIndex) {

    const float triangleHeight = .5 * tanf(M_PI / 3.0);

    const float baseSize = sqrtf(3.0);
    const float halfBaseSize = .5 * baseSize;
    const ofVec2f source(0, 1);
    const ofVec2f sink1(-halfBaseSize, -.5);
    const ofVec2f sink2(halfBaseSize, -.5);
    const ofVec2f center = (source + sink1 + sink2) / 3.0;
    const float bezierOffset = 0.5 * baseSize;
    const float maxInternalOffset = (.25 * source - .5 * center + .25 * sink1).length();
    const float centerStretchFactor = (maxInternalOffset + bezierOffset) / bezierOffset;


    ofVec2f focusPt = isSourceSpline ? ofVec2f(baseSize, 1) : ofVec2f(0, -2);
    float fromFocusAngle = M_PI * (isSourceSpline ? (1.0 + t / 3.0) : ((1.0 + t) / 3.0));
    ofVec2f toPtVector(cosf(fromFocusAngle), sinf(fromFocusAngle));

    float offset = (offsetIndex == 2) ? (.5 * baseSize) : baseSize;
    ofVec2f xy = focusPt + offset * toPtVector;

    if(offsetIndex == 0) {
        //project point on base spline
        ofVec2f projBase = isSourceSegment ? ofVec2f(0,1) : ofVec2f(halfBaseSize, -.5);
        xy = dot(xy, projBase) * projBase;
    }

    //in case we are dealing with the center point:
    if(offsetIndex == -1)
        xy = ofVec2f(0,0);
    
    const ofVec2f cornerTL = source + (sink1 - sink2);
    const ofVec2f cornerTR = source + (sink2 - sink1);
    const ofVec2f cornerB = sink1 + (sink2 - source);

    ofVec2f vecSource = (center - source).normalize();
    ofVec2f vecSink1 = (sink1 - center).normalize();
    ofVec2f vecSink2 = (sink2 - center).normalize();
 
    float traversalDistance = 2. * (center - source).length();
 
    float projSource = dot(xy - source, vecSource);
    float projSink1 = dot(xy - sink1, vecSink1);
    float projSink2 = dot(xy - sink2, vecSink2);
 
    float orSource = cross(xy - source, vecSource);
    float orSink1 = cross(xy - sink1, vecSink1);
    float orSink2 = cross(xy - sink2, vecSink2);
 
    float val1 = projSource / traversalDistance;
    float val2 = 1.0 + projSink1 / traversalDistance;
    float val3 = 1.0 + projSink2 / traversalDistance;

    float offsetX = 0;
    if(ABS(projSource) < .0001)
        offsetX = val1;
    else if(ABS(projSink1) < .0001)
        offsetX = val2;
    else if(ABS(projSink2) < .0001)
        offsetX = val3;
    else {
        float power = 2.0;
        float weight1 = powf(1.0 / ABS(projSource), power);
        float weight2 = powf(1.0 / ABS(projSink1), power);
        float weight3 = powf(1.0 / ABS(projSink2), power);
        float sumWeight = weight1 + weight2 + weight3;
    
        offsetX = (weight1 / sumWeight) * val1
                    + (weight2 / sumWeight) * val2
                    + (weight3 / sumWeight) * val3;
    }
 
 
  ofVec2f to = xy - focusPt;
  float toDist = to.length();
  to /= toDist;
 
  float dist = MAX(0.0, toDist - bezierOffset);
 
  float maxAng = M_PI / 6.;
 
  float angle = acos(dot(to, (center - focusPt).normalize()));
  float maxOffset = baseSize / cos(M_PI / 6.0 - angle) - bezierOffset;
 
  float circDistFrac = dist / (baseSize - bezierOffset);
  float projDistFrac = dist / maxOffset;
 
 
  float angleFrac = 1. - angle / maxAng;
 
 
  float offFactor = pow(projDistFrac, 2.0 + abs(angleFrac) * projDistFrac);
  float offsetY = (1. - offFactor) * circDistFrac + offFactor * projDistFrac;
  offsetY = 1. - offsetY;

  if(isnan(offsetX) || isnan(offsetY))
      cout << "OFFSET VALUE is NaN" << endl;

  return ofVec2f(offsetX - .5, offsetY);
}