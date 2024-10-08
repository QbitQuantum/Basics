void Mesh::applyTransformation(std::vector<Matrix3frm>& rmat, std::vector<Vector3f>& tvec, int globalTime) {
	
	pcl::PointCloud<pcl::PointXYZ> pointCloud;
	pcl::fromROSMsg(mesh_.cloud, pointCloud);

	Matrix3frm rmatPrev = rmat[globalTime - 1];
	Vector3f tvecPrev = tvec[globalTime - 1];

	Matrix3frm rmatCurr = rmat[globalTime];
	Vector3f tvecCurr = tvec[globalTime];

	Matrix3frm rmatPrevInverse = rmatPrev.inverse();
	Matrix3frm rmatCurrInverse = rmatCurr.inverse();
	float x, y, z;
	for(int point = 0; point < pointCloud.points.size(); point++) 
	{
		
		x = pointCloud.points[point].x * rmatCurr(0, 0) + pointCloud.points[point].y * rmatCurr(0, 1) + 
			pointCloud.points[point].z * rmatCurr(0, 2) + tvecCurr(0);
		y = pointCloud.points[point].x * rmatCurr(1, 0) + pointCloud.points[point].y * rmatCurr(1, 1) + 
			pointCloud.points[point].z * rmatCurr(1, 2) + tvecCurr(1);
		z = pointCloud.points[point].x * rmatCurr(2, 0) + pointCloud.points[point].y * rmatCurr(2, 1) + 
			pointCloud.points[point].z * rmatCurr(2, 2) + tvecCurr(2);
		
		x -= tvecPrev(0);
		y -= tvecPrev(1);
		z -= tvecPrev(2);
		
		pointCloud.points[point].x = x * rmatPrevInverse(0, 0) + y * rmatPrevInverse(0, 1) + 
			z * rmatPrevInverse(0, 2);
		pointCloud.points[point].y = x * rmatPrevInverse(1, 0) + y * rmatPrevInverse(1, 1) + 
			z * rmatPrevInverse(1, 2);
		pointCloud.points[point].z = x * rmatPrevInverse(2, 0) + y * rmatPrevInverse(2, 1) + 
			z * rmatPrevInverse(2, 2);
		
	}
	
	pcl::toROSMsg(pointCloud, mesh_.cloud);
}