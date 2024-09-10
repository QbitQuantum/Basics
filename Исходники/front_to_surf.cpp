Flux_Pts ell_fill(Pt2dr c,REAL A,REAL B,REAL teta,bool front)
{
      return new Flux_To_Surf_Not_Comp(ellipse(c,A,B,teta),front) ;
}