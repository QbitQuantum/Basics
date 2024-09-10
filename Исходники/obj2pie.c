void addpoint(float x, float y, float z)
{
	if (points == NULL)
	{
		points = (vector3f*) malloc(sizeof(vector3f));
		count_points = 1;
	}
	else
	{
		count_points++;
		points = (vector3f*)realloc(points, count_points * sizeof(vector3f));
	}

	if( pieVersion == 2)
	{
		points[count_points-1].x = rintf(x);
		points[count_points-1].y = rintf(y);
		points[count_points-1].z = rintf(z);
	}
	else // pieVersion == 3
	{
		points[count_points-1].x = x;
		points[count_points-1].y = y;
		points[count_points-1].z = z;
	}
}