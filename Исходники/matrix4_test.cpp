void Matrix4_Test::matrix4inverse()
{
	int boneId = 3;
	const Cluster* cluster = adapter->clusters();
	Matrix4 m = cluster[boneId].world2local();
	Matrix4 mInv = m.inverse();

	Matrix rotInv(0.99910, -0.00541, -0.04197,
	  		      0.00960,  0.99491,  0.10028, 
		          0.04122, -0.10060,  0.99407);
	Vector transInv(-5.36200, 8.39254, 0.88334);

	QVERIFY(mInv.rotation() == rotInv);
	QVERIFY(mInv.translation() == transInv);
}