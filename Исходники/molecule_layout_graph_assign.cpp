bool MoleculeLayoutGraph::_prepareAssignedList (Array<int> &assigned_list, BiconnectedDecomposer &bc_decom, ObjArray<MoleculeLayoutGraph> &bc_components, Array<int> &bc_tree)
{
   assigned_list.clear();

   for (int i = vertexBegin(); i < vertexEnd(); i = vertexNext(i))
   {
      if (_layout_vertices[i].type == ELEMENT_NOT_DRAWN)
         continue;

      const Vertex &vert = getVertex(i);

      for (int j = vert.neiBegin(); j < vert.neiEnd(); j = vert.neiNext(j))
      {
         if (_layout_vertices[vert.neiVertex(j)].type == ELEMENT_NOT_DRAWN)
         {
            assigned_list.push(i);
            break;
         }
      }
   }

   if (assigned_list.size() == 0)
   {
      // restore ignored ears in chains
      for (int i = vertexBegin(); i < vertexEnd(); i = vertexNext(i))
         if (_layout_vertices[i].type == ELEMENT_IGNORE)
            _layout_vertices[i].type = ELEMENT_BOUNDARY;

      _refineCoordinates(bc_decom, bc_components, bc_tree);
      return false;
   }

   // ( 2] the list is ordered with cyclic atoms at the top of the list;
   //   with descending ATCD numbers and acyclic atoms at the bottom;
   //   of the list with descending ATCD numbers;;
   assigned_list.qsort(_vertex_cmp, this);
   return true;
}