 grasswedge(int i) :
   dir(2*M_PI*(i+0.5f)/float(NUMGRASSWEDGES), 0),
   across(2*M_PI*((i+0.5f)/float(NUMGRASSWEDGES) + 0.25f), 0),
   edge1(vec(2*M_PI*i/float(NUMGRASSWEDGES), 0).div(cos(M_PI/NUMGRASSWEDGES))),
   edge2(vec(2*M_PI*(i+1)/float(NUMGRASSWEDGES), 0).div(cos(M_PI/NUMGRASSWEDGES))),
   bound1(vec(2*M_PI*(i/float(NUMGRASSWEDGES) - 0.25f), 0), 0),
   bound2(vec(2*M_PI*((i+1)/float(NUMGRASSWEDGES) + 0.25f), 0), 0)
 {
     across.div(-across.dot(bound1));
 }