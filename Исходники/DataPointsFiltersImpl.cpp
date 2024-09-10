void DataPointsFiltersImpl<T>::ShadowDataPointsFilter::inPlaceFilter(
	DataPoints& cloud)
{
	// Check if normals are present
	if (!cloud.descriptorExists("normals"))
	{
		throw InvalidField("ShadowDataPointsFilter, Error: cannot find normals in descriptors");
	}

	const int dim = cloud.features.rows();

	const BOOST_AUTO(normals, cloud.getDescriptorViewByName("normals"));
	int j = 0;

	for(int i=0; i < cloud.features.cols(); i++)
	{
		const Vector normal = normals.col(i).normalized();
		const Vector point = cloud.features.block(0, i, dim-1, 1).normalized();

		const T value = anyabs(normal.dot(point));

		if(value > eps) // test to keep the points
		{
			cloud.features.col(j) = cloud.features.col(i);
			cloud.descriptors.col(j) = cloud.descriptors.col(i);
			j++;
		}
	}

	cloud.conservativeResize(j);
}