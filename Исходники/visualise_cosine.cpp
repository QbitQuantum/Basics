map<long, int> getCheckMap(const map<long, vector<double> >& ratingMatrix, map<int, vector<double> >& clusterCenters)
{
	map<long, int> checkMap;

	for(map<long, vector<double> >::const_iterator rating_iter = ratingMatrix.begin(); rating_iter != ratingMatrix.end(); rating_iter++)
	{
	    // Use only if want to see al the distaces
	    //This will hold the Canberra distances for the current user
	    vector<double> distance(clusterCenters.size());

	    //cout<<"Calculating Cluster Assignment for user: "******" ";

			// Calculate the canberra distance
			currentDistance = exp(-cosineSimilarity(vector<double>(rating_iter->second.begin(), rating_iter->second.end()), vector<double>(cluster_it->second.begin(), cluster_it->second.end())));
				
			// TODO:: TODO:: check for multiple matches to minvalue
			if(currentDistance < minValue)
			{
			    minValue = currentDistance;
			    minIndex = cluster_it->first;
			}

	    }

	    // Set the cluster for the corresponding user
	    checkMap[rating_iter->first] = minIndex;		
	}

	return checkMap;
}