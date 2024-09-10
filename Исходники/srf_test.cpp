void
APITestUtil::CombinedTests()
{
	// now let's build a test object
	NURBSSet nset;
	Matrix3 mat;
	mat.IdentityMatrix();


	// build an independent point
	int indPnt = MakeTestPoint(nset);

	// now a constrained point
	int ptPnt = MakeTestPointCPoint(nset, indPnt);



	// build a cv curve
	int cvCrv = MakeTestCVCurve(nset, mat);

	// and a constrained point on that curve
	int crvPnt = MakeTestCurveCPoint(nset, cvCrv);

	// now a point curve
	int ptCrv = MakeTestPointCurve(nset, mat);

	// Blend the two curves
	int blendCrv = MakeTestBlendCurve(nset, cvCrv, ptCrv);

	// make an offset of the CV curve
	int offCrv = MakeTestOffsetCurve(nset, cvCrv);

	// make a Transform curve of the point curve
	int xformCrv = MakeTestXFormCurve(nset, ptCrv);

	// make a mirror of the blend
	int mirCrv = MakeTestMirrorCurve(nset, blendCrv);

	// make a fillet curve (It makes it's own point curves to fillet)
	int fltCrv = MakeTestFilletCurve(nset);

	// make a chamfer curve (It makes it's own point curves to fillet)
	int chmCrv = MakeTestChamferCurve(nset);




	// build a cv surface
	int cvSurf = MakeTestCVSurface(nset, mat);


	// and a constrained point on that surface
	int srfPnt = MakeTestSurfCPoint(nset, cvSurf);

	// Curve Surface intersection point.
	int cvCrv2 = MakeTestCVCurve(nset, RotateXMatrix(PI/2.0f) * TransMatrix(Point3(0, 0, -175)));
	int srfIntPoint = MakeTestCurveSurface(nset, cvSurf, cvCrv2);

	// Now an Iso Curve on the CV surface
	int isoCrv1 = MakeTestIsoCurveU(nset, cvSurf);

	// Now an Iso Curve on the CV surface
	int isoCrv2 = MakeTestIsoCurveV(nset, cvSurf);

	// Now a Surface Edge Curve on the CV surface
	int surfEdgeCrv = MakeTestSurfaceEdgeCurve(nset, cvSurf);

	// build a CV Curve on Surface
	int cvCOS = MakeTestCurveOnSurface(nset, cvSurf);

	// build a Point Curve on Surface
	int pntCOS = MakeTestPointCurveOnSurface(nset, cvSurf);

	// build a Surface Normal Offset Curve
	int cnoCrf = MakeTestSurfaceNormalCurve(nset, cvCOS);

    // Make a curve-curve intersection point
    int curveCurve = MakeTestCurveCurve(nset, isoCrv1, isoCrv2, TRUE);

	// build a point surface
	int ptSurf = MakeTestPointSurface(nset, mat);

	// Blend the two surfaces
	int blendSurf = MakeTestBlendSurface(nset, cvSurf, ptSurf);

	// Offset of the blend
	int offSurf = MakeTestOffsetSurface(nset, blendSurf);

	// Transform of the Offset
	int xformSurf = MakeTestXFormSurface(nset, offSurf);

	// Mirror of the transform surface
	int mirSurf = MakeTestMirrorSurface(nset, xformSurf);

	// Make a Ruled surface between two curves
	int rulSurf = MakeTestRuledSurface(nset, cvCrv, ptCrv);

	// Make a ULoft surface
	int uLoftSurf = MakeTestULoftSurface(nset, ptCrv, offCrv, xformCrv);

	// Make a Extrude surface
	int extSurf = MakeTestExtrudeSurface(nset, xformCrv);

	// Make a lathe
	int lthSurf = MakeTestLatheSurface(nset);

	// these will build their own curves to work with
	// UV Loft
	int uvLoftSurf = MakeTestUVLoftSurface(nset);


	// 1 Rail Sweep
	int oneRailSurf = MakeTest1RailSweepSurface(nset);

	// 2 Rail Sweep
	int twoRailSurf = MakeTest2RailSweepSurface(nset);

	// MultiCurveTrim Surface
	int multiTrimSurf = MakeTestMultiCurveTrimSurface(nset);


	// Now make the curves and surfaces that we'll use later for the join tests
	int jc1, jc2, js1, js2;
	AddObjectsForJoinTests(nset, jc1, jc2, js1, js2);

	int bc, bs;
	AddObjectsForBreakTests(nset, bc, bs);


	Object *obj = CreateNURBSObject(mpIp, &nset, mat);
	INode *node = mpIp->CreateObjectNode(obj);
	node->SetName(GetString(IDS_TEST_OBJECT));




	NURBSSet addNset;
	// build a point surface
	int addptSurf = AddTestPointSurface(addNset);

	// add an iso curve to the previously created CV Surface
	NURBSId id = nset.GetNURBSObject(cvSurf)->GetId();
	int addIsoCrv = AddTestIsoCurve(addNset, id);

	AddNURBSObjects(obj, mpIp, &addNset);




	// now test some changing functionality
	// Let's change the name of the CVSurface
	NURBSObject* nObj = nset.GetNURBSObject(cvSurf);
	nObj->SetName(_T("New CVSurf Name"));  // testing only, no need to localize

	// now let's change the position of one of the points in the point curve
	NURBSPointCurve* ptCrvObj = (NURBSPointCurve*)nset.GetNURBSObject(ptCrv);
	ptCrvObj->GetPoint(0)->SetPosition(0, Point3(10, 160, 0)); // moved from 0,150,0

	// now let's change the position and weight of one of the CVs
	// in the CV Surface
	NURBSCVSurface* cvSurfObj = (NURBSCVSurface*)nset.GetNURBSObject(cvSurf);
	cvSurfObj->GetCV(0, 0)->SetPosition(0, Point3(-150.0, -100.0, 20.0)); // moved from 0,0,0
	cvSurfObj->GetCV(0, 0)->SetWeight(0, 2.0); // from 1.0


	// now let's do a transform of a curve.
	NURBSIdTab xfmTab;
	NURBSId nid = nset.GetNURBSObject(jc1)->GetId();
	xfmTab.Append(1, &nid);
	Matrix3 xfmMat;
	xfmMat = TransMatrix(Point3(10, 10, -10));
	SetXFormPacket xPack(xfmMat);
	NURBSResult res = Transform(obj, xfmTab, xPack, xfmMat, 0);




	// Now let's Join two curves
	NURBSId jc1id = nset.GetNURBSObject(jc1)->GetId(),
			jc2id = nset.GetNURBSObject(jc2)->GetId();
	JoinCurves(obj, jc1id, jc2id, FALSE, TRUE, 20.0, 1.0f, 1.0f, 0);

	// Now let's Join two surfaces
	NURBSId js1id = nset.GetNURBSObject(js1)->GetId(),
			js2id = nset.GetNURBSObject(js2)->GetId();
	JoinSurfaces(obj, js1id, js2id, 1, 0, 20.0, 1.0f, 1.0f, 0);

	// Break a Curve
	NURBSId bcid = nset.GetNURBSObject(bc)->GetId();
	BreakCurve(obj, bcid, .5, 0);

	// Break a Surface
	NURBSId bsid = nset.GetNURBSObject(bs)->GetId();
	BreakSurface(obj, bsid, TRUE, .5, 0);

	mpIp->RedrawViews(mpIp->GetTime());
	nset.DeleteObjects();
	addNset.DeleteObjects();


	// now do a detach
	NURBSSet detset;
	Matrix3 detmat;
	detmat.IdentityMatrix();
	// build a cv curve
	int detcvCrv = MakeTestCVCurve(detset, detmat);

	// now a point curve
	int detptCrv = MakeTestPointCurve(detset, detmat);

	// Blend the two curves
	int detblendCrv = MakeTestBlendCurve(detset, detcvCrv, detptCrv);

	Object *detobj = CreateNURBSObject(mpIp, &detset, detmat);
	INode *detnode = mpIp->CreateObjectNode(detobj);
	detnode->SetName("Detach From");

	BOOL copy = TRUE;
	BOOL relational = TRUE;
	NURBSIdList detlist;
	NURBSId oid = detset.GetNURBSObject(detblendCrv)->GetId();
	detlist.Append(1, &oid);
	DetachObjects(GetCOREInterface()->GetTime(), detnode, detobj,
					detlist, "Detach Test", copy, relational);
	mpIp->RedrawViews(mpIp->GetTime());

}