CKERROR CreateARTPlusPatternTransformationProto(CKBehaviorPrototype** pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("Single Marker Transformation");
	if(!proto) 	return CKERR_OUTOFMEMORY;

//---	Inputs declaration
	proto->DeclareInput("In");

//---	Outputs declaration
	proto->DeclareOutput("Out");

//----- Input Parameters Declaration
	proto->DeclareInParameter("Object", CKPGUID_3DENTITY);
	proto->DeclareInParameter("Pattern Number",CKPGUID_INT, "0");
	proto->DeclareInParameter("Pattern Width (cm)", CKPGUID_FLOAT, "8.0");

//---	Output Parameters Declaration
	proto->DeclareOutParameter("Position",CKPGUID_VECTOR);
	proto->DeclareOutParameter("Quaternion",CKPGUID_QUATERNION);
	proto->DeclareOutParameter("Marker ID",CKPGUID_INT, "-1");
	proto->DeclareOutParameter("Detected",CKPGUID_BOOL, FALSE);
	proto->DeclareOutParameter("Transformation Matrix",CKPGUID_MATRIX);

//----	Local Parameters Declaration

//----	Settings Declaration

	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetBehaviorCallbackFct(ARTPlusPatternTransformationCB,CKCB_BEHAVIORBASE|CKCB_BEHAVIOREDITIONS|CKCB_BEHAVIORPAUSE|CKCB_BEHAVIORREADSTATE|CKCB_BEHAVIORRESET|CKCB_BEHAVIORACTIVATESCRIPT|CKCB_BEHAVIORDEACTIVATESCRIPT|CKCB_BEHAVIORRESUME|CKCB_BEHAVIORLOAD|CKCB_BEHAVIORNEWSCENE,NULL);
	proto->SetFunction(ARTPlusPatternTransformation);

	*pproto = proto;
	return CK_OK;
}