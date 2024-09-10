float ShipCockpit::CalculateSignedForwardVelocity(vector3d normalized_forward, vector3d velocity) {
	float velz_cos = velocity.Dot(normalized_forward);
	return (velz_cos * normalized_forward).Length() * (velz_cos < 0.0 ? -1.0 : 1.0);
}