TurnData GetTurnDirection(Vector3f _point_faced, Vector3f _point_to_face)
{
	TurnData d;
	_point_to_face.normalize();
	_point_faced.normalize();
	Vector3f right_vector = Vector3f(_point_faced.y, -_point_faced.x, 0);
	d.turn_factor = right_vector.dotProduct(_point_to_face);
	return d;
}