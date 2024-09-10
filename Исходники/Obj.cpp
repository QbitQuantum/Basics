Vector2i Obj::load_heightmap(string file_name, float scale)
{
	
	int width = 0, height = 0;
	
	string line;
	ifstream myfile (file_name.c_str());
	if (myfile.is_open()) {
		while (! myfile.eof() ) {
			getline (myfile,line);
			int this_width = 0;
			for (string::iterator it=line.begin() ; it < line.end(); it++ )
				if (*it == ',') this_width++;
			if (width == 0) {
				width = this_width;
			} else if (this_width == 0) {
				break;
			} else if (this_width != width) {
				cerr << "all lines in the heightmap must be the same length" << endl;
			}
			height++;
		}
		myfile.close();
	} else {
		cerr << "could not open file " << file_name << endl;
	}
	
	int size = width*height;
	vertices = new Vertex[size];
	v_poss = new Vector3f[size];
	v_norms = new Vector3f[size];
	v_texts = new Vector2f[size];
	face_count = (width-1)*(height-1);
	faces = new Face[(width-1)*(height-1)];
	
	//myfile.open(file_name.c_str());
	ifstream myfile2 (file_name.c_str());
	for (int i = 0 ; i < height ; i++) {
		getline (myfile2,line);
		string tmp = "";
		int j = 0;
		for (string::iterator it=line.begin() ; it < line.end(); it++ ) {
			if (*it == ',') {
				int index = i*width+j;
				v_poss[index].init((i/*-((float)width)/2.0f*/)*scale,atof(tmp.c_str())*scale,(j/*-((float)height)/2.0f*/)*scale);
				v_texts[index].init(i,j);
				v_norms[index].init(0,1,0);
				vertices[index].pos = &v_poss[index];
				vertices[index].text = &v_texts[index];
				vertices[index].normal = &v_norms[index];
				
				tmp = "";
				j++;
			} else {
				tmp += *it;
			}
		}
	}
	myfile2.close();
	
	for (int i = 0; i < height-1 ; i++) {
		for (int j = 0; j < width-1 ; j++) {
			
			if (i > 0 && j > 0) {
				int index = i*width+j;
				//cout << "setting normal at:" << v_poss[index] << endl;
				
				Vector3f norm_i = v_poss[(i-1)*width+j].dir_between(v_poss[(i+1)*width+j]);
				//cout << "i dir " << norm_i << endl;
				norm_i.rotate(Vector3f(0,0,90));
				//cout << "i dir " << norm_i << endl;
				norm_i.point_up();
				//cout << "i dir " << norm_i << endl;
				Vector3f norm_j = v_poss[i*width+(j-1)].dir_between(v_poss[i*width+(j+1)]);
				//cout << "j dir " << norm_j << endl;
				norm_j.rotate(Vector3f(90,0,0));
				//cout << "j dir " << norm_j << endl;
				norm_j.point_up();
				//cout << "j dir " << norm_j << endl;
				
				v_norms[index] = (norm_i + norm_j);
				//cout << "normal " << v_norms[index] << endl;
				v_norms[index].normalise();
				//cout << "normal " << v_norms[index] << endl;
				vertices[index].normal = &v_norms[index];
				
				//cout << "set normal at " << v_poss[index] << " to " << v_norms[index] << endl;
			}
			
			int f_index = i*(width-1)+j;
			faces[f_index].vertex_count = 4;
			faces[f_index].vertices = new Vertex[4];
			faces[f_index].vertices[0] = vertices[i*width+j];
			faces[f_index].vertices[1] = vertices[i*width+(j+1)];
			faces[f_index].vertices[2] = vertices[(i+1)*width+(j+1)];
			faces[f_index].vertices[3] = vertices[(i+1)*width+j];
		}
	}
	
	Vector2i map_size(width,height);
	return map_size;
	
}