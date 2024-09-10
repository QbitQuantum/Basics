double CKinFuTracker::directRotation(const CKeyFrame::tp_ptr pRefeFrame_, const CKeyFrame::tp_ptr pLiveFrame_, SO3Group<double>* pR_rl_)
{
	Intr sCamIntr_ = pRefeFrame_->_pRGBCamera->getIntrinsics(2);
	Matrix3d K = Matrix3d::Identity();
	//note that camera parameters are 
	K(0, 0) = sCamIntr_.fx;
	K(1, 1) = sCamIntr_.fy;
	K(0, 2) = sCamIntr_.cx;
	K(1, 2) = sCamIntr_.cy;
	SO3Group<double> CurR_rl_ = *pR_rl_;
	SO3Group<double> PrevR_rl_ = *pR_rl_;
	SO3Group<double> MinR_rl_ = *pR_rl_;
	Matrix3d R_rl_Kinv = PrevR_rl_.matrix() *K.inverse();
	Matrix3d H_rl = K * R_rl_Kinv;

	//get R,T of previous 
	Matrix3d H_rl_t = H_rl.transpose();
	Matrix3d R_rl_Kinv_t = R_rl_Kinv.transpose();
	const Matd33&  devH_rl = pcl::device::device_cast<pcl::device::Matd33> (H_rl_t);
	const Matd33&  devR_rl_Kinv = pcl::device::device_cast<pcl::device::Matd33> (R_rl_Kinv_t);
	double dMinEnergy = numeric_limits<double>::max();
	double dPrevEnergy = numeric_limits<double>::max();
	dPrevEnergy = energy_direct_radiance_rotation(sCamIntr_, devR_rl_Kinv, devH_rl, _n_rad_origin_2_ref, _n_rad_live[2], _err_live[2]);
	dMinEnergy = dPrevEnergy;
	//cout << setprecision(15) << dMinEnergy << endl;
	for (short sIter = 0; sIter < 5; ++sIter) {
		//get R and T
		GpuMat gSumBuf = btl::device::direct_rotation(sCamIntr_, devR_rl_Kinv, devH_rl, _n_rad_origin_2_ref, _n_rad_live[2], _err_live[2]);
		Mat Buf; gSumBuf.download(Buf);
		SO3Group<double> R_rl = btl::utility::extractRFromBuffer<double>((double*)Buf.data);
		//cout << Tran_nc.matrix() << endl;
		CurR_rl_ = R_rl *PrevR_rl_;
		R_rl_Kinv = CurR_rl_.matrix()*K.inverse();
		H_rl = K * R_rl_Kinv;

		H_rl_t = H_rl.transpose();
		R_rl_Kinv_t = R_rl_Kinv.transpose();
		double dCurEnergy = energy_direct_radiance_rotation(sCamIntr_, devR_rl_Kinv, devH_rl, _n_rad_origin_2_ref, _n_rad_live[2], _err_live[2]);
		//cout << sIter << ": " << dPrevEnergy << " " << dCurEnergy << endl;
		if (dCurEnergy < dMinEnergy){
			dMinEnergy = dCurEnergy;
			MinR_rl_ = CurR_rl_;
		}
		if (dMinEnergy / dCurEnergy < 0.25){ //divereges
			//cout << "Diverge Warning:" << endl;
			dCurEnergy = dMinEnergy;
			CurR_rl_ = MinR_rl_;
			break;
		}
		PrevR_rl_ = CurR_rl_;
		if (fabs(dPrevEnergy / dCurEnergy - 1) < 0.01f){ //converges
			//cout << "Converges" << endl;
			dCurEnergy = dMinEnergy;
			CurR_rl_ = MinR_rl_;
			break;
		}
		dPrevEnergy = dCurEnergy;
	}
	*pR_rl_ = CurR_rl_;
	return dMinEnergy;
}