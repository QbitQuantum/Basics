void find_grid(AxisAlignedBox3 bbox, float reso,vector<unsigned int> *no_planes){
	/*This function finds the number of x, y and z planes that can fit in a given bounding box. The resolution(scaling factor) needed for the grid is specified as reso. This function fills up the no_planes vector by the number of x,y and z planes which will be able to fit in the bounding box. Assuming that th vector that will be passed to this function will be already initialized to length three. Since the bounding box is not to be treated too seriously to the point of one extra sample in one dimension, we will not specify two different fields for x direction size in no_planes.*/
	Vector3 lengths= bbox.getExtent();
	cout<<no_planes->size()<<endl;
	assert(no_planes->size()==3);

	(*no_planes)[0] = (unsigned int)floor(lengths[0]/(dist_x*reso));
	(*no_planes)[1] = (unsigned int)floor(lengths[1]/(dist_y*reso));
	(*no_planes)[2] = (unsigned int)floor(lengths[2]/(dist_z*reso));

	return;
}