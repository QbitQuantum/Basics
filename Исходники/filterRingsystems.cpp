void
FilterRingsystems::Calculate(OpenBabel::OBMol* mol)
{
   // Are there rings?
   bool rings(false);
   OpenBabel::OBAtom* atom;
   std::vector<OpenBabel::OBAtom*>::iterator i;
   for (atom = mol->BeginAtom(i); atom; atom = mol->NextAtom(i))
   {
      if (atom->IsInRing())
      {
         rings = true;
         break;
      }
   }
   
   if (rings)
   {
      // Make workcopy of original mol
      OpenBabel::OBMol m = *mol; m.DeleteHydrogens();
   
      // Remove all atoms that are not part of ring
      std::vector<OpenBabel::OBAtom*> nonRingAtoms;
      nonRingAtoms.clear();
      for (atom = m.BeginAtom(i); atom; atom = m.NextAtom(i))
      {
         if (!atom->IsInRing()) nonRingAtoms.push_back(atom);
      }
      for (unsigned int i(0); i < nonRingAtoms.size(); ++i)
      {
         m.DeleteAtom(nonRingAtoms[i]);
      }
      
      // Remove all bonds that are not part of a ring
      std::vector<OpenBabel::OBBond*> nonRingBonds;
      nonRingBonds.clear();
      OpenBabel::OBBond* bond;
      std::vector<OpenBabel::OBBond*>::iterator j;
      for (bond = m.BeginBond(j); bond; bond = m.NextBond(j))
      {
         if (!bond->IsInRing()) nonRingBonds.push_back(bond);
      }
      for (unsigned int i(0); i < nonRingBonds.size(); ++i)
      {
         m.DeleteBond(nonRingBonds[i]);
      }
      
      // Count ringsystems
      std::vector<std::vector< int > > ringsystems;
      m.ContigFragList(ringsystems);
      _result = ringsystems.size();

   }
   else
   {
      _result = 0;
   }
   
   if ((_minLimit && (_result < _min)) || (_maxLimit && (_result > _max)))
   {
      _passed = false;
   }
   else
   {
      _passed = true;
   }
}