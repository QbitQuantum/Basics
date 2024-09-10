TEST( Transform, vectorTransformation )
{
   // construct a transformation we'll use for testing
   Transform trans;
   {
      trans.m_rotation.setAxisAngle( Quad_1000, FastFloat::fromFloat( DEG2RAD( 90.0f ) ) );
      trans.m_translation.set( 10, 20, 30 );
   }

   // create the test vector
   Vector testVec( 0, 20, 0 );

   // transform the vector
   Vector transformedVec;
   trans.transform( testVec, transformedVec );

   // the transform should:
   //  1. rotate the vector around the X axis, transforming it to ( 0, 0, 20 )
   //  2. translate it by ( 10, 20, 30 ), effectively transforming it to ( 10, 20, 50 )
   COMPARE_VEC( Vector( 10, 20, 50 ), transformedVec );
}