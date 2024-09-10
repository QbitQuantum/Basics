bool PlaceActor(NxVec3 position, NxVec3 velocity, unsigned int actind)
/*	This function is an intermediate step between CreateInitialPile that defines that initial positions
	and velocities of each actor in the pile, and the actor creation routine, which may be simply the
	familiar CreateRubbleGrain if actors should have a generic (or random) shape, or the more specialized
	CreateSpecificActor, that reads the shape information from a shapes file. The branching is decided
	simply by looking for the existence of a shapes file. EDIT: a shape file for non-uniform spheres is now
	implemented, as is a mixed polyhedra-non-uniform-sphere file. Branching determined by the section
	separator: SPHERE or SHAPE. EDIT: this function should not be called except by CreateInitialPile.
*/
{
	bool success=false;
	static bool skipSHFile=false;

	// attempt to open a shapes file
	char shfile[255];
	sprintf(shfile,"%s\\%s\\%s.sh",_getcwd(NULL,0),gRunBaseName,gRunBaseName);
	static ifstream fp(shfile);
	if (fp.fail() || skipSHFile) {// the easy default path. creating actors based on grain_type form ini file.
		NxActor* actor=CreateRubbleGrain(position);
		if (actor) actor->setLinearVelocity(velocity);
		if (actor) success=true;
	}
	else // this is the more complex path. read shapes from the shapes file.
	{
		// sigh. ok, here we go. the .sh file remains open so we just need to skip the header once:
		static char line[255];
		if (actind==0){
			while (fp.good()){
				fp.getline(line,255);
				if (strcmp(line,"SHAPE")==0 || strcmp(line,"SPHERE")==0) break;
			}
			if (fp.eof()) {cout<<"ERROR:shape segments not found in shape file."<<endl; fp.close(); skipSHFile=true; return false;}
		}

		// otherwise, we should be in position to start reading vertex info.
		if (strcmp(line,"SHAPE")==0)
		{
			float xx,yy,zz;
			NxVec3 vertex;
			vector<NxVec3> verts;
			while (fp.good())
			{
				fp.getline(line,255);
				if (strcmp(line,"\0")==0) continue; //skip empty lines. (but lines with nothing but ws are a problem.)
				if (strcmp(line,"SHAPE")==0 || strcmp(line,"SPHERE")==0 || fp.eof()) break;
				if (sscanf_s(line,"%f%f%f",&xx,&yy,&zz)<3) {cout<<"ERROR:bad format in shapes file."<<endl; fp.close(); return false;}
				vertex.x=xx; vertex.y=yy; vertex.z=zz;
				verts.push_back(vertex);
			}
			if (fp.eof() && actind<(RUBBLE_SIZE-1)){
				cout<<"WARNING:not enough shapes in shape file. additional shapes determined by grain_type"<<endl;
				fp.close();
				skipSHFile=true;
			}

			// well well. i do believe we have extracted the vertex information for shape actind. now what?
			NxActor* actor=CreateSpecificConvexShape(position,gDefaultDensity,verts); // someone else's problem now.
			if (actor){
				actor->setLinearVelocity(velocity);
				success=true;
			}
		}
		else if (strcmp(line,"SPHERE")==0)
		{
			float rr;
			fp.getline(line,255);
			if (sscanf_s(line,"%f",&rr)<1) {cout<<"ERROR:bad format in shapes file."<<endl; fp.close(); return false;}
			while (fp.good())
			{
				fp.getline(line,255);
				if (strcmp(line,"\0")==0) continue; //skip empty lines. (but lines with nothing but ws are a problem.)
				if (strcmp(line,"SHAPE")==0 || strcmp(line,"SPHERE")==0 || fp.eof()) break;
				cout<<"ERROR:bad format in shapes file."<<endl; fp.close(); return false;
			}
			if (fp.eof() && actind<(RUBBLE_SIZE-1)){
				cout<<"WARNING:not enough shapes in shape file. additional shapes determined by grain_type"<<endl;
				fp.close();
				skipSHFile=true;
			}
			NxActor* actor=CreateSphericalGrain(position,gDefaultDensity,rr*2);
			if (actor){
				actor->setLinearVelocity(velocity);
				success=true;
			}
		}
		else
		{
			cout<<"WARNING:unknown *shape* in shapes file. additional shapes determined by grain_type"<<endl;
			fp.close();
			skipSHFile=true;
		}
	}

	// done.
	return success;
}