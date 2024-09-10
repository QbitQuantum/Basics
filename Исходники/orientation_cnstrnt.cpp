void OrientConstRotation::Update(TimeValue t){
	Interval iv = FOREVER;
	ivalid = FOREVER;
	
	int ct = pblock->Count(orientation_target_list);
	int ctf = pblock->Count(orientation_target_weight);

	float total_orient_target_weight_prev = 0.0f, total_orient_target_weight_current = 0.0f;
	float orient_targ_Wt_current = 0.0f;
	Quat quat_prev, quat_current, lCurRot;
	INode *orient_target_prev= NULL, *orient_target_current= NULL;
	Matrix3 targetTM(1);
	Point3 trans, scaleP;

	quat_prev.Identity();
	quat_current.Identity();
	lCurRot.Identity();

		if (ct == 1){
			pblock->GetValue(orientation_target_list, t, orient_target_prev, iv, 0);
			pblock->GetValue(orientation_target_weight, t, orient_targ_Wt_current, iv, 0);
				ivalid &= iv;

				if (orient_target_prev == NULL){
					targetTM.IdentityMatrix();
				}
				else {
					targetTM = orient_target_prev->GetNodeTM(t, &ivalid);
				}

				if (IsLocal() && orient_target_prev != NULL) {
					targetTM = targetTM * Inverse(orient_target_prev->GetParentTM(t));
				}
				AffineParts comps;		// Requires header decomp.h
				decomp_affine(targetTM, &comps);
				quat_current = comps.q;
				quat_current.Normalize();
				quat_current.MakeClosest(quat_prev);

				lCurRot = quat_current;

				quat_prev = lCurRot;
				total_orient_target_weight_prev += orient_targ_Wt_current;
//			}
		}
		else if (ct > 1){

			pblock->GetValue(orientation_target_list, t, orient_target_prev, iv, 0);
			pblock->GetValue(orientation_target_weight, t, orient_targ_Wt_current, iv, 0);
//			if (orient_target_prev != NULL)
//			{
				ivalid &= iv;

				if (orient_target_prev == NULL){
					targetTM.IdentityMatrix();
				}
				else {
					targetTM = orient_target_prev->GetNodeTM(t, &ivalid);
				}

				if (IsLocal() && orient_target_prev != NULL) {
					targetTM = targetTM * Inverse(orient_target_prev->GetParentTM(t));
				}
				AffineParts comps;		// Requires header decomp.h
				decomp_affine(targetTM, &comps);
				quat_current = comps.q;
				quat_current.Normalize();
				quat_current.MakeClosest(quat_prev);

				lCurRot = quat_current;

				quat_prev = lCurRot;
				total_orient_target_weight_prev += orient_targ_Wt_current;
//			}

			for (int i = 0; i < ct -1; i++) {
//				ct = pblock->Count(orientation_target_list);
				pblock->GetValue(orientation_target_list, t, orient_target_current, iv, i+1);
				pblock->GetValue(orientation_target_weight, t, orient_targ_Wt_current, iv, i+1);
//				if (orient_target_current != NULL){
					ivalid &= iv;

					if (orient_target_current == NULL){
						targetTM.IdentityMatrix();
					}
					else {
						targetTM = orient_target_current->GetNodeTM(t, &ivalid);
					}

//					Matrix3 targetTM = orient_target_current->GetNodeTM(t, &ivalid);
					if (IsLocal() && orient_target_current != NULL) {
						targetTM = targetTM * Inverse(orient_target_current->GetParentTM(t));
					}
					AffineParts comps;		// Requires header decomp.h
					decomp_affine(targetTM, &comps);
					quat_current = comps.q;
					quat_current.Normalize();
					quat_current.MakeClosest(quat_prev);

					float slerp_wt = 0.0f;
					if ((total_orient_target_weight_prev + orient_targ_Wt_current) != 0.0){
						slerp_wt = orient_targ_Wt_current / (total_orient_target_weight_prev + orient_targ_Wt_current);
					}

					lCurRot = Slerp(quat_prev, quat_current, slerp_wt);
					lCurRot.Normalize();

					quat_prev = lCurRot;
					total_orient_target_weight_prev += orient_targ_Wt_current;
//				}
			}			//for (int i = 0; i < ct -1; i++)
		}				//else if (ct > 1)

		if (oldTargetNumber != ct) {
			InitialOrientQuat = lCurRot;
		}

		curRot = lCurRot;
		if (total_orient_target_weight_prev > 0.0){
			if (Relative()){
				if(IsLocal()){
					curRot =   baseRotQuatLocal * (lCurRot /InitialOrientQuat);
				}
				else{
					curRot =   baseRotQuatWorld * (lCurRot /InitialOrientQuat);
				}
			}
		}
		else {
			curRot = baseRotQuatLocal;
		}
		curRot.MakeClosest(IdentQuat());
		curRot.Normalize();
		oldTargetNumber = ct;
//	if (ivalid.Empty()) ivalid.SetInstant(t);
}