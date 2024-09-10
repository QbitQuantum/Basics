void labelPolygons(_Polygon (&Polygons)[6], int (&orderOfPolygons)[6])
{
    float distanceFromAToD = 0, dist;
    for (int k=0; k<6; k++)
    {
        if (k != orderOfPolygons[0])
        {
            dist = calcDistanceBet2Points(Polygons[orderOfPolygons[0]].Center, Polygons[k].Center);
            if (dist > distanceFromAToD)
            {
                distanceFromAToD = dist;
                orderOfPolygons[3] = k;
            }
        }
    }

    Vec3f DA = Vec3f(Polygons[orderOfPolygons[0]].Center.x - Polygons[orderOfPolygons[3]].Center.x,
                    Polygons[orderOfPolygons[0]].Center.y - Polygons[orderOfPolygons[3]].Center.y,
                    0);

    float distFromD, distBCFromD[2][2] = {0}, distEFFromD[2][2] = {0};
	int indexBC = 0, indexEF = 0;
    for (int k=0; k<6; k++)
    {
        if (k == orderOfPolygons[3] || k == orderOfPolygons[0])
            continue;
        Vec3f DV = Vec3f(Polygons[k].Center.x - Polygons[orderOfPolygons[3]].Center.x,
                    Polygons[k].Center.y - Polygons[orderOfPolygons[3]].Center.y,
                    0);

        distFromD = calcDistanceBet2Points(Polygons[orderOfPolygons[3]].Center, Polygons[k].Center);

        Vec3f cP = DA.cross(DV);
        if (cP.val[2] > 0)
        {
			distEFFromD[indexEF][0] = distFromD;
			distEFFromD[indexEF][1] = k;
			indexEF++;
        }
        else
        {
			distBCFromD[indexBC][0] = distFromD;
			distBCFromD[indexBC][1] = k;
			indexBC++;
        }
		if (distBCFromD[0][0] > distBCFromD[1][0])
		{
			orderOfPolygons[1] = distBCFromD[0][1]; // Polygon B
			orderOfPolygons[2] = distBCFromD[1][1]; // Polygon C
		}
		else
		{
			orderOfPolygons[1] = distBCFromD[1][1]; // Polygon B
			orderOfPolygons[2] = distBCFromD[0][1]; // Polygon C
		}
		
		if (distEFFromD[0][0] > distEFFromD[1][0])
		{
			orderOfPolygons[5] = distEFFromD[0][1]; // Polygon F
			orderOfPolygons[4] = distEFFromD[1][1]; // Polygon E
		}
		else
		{
			orderOfPolygons[5] = distEFFromD[1][1]; // Polygon F
			orderOfPolygons[4] = distEFFromD[0][1]; // Polygon E
		}		
    }
}