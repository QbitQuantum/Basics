void VectorLocalization2D::getPointCloudGradient(vector2f loc, float angle, vector2f& locGrad, float& angleGrad, const std::vector< vector2f >& pointCloud, const std::vector< vector2f >& pointNormals, float& logWeight, const VectorLocalization2D::PointCloudParams& pointCloudParams, const vector<int> & lineCorrespondences, const vector<line2f> &lines)
{
  //static const bool UseAnalyticRender = false;
  static const bool debug = false;
  FunctionTimer *ft;
  if(EnableProfiling)
    ft = new FunctionTimer(__FUNCTION__);
  
  float numTotalPoints = pointCloud.size();
  
  if(EnableProfiling) ft->Lap(__LINE__);
  
  /*
  float minRange = pointCloudParams.minRange;
  float maxRange = pointCloudParams.maxRange;
  float a0 = angle-0.5*pointCloudParams.fieldOfView;
  float a1 = angle+0.5*pointCloudParams.fieldOfView;
  if(UseAnalyticRender){
    lineCorrespondences = currentMap->getRayToLineCorrespondences(loc, angle, a0, a1, pointCloud, minRange, maxRange, true, &lines);
  }else{
    lineCorrespondences = currentMap->getRayToLineCorrespondences(loc, angle, a0, a1, pointCloud, minRange, maxRange);
    lines = currentMap->lines;
  }
  */
  if(EnableProfiling) ft->Lap(__LINE__);
  
  float numPoints = 0;
  
  float cosAngle;
  int noCorrespondences = 0;
  logWeight = 0.0;
  
  int numObservedPoints = int(pointCloud.size());
  pointCloudEval.numObservedPoints = numObservedPoints;
  
  //Construct gradients per point in point cloud
  gradients2.resize(numObservedPoints);
  points2.resize(numObservedPoints);
  int numPointsInt = 0;
  
  Vector2f curPoint, locE(V2COMP(loc)), attraction, lineNorm, rotatedNormal;
  Matrix2f rotMat1;
  rotMat1 = Rotation2Df(angle);
  
  for(int i=0; i<numObservedPoints; i++){
    curPoint = rotMat1*Vector2f(V2COMP(pointCloud[i])) + locE;
    rotatedNormal = rotMat1*Vector2f(V2COMP(pointNormals[i]));
    attraction = Vector2f(0,0);
    
    if(lineCorrespondences[i]>=0 && lineCorrespondences[i]<lines.size()){
      lineNorm = Vector2f(V2COMP(lines[lineCorrespondences[i]].Perp()));
      cosAngle = fabs(lineNorm.dot(rotatedNormal));
      
      //Attraction only for valid correspondences
      if(cosAngle > pointCloudParams.minCosAngleError){
        attraction = attractorFunction(lines[lineCorrespondences[i]], curPoint, pointCloudParams.attractorRange, pointCloudParams.correspondenceMargin);
        //Add the point and attraction (only if non-zero)
        //logWeight += -min(attraction.squaredNorm()/pointCloudParams.stdDev, -pointCloudParams.logShortHitProb)*pointCloudParams.corelationFactor;
        
        gradients2[numPointsInt] = attraction;
        points2[numPointsInt] = curPoint;
        numPointsInt++;
      }
    }else{
      noCorrespondences++;
    }
  }
  points2.resize(numPointsInt);
  gradients2.resize(numPointsInt);
  numPoints = float(numPointsInt);
  pointCloudEval.numCorrespondences = int(points2.size());
  
  if(debug) printf("No correspondences: %d/%d \n",noCorrespondences,int(pointCloud.size()));
  
  if(numPoints<pointCloudParams.minPoints){
    locGrad.zero();
    angleGrad = 0.0;
    return;
  }
  
  //Estimate translation and rotation
  Vector2f locGradE(0,0);
  Vector2f heading(0,0), curHeading, r;
  float headingAngle;
  pointCloudEval.meanSqError = 0.0;
  for(int i = 0; i<numPointsInt; i++){
    r = points2[i] - locE;
    pointCloudEval.meanSqError += gradients2[i].squaredNorm();
    if(r.squaredNorm()<sq(0.001))
      continue;
    
    locGradE += gradients2[i];
    headingAngle = eigenCross(r,gradients2[i]);
    curHeading = Vector2f(cos(headingAngle),sin(headingAngle));
    heading += curHeading;
  }
  locGradE = locGradE/numPoints;
  locGrad.set(locGradE.x(),locGradE.y());
  heading = heading/numPoints;
  pointCloudEval.meanSqError = pointCloudEval.meanSqError/numPoints;
  
  angleGrad = bound(atan2(heading.y(),heading.x()),-pointCloudParams.maxAngleGradient,pointCloudParams.maxAngleGradient);
  
  locGrad = locGrad.bound(pointCloudParams.maxLocGradient);
  if(debug) printf("LocGrad: %6.2f %6.2f AngleGrad:%6.1f\u00b0\n",V2COMP(locGrad), DEG(angleGrad));
    
  if(EnableProfiling) delete ft;
}