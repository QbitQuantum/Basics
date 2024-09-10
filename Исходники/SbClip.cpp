/*!
  Clip polygon against \a plane. This might change the number of
  vertices in the polygon. For each time a new vertex is created, the
  callback supplied in the constructor (if != NULL) is called with the
  line being clipped and the new vertex calculated. The callback
  should return a new void pointer to be stored by the clipper.
*/
void
SbClip::clip(const SbPlane & plane)
{
  int n = this->array[this->curr].getLength();

  if (n == 0) return;

  // create loop
  SbClipData dummy = this->array[this->curr][0];
  this->array[this->curr].append(dummy);

  const SbVec3f & planeN = plane.getNormal();

  for (int i = 0; i < n; i++) {
    SbVec3f v0, v1;
    void * data0, *data1;
    this->array[this->curr][i].get(v0, data0);
    this->array[this->curr][i+1].get(v1, data1);

    float d0 = plane.getDistance(v0);
    float d1 = plane.getDistance(v1);

    if (d0 >= 0.0f && d1 < 0.0f) { // exit plane
      SbVec3f dir = v1-v0;
      // we know that v0 != v1 since we got here
      (void) dir.normalize();
      float dot = dir.dot(planeN);
      SbVec3f newvertex = v0 - dir * (d0/dot);
      void * newdata = NULL;
      if (this->callback) {
        newdata = this->callback(v0, data0, v1, data1, newvertex, this->cbdata);
      }
      outputVertex(newvertex, newdata);
    }
    else if (d0 < 0.0f && d1 >= 0.0f) { // enter plane
      SbVec3f dir = v1-v0;
      // we know that v0 != v1 since we got here
      (void) dir.normalize();
      float dot = dir.dot(planeN);
      SbVec3f newvertex = v0 - dir * (d0/dot);
      void * newdata = NULL;
      if (this->callback) {
        newdata = this->callback(v0, data0, v1, data1, newvertex, this->cbdata);
      }
      outputVertex(newvertex, newdata);
      outputVertex(v1, data1);
    }
    else if (d0 >= 0.0f && d1 >= 0.0f) { // in plane
      outputVertex(v1, data1);
    }
  }
  this->array[this->curr].truncate(0);
  this->curr ^= 1;
}