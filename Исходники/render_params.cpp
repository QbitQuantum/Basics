bool RenderParamInterface::needsLayoutSub (BaseMolecule& mol)
{
   QS_DEF(RedBlackSet<int>, atomsToIgnore);
   atomsToIgnore.clear();
   for (int i = mol.multiple_groups.begin(); i < mol.multiple_groups.end(); i = mol.multiple_groups.next(i)) {
      const Array<int>& atoms = mol.multiple_groups[i].atoms;
      const Array<int>& patoms = mol.multiple_groups[i].parent_atoms;
      for (int j = 0; j < atoms.size(); ++j)
         atomsToIgnore.find_or_insert(atoms[j]);
      for (int j = 0; j < patoms.size(); ++j)
         if (atomsToIgnore.find(patoms[j]))
            atomsToIgnore.remove(patoms[j]);
   }
   for (int i = mol.vertexBegin(); i < mol.vertexEnd(); i = mol.vertexNext(i)) {
      if (atomsToIgnore.find(i))
         continue;
      for (int j = mol.vertexNext(i); j < mol.vertexEnd(); j = mol.vertexNext(j)) {
         if (atomsToIgnore.find(j))
            continue;
         const Vec3f& v = mol.getAtomXyz(i);
         const Vec3f& w = mol.getAtomXyz(j);
         Vec3f d;
         d.diff(v, w);
         d.z = 0;
         if (d.length() < 1e-3)
            return true;
      }
   }
   return false;
}