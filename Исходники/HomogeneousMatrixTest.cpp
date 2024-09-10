void HomogeneousMatrixTest::testRPYConversions() {
	double xExpected, yExpected, zExpected, rollExpected, pitchExpected, yawExpected;
	double xActual, yActual, zActual, rollActual, pitchActual, yawActual;
	IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform1(new HomogeneousMatrix44());

	xExpected = 1.0;
	yExpected = 2.0;
	zExpected = 3.0;
	rollExpected = 0.5*M_PI;
	pitchExpected = 0.0;
	yawExpected = 0.0;

	HomogeneousMatrix44::xyzRollPitchYawToMatrix(xExpected, yExpected, zExpected, rollExpected, pitchExpected, yawExpected, transform1);
	std::cout << "---> transform1 " << std::endl <<*transform1;
	HomogeneousMatrix44::matrixToXyzRollPitchYaw(transform1, xActual, yActual, zActual, rollActual, pitchActual, yawActual);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(xExpected, xActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(yExpected, yActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(zExpected, zActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(rollExpected, rollActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(pitchExpected, pitchActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(yawExpected, yawActual, maxTolerance);

	xExpected = 1.0;
	yExpected = 2.0;
	zExpected = 3.0;
	rollExpected = 0.0;
	pitchExpected = 0.0;
	yawExpected = 0.5 * M_PI;

	Eigen::AngleAxis<double> rotation2(yawExpected, Eigen::Vector3d(0,0,1));
	Transform3d transformation2;
	transformation2 = Eigen::Affine3d::Identity();
	transformation2.translate(Eigen::Vector3d(xExpected,yExpected,zExpected));
	transformation2.rotate(rotation2);
	IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform2(new HomogeneousMatrix44(&transformation2));


	HomogeneousMatrix44::matrixToXyzRollPitchYaw(transform2, xActual, yActual, zActual, rollActual, pitchActual, yawActual);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(xExpected, xActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(yExpected, yActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(zExpected, zActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(rollExpected, rollActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(pitchExpected, pitchActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(yawExpected, yawActual, maxTolerance);

	xExpected = 1.0;
	yExpected = 2.0;
	zExpected = 3.0;
	rollExpected = 0.0;
	pitchExpected = 0.5 * M_PI;
	yawExpected = 0;

	Eigen::AngleAxis<double> rotation3(pitchExpected, Eigen::Vector3d(0,1,0));
	Transform3d transformation3;
	transformation3 = Eigen::Affine3d::Identity();
	transformation3.translate(Eigen::Vector3d(xExpected,yExpected,zExpected));
	transformation3.rotate(rotation3);
	IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform3(new HomogeneousMatrix44(&transformation3));

	HomogeneousMatrix44::matrixToXyzRollPitchYaw(transform3, xActual, yActual, zActual, rollActual, pitchActual, yawActual);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(xExpected, xActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(yExpected, yActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(zExpected, zActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(rollExpected, rollActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(pitchExpected, pitchActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(yawExpected, yawActual, maxTolerance);

	xExpected = 1.0;
	yExpected = 2.0;
	zExpected = 3.0;
	rollExpected = 0.5 * M_PI;
	pitchExpected = 0.0;
	yawExpected = 0;

	Eigen::AngleAxis<double> rotation4(rollExpected, Eigen::Vector3d(1,0,0));
	Transform3d transformation4;
	transformation4 = Eigen::Affine3d::Identity();
	transformation4.translate(Eigen::Vector3d(xExpected,yExpected,zExpected));
	transformation4.rotate(rotation4);
	IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform4(new HomogeneousMatrix44(&transformation4));


	HomogeneousMatrix44::matrixToXyzRollPitchYaw(transform4, xActual, yActual, zActual, rollActual, pitchActual, yawActual);
	std::cout << "---> transform4 " << std::endl <<*transform4;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(xExpected, xActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(yExpected, yActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(zExpected, zActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(rollExpected, rollActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(pitchExpected, pitchActual, maxTolerance);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(yawExpected, yawActual, maxTolerance);

	/* CHecke if Eigen generated and xyzRPY generated _matices_ are similar */
	const double* matrixData1 = transform1->getRawData();
	const double* matrixData4 = transform4->getRawData();
	for (unsigned int i = 0; i < 16; ++i) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(matrixData1[i], matrixData4[i], maxTolerance);
	}
}