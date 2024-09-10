// TODO Check for reference passing or const reference passing
double canberra_location(long nl, long ne, std::vector<std::vector<long> >& lists, long k, std::vector<long>& i1, std::vector<long>& i2, std::vector<double>& dist)
{
	long		i, idx1, idx2, l1, l2, count;
	double		distance, indicator;

	indicator = 0.0;
	count = 0;

	for (idx1 = 1; idx1 <= nl - 1; idx1++)
		for (idx2 = idx1 + 1; idx2 <= nl; idx2++) 
		{
			distance = 0.0;
			for (i = 1; i <= ne; i++) 
			{
				l1 = lists[idx1 - 1][i - 1] + 1 <= k + 1 ? lists[idx1 - 1][i - 1] + 1 : k + 1;
				l2 = lists[idx2 - 1][i - 1] + 1 <= k + 1 ? lists[idx2 - 1][i - 1] + 1 : k + 1;
				distance += fabs(l1 - l2) / (l1 + l2);
			}

			i1[count] = idx1 - 1;
			i2[count] = idx2 - 1;
			dist[count] = distance;
			count++;

			indicator += 2.0 * distance / (nl * (nl - 1));
		}

	return (indicator);
}