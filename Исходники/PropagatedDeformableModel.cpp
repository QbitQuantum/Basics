SpinalCord* PropagatedDeformableModel::mergeBidirectionalSpinalCord(SpinalCord* spinalCord1, SpinalCord* spinalCord2)
{
	int radialResolution = spinalCord1->getRadialResolution();
	SpinalCord* mesh = new SpinalCord();
	mesh->setRadialResolution(radialResolution);

	// Adding first mesh
	unsigned int numberOfPoints = spinalCord1->getNbrOfPoints(), numberOfTriangles = spinalCord2->getNbrOfTriangles();
	int numberOfDisk = numberOfPoints/radialResolution;
	vector<Vertex*> listPoints1 = spinalCord1->getListPoints();
	// Ajout du premier disque
	for (int j=0; j<radialResolution; j++)
	{
		mesh->addPoint(new Vertex(*listPoints1[numberOfDisk*radialResolution-1-j]));//(numberOfDisk-1)*radialResolution+j]));
	}
	// Ajout des suivants
	for (int i=1; i<numberOfDisk; i++)
	{
		for (int j=0; j<radialResolution; j++)
		{
			mesh->addPoint(new Vertex(*listPoints1[(numberOfDisk-i)*radialResolution-1-j]));//(numberOfDisk-1-i)*radialResolution+j]));
		}
		// Ajout des triangles - attention � la structure en cercle
		for (int k=0; k<radialResolution-1; k++)
		{
			mesh->addTriangle((i-1)*radialResolution+k,(i-1)*radialResolution+k+1,i*radialResolution+k);
			mesh->addTriangle((i-1)*radialResolution+k+1,i*radialResolution+k+1,i*radialResolution+k);
		}
		// Ajout des deux derniers triangles pour fermer le tube
		mesh->addTriangle((i-1)*radialResolution+radialResolution-1,(i-1)*radialResolution,i*radialResolution+radialResolution-1);
		mesh->addTriangle((i-1)*radialResolution,i*radialResolution,i*radialResolution+radialResolution-1);
	}

	// Adding second mesh
	numberOfPoints = spinalCord2->getNbrOfPoints(), numberOfTriangles = spinalCord2->getNbrOfTriangles();
	numberOfDisk = numberOfPoints/radialResolution;
	vector<Vertex*> listPoints2 = spinalCord2->getListPoints();
	int offsetTriangles = mesh->getNbrOfPoints()-radialResolution;
	// Points between meshes need offset to adjust properly triangles
	double distanceMin = 10000.0, dist;
	int indexMin = 0;
	Vertex* point = mesh->getListPoints()[offsetTriangles];
	for (int m=0; m<radialResolution; m++)
	{
		dist = point->distance(*listPoints2[m]);
		if (dist < distanceMin) {
			distanceMin = dist;
			indexMin = m;
		}
	}
	// Ajout des suivants
	for (int i=1; i<numberOfDisk; i++)
	{
		for (int j=0; j<radialResolution; j++)
		{
			mesh->addPoint(new Vertex(*listPoints2[i*radialResolution+(j+indexMin)%radialResolution]));
		}
		// Ajout des triangles - attention � la structure en cercle
		for (int k=0; k<radialResolution-1; k++)
		{
			mesh->addTriangle(offsetTriangles+(i-1)*radialResolution+k,offsetTriangles+(i-1)*radialResolution+k+1,offsetTriangles+i*radialResolution+k);
			mesh->addTriangle(offsetTriangles+(i-1)*radialResolution+k+1,offsetTriangles+i*radialResolution+k+1,offsetTriangles+i*radialResolution+k);
		}
		// Ajout des deux derniers triangles pour fermer le tube
		mesh->addTriangle(offsetTriangles+(i-1)*radialResolution+radialResolution-1,offsetTriangles+(i-1)*radialResolution,offsetTriangles+i*radialResolution+radialResolution-1);
		mesh->addTriangle(offsetTriangles+(i-1)*radialResolution,offsetTriangles+i*radialResolution,offsetTriangles+i*radialResolution+radialResolution-1);
	}
	return mesh;
}