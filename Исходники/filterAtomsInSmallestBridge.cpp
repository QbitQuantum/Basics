void
FilterAtomsInSmallestBridge::Calculate(OpenBabel::OBMol* mol)
{
   // Are there rings?
   OpenBabel::OBAtom* atom;
   std::vector<OpenBabel::OBAtom*>::iterator i;
   bool rings(false);
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
   
      // Iteratively remove all endstanding atoms until none are left
      OpenBabel::OBAtom* atom;
      std::vector<OpenBabel::OBAtom*>::iterator i;
      bool endstanding(true);
      while (endstanding && m.NumAtoms())
      {
         endstanding = false;
         for (atom = m.BeginAtom(i); atom; atom = m.NextAtom(i))
         {
            if (atom->GetValence() < 2)
            {
               if (m.DeleteAtom(atom))
               {
                  endstanding = true;
                  break;
               }
            }
         }
      }

      // Now remove all ring atoms
      rings = true;
      while (rings && m.NumAtoms())
      {
         rings = false;
         for (atom = m.BeginAtom(i); atom; atom = m.NextAtom(i))
         {
            if (atom->IsInRing())
            {
               if (m.DeleteAtom(atom))
               {
                  rings = true;
                  break;
               }
            }
         }
      }
   
      // Separate into fragments
      if (m.NumAtoms())
      {
         std::vector<std::vector<int> > bridges;
         m.ContigFragList(bridges);
         _result = bridges[0].size();
         for (unsigned int i(1); i < bridges.size(); ++i)
         {
            if (bridges[i].size() < _result) _result = bridges[i].size();
         }
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
   else
   {
      _result = 0;
      _passed = true;
   }
}