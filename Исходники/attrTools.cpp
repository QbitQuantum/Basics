ATTR_TYPE getPlugAttrType(MPlug plug)
{
	MStatus stat = MS::kSuccess;

	MPlug p = plug;
	while (p.isChild())
		p = p.parent();
	plug = p;
	MObject attObj = plug.attribute(&stat);
	MFnAttribute att(attObj);

	if (!stat)
		return ATTR_TYPE::ATTR_TYPE_NONE;
	MString attName = att.name();

	// all 3 child attributes are vectors for osl
	if (p.numChildren() == 3)
		return ATTR_TYPE::ATTR_TYPE_VECTOR;

	if (attName == "input1")
	{
		if (plug.node().hasFn(MFn::kMultiplyDivide))
			return ATTR_TYPE::ATTR_TYPE_VECTOR;
	}
	if (attName == "input2")
	{
		if (plug.node().hasFn(MFn::kMultiplyDivide))
			return ATTR_TYPE::ATTR_TYPE_VECTOR;
	}

	if (attName == "output")
	{
		if (plug.node().hasFn(MFn::kMultiplyDivide))
			return ATTR_TYPE::ATTR_TYPE_VECTOR;
	}

	if (attName == "outValue")
	{
		if (plug.node().hasFn(MFn::kGammaCorrect))
			return ATTR_TYPE::ATTR_TYPE_COLOR;
	}
	if (attName == "outDPdu")
		return ATTR_TYPE::ATTR_TYPE_VECTOR;

	if (attName == "outDPdv")
		return ATTR_TYPE::ATTR_TYPE_VECTOR;

	if (attName == "outColor")
		return ATTR_TYPE::ATTR_TYPE_COLOR;

	if (attName == "uvCoord")
		return ATTR_TYPE::ATTR_TYPE_VECTOR;

	if (attName == "outUV")
		return ATTR_TYPE::ATTR_TYPE_VECTOR;

	if (attName == "color")
		return ATTR_TYPE::ATTR_TYPE_COLOR;

	if (attName == "normalCamera")
		return ATTR_TYPE::ATTR_TYPE_VECTOR;

	if (attName == "pointWorld")
		return ATTR_TYPE::ATTR_TYPE_VECTOR;

	if (attName == "rayDirection")
		return ATTR_TYPE::ATTR_TYPE_VECTOR;

	if (att.isUsedAsColor())
		return ATTR_TYPE::ATTR_TYPE_COLOR;
	if (attObj.apiType() == MFn::kNumericAttribute)
	{
		MFnNumericAttribute na(attObj, &stat);
		if (!stat)
			return ATTR_TYPE::ATTR_TYPE_NONE;
		if (na.unitType() == MFnNumericData::Type::kFloat)
			return ATTR_TYPE::ATTR_TYPE_FLOAT;
	}
	if (attObj.apiType() == MFn::kAttribute3Float)
	{
		return ATTR_TYPE::ATTR_TYPE_VECTOR;
	}
	return ATTR_TYPE::ATTR_TYPE_NONE;
}