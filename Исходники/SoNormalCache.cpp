/*!
  Generates per face normals for quad data.
*/
void
SoNormalCache::generatePerFaceQuad(const SbVec3f * const coords,
                                   const unsigned int numcoords,
                                   const int vPerRow,
                                   const int vPerColumn,
                                   const SbBool ccw)
{
#if NORMALCACHE_DEBUG && COIN_DEBUG
  SoDebugError::postInfo("SoNormalCache::generatePerFaceQuad", "generating normals");
#endif

  this->clearGenerator();
  PRIVATE(this)->normalArray.truncate(0, TRUE);
  // avoid reallocations in growable array by setting the buffer size first
  PRIVATE(this)->normalArray.ensureCapacity((vPerRow-1)*(vPerColumn-1));
  
#if COIN_DEBUG
  if (vPerRow <= 1 || vPerColumn <= 1 || 
      static_cast<unsigned int>(vPerRow * vPerColumn) > numcoords) {

    SoDebugError::postWarning("SoNormalCache::generatePerFaceQuad", "Illegal "
                              "facequad dimension: [%d %d] with %d coordinates "
                              "available. verticesPerRow and verticesPerColumn "
                              "should be > 1, and verticesPerRow * verticesPerColumn "
                              "<= number of coordinates available.", 
                              vPerRow, vPerColumn, numcoords);
  }
#endif // COIN_DEBUG

#define IDX(r, c) ((r)*(vPerRow)+(c))

  for (int i = 0; i < vPerColumn-1; i++) {
    for (int j = 0; j < vPerRow-1; j++) {
      const unsigned int idx1 = IDX(i, j);
      const unsigned int idx2 = IDX(i+1, j);
      const unsigned int idx3 = IDX(i, j+1);

      if (idx2 < numcoords) { // Check the largest index only
        SbVec3f n = (coords[idx2] - coords[idx1]).cross(coords[idx3] - coords[idx1]);

        // Be robust when it comes to erroneously specified polygons.
        if ((n.normalize() == 0.0f) && coin_debug_extra())  {
          static uint32_t normgenerrors_facequad = 0;
          if (normgenerrors_facequad < 1) {
            SoDebugError::postWarning("SoNormalCache::generatePerFaceQuad",
                                      "Erroneous triangle specification in model "
                                      "(indices= [%d, %d, %d], "
                                      "coords=<%f, %f, %f>, <%f, %f, %f>, <%f, %f, %f>) "
                                      "(this warning will be printed only once, "
                                      "but there might be more errors).",
                                      idx1, idx2, idx3,
                                      coords[idx1][0], coords[idx1][1], coords[idx1][2],
                                      coords[idx2][0], coords[idx2][1], coords[idx2][2],
                                      coords[idx3][0], coords[idx3][1], coords[idx3][2]);
          }
          normgenerrors_facequad++;
        }
        
        PRIVATE(this)->normalArray.append(ccw ? -n : n);
      }
      else {
        // Generate normals even for invalid input
        SbVec3f dummynormal(0.0, 0.0, 0.0);
        PRIVATE(this)->normalArray.append(ccw ? -dummynormal : dummynormal);
      }
    }
  }

#undef IDX

  if (PRIVATE(this)->normalArray.getLength()) {
    PRIVATE(this)->normalData.normals = PRIVATE(this)->normalArray.getArrayPtr();
    PRIVATE(this)->numNormals = PRIVATE(this)->normalArray.getLength();
  }

#if NORMALCACHE_DEBUG && COIN_DEBUG
  SoDebugError::postInfo("SoNormalCache::generatePerFaceQuad",
                         "generated normals per face quad: %p %d\n",
                         PRIVATE(this)->normalData.normals, PRIVATE(this)->numNormals);
#endif

}