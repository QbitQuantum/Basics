TString MillePedeTrees::DelRphi(const TString &tree1, const TString &tree2) const
{
  // distance vector in rphi/xy plane times unit vector e_phi = (-y/r, x/r)
  // tree2 gives reference for e_phi 
  const TString deltaX = Parenth(tree1 + XPos() += (Min() += tree2) += XPos());
  const TString deltaY = Parenth(tree1 + YPos() += (Min() += tree2) += YPos());
  // (delta_x * (-y) + delta_y * x) / r
  // protect against possible sign of RPos:
  return Parenth(Parenth(deltaX + Mal() += ("-" + tree2) += YPos()
			 += Plu() += deltaY + Mal() += tree2 + XPos()
			 ) += Div() += Sqrt(RPos2(tree2)) //RPos(tree2)
		 );
}