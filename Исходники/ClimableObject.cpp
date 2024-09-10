float CClimableObject::DDSideToAxis(CPHCharacter *actor,Fvector &dir)const
{
	VERIFY(actor);
	DToAxis(actor,dir);
	Fvector side;side.set(m_side);to_mag_and_dir(side);
	float dot=side.dotproduct(dir);
	if(dot>0.f)
	{
		dir.set(side);
		return dot;
	}
	else
	{
		dir.set(side);
		dir.invert();
		return -dot;
	}
	
}