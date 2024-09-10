void getRotationAndEyePositionFromModelView( const Matrix4f& modelViewMatrix,
                                                   Matrix3f& rotationMatrix,
                                                   Vector3f& eye )
{
    Matrix4f iMv;
    modelViewMatrix.inverse( iMv );
    iMv.get_sub_matrix( rotationMatrix, 0, 0 );
    iMv.get_translation( eye );
}