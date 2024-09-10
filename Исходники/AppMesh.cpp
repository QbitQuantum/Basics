void AppMesh::computeNormals()
{
   // Clear normals
   normals.setSize( points.size() );
   for (S32 iNorm = 0; iNorm < normals.size(); iNorm++)
      normals[iNorm] = Point3F::Zero;

   // Sum triangle normals for each vertex
   for (S32 iPrim = 0; iPrim < primitives.size(); iPrim++)
   {
      const TSDrawPrimitive& prim = primitives[iPrim];

      for (S32 iInd = 0; iInd < prim.numElements; iInd += 3)
      {
         // Compute the normal for this triangle
         S32 idx0 = indices[prim.start + iInd + 0];
         S32 idx1 = indices[prim.start + iInd + 1];
         S32 idx2 = indices[prim.start + iInd + 2];

         const Point3F& v0 = points[idx0];
         const Point3F& v1 = points[idx1];
         const Point3F& v2 = points[idx2];

         Point3F n;
         mCross(v2 - v0, v1 - v0, &n);
         n.normalize();    // remove this to use 'weighted' normals (large triangles will have more effect)

         normals[idx0] += n;
         normals[idx1] += n;
         normals[idx2] += n;
      }
   }

   // Normalize the vertex normals (this takes care of averaging the triangle normals)
   for (S32 iNorm = 0; iNorm < normals.size(); iNorm++)
      normals[iNorm].normalize();
}