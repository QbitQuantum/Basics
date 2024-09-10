void reorder_nodeList_merge_bitNumber(const pair<vector<int>, vector<int> >  &iDx, vector<Node> &nodeList, int sz)
{
	#ifdef OPEN_ALL_STREAMS
	stringstream ss;
	ss << "graphs\\slashburn_graph_" << sz << ".txt";
	string fileName; ss >> fileName;
    fstream fs(fileName.c_str(), std::ios::out);
	#endif // OPEN_ALL_STREAMS
	for(vector<Node>::iterator sit = nodeList.begin(); sit != nodeList.end(); ++sit){
		if(SLASHBURN_GRAPH_WIDTH == SUB_CNT){
			sit->rowId = iDx.first[sit->rowId];
		}
		for(BitList::iterator bit = sit->bitList.begin(); bit != sit->bitList.end(); ++bit){
			bit->colId = iDx.second[bit->colId];
			#ifdef OPEN_ALL_STREAMS
			fs << sit->rowId + 1 << " " << bit->colId + 1 << " " << bit->weight << endl;
			#endif // OPEN_ALL_STREAMS
        }
	}
	sort(nodeList.begin(), nodeList.end(), cmp);
	int newsz = (int)ceil((int)nodeList.size() * 1.0 / BASE_NUM);
	vector<Node> tmp(newsz);
	for(int sit = 0; sit < (int)nodeList.size(); sit += BASE_NUM){
		BitList mergedList;
		map<int, BitNumber> bitNumberCollector;
		for(int offset = 0; offset < min(BASE_NUM, (int)nodeList.size() - sit); offset++){
			for(BitList::iterator bit = nodeList[sit + offset].bitList.begin(); bit != nodeList[sit + offset].bitList.end(); ++bit){
				int newColId = bit->colId / BASE_NUM;
				int gNum = bit->colId % BASE_NUM;
				if(bitNumberCollector.find(newColId) != bitNumberCollector.end()){
					bitNumberCollector[newColId].eid |= (1 << (BASE_NUM - 1 - gNum + BASE_NUM * (BASE_NUM - 1 - offset % BASE_NUM)));
				}
				else{
					BitNumber bNum;
					bNum.did = newColId * BASE_NUM;
					bNum.colId = newColId;
					bNum.eid = (1 << (BASE_NUM - 1 - gNum + BASE_NUM * (BASE_NUM - 1 - offset % BASE_NUM)));
					bitNumberCollector[newColId] = bNum;
				}
			}
		}
		for(map<int, BitNumber>::iterator mit = bitNumberCollector.begin(); mit != bitNumberCollector.end(); ++mit){
			mergedList.push_back(mit->second);
		}
		tmp[sit / BASE_NUM].rowId = sit / BASE_NUM;
		tmp[sit / BASE_NUM].wordId = sit / BASE_NUM;
		tmp[sit / BASE_NUM].bitList.swap(mergedList);
    }
	nodeList.swap(tmp);
	#ifdef OPEN_ALL_STREAMS
	fs.close();
	#endif // OPEN_ALL_STREAMS
}