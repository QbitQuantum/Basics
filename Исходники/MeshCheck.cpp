TrianglesList meshRemoveIntersectedTriangles(TrianglesList &triangles)
{
	CGAL::Timer timer;
	timer.start();

	TrianglesList result;

	//Collision boxes
	std::vector<BoxInt> boxes;

	std::list<Triangle>::iterator triangleIter;
	for(triangleIter = triangles.begin(); triangleIter != triangles.end(); ++triangleIter)
	{
		//Triangle t = *triangleIter;

		TriangleVisitedInfoMC *tvi = new TriangleVisitedInfoMC;
		tvi->triangle = &(*triangleIter); //Use the pointer, it should not change into the container, since there aren't new added elements
		tvi->intersected = false;

		boxes.push_back( BoxInt( (*triangleIter).bbox(), tvi ));
	}


	//Do intersection
	CGAL::box_self_intersection_d( boxes.begin(), boxes.end(), reportSelfIntersectionCallback);


	//cycle on boxes and build result and delete tvi
	std::vector<BoxInt>::iterator vectorBoxesIter;
	for(vectorBoxesIter = boxes.begin(); vectorBoxesIter != boxes.end(); ++vectorBoxesIter)
	{
		BoxInt boxInt = *vectorBoxesIter;
		TriangleVisitedInfoMC *tviHandled = boxInt.handle();
		if ((!(tviHandled->intersected)) && (!(tviHandled->triangle->is_degenerate())))
		{
			Triangle t = *(tviHandled->triangle);
			result.push_back(t);
		}

		delete tviHandled;
	}


	timer.stop();
	std::cout << "Total meshRemoveIntersectedTriangles time: " << timer.time() << std::endl;

	return result;
}