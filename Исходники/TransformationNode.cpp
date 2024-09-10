 /**
  * Get matrix representation of the transformation.
  *
  * @return Transformation matrix
  */
 Matrix<4,4,float> TransformationNode::GetTransformationMatrix() {
     // get the rotation from the quaternion
     Matrix<4,4,float> m = rotation.GetMatrix().GetExpanded();
     m.Transpose();
     // write in the positional information
     m(3,0) = position[0];
     m(3,1) = position[1];
     m(3,2) = position[2];
     return GetScaleMatrix() * m;
 }