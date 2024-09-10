void CTracker::Update(vector<Point2f>& detections)
{
	// If there is no tracks yet, then every point begins its own track.
	if (tracks.size() == 0)
	{
		// If no tracks yet
		for (int i = 0; i < detections.size(); ++i)
		{
			CTrack* tr = new CTrack(detections[i], dt, Accel_noise_mag);
			tracks.push_back(tr);
		}	
	}

	int N = tracks.size();
	int M = detections.size();
	vector<vector<float>> Cost(N, vector<float>(M));
	vector<int> assignment;

	float dist;
	for (int i = 0; i < tracks.size(); ++i)
	{	
		// Point2f prediction=tracks[i]->prediction;
		// console_log(to_string(prediction.x) + to_string(prediction.y));
		for (int j = 0; j < detections.size(); ++j)
		{
			Point2f diff = (tracks[i]->prediction - detections[j]);
			dist = sqrtf(diff.x * diff.x + diff.y * diff.y);
			Cost[i][j] = dist;
		}
	}

	// Solving assignment problem (tracks and predictions of Kalman filter)
	AssignmentProblemSolver APS;
	APS.Solve(Cost, assignment, AssignmentProblemSolver::optimal);

	// clean assignment from pairs with large distance
	// Not assigned tracks
	vector<int> not_assigned_tracks;

	for (int i = 0; i < assignment.size(); ++i)
	{
		if (assignment[i] != -1)
		{
			if (Cost[i][assignment[i]] > dist_thres)
			{
				assignment[i] = -1;
				// Mark unassigned tracks, and increment skipped frames counter,
				// when skipped frames counter will be larger than threshold, track will be deleted.
				not_assigned_tracks.push_back(i);
			}
		}
		else
		{			
			// If track have no assigned detect, then increment skipped frames counter.
			tracks[i]->skipped_frames++;
		}

	}

	// If track didn't get detects long time, remove it.
	for (int i = 0; i < tracks.size(); ++i)
	{
		if (tracks[i]->skipped_frames > maximum_allowed_skipped_frames)
		{
			delete tracks[i];
			tracks.erase(tracks.begin() + i);
			assignment.erase(assignment.begin() + i);
			--i;
		}
	}

	// Search for unassigned detects
	vector<int> not_assigned_detections;
	vector<int>::iterator it;
	for (int i = 0; i < detections.size(); ++i)
	{
		it = find(assignment.begin(), assignment.end(), i);
		if (it == assignment.end())
		{
			not_assigned_detections.push_back(i);
		}
	}

	// and start new tracks for them.
	if (not_assigned_detections.size() != 0)
	{
		for (int i = 0; i < not_assigned_detections.size(); ++i)
		{
			CTrack* tr = new CTrack(detections[not_assigned_detections[i]], dt,Accel_noise_mag);
			tracks.push_back(tr);
		}	
	}

	// Update Kalman Filters state
	for (int i = 0; i < assignment.size(); ++i)
	{
		// If track updated less than one time, than filter state is not correct.
		tracks[i]->KF->GetPrediction();

		if (assignment[i] != -1) // If we have assigned detect, then update using its coordinates,
		{
			tracks[i]->skipped_frames = 0;
			tracks[i]->prediction = tracks[i]->KF->Update(detections[assignment[i]], 1);
			tracks[i]->raw = detections[assignment[i]];
		}
		else				  // if not continue using predictions
		{
			tracks[i]->prediction = tracks[i]->KF->Update(Point2f(0, 0), 0);
			tracks[i]->raw = Point2f(0, 0);
		}
		
		if(tracks[i]->trace.size() > max_trace_length)
		{
			tracks[i]->trace.erase(tracks[i]->trace.begin(), tracks[i]->trace.end() - max_trace_length);
		}

		tracks[i]->trace.push_back(tracks[i]->prediction);
		tracks[i]->KF->LastResult = tracks[i]->prediction;
	}

}