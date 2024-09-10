 void TripletHelper::FillRowCol_(Index n_entries, const IdentityMatrix& matrix, Index row_offset, Index col_offset, Index* iRow, Index* jCol)
 {
   DBG_ASSERT(n_entries == matrix.Dim());
   for (Index i=0; i<n_entries; i++) {
     iRow[i] = i + row_offset + 1;
     jCol[i] = i + col_offset + 1;
   }
 }