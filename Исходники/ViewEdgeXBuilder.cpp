FEdge *ViewEdgeXBuilder::BuildSmoothFEdge(FEdge *feprevious, const OWXFaceLayer& ifl)
{
	WOEdge *woea, *woeb;
	real ta, tb;
	SVertex *va, *vb;
	FEdgeSmooth *fe;
	// retrieve exact silhouette data
	WXSmoothEdge *se = ifl.fl->getSmoothEdge();

	if (ifl.order) {
		woea = se->woea();
		woeb = se->woeb();
		ta = se->ta();
		tb = se->tb();
	}
	else {
		woea = se->woeb();
		woeb = se->woea();
		ta = se->tb();
		tb = se->ta();
	}

	Vec3r normal;
	// Make the 2 Svertices
	if (feprevious == 0) { // that means that we don't have any vertex already built for that face
		Vec3r A1(woea->GetaVertex()->GetVertex());
		Vec3r A2(woea->GetbVertex()->GetVertex());
		Vec3r A(A1 + ta * (A2 - A1));

		va = MakeSVertex(A, false);
		// Set normal:
		Vec3r NA1(ifl.fl->getFace()->GetVertexNormal(woea->GetaVertex()));
		Vec3r NA2(ifl.fl->getFace()->GetVertexNormal(woea->GetbVertex()));
		Vec3r na((1 - ta) * NA1 + ta * NA2);
		na.normalize();
		va->AddNormal(na);
		normal = na;

		// Set CurvatureInfo
		CurvatureInfo *curvature_info_a =
		        new CurvatureInfo(*(dynamic_cast<WXVertex*>(woea->GetaVertex())->curvatures()),
		                          *(dynamic_cast<WXVertex*>(woea->GetbVertex())->curvatures()), ta);
		va->setCurvatureInfo(curvature_info_a);
	}
	else {
		va = feprevious->vertexB();
	}

	Vec3r B1(woeb->GetaVertex()->GetVertex());
	Vec3r B2(woeb->GetbVertex()->GetVertex());
	Vec3r B(B1 + tb * (B2 - B1));

	if (feprevious && (B - va->point3D()).norm() < 1.0e-6)
		return feprevious;

	vb = MakeSVertex(B, false);
	// Set normal:
	Vec3r NB1(ifl.fl->getFace()->GetVertexNormal(woeb->GetaVertex()));
	Vec3r NB2(ifl.fl->getFace()->GetVertexNormal(woeb->GetbVertex()));
	Vec3r nb((1 - tb) * NB1 + tb * NB2);
	nb.normalize();
	normal += nb;
	vb->AddNormal(nb);

	// Set CurvatureInfo
	CurvatureInfo *curvature_info_b =
	        new CurvatureInfo(*(dynamic_cast<WXVertex*>(woeb->GetaVertex())->curvatures()),
	                          *(dynamic_cast<WXVertex*>(woeb->GetbVertex())->curvatures()), tb);
	vb->setCurvatureInfo(curvature_info_b);

	// Creates the corresponding feature edge
	fe = new FEdgeSmooth(va, vb);
	fe->setNature(ifl.fl->nature());
	fe->setId(_currentFId);
	fe->setFrsMaterialIndex(ifl.fl->getFace()->frs_materialIndex());
	fe->setFace(ifl.fl->getFace());
	fe->setFaceMark(ifl.fl->getFace()->GetMark());
	if (feprevious == 0)
		normal.normalize();
	fe->setNormal(normal);
	fe->setPreviousEdge(feprevious);
	if (feprevious)
		feprevious->setNextEdge(fe);
	_pCurrentSShape->AddEdge(fe);
	va->AddFEdge(fe);
	vb->AddFEdge(fe);

	++_currentFId;
	ifl.fl->userdata = fe;
	return fe;
}