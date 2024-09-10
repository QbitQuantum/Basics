void AlgFourierProp::ft(FILE *fp,MomentaList& mlist)
{
  char *fname="ft(FILE*,MomentaList&)";
  VRB.Func(cname,fname);
  
  //----------------------------------------------------------------
  // begin loop over momenta
  //----------------------------------------------------------------
  int nmom;
  for( nmom=0; nmom < mlist.size(); nmom++ ) 
    {
      //------------------------------------------------------------
      // Calculate single momenta
      //------------------------------------------------------------
      
      momprop=Float(0.0);
      
      calcmom(mlist[nmom]);
      
      //------------------------------------------------------------
      // Global sum
      //------------------------------------------------------------
      
      // 288 = 4 x 3(src) x 4 x 3(snk) x 2(re/im)
      // the final argument means which direction to exclude.
      // here 99 means NO exclusion and end up to be a global sum

      slice_sum((Float*)&momprop, 288, 99);
      
      //------------------------------------------------------------
      // Output to file
      //------------------------------------------------------------
      
      int s1,c1,s2,c2;
      Fprintf(fp,"MOMENTUM= %d %d %d %d \n",
              mlist[nmom].x(),
              mlist[nmom].y(),
              mlist[nmom].z(),
              mlist[nmom].t() );
      for( s1=0; s1<4; ++s1){ 
	for( c1=0; c1<3; ++c1){
	  for( s2=0; s2<4; ++s2){ 
	    for( c2=0; c2<3; ++c2){
	      Fprintf(fp, "%-25.15e %-25.15e \n",
		      (Float)momprop.wmat().d[s1].c[c1].d[s2].c[c2].real(),
		      (Float)momprop.wmat().d[s1].c[c1].d[s2].c[c2].imag());
	    }
	  }
	}
      }
    }   // end loop over momenta
}