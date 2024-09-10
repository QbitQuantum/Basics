 void Curve3<Real>::GetFrame ( Real t, Vector3<Real>& position,
                               Vector3<Real>& tangent, Vector3<Real>& normal, Vector3<Real>& binormal )
 const
 {
     position = GetPosition( t );
     Vector3<Real> velocity = GetFirstDerivative( t );
     Vector3<Real> acceleration = GetSecondDerivative( t );
     Real VDotV = velocity.Dot( velocity );
     Real VDotA = velocity.Dot( acceleration );
     normal = VDotV * acceleration - VDotA * velocity;
     normal.Normalize();
     tangent = velocity;
     tangent.Normalize();
     binormal = tangent.Cross( normal );
 }