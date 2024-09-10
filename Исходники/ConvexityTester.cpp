bool isConvexPolygon(const vector<vec4>& verts)
{
	if(verts.empty() || verts.size() < 3)
		return false;

	vec3 normal= vec3(0);
	vec3 t = vec3(0);  // t is for "temp normal" or "test normal"

	vec3 startPoint = vec3(verts.at(0));
	vec3 startPointPlus1 = vec3(verts.at(1));	
	vec3 endPoint = vec3(verts.at(verts.size()-2));
	//Normal = v[1]-v[0] X v[n-1]-v[0] where n=size of array of vertices
	normal = cross( startPointPlus1-startPoint , endPoint-startPoint );
	//For each vertex 'iter' after the 0th index in verts
	for(int i = 1; i < (int)(verts.size()-2); ++i)
	{
		//T= (v[i+1]-v[i]) cross (v[v-1]-v[i])
		t = cross( vec3(verts.at(i+1)) - vec3(verts.at(i)) , vec3(verts.at(i-1)) - vec3(verts.at(i)) );

		if( (t.y < 0 && normal.y > 0) || (t.y > 0 && normal.y < 0) )
		{
			return false;
		}
	}
	return true;
}