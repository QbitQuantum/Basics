void Molecule::setRotation(Quaternion q)
{
	q.normalize();
	rotation = q * rotation;
	for (size_t i=0;i<residueCount;i++)
	{
		Residues[i].relativePosition = q.rotateVector(Residues[i].relativePosition);
		Residues[i].position.x = Residues[i].relativePosition.x + center.x;
		Residues[i].position.y = Residues[i].relativePosition.y + center.y;
		Residues[i].position.z = Residues[i].relativePosition.z + center.z;
	}
}