  void
  fillSubModelArary (const ModelContainer* pModelContainer, const TreeNode *root, Array<SubModel>& array, Vector3& pLo, Vector3& pHi)
  {
    Vector3 lo = Vector3 (inf (), inf (), inf ());
    Vector3 hi = Vector3 (-inf (), -inf (), -inf ());
    //printf("[VMAP] %i Submodels\n", root->getNValues ());
    for (int i = 0; i < root->getNValues (); i++)
      {
        SubModel sm = pModelContainer->getSubModel (root->getStartPosition () + i);
        lo = lo.min (sm.getAABoxBounds ().low ());
        hi = hi.max (sm.getAABoxBounds ().high ());
        array.append (sm);
      }

    if (root->getChild ((TreeNode *) & pModelContainer->getTreeNode (0), 0))
      {
        fillSubModelArary (pModelContainer, root->getChild ((TreeNode *) & pModelContainer->getTreeNode (0), 0), array, lo, hi);
      }
    if (root->getChild ((TreeNode *) & pModelContainer->getTreeNode (0), 1))
      {
        fillSubModelArary (pModelContainer, root->getChild ((TreeNode *) & pModelContainer->getTreeNode (0), 1), array, lo, hi);
      }

    float dist1 = (hi - lo).magnitude ();
    AABox b;
    root->getBounds (b);
    float dist2 = (b.high () - b.low ()).magnitude ();
    if (dist1 > dist2)
      {
        // error
        //printf("error in boundingbox size vs. hi-lo size.");
        // this error seems to happen alot! maybe need to do something against it?
        int xxx = 0;
      }
  }