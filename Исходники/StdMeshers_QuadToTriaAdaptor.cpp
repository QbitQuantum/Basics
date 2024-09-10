//=======================================================================
//function : FindBestPoint
//purpose  : Auxilare for Compute()
//           V - normal to (P1,P2,PC)
//=======================================================================
static gp_Pnt FindBestPoint(const gp_Pnt& P1, const gp_Pnt& P2,
                            const gp_Pnt& PC, const gp_Vec& V)
{
  double a = P1.Distance(P2);
  double b = P1.Distance(PC);
  double c = P2.Distance(PC);
  if( a < (b+c)/2 )
    return PC;
  else {
    // find shift along V in order to a became equal to (b+c)/2
    double shift = sqrt( a*a + (b*b-c*c)*(b*b-c*c)/16/a/a - (b*b+c*c)/2 );
    gp_Dir aDir(V);
    gp_Pnt Pbest( PC.X() + aDir.X()*shift,  PC.Y() + aDir.Y()*shift,
                  PC.Z() + aDir.Z()*shift );
    return Pbest;
  }
}