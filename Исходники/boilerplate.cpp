void draw_triangle_pixel(int i, int j){
	vec2 p0=_p0-vec2(i,j);
	vec2 p1=_p1-vec2(i,j);
	vec2 p2=_p2-vec2(i,j);
	vector<vec2> output(3),input;
	output[0]=p0;
	output[1]=p1;
	output[2]=p2;
	
	// left edge
{
	input=output;
	output.clear();
	vec2 s=input.back();
	for(vec2 e : input){
		if(e.x>=0){
			if(s.x<0){
				output.push_back(vec2(0, (s+(-s.x/(e-s).x)*(e-s)).y ));
			}
			output.push_back(e);
		}else if(s.x>=0){
			output.push_back(vec2(0, (s+(-s.x/(e-s).x)*(e-s)).y ));
		}
		s=e;
	}
}

	//right edge
{
	input=output;
	output.clear();
	vec2 s=input.back();
	for(vec2 e : input){
		if(e.x<=1){
			if(s.x>1){
				output.push_back(vec2(1, (e+((-e.x+1)/(s-e).x)*(s-e)).y ));
			}
			output.push_back(e);
		}else if(s.x<=1){
			output.push_back(vec2(1, (e+((-e.x+1)/(s-e).x)*(s-e)).y ));
		}
		s=e;
	}
}

	for(int k=0;k<output.size();k++){
		float t=output[k].x;
		output[k].x=output[k].y;
		output[k].y=t;
	}
	
		// left edge
{
	input=output;
	output.clear();
	vec2 s=input.back();
	for(vec2 e : input){
		if(e.x>=0){
			if(s.x<0){
				output.push_back(vec2(0, (s+(-s.x/(e-s).x)*(e-s)).y ));
			}
			output.push_back(e);
		}else if(s.x>=0){
			output.push_back(vec2(0, (s+(-s.x/(e-s).x)*(e-s)).y ));
		}
		s=e;
	}
}

	//right edge
{
	input=output;
	output.clear();
	vec2 s=input.back();
	for(vec2 e : input){
		if(e.x<=1){
			if(s.x>1){
				output.push_back(vec2(1, (e+((-e.x+1)/(s-e).x)*(s-e)).y ));
			}
			output.push_back(e);
		}else if(s.x<=1){
			output.push_back(vec2(1, (e+((-e.x+1)/(s-e).x)*(s-e)).y ));
		}
		s=e;
	}
}

	for(int k=0;k<output.size();k++){
		float t=output[k].x;
		output[k].x=output[k].y;
		output[k].y=t;
	}

	for(vec2 e:output){
//		cout<<e.x<<'\t'<<e.y<<endl;
	}
	
	float a=0;
	if(!output.empty()){
		for(int k=0;k<output.size()-1;k++){
			a+=output[k].x*output[k+1].y;
			a-=output[k].y*output[k+1].x;
		}
		a+=output.back().x*output.front().y;
		a-=output.back().y*output.front().x;
	}
	a*=0.5f;
	if(a<0)a*=-1;
//	cout<<"pixel "<<i<<'\t'<<j<<" set "<<a<<endl;
	ib.SetPixel(i,j,vec3(a,a,a));
}