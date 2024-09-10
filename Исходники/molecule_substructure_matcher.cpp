void MoleculeSubstructureMatcher::makeTransposition (BaseMolecule &mol, Array<int> &transposition_out)
{
   int i;

   transposition_out.clear();

   for (i = mol.vertexBegin(); i < mol.vertexEnd(); i = mol.vertexNext(i))
      transposition_out.push(i);

   transposition_out.qsort(_compare, &mol);
}