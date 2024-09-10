bool GenericObjectDetector::RunVOC()
{

	FileInfos imglist;
	db_man.Init(DB_VOC07);
	if( !db_man.GetImageList(imglist) )
		return false;

	for(size_t id=0; id<10; id++)
	{
		double start_t = getTickCount();

		img = imread(imglist[id].filepath);

		// preprocessing
		Preprocess(img);

		segmentor.DoSegmentation(img);
		const vector<visualsearch::SuperPixel>& sps = segmentor.superPixels;

		vector<ImgWin> det_wins;

		// loop all segment
		for (size_t sel_id=0; sel_id<sps.size(); sel_id++)
		{
			// test all window settings
			for(size_t win_id=0; win_id<winconfs.size(); win_id++)
			{
				// compute adjust range
				Point minpt, maxpt;
				if( !WinLocRange(sps[sel_id].box, winconfs[win_id], minpt, maxpt) )
					continue;

				Point curpt(sps[sel_id].box.x+sps[sel_id].box.width/2, sps[sel_id].box.y+sps[sel_id].box.height/2);
				double bestscore = 0;
				ImgWin bestWin;
				// do shifting
				for(int i=0; i<10; i++)
				{
					// generate locations
					vector<ImgWin> wins;
					SampleWinLocs(curpt, winconfs[win_id], minpt, maxpt, 6, wins);
					if(wins.empty())
						continue;

					for(size_t j=0; j<wins.size(); j++)
						wins[j].score = ComputeCenterSurroundMeanColorDiff(wins[j]);

					// sort
					sort(wins.begin(), wins.end());

					const ImgWin selWin = wins[wins.size()-1];
					//cout<<"Best score: "<<selWin.score<<endl;
					if(selWin.score > bestscore)
					{
						// shift to max point
						curpt.x = selWin.x + selWin.width/2;
						curpt.y = selWin.y + selWin.height/2;

						// update
						bestWin = selWin;
					}
				}

				det_wins.push_back(bestWin);
			}
		}

		sort(det_wins.begin(), det_wins.end());

		cout<<"Time for image "<<id<<": "<<(getTickCount()-start_t) / getTickFrequency()<<"s"<<endl;

		// visualize final results
		reverse(det_wins.begin(), det_wins.end());

		visualsearch::ImgVisualizer::DrawImgWins("final", img, det_wins);

		waitKey(0);
	}

	return true;
}