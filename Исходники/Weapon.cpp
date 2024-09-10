void Weapon::SetFireVector( Vector3D& Aim)
{
	//Point the bullet particles somewhere. Also
	//make sure that it ignores the rotation values
	//if we're using this.
	AimUsingRotation = false;
	Aim.Normalize();
	Bullets.StreamHeading.x = Aim.x*ProjectileSpeed;
	Bullets.StreamHeading.y = Aim.y*ProjectileSpeed;
	Bullets.StreamHeading.z = Aim.z*ProjectileSpeed;	

}