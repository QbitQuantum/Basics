Surface makeGenCyl(const Curve &profile, const Curve &sweep )
{
    Surface surface;

    if (!checkFlat(profile))
    {
        cerr << "genCyl profile curve must be flat on xy plane." << endl;
        exit(0);
    }

    // TODO: Here you should build the surface.  See surf.h for details.
    Curve c = profile;
    Curve sweepL = sweep;
    unsigned step = sweep.size();
    Matrix4f transform;
    Matrix4f transinverse;
    Curve newc;
    vector<Curve> clist;
    for(unsigned i=0;i<step;i++){//sweepL.size();i++){
      CurvePoint p = sweepL[i];
      transform = getTransform(p);
      transinverse = transform.inverse();
      transinverse.transpose();
      newc.clear();
      for(unsigned j=0;j<c.size();j++){
	Vector4f tempV = transform*Vector4f(c[j].V,1);
	Vector4f tempN = transinverse*Vector4f(c[j].N,1);
	Vector3f newV = Vector3f(tempV[0],tempV[1],tempV[2]);
	Vector3f newN = Vector3f(-tempN[0],-tempN[1],-tempN[2]);
	struct CurvePoint newp = {newV,c[j].T,newN,c[j].B};
	newc.push_back(newp);
      }
      clist.push_back(newc);
    }
    for(unsigned k=0;k<clist.size()-1;k++){
      pushVV(surface,clist[k]);
      addTriangle(surface,clist[k],clist[k+1],k);
    }
    pushVV(surface,clist[clist.size()-1]);
    pushVV(surface,clist[0]);
    addTriangle(surface,clist[clist.size()-1],clist[0],clist.size()-1);
    return surface;
}