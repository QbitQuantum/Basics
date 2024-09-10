bool CellTrack::tracking()
{	
	assert(m_numFrames >= 2);
	/*
	 * 0. reset containers
	 */
	cout<<endl<<"start tracking ..."<<endl;
	m_frames.clear();
	m_frames.resize(m_numFrames);
	if(! m_tracks.empty())
	{
		vector<Track>::iterator it = m_tracks.begin();
		while(it != m_tracks.end())
		{
			Cell* p = (*it).entry;
			assert(p!=NULL);
			Cell* next = p;
			while(p->next)
			{
				next = p->next;
				delete p;
				p = next;
			}
			delete p;
			it++;
		}
		m_tracks.clear();
		m_numTracks = 0;
	}
	/*
	 * 1. local variables and member vaiable getParams
	 */
	vector<Frame> t_frames;
	Alignment alg;
	t_frames.resize(2*m_numFrames - 2);
	double * row = NULL; // the delete operation of row is done by alg

	/*
	 * 2. the first round of comparison
	 */
	
	// 2.1 load the first tree

	int i = 0; // the entry of t_frames
	int t = 1; // the entry of time
	// 2.2 go to the loop of m_numFrames - 1 times comparison
	//     and m_numFrames -1 matches will bed set
	
	m_matches.resize(m_numFrames - 1);
	cout<<"\tThe first round alignment "<<endl;
	for(int t = 1; t < m_numFrames; t++)
	{
		cout<<"\talign tree"<<t<<" and tree"<<(t+1)<<endl;
		
		alg.align(m_trees[t-1], m_trees[t]);
		
		row = alg.result();

		create_match(row, m_trees[t-1].nodeCount(), m_trees[t].nodeCount(), m_matches[t-1]);

		create_frames(m_matches[t-1],t_frames[i],t_frames[i+1]);
				
		alg.clear();
		
		i = i + 2;
	}
	
	/*
	 * 3. the second round of alignment to merge nodes from tim 1 ~ m_numFrames -2
	 */
	cout<<endl<<"\tThe second round alignment "<<endl;
	i = 0;
	t = 0;
	m_frames[t++] = t_frames[i++];
	
	while( t <= m_numFrames - 2)
	{
		cout<<"\talign tree"<<(t+1)<<endl;
		
		alg.align(m_trees[t],t_frames[i], t_frames[i+1]);
		
		row = alg.result();
		
		m_frames[t++] = merge_frames(m_trees[t], row , t_frames[i], t_frames[i+1]);
		
		alg.clear();
				
		i = i+2;
	}
	// now t = m_numFrames - 1,  i+1 = 2*m_numFrames -2
	m_frames[t] = t_frames[i];
	
	t_frames.clear();
	
	/*
	 * 4. set tracks and trackId for each cell
	 */
	t = 0;
	int trackId = 1;         //the cell id starts from 1, the cell id = 0 is the background
	while(t < m_numFrames)
	{
		Frame& f = m_frames[t];
		Frame::iterator it = f.begin();
		while(it != f.end())
		{
			if((*it)->prev == NULL)
			{
				Track tk;
				tk.trackId = trackId;
				tk.start = t;
				tk.end = t;           // to be set later
				tk.altitude = 0.00;
				tk.entry = (*it);
				//set the cell's cell id
				Cell* p = *it;
				while(p)
				{
					ComponentTree::Node* node = m_trees[(tk.end)++].getNode(p->label);
					tk.altitude += node->mean - node->level;
					p->trackId = trackId;
					p = p->next;
				}
				tk.altitude = tk.altitude/(tk.end - tk.start);
				m_tracks.push_back(tk);
				trackId++;
			}
			it++;
		}
		t++;
	}
	m_numTracks = m_tracks.size();
	cout<<"number of tracks : "<<m_numTracks<<endl;
	//out put tracks
	for(int i=0; i< m_numTracks; i++)
	{
		Cell* entry = m_tracks[i].entry;
		Cell* p = entry;
		while(p)
		{
			p=p->next;
		}
	}
	cout<<endl;
	/*
	 * 5. save results according to the trackId and labels 
	 */
	time(&end);
	timeElapsed(start,end);
	
	saveImages();
	saveGraph();
	saveGraph2();
	saveTracking();
	
	return true;
}