void
DEMParticleCreator::addExtraTranslations(const Vec& shift, 
                                         REAL boundaryMargin,
                                         Vec inPlaneDiag,
                                         REAL widthX, REAL widthY, REAL widthZ,
                                         const Face& face,
                                         const IntersectionStatus status, 
                                         std::vector<Vec>& translations) 
{
  if (status.second.first == Face::Location::VERTEX) {
    int vertIndex = status.second.second;
    //std::cout << "is vertex " << vertIndex << "\n";
    if (vertIndex == 0) {
      for (int ii = 1; ii < 4; ++ii) {
        Vec inPlane = face.vertex[ii] - face.vertex[vertIndex];
        auto length = inPlane.length();
        inPlane.normalizeInPlace();
        if (ii == 2) {
          inPlane *= length;
          inPlane += (inPlaneDiag*boundaryMargin);
        } else {
          inPlane *= (length + boundaryMargin);
        }
        Vec outOfPlane = inPlane + shift;
        translations.push_back(inPlane);
        translations.push_back(outOfPlane);
      }
    } else if (vertIndex == 1 || vertIndex == 3) {
      Vec normal = Vec(1,1,1) - inPlaneDiag;
      Vec vec1 = normal * Vec(widthX + boundaryMargin, 
        widthY + boundaryMargin, widthZ + boundaryMargin);
      Vec vec2 = face.vertex[2] - face.vertex[vertIndex];
      auto length = vec2.length();
      vec2.normalizeInPlace();
      vec2 *= (length + boundaryMargin);
      //std::cout << "vec1 = " << vec1 << " vec2 = " << vec2 << "\n";
      translations.push_back(vec1 + vec2);
    }
  } 
  else if (status.second.first == Face::Location::EDGE) {
    int edgeIndex = status.second.second;
    //std::cout << "is edge " << edgeIndex << "\n";
    if (edgeIndex == 0 || edgeIndex == 3) {
      int oppIndex = (edgeIndex+3) % 4;
      Vec inPlane = face.vertex[oppIndex] - face.vertex[edgeIndex];
      auto length = inPlane.length() + boundaryMargin;
      inPlane.normalizeInPlace();
      inPlane *= length;
      Vec outOfPlane = inPlane + shift;
      translations.push_back(inPlane);
      translations.push_back(outOfPlane);
    }
  }
}