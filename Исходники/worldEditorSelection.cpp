void WorldEditorSelection::rotate(const EulerF & rot, const Point3F & center)
{
   // single selections will rotate around own axis, multiple about world
   if(size() == 1)
   {
      SceneObject* object = dynamic_cast< SceneObject* >( at( 0 ) );
      if( object )
      {
         MatrixF mat = object->getTransform();

         Point3F pos;
         mat.getColumn(3, &pos);

         // get offset in obj space
         Point3F offset = pos - center;
         MatrixF wMat = object->getWorldTransform();
         wMat.mulV(offset);

         //
         MatrixF transform(EulerF(0,0,0), -offset);
         transform.mul(MatrixF(rot));
         transform.mul(MatrixF(EulerF(0,0,0), offset));
         mat.mul(transform);

         object->setTransform(mat);
      }
   }
   else
   {
      for( iterator iter = begin(); iter != end(); ++ iter )
      {
         SceneObject* object = dynamic_cast< SceneObject* >( *iter );
         if( !object )
            continue;
            
         MatrixF mat = object->getTransform();

         Point3F pos;
         mat.getColumn(3, &pos);

         // get offset in obj space
         Point3F offset = pos - center;

         MatrixF transform(rot);
         Point3F wOffset;
         transform.mulV(offset, &wOffset);

         MatrixF wMat = object->getWorldTransform();
         wMat.mulV(offset);

         //
         transform.set(EulerF(0,0,0), -offset);

         mat.setColumn(3, Point3F(0,0,0));
         wMat.setColumn(3, Point3F(0,0,0));

         transform.mul(wMat);
         transform.mul(MatrixF(rot));
         transform.mul(mat);
         mat.mul(transform);

         mat.normalize();
         mat.setColumn(3, wOffset + center);

         object->setTransform(mat);
      }
   }

   mCentroidValid = false;
}