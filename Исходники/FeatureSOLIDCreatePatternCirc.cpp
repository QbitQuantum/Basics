void FeatureSOLIDCreatePatternCirc::GetInfo(void)
{
	
	TransCAD::IStdSolidOperatePatternCircularFeaturePtr spFeature = GetTransCADFeature();

	TransCAD::IReferencePtr spTargetFeature = spFeature->TargetFeature;
	
	_featurename = spTargetFeature->ReferenceeName;

	
	_isradial = spFeature->IsRadialAnignment;

	_gcvt(spFeature->NumberOfPatterns, MAX_DIGITS, _patternnumber);
	
	_gcvt(spFeature->AngleIncrement, MAX_DIGITS, _angleincrement);


	spFeature->GetCenterAxis(&_ptorg[0],&_ptorg[1],&_ptorg[2],&_ptvec[0],&_ptvec[1],&_ptvec[2]);

	_ptvec[0]=0;
		_ptvec[1]=0;
			_ptvec[2]=1;
 
	cout<<_featurename<<endl<<_patternnumber<<endl<<_angleincrement<<endl<<_isradial<<endl<<endl<<endl;
	cout<<_ptorg[0]<<endl<<_ptorg[1]<<endl<<_ptorg[2]<<endl<<_ptvec[0]<<endl<<_ptvec[1]<<endl<<_ptvec[2]<<endl;


}