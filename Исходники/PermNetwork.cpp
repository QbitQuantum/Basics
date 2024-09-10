// Compute one or more layers corresponding to one network of one leaf
void PermNetwork::setLayers4Leaf(long lyrIdx, const ColPerm& p,
				 const Vec<long>& benesLvls, long gIdx,
				 const SubDimension& leafData, 
				 const Permut& map2cube)
{
#ifdef DEBUG_PRINTOUT
  std::cerr << "Layer "<<lyrIdx<<", column-permutation="<< p << endl;
#endif
  // Compute the shift amounts for all the layers in this network
  Vec<bool> isID;
  Vec<Permut> shifts;
  if (benesLvls.length()==1) {// Special case for a "trivial" 1-layer network
    shifts.SetLength(1);
    isID.SetLength(1);
    isID[0] = !p.getShiftAmounts(shifts[0]);
  }
  else  // The general case of a multi-layer Benes network
    p.getBenesShiftAmounts(shifts,isID,benesLvls);

  // Copy the shift amounts to the right place in the bigger network,
  // renaming the slots from a linear array to the hyper cube
  for (long i=0; i<benesLvls.length(); i++) {
    PermNetLayer& lyr = layers[lyrIdx+i];
    lyr.genIdx = gIdx;
    lyr.isID = isID[i];
    lyr.e = leafData.e;
    if (!lyr.isID) {
#ifdef DEBUG_PRINTOUT
      std::cerr << "layer "<<lyrIdx+i<<": "<<shifts[i]<<endl;
#endif
      if (leafData.good) // For good leaves, shift by -x is the same as size-x
	for (long k=0; k<shifts[i].length(); k++)
	  if (shifts[i][k]<0) shifts[i][k] += leafData.size;
      applyPermToVec(lyr.shifts, shifts[i], map2cube); // do the renaming
#ifdef DEBUG_PRINTOUT
      std::cerr << "       : "<<lyr.shifts<<endl;
#endif
    }
    //    else std::cerr << "layer "<<lyrIdx+i<<"= identity\n";
  }
}