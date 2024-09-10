	virtual void Execute(SActivationInfo *pActInfo)
	{
		bool bResult = false;
		if (udpListener->IsWorking()) {
			if (udpListener->ReceiveLine() != -1) {
				string chaine = udpListener->GetRecMessage();
				string token0 = udpListener->GetToken(0);
				Quat gyro = udpListener->TokenToQuat(token0);
				string token1 = udpListener->GetToken(1);
				Vec3 accel = udpListener->TokenToVec3(token1);
				string token2 = udpListener->GetToken(2);
				float compass = udpListener->TokenToFloat(token2);
				
				//if(!gyro.IsValid()) CryLogAlways("NOT VALID");

				ActivateOutput(pActInfo, EOP_Gyro_xyz, Vec3(gyro.v.x,gyro.v.y,gyro.v.z));
				ActivateOutput(pActInfo, EOP_Gyro_w, gyro.w);
				
				ActivateOutput(pActInfo, EOP_Accel, accel);
				ActivateOutput(pActInfo, EOP_Compass, compass);
				
				bResult = true;
			}
		}
		return;
	}