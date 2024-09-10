 //
 // GetVertexPosition
 //
 // Get the position of the given vertex
 //
 void Type::GetVertexPosition(Vector &pos, const Matrix &origin, S32 x, S32 z)
 {
   // Get the world position of the first shadow vertex
   origin.Transform(pos, GetLayer(LAYER_LOWER).GetCell(x, z).pos);
 }