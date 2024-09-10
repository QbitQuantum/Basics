void PartFilter::computeDistance(int partition)
{
	std::multimap<int, std::string>::iterator it;
	for (int i=0 ; i<mModels.size() ; i++)
	{
		double distance=0;
		it = mOffsetPartToName[i].find(partition);
		for (it = mOffsetPartToName[i].equal_range(partition).first ; it != mOffsetPartToName[i].equal_range(partition).second ; ++it)
		{
			if (mJointNameToPos[(*it).second] != -1)
			{
				int pos = mJointNameToPos[(*it).second];
				double distTemp=0;
				// Mahalanobis distance
				//cout << (*it).second << "=>" << mPosNames[pos] << endl;
				Eigen::Vector3d jtPos = mModels[i]->getJoint((*it).second)->getXYZVect();
				Eigen::Vector3d jtObs(mCurrentFrame[pos][1], mCurrentFrame[pos][2], mCurrentFrame[pos][3]);
				Eigen::Vector3d diff = jtPos - jtObs;
				Eigen::Matrix3d cov;
				cov.setIdentity();
				distTemp = diff.transpose()*(cov*diff);
				distance += distTemp;
			}
		}
		mCurrentDistances[i] = distance;
	}
}