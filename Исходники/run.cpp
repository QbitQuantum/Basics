fptype Run::trackLength()
{
    fptype result = 0.0;

    if (route.size() > 1)
    {
	for (std::vector<Point*>::const_iterator i = route.begin();
	     i != route.end(); ++i)
	{
	    Point* thisPoint = *i;
	    std::vector<Point*>::const_iterator j = i+1;
	    if (j != route.end())
	    {
		Point* nextPoint = *j;
		result += thisPoint->distance(*nextPoint);
	    }
	}
    }

    return result;
}