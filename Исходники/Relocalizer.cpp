void Relocalizer::threadLoop(int idx)
{
	if(!multiThreading && idx != 0) return;

	SE3Tracker* tracker = new SE3Tracker(w,h,K);

	boost::unique_lock<boost::mutex> lock(exMutex);
	while(continueRunning)
	{
		// if got something: do it (unlock in the meantime)
		if(nextRelocIDX < maxRelocIDX && CurrentRelocFrame)
		{
			Frame* todo = KFForReloc[nextRelocIDX%KFForReloc.size()];
			nextRelocIDX++;
			if(todo->neighbors.size() <= 2) continue;

			std::shared_ptr<Frame> myRelocFrame = CurrentRelocFrame;

			lock.unlock();

			// initial Alignment
			SE3 todoToFrame = tracker->trackFrameOnPermaref(todo, myRelocFrame.get(), SE3());

			// try neighbours
			float todoGoodVal = tracker->pointUsage * tracker->lastGoodCount / (tracker->lastGoodCount+tracker->lastBadCount);
			if(todoGoodVal > relocalizationTH)
			{
				int numGoodNeighbours = 0;
				int numBadNeighbours = 0;

				float bestNeightbourGoodVal = todoGoodVal;
				float bestNeighbourUsage = tracker->pointUsage;
				Frame* bestKF = todo;
				SE3 bestKFToFrame = todoToFrame;
				for(Frame* nkf : todo->neighbors)
				{
					SE3 nkfToFrame_init = se3FromSim3((nkf->getScaledCamToWorld().inverse() * todo->getScaledCamToWorld() * sim3FromSE3(todoToFrame.inverse(), 1))).inverse();
					SE3 nkfToFrame = tracker->trackFrameOnPermaref(nkf, myRelocFrame.get(), nkfToFrame_init);

					float goodVal = tracker->pointUsage * tracker->lastGoodCount / (tracker->lastGoodCount+tracker->lastBadCount);
					if(goodVal > relocalizationTH*0.8 && (nkfToFrame * nkfToFrame_init.inverse()).log().norm() < 0.1)
						numGoodNeighbours++;
					else
						numBadNeighbours++;

					if(goodVal > bestNeightbourGoodVal)
					{
						bestNeightbourGoodVal = goodVal;
						bestKF = nkf;
						bestKFToFrame = nkfToFrame;
						bestNeighbourUsage = tracker->pointUsage;
					}
				}

				if(numGoodNeighbours > numBadNeighbours || numGoodNeighbours >= 5)
				{
					if(enablePrintDebugInfo && printRelocalizationInfo)
						printf("RELOCALIZED! frame %d on %d (bestNeighbour %d): good %2.1f%%, usage %2.1f%%, GoodNeighbours %d / %d\n",
								myRelocFrame->id(), todo->id(), bestKF->id(),
								100*bestNeightbourGoodVal, 100*bestNeighbourUsage,
								numGoodNeighbours, numGoodNeighbours+numBadNeighbours);

					// set everything to stop!
					continueRunning = false;
					lock.lock();
					resultRelocFrame = myRelocFrame;
					resultFrameID = myRelocFrame->id();
					resultKF = bestKF;
					resultFrameToKeyframe = bestKFToFrame.inverse();
					resultReadySignal.notify_all();
					hasResult = true;
					lock.unlock();
				}
				else
				{
					if(enablePrintDebugInfo && printRelocalizationInfo)
						printf("FAILED RELOCALIZE! frame %d on %d (bestNeighbour %d): good %2.1f%%, usage %2.1f%%, GoodNeighbours %d / %d\n",
								myRelocFrame->id(), todo->id(), bestKF->id(),
								100*bestNeightbourGoodVal, 100*bestNeighbourUsage,
								numGoodNeighbours, numGoodNeighbours+numBadNeighbours);
				}
			}

			lock.lock();
		}
		else
		{
			newCurrentFrameSignal.wait(lock);
		}
	}

	delete tracker;
}