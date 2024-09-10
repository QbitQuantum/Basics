bool GeospatialBoundingBox::resample(double sampling_tolerance, double step)	{

	std::cout << _format("Re-sampling process initiated.").c_str() << std::endl;

	///Get all the points contained in the file
	std::vector<Vector3f> points = getPoints(true);

    ///Make 2 copies of the points
    std::vector<Vector3f> sorted_vertices_based_x,sorted_vertices_based_y;
    for (int i=0;i<points.size();i++)         {
            sorted_vertices_based_x.push_back(points[i]);
            sorted_vertices_based_y.push_back(points[i]);
    }

	std::cout << _format("Vertices sorted based on x:%d, vertices sorted based on y:%d",sorted_vertices_based_x.size(),sorted_vertices_based_y.size()).c_str() << std::endl;

    ///sort based on the x component
	SorterComplexType::quicksort(sorted_vertices_based_x,0,sorted_vertices_based_x.size()-1,0);
    ///sort based on the y component
	SorterComplexType::quicksort(sorted_vertices_based_y,0,sorted_vertices_based_y.size()-1,1);


    //go through the sorted arrays and count only unique number of x and y
    bool size_not_ok = true;
    int sizex,sizey;
    std::vector<Vector3f> unique_sorted_x,unique_sorted_y;
    while(size_not_ok)  {
             size_not_ok = false;
             for (unsigned int i=0;i<sorted_vertices_based_x.size();i++)     {
                     unsigned int starting_pos = i;
                     unique_sorted_x.push_back(sorted_vertices_based_x[starting_pos]);
                     while (i+1 < sorted_vertices_based_x.size() && fabs(sorted_vertices_based_x[starting_pos](0) - sorted_vertices_based_x[i+1](0)) <= sampling_tolerance)    i++;
                     //if (i+1 < sorted_vertices_based_x.size()) printf("%f\n",fabs(sorted_vertices_based_x[starting_pos](0) - sorted_vertices_based_x[i+1](0)));
             }
             sizex = unique_sorted_x.size();
		//if its bigger than then max size then increase the size of the cells
		if (sizex > MAX_SIZE_X) {
			size_not_ok = true;
			unique_sorted_x.clear();
			sampling_tolerance += step;
		}
     }
     size_not_ok = true;
     while(size_not_ok)  {
             size_not_ok = false;
             for (int j=0;j<sorted_vertices_based_y.size();j++)     {
                     int starting_pos = j;
                     unique_sorted_y.push_back(sorted_vertices_based_y[starting_pos]);
                     while (j+1 < sorted_vertices_based_y.size() && fabs(sorted_vertices_based_y[starting_pos](1) - sorted_vertices_based_y[j+1](1)) <= sampling_tolerance)            j++;
                     //if (j+1 < sorted_vertices_based_y.size()) printf("%f\n",fabs(sorted_vertices_based_y[starting_pos](1) - sorted_vertices_based_y[j+1](1)));
             }
             sizey = unique_sorted_y.size();
		//if its bigger than then max size then increase the size of the cells
		if (sizey > MAX_SIZE_Y)  {
			size_not_ok = true;
			unique_sorted_y.clear();
			sampling_tolerance += step;
		}
     }

     std::cout << _format("Chosen epsilon(bin size): %f. Map size will be %dx%d",sampling_tolerance,sizex,sizey).c_str() << std::endl;

     ///Check if the size of the map is more than the maximum size
     if (sizex > MAX_SIZE_X || sizey > MAX_SIZE_Y)	{
    	 std::cout << _format("The size of the map exceeds the maximum conditions.") << std::endl;
    	 return false;
     }

     //It will generate maps of size K pixels
     int map_sizex = min(sizex,MAX_SIZE_X);
     int map_sizey = min(sizey,MAX_SIZE_Y);

	 	 //create an XYZ map(2d grid) which will store all the points
	 xyz_map = new Image(map_sizex,map_sizey, 0.0f,0.0f,0.0f,1.0f);
	 Image *weights = new Image(map_sizex,map_sizey,0.0f,0.0f,0.0f,1.0f);

	 //go through the sorted points in x and y and distribute them in the grid
	 int hits = 0;
	 for (int i=0;i<map_sizex;i++)  {
			 if (i >= sizex) break;
			 for (int j=0;j<sorted_vertices_based_y.size();j++)     {
							 if (fabs(unique_sorted_x[i](0)-sorted_vertices_based_y[j](0)) <= sampling_tolerance)      {
									 //find where it should be positioned
									 int pos = -1;
									 for (int u=0;u<unique_sorted_y.size();u++)     {
											 if (fabs(unique_sorted_y[u](1) - sorted_vertices_based_y[j](1)) <= sampling_tolerance)    {
													 pos  = u;
													 //pos = sizey-1-pos; //flip it because of the upper left corner origin
													 break;
											 }
									 }
									 if (pos >= 0 && pos < map_sizey)        {/*printf("within range\n");*/;}
									 else {/*printf(" %d =<pos: %d < %d\n",ny*map_size,pos,(ny+1)*map_size);*/ continue;}
									 Color existing_value = weights->getPixel(i,pos);
									 weights->setPixel(i,pos, existing_value + Color(1.0f));
									 existing_value = xyz_map->getPixel(i,pos);
									 xyz_map->setPixel(i,pos, existing_value + Color(float(unique_sorted_x[i](0)),float(sorted_vertices_based_y[j](1)),float(sorted_vertices_based_y[j](2))));
									 hits++;
							 }
			 }
	 }
	 //averaging
	 for (int y=0;y<weights->getHeight();y++)     {
			 for (int x=0;x<weights->getWidth();x++)     {
					 if (weights->getPixel(x,y) != Color(0.0f,0.0f,0.0f,1.0f))        {
							 xyz_map->setPixel(x,y, xyz_map->getPixel(x,y)/weights->getPixel(x,y).r());
					 }
			 }
	 }
	 if (hits==0)	{
		 std::cout << _format("XYZ map contains no points.").c_str() << std::endl;
	 }

	 std::cout << _format("Re-sampling process complete.").c_str() << std::endl;

	delete weights;
	return true;
}