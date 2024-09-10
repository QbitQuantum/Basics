//create a plane passing the center, with the average of some normals as normal
//the plane created is stored in m_basePlane
//用：CGAL::Plane_3<Kernel>我们这里默认了所得到的边界点是有顺序的！！！
void SgpProp::createPlane(Vertex_handle &center, Polyhedron* mesh)
{
	std::cout << "  SgpProp::createPlane() begin!" <<std::endl;
	CGAL::Timer timer;
	timer.start();	

	std::list<Vertex_handle>& main_border = mesh->main_border();
	if (main_border.empty())
	{
		main_border = mesh->extract_longest_border();
	}

	std::list<Vector_3 > spokes;//a circular linked list
	for (std::list<Vertex_handle>::iterator it=main_border.begin(); it!=main_border.end(); ++it)
	{
		Vertex_handle vh = *it;
		spokes.push_back(vh->point() - center->point());
	}
	spokes.push_back(*(spokes.begin()) );

	std::list<Vector_3 >::iterator bVector = spokes.begin();
	std::list<Vector_3 >::iterator nVector = bVector;
	Vector_3 sum_norm(0,0,0);
	for(++nVector; nVector != spokes.end(); ++nVector,++bVector)
	{
		sum_norm = sum_norm + CGAL::cross_product(*bVector,*nVector);
	} 

	m_basePlaneNormal = sum_norm/(spokes.size()+1);
	
	std::cout << "....Time: " << timer.time() << " seconds." << std::endl<<std::endl;
}