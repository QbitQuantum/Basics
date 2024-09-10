void
FilterBridgeFraction::Calculate(OpenBabel::OBMol* mol)
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
      unsigned int natoms(m.NumAtoms());
      if (!natoms)
      {
         _result = 0.0;
         _passed = false;
         return;
      }
   
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
   
      _result = (double) m.NumAtoms() / (double) natoms;
   }
   else
   {
      _result = 0.0;
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