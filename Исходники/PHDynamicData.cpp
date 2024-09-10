void PHDynamicData::CalculateData()
{

	DMXPStoFMX(dBodyGetRotation(body),
		dBodyGetPosition(body),BoneTransform);
	Fmatrix zero;
	zero.set(ZeroTransform);
	zero.invert();
	BoneTransform.mulB_43(zero);
	for(unsigned int i=0;i<numOfChilds;++i){

		Childs[i].CalculateR_N_PosOfChilds(body);
	}
}