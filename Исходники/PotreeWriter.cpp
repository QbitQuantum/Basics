void PotreeWriterNode::flush(){

	if(cache.size() > 0){
		 // move data file aside to temporary directory for reading
		string filepath = path + "/data/" + name + potreeWriter->getExtension();
		string temppath = path +"/temp/prepend" + potreeWriter->getExtension();
		if(fs::exists(filepath)){
			fs::rename(fs::path(filepath), fs::path(temppath));
		}
		

		PointWriter *writer = createWriter(path + "/data/" + name + potreeWriter->getExtension(), scale);
		if(fs::exists(temppath)){
			PointReader *reader = createReader(temppath);
			while(reader->readNextPoint()){
				writer->write(reader->getPoint());
			}
			reader->close();
			delete reader;
			fs::remove(temppath);
		}

		for(int i = 0; i < cache.size(); i++){
			writer->write(cache[i]);
		}
		writer->close();
		delete writer;

		cache = vector<Point>();
	}else if(cache.size() == 0 && grid->numAccepted > 0 && addCalledSinceLastFlush == false){
		delete grid;
		grid = new SparseGrid(aabb, spacing);
	}
	
	addCalledSinceLastFlush = false;

	for(int i = 0; i < 8; i++){
		if(children[i] != NULL){
			children[i]->flush();
		}
	}
}