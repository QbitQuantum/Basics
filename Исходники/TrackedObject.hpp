	bool getPoseAt(const ros::Time& time, StateType& pose, ros::Time& stamp)
	{
		std::deque<TimeState> past_poses_copy;

		{
			boost::mutex::scoped_lock past_poses_lock(past_poses_mutex_);
			past_poses_copy = past_poses_;
		}

		if (past_poses_copy.empty())
			return false;

		TimeState result = *(past_poses_copy.rbegin());
		if (result.first <= time)
		{
			typename std::deque<TimeState>::const_reverse_iterator iter =
					past_poses_copy.rbegin()++;
			while(iter != past_poses_copy.rend() && iter->first <= time)
			{
				iter++;
			}
			if (iter != past_poses_copy.rend())
			{
				// check which time is the nearest
				double delta_after = fabs(iter->first.toSec() - time.toSec());
				double delta_before = fabs(
						(iter - 1)->first.toSec() - time.toSec());
				if (delta_before < delta_after)
				{
					result = *(--iter);
				}
				else
				{
					result = *iter;
				}
			}
			else
			{
				result = *(--iter);
			}
		}

		pose = result.second;
		stamp = result.first;
		return true;
	}