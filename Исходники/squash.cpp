MStatus squash::initialize()
{
	MFnNumericAttribute nAttr;
	MStatus				stat;

	lengthOriginal = nAttr.create( "lengthOriginal", "lo", MFnNumericData::kDouble, 1.0 );
	nAttr.setStorable(true);
	lengthModify = nAttr.create( "lengthModify", "lm", MFnNumericData::kDouble, 1.0 );
	nAttr.setStorable(true);
	squashRate = nAttr.create( "squashRate", "r", MFnNumericData::kDouble, 1.0 );
	nAttr.setStorable(true);
	forceValue = nAttr.create( "forceValue", "f", MFnNumericData::kDouble, 0.0 );
	nAttr.setStorable(true);

	output = nAttr.create( "output", "o", MFnNumericData::kDouble, 0.0 );
	nAttr.setWritable(false);
	nAttr.setStorable(true);

	stat = addAttribute( lengthOriginal );
		if (!stat) { stat.perror("addAttribute"); return stat;}
	stat = addAttribute( lengthModify );
		if (!stat) { stat.perror("addAttribute"); return stat;}
	stat = addAttribute( squashRate );
		if (!stat) { stat.perror("addAttribute"); return stat;}
	stat = addAttribute( forceValue );
		if (!stat) { stat.perror("addAttribute"); return stat;}
	stat = addAttribute( output );
		if (!stat) { stat.perror("addAttribute"); return stat;}

	stat = attributeAffects( lengthOriginal, output );
		if (!stat) { stat.perror("attributeAffects"); return stat;}
	stat = attributeAffects( lengthModify, output );
		if (!stat) { stat.perror("attributeAffects"); return stat;}
	stat = attributeAffects( squashRate, output );
		if (!stat) { stat.perror("attributeAffects"); return stat;}
	stat = attributeAffects( forceValue, output );
		if (!stat) { stat.perror("attributeAffects"); return stat;}

	return MS::kSuccess;
}