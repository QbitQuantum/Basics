void STGGeneric::makeChildren(SphereTree *st, int node, int level, const SurfaceRep &surRep) const{
  //  get the error of the parent
  Sphere parS = st->nodes.index(node);
  double parErr = eval->evalSphere(parS);

  //  get minimum bounding sphere for points to give to reducer
  Sphere boundingSphere;
  SFWhite::makeSphere(&boundingSphere, *surRep.getSurPts());

  //  generate the set of child spheres
  Array<Sphere> initChildren, children;
  reducer->getSpheres(&initChildren, st->degree, surRep, &boundingSphere, parErr);

  //  do sphere refit - local optimisation
  if (useRefit){
    OUTPUTINFO("Refitting\n");
    SOPerSphere perSphere;
    perSphere.numIter = 3;
    perSphere.eval = eval;
    perSphere.optimise(&initChildren, surRep);
    }

  //  apply optimiser if required
  if (optimiser && (maxOptLevel < 0 || level <= maxOptLevel))
    optimiser->optimise(&initChildren, surRep, -1, &parS, level-1);

  //  remove redundent spheres
  RELargest reLargest;
  if (!reLargest.reduceSpheres(&children, initChildren, surRep))
    children.clone(initChildren);

  int numChildren = children.getSize();
  if (numChildren == 0)
    return;

  //  get the points that this node covers
  const Array<Surface::Point> *surPts = surRep.getSurPts();
  int numPts = surPts->getSize();

  //  info for areas to be covered by each sphere
  Array<Array<Surface::Point> > subPts(numChildren);
  Array<bool> covered(numPts);
  covered.clear();

  //  make the divisions between the children
  SurfaceDivision surDiv;
  surDiv.setup(children, surPts);

  //  do the children
  int firstChild = st->getFirstChild(node);
  for (int i = 0; i < numChildren; i++){
    //  get sphere
    Sphere s = children.index(i);

    //  list the points in the sphere
    Array<int> listPoints;
    surRep.listContainedPoints(&listPoints, NULL, s, NULL);
    int numList = listPoints.getSize();

    //  filter points
    Array<Surface::Point> *filterPts = &subPts.index(i);
    filterPts->resize(0);
    for (int j = 0; j < numList; j++){
      //  get point
      int pI = listPoints.index(j);
      Surface::Point p = surPts->index(pI);

      //  check if it's in the region
      if (surDiv.pointInRegion(p.p, i)){
        covered.index(j) = true;
        filterPts->addItem() = p;
        }
      }
    }

  //  count/cover uncovered points
  for (int i = 0; i < numPts; i++){
    if (!covered.index(i)){
      //  get the point
      Point3D p = surPts->index(i).p;

      //  find the closest sphere
      int closestJ = -1;
      float closestD = 0;
      for (int j = 0; j < numChildren;  j++){
        Sphere s = children.index(j);
        float d = p.distance(s.c) - s.r;
        if (d < closestD){
          closestJ = j;
          closestD = d;
          }
        }

      subPts.index(closestJ).addItem() = surPts->index(i);
      }
    }

  //  store spheres & recurse to children 
  int childNum = firstChild;
  for (int i = 0; i < numChildren; i++){
    if (subPts.index(i).getSize() > 1){
      //  recreate the sphere
      Sphere s = children.index(i);

      //  add sphere to tree
      st->nodes.index(childNum).c = s.c;
      st->nodes.index(childNum).r = s.r;

      if (level < st->levels-1 && numChildren > 1){
        const Array<Surface::Point> *pts = &subPts.index(i);

        //  make cells to have 10 pts each, most will have alot more
        int numCells = pts->getSize() / PTS_PER_CELL;
        int gridDim = ceil(pow(numCells, 1.0 / 3.0));
        OUTPUTINFO("numCells = %d, gridDim = %d\n", numCells, gridDim);

        //  make children by recursion
        SurfaceRep subRep;
        subRep.setup(*pts, gridDim);

        makeChildren(st, childNum, level+1, subRep);
        }

      childNum++;
      }
    }

  //  NULL out the rest of the spheres
  for (int i = childNum; i < st->degree; i++)
    st->initNode(firstChild+i, level+1);
}