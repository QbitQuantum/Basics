void Mesh::mirrorMesh(vector<int> planar_faces){

	map<int, Face*> mirror_faces;
	vector<Vertex*> mirror_vertices;
	map<int, Face*> updated_faces;
	map<int, int> temp_twins;

	int last_face_id;


	std::set<int> planar_set;
	for(vector<int>::iterator it = planar_faces.begin(); it != planar_faces.end(); it++) planar_set.insert(*it);
	 

	Face* pface = faces[(*planar_faces.begin())];
	ofVec3f o = vList[pface->getA()->getId()]->getPoint(); //get a point on this plane
	ofVec3f n = pface->getFaceNormal();
	double w = -(n.x * o.x) - (n.y * o.y) - (n.z * o.z);
	
	for(
		vector<Vertex*>::iterator it = vList.begin(); it != vList.end(); it++){
		ofVec3f p = (*it)->getPoint();
		double distance = n.x*p.x + n.y*p.y + n.z*p.z + w;
		ofVec3f pos = p + 2*distance * -1*n; //starting from the original the distance in the other direction
		int vid = vList.size()+mirror_vertices.size();

		if(!closeEnough(p, pos)){
			mirror_vertices.push_back(new Vertex(vid, pos.x, pos.y, pos.z));
			temp_twins.insert(pair<int, int> ((*it)->getId(), vid));
			insertTwin((*it)->getId(), vid);
		 }else{
		 	temp_twins.insert(pair<int, int> ((*it)->getId(), (*it)->getId())); //link it to itself
		 }
	}
	vList.insert(vList.end(), mirror_vertices.begin(), mirror_vertices.end());

	//find any additional planar triangles 
	for(map<int, Face*>::iterator it = faces.begin(); it != faces.end(); it++){
		last_face_id = (*it).first;
		Face* x = (*it).second;
		if(planar_set.count(x->getId()) > 0) continue;
		int a = x->getA()->getId();
		int b = x->getB()->getId();
		int c = x->getC()->getId();
		if(temp_twins[a] == a && temp_twins[b] == b && temp_twins[c] == c) planar_set.insert(x->getId());
		 
		
	}

	//remove any triangles that lie on the mirror plane
   	for(map<int, Face*>::iterator it = faces.begin(); it != faces.end(); it++){
   		Face* x = (*it).second;
   		if(planar_set.count(x->getId()) == 0) updated_faces.insert(*it);
   	}

   	faces.clear();
   	faces.insert(updated_faces.begin(), updated_faces.end());

	//now replicate remaining faces with new vertex values
	for(map<int, Face*>::iterator it = faces.begin(); it != faces.end(); it++){
		Face* x = (*it).second;
		int a = x->getA()->getId();
		int b = x->getB()->getId();
		int c = x->getC()->getId();

		x->resetFaceVertexNexts(); //this will make it so that it will look for connections

		int fid = last_face_id + mirror_faces.size() + 1; //okay to have mirror faces size because it will be sequential 
		Face* n_face = new Face(fid, temp_twins[b], temp_twins[a], temp_twins[c]); //flip to make ccw
		mirror_faces.insert(pair<int, Face*> (fid, n_face));
	}

	assert(mirror_faces.size() == faces.size());
	faces.insert(mirror_faces.begin(), mirror_faces.end());
	assert(faces.size() == 2*mirror_faces.size()); //make sure we didn't duplicate any indices
	constructTopology();
}