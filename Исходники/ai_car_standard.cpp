///trim the patch's width in-place
void AiCarStandard::TrimPatch(Bezier & patch, float trimleft_front, float trimright_front, float trimleft_back, float trimright_back)
{
	Vec3 frontvector = (patch.GetPoint(0,3) - patch.GetPoint(0,0));
	Vec3 backvector = (patch.GetPoint(3,3) - patch.GetPoint(3,0));
	float frontwidth = frontvector.Magnitude();
	float backwidth = backvector.Magnitude();
	if (trimleft_front + trimright_front > frontwidth)
	{
		float scale = frontwidth/(trimleft_front + trimright_front);
		trimleft_front *= scale;
		trimright_front *= scale;
	}
	if (trimleft_back + trimright_back > backwidth)
	{
		float scale = backwidth/(trimleft_back + trimright_back);
		trimleft_back *= scale;
		trimright_back *= scale;
	}

	Vec3 newfl = patch.GetPoint(0,0);
	Vec3 newfr = patch.GetPoint(0,3);
	Vec3 newbl = patch.GetPoint(3,0);
	Vec3 newbr = patch.GetPoint(3,3);

	if (frontvector.Magnitude() > 0.001)
	{
		Vec3 trimdirection_front = frontvector.Normalize();
		newfl = patch.GetPoint(0,0) + trimdirection_front*trimleft_front;
		newfr = patch.GetPoint(0,3) - trimdirection_front*trimright_front;
	}

	if (backvector.Magnitude() > 0.001)
	{
		Vec3 trimdirection_back = backvector.Normalize();
		newbl = patch.GetPoint(3,0) + trimdirection_back*trimleft_back;
		newbr = patch.GetPoint(3,3) - trimdirection_back*trimright_back;
	}

	patch.SetFromCorners(newfl, newfr, newbl, newbr);
}