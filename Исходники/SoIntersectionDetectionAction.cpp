// Execute full set of intersection detection operations on all the
// primitives that has been souped up from the scene graph.
void
SoIntersectionDetectionAction::PImpl::doIntersectionTesting(void)
{
  if (this->callbacks.empty()) {
    SoDebugError::postWarning("SoIntersectionDetectionAction::PImpl::doIntersectionTesting",
                              "intersection testing invoked, but no callbacks set up");
    return;
  }

  delete this->traverser;
  this->traverser = NULL;

  if (ida_debug()) {
    SoDebugError::postInfo("SoIntersectionDetectionAction::PImpl::doIntersectionTesting",
                           "total number of shapedata items == %d",
                           this->shapedata.getLength());

  }

  const SbOctTreeFuncs funcs = {
    NULL /* ptinsidefunc */,
    shapeinsideboxfunc,
    NULL /* insidespherefunc */,
    NULL /* insideplanesfunc */
  };

  SbBox3f b = this->fullxfbbox.project();
  // Add a 1% slack to the bounding box, to avoid problems in
  // SbOctTree due to floating point inaccuracies (see assert() in
  // SbOctTree::addItem()).
  //
  // This may be just a temporary hack -- see the FIXME at the
  // same place.
  SbMatrix m;
  m.setTransform(SbVec3f(0, 0, 0), // translation
                 SbRotation::identity(), // rotation
                 SbVec3f(1.01f, 1.01f, 1.01f), // scalefactor
                 SbRotation::identity(), // scaleorientation
                 SbVec3f(b.getCenter())); // center
  b.transform(m);

  SbOctTree shapetree(b, funcs);
  for (int k = 0; k < this->shapedata.getLength(); k++) {
    ShapeData * shape = this->shapedata[k];
    if (shape->xfbbox.isEmpty()) { continue; }
    shapetree.addItem(shape);
  }

  if (ida_debug()) { shapetree.debugTree(stderr); }

  // For debugging.
  unsigned int nrshapeshapeisects = 0;
  unsigned int nrselfisects = 0;

  const float theepsilon = this->getEpsilon();

  for (int i = 0; i < this->shapedata.getLength(); i++) {
    ShapeData * shape1 = this->shapedata[i];

    // If the shape has no geometry, immediately skip to next
    // iteration of for-loop.
    if (shape1->xfbbox.isEmpty()) { continue; }

    // Remove shapes from octtree as we iterate over the full set, to
    // avoid self-intersection and to avoid checks against other
    // shapes happening both ways.
    shapetree.removeItem(shape1);

    // FIXME: shouldn't we also invoke the filter-callback here? 20030403 mortene.
    if (this->internalsenabled) {
      nrselfisects++;
      SbBool cont;
      this->doInternalPrimitiveIntersectionTesting(shape1->getPrimitives(), cont);
      if (!cont) { goto done; }
    }

    SbBox3f shapebbox = shape1->xfbbox.project();
    if (theepsilon > 0.0f) {
      const SbVec3f e(theepsilon, theepsilon, theepsilon);
      // Extend bbox in all 6 directions with the epsilon value.
      shapebbox.getMin() -= e;
      shapebbox.getMax() += e;
    }
    SbList<void*> candidateshapes;
    shapetree.findItems(shapebbox, candidateshapes);

    if (ida_debug()) {
      SoDebugError::postInfo("SoIntersectionDetectionAction::PImpl::doIntersectionTesting",
                             "shape %d intersects %d other shapes",
                             i, candidateshapes.getLength());

      // debug, dump to .iv-file the "master" shape bbox given by i,
      // plus ditto for all intersected shapes
#if 0
      if (i == 4) {
        SoSeparator * root = new SoSeparator;
        root->ref();

        root->addChild(make_scene_graph(shape1->xfbbox, "mastershape"));

        for (int j = 0; j < candidateshapes.getLength(); j++) {
          ShapeData * s = (ShapeData * )candidateshapes[j];
          SbString str;
          str.sprintf("%d", j);
          root->addChild(make_scene_graph(s->xfbbox, str.getString()));
        }

        SoOutput out;
        SbBool ok = out.openFile("/tmp/shapechk.iv");
        assert(ok);
        SoWriteAction wa(&out);
        wa.apply(root);

        root->unref();
      }
#endif // debug
    }

    SbXfBox3f xfboxchk;
    if (theepsilon > 0.0f) { xfboxchk = expand_SbXfBox3f(shape1->xfbbox, theepsilon); }
    else { xfboxchk = shape1->xfbbox; }

    for (int j = 0; j < candidateshapes.getLength(); j++) {
      ShapeData * shape2 = static_cast<ShapeData *>(candidateshapes[j]);

      if (!xfboxchk.intersect(shape2->xfbbox)) {
        if (ida_debug()) {
          SoDebugError::postInfo("SoIntersectionDetectionAction::PImpl::doIntersectionTesting",
                                 "shape %d intersecting %d is a miss when tried with SbXfBox3f::intersect(SbXfBox3f)",
                                 i, j);
        }
        continue;
      }

      if (!this->filtercb ||
          this->filtercb(this->filterclosure, shape1->path, shape2->path)) {
        nrshapeshapeisects++;
        SbBool cont;
        this->doPrimitiveIntersectionTesting(shape1->getPrimitives(), shape2->getPrimitives(), cont);
        if (!cont) { goto done; }
      }
    }
  }

 done:
  if (ida_debug()) {
    SoDebugError::postInfo("SoIntersectionDetectionAction::PImpl::doIntersectionTesting",
                           "shape-shape intersections: %d, shape self-intersections: %d",
                           nrshapeshapeisects, nrselfisects);
  }
}