RealVectorValue
CrackFrontDefinition::calculateCrackFrontDirection(const Node* crack_front_node,
                                                   const RealVectorValue& tangent_direction,
                                                   const CRACK_NODE_TYPE ntype) const
{
  RealVectorValue crack_dir;
  RealVectorValue zero_vec(0.0);

  bool calc_dir = true;
  if (_end_direction_method == END_CRACK_DIRECTION_VECTOR)
  {
    if (ntype == END_1_NODE)
    {
      crack_dir = _crack_direction_vector_end_1;
      calc_dir = false;
    }
    else if (ntype == END_2_NODE)
    {
      crack_dir = _crack_direction_vector_end_2;
      calc_dir = false;
    }
  }

  if (calc_dir)
  {
    if (_direction_method == CRACK_DIRECTION_VECTOR)
    {
      crack_dir = _crack_direction_vector;
    }
    else if (_direction_method == CRACK_MOUTH)
    {
      if (_crack_mouth_coordinates.absolute_fuzzy_equals(*crack_front_node,1.e-15))
      {
        mooseError("Crack mouth too close to crack front node");
      }
      RealVectorValue mouth_to_front = *crack_front_node - _crack_mouth_coordinates;

      RealVectorValue crack_plane_normal = mouth_to_front.cross(tangent_direction);
      if (crack_plane_normal.absolute_fuzzy_equals(zero_vec,1.e-15))
      {
        mooseError("Vector from crack mouth to crack front node is collinear with crack front segment");
      }

      crack_dir = tangent_direction.cross(crack_plane_normal);
      Real dotprod = crack_dir*mouth_to_front;
      if (dotprod < 0)
      {
        crack_dir = -crack_dir;
      }
    }
    else if (_direction_method == CURVED_CRACK_FRONT)
    {
      crack_dir = tangent_direction.cross(_crack_plane_normal);
    }
  }
  crack_dir = crack_dir.unit();

  return crack_dir;
}