/*Greedy method for data association & false positive models*/
void TrackAssociation::FindMatch(std::vector<AffinityVal> &affinity_mat, const std::vector<cv::Rect> &evidence, std::vector<int> &assign_match, std::vector<bool> &evidence_used, std::vector<bool> &model_used)
{
	const float default_th = 0.25f;
	//match threshold
	const float match_pos = 0.3f;
	const float match_scale = 0.7f;
	const float match_app = 0.52f; // range from [0,1]
	//w/o app model
	const float match_pos_no_app = 0.8f;
	const float match_scale_no_app = 0.9f;

	size_t model_size = subTrackVector.size(); // for each sub object
	size_t evidence_size = evidence.size(); // external detection

	assign_match.assign(evidence_size, -1); // assign list is for each detection evidence

	model_used.assign(model_size,false);
	evidence_used.assign(evidence_size,false);
	
	for(size_t i = 0; i < affinity_mat.size(); ++i)
	{
		AffinityVal &aff = affinity_mat[i];
		float probScale = aff.probScale;
		float probPos = aff.probPos;
		int index = aff.index;
		size_t n = index/model_size;//index of evidence
		size_t m = index-n*model_size;//index of model

		ObjSubTrack *subTrack = subTrackVector[m];

		size_t missing_count = subTrack->missing_count;
		float missing_discount = 1;
		float missing_discount_scale = 1;
		// upper limit for relaxation
		if(missing_count >= 4)
		{
			missing_count = 4;
			missing_discount = logf(1+missing_count/2.0f)+1;
		}

		float scale_th;
		float pos_th;
		if (subTrack->appModel.valid)
		{
			scale_th = match_scale;
			pos_th = match_pos;
		}else
		{//for tracks without appearance model
			scale_th = match_scale_no_app;
			pos_th = match_pos_no_app;

			if (missing_count >= 1)
			{
				missing_discount = 1.09f;
			}
		}

		bool space_scale_match;
		
		//for tracked lost objs
		if (subTrack->appModel.valid && subTrack->appModel.tracker.tracking_lost)
		{
			//loose positional threshold
			bool pos_fall;
			pos_fall = ((subTrack->appModel.tracker.searchRegion & evidence[n]).area()
				/ float(evidence[n].area())) > 0.0f;
			
			space_scale_match = pos_fall && probScale >= scale_th;
		}
		else
		{
			space_scale_match = probScale >= scale_th && probPos>= pos_th/missing_discount;
		}
		
		if(space_scale_match)
		{
			bool featureSupport = subTrack->TestFeatureSupport(objSeg,objSeg->frameNO,evidence[n]);
			if (featureSupport)
			{
				if(subTrack->appModel.valid)
				{
					float probApp = subTrack->appModel.TestHistSimi(this->frame_pool.back(),evidence[n]);
					float probHarr = subTrack->appModel.TestSimi(this->frame_pool.back(),evidence[n],true);
					probHarr = (probHarr + 1)/2;// to [0,1]
					aff.proApp = probApp + probHarr;
				}else //no valid appearance 
				{
					aff.proApp = default_th; //default value
				}
			}else
			{
				aff.proApp = 0;
			}
		}else
		{
			aff.proApp = 0;
		}
	}

	//sort by appearance values
	std::sort(affinity_mat.begin(),affinity_mat.end(),MyCompareFunc);

	for (size_t i = 0; i < affinity_mat.size(); ++i)
	{
		AffinityVal &aff = affinity_mat[i];
		int index = aff.index;
		int n = index/model_size;//index of evidence
		int m = index-n*model_size;//index of model
		float appVal = aff.proApp;
		if (appVal >= default_th)//above the threshold
		{
			if (!model_used[m] && !evidence_used[n])//both unused
			{
				assign_match[n] = m;
				model_used[m] = true;
				evidence_used[n] = true;
			}
		}
	}
}