bool IK::Solve(Vector3 targetPos)
{
	//http://mrl.nyu.edu/~perlin/gdc/ik/ik.java.html

	//Get nodes
	Node* hip = effector_->GetParent()->GetParent();
	Node* knee = effector_->GetParent();

	// Get current world position for the 3 joints of the IK chain
	Vector3 hipPos = hip->GetWorldPosition(); // Thigh pos (hip joint)
	Vector3 kneePos = knee->GetWorldPosition(); // Calf pos (knee joint)
	Vector3 effectorPos = effector_->GetWorldPosition(); // Foot pos (ankle joint)

	// Pre IK Direction vectors
	Vector3 thighDir = kneePos - hipPos; // Thigh direction
	Vector3 calfDir = effectorPos - kneePos; // Calf direction	

	// Vectors lengths
	float A = Vector3(thighDir).Length();//length of hip to knee
	float B = Vector3(calfDir).Length();//length of knee to foot
	Vector3 P = hip->WorldToLocal(targetPos);//target at origin
	Vector3 D = hip->WorldToLocal(kneePos);//pre solve knee at origin
	//float limbLength = length1 + length2;
	//float lengthH = targetDir.Length();

	//PERLINS STUFF
	//bool test = Perlin(A,B,C,D);
	//GetSubsystem<DebugHud>()->SetAppStats("ik:", String(test) );
	//------
	Vector3 R;
	DefineM(P,D);
	R = Rot(Minv,P);
	//FIND D
	float c = R.Length();
    float d = Max(0.0f, Min(A, (c + (A*A-B*B)/c) / 2.0f));//FindD(A,B,R.Length());
    //FIND E
    float e = sqrtf(A*A-d*d);//FindE(A,d);
    Vector3 S = Vector3(d,e,0.0f);
    Vector3 Q = Rot(Mfwd,S);

    //Convert Q back to world space
    Vector3 worldQ = effector_->GetParent()->GetParent()->LocalToWorld(Q);

    //Get angles
    Vector3 tdn = thighDir.Normalized();
    Vector3 ntdn = Vector3(worldQ-hipPos).Normalized();
    Vector3 cdn = calfDir.Normalized();
    Vector3 ncdn = Vector3(targetPos-worldQ).Normalized();

    //Vector3 hipAxis = tdn.CrossProduct(ntdn); 
    //float hipAngle = tdn.Angle(ntdn);
    //Vector3 kneeAxis = cdn.CrossProduct(ncdn);
    //float kneeAngle = cdn.Angle(ncdn);

    //GetSubsystem<DebugHud>()->SetAppStats("ik:", String(hipAngle)+":"+String(kneeAngle) );

    //knee->SetWorldRotation(knee->GetWorldRotation() * Quaternion(kneeAngle,kneeAxis) );
	//hip->SetWorldRotation(hip->GetWorldRotation() * Quaternion(hipAngle,hipAxis) );
	//do top level first, then get new angle for lower level, since it might mangle it
	bool success = d > 0.0f && d < A;

	if(success)
	{
		Quaternion hipRot = Quaternion(tdn,ntdn);
		hip->Rotate(hipRot,TS_WORLD );
		knee->Rotate(Quaternion(cdn,ncdn)*hipRot.Inverse(),TS_WORLD );
	}

    if(drawDebug_)
    {
	    DebugRenderer* dbg = effector_->GetScene()->GetComponent<DebugRenderer>();
	    
	    /*dbg->AddLine(hipPos,hipPos+tdn,Color(0.0f,1.0f,0.0f),false);
    	dbg->AddLine(hipPos,hipPos+ntdn,Color(0.0f,0.0f,1.0f),false);
	    dbg->AddLine(kneePos,kneePos+cdn,Color(0.0f,1.0f,0.0f),false);
    	dbg->AddLine(kneePos,kneePos+ncdn,Color(0.0f,0.0f,1.0f),false);

    	dbg->AddSphere(Sphere(effectorPos,0.2f),Color(0.0f,1.0f,0.0f),false);
    	dbg->AddSphere(Sphere(targetPos,0.2f),Color(0.0f,0.0f,1.0f),false);*/
	    //at origin
	    /*dbg->AddSphere(Sphere(Vector3(),0.2f),Color(0.0f,0.0f,0.0f),false);//origin
	    dbg->AddSphere(Sphere(D,0.2f),Color(0.1f,0.0f,0.0f),false);//old elbow
	    dbg->AddSphere(Sphere(P,0.2f),Color(0.0f,1.0f,0.0f),false);//target
	    dbg->AddLine(Vector3(),P,Color(0.1f,0.1f,0.1f),false);

	    //show solve at origin
	    dbg->AddSphere(Sphere(Q,0.2f),Color(1.0f,0.0f,0.0f),false);
		dbg->AddLine(Vector3(),Q,Color(1.0f,0.0f,0.0f),false);
		dbg->AddLine(Q,P,Color(1.0f,0.0f,0.0f),false);*/

		//show solve at position
		dbg->AddSphere(Sphere(worldQ,0.2f),Color(1.0f,0.0f,0.0f),false);
		dbg->AddSphere(Sphere(targetPos,0.2f),Color(0.0f,1.0f,0.0f),false);
		dbg->AddLine(hipPos,worldQ,Color(1.0f,0.0f,0.0f),false);
		dbg->AddLine(worldQ,targetPos,Color(1.0f,0.0f,0.0f),false);
	}

    return success;

	
}