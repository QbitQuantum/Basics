bool CodeAtlas::ComponentLayouter::compute()
{
	CHECK_ERRORS_RETURN_BOOL(m_status);

	SymbolNode::Ptr node = m_parent;
	// for a interior node, find attribute
	FuzzyDependAttr::Ptr fuzzyAttr = node->getAttr<FuzzyDependAttr>();


#ifndef ONLY_USE_WORD_SIMILARITY
	if (fuzzyAttr.isNull() || 
		fuzzyAttr->edgeWeightVector().size() <= 0 || 
		fuzzyAttr->vtxEdgeMatrix().cols() <= 0 ||
		fuzzyAttr->vtxEdgeMatrix().rows() <= 0)
	{
		m_status |= WARNING_NO_EDGE;
		if (!ComponentLayouter::compute(NULL, NULL, m_childList, m_nodePos, m_nodeRadius, m_totalRadius))
			trivalLayout();
	}
	else
	{
		// fill data used to compute layout
		SparseMatrix& vtxEdgeMatrix = fuzzyAttr->vtxEdgeMatrix();
		VectorXd&	  edgeWeight	= fuzzyAttr->edgeWeightVector();
		
#ifdef CHOOSE_IMPORTANT_EDGES
		// filter edges		
		VectorXi degreeVec;
		degreeVec.setZero(vtxEdgeMatrix.rows());
		for (int ithEdge = 0; ithEdge < vtxEdgeMatrix.cols(); ++ithEdge)
		{
			int src, tar;
			GraphUtility::getVtxFromEdge(vtxEdgeMatrix, ithEdge, src, tar);
			degreeVec[src]++;
			degreeVec[tar]++;
		}

		float maxVal = degreeVec.maxCoeff();
		float minVal = degreeVec.minCoeff();
		const float ratio = 0.2f;
		float threshold = min(minVal + (maxVal - minVal) * ratio, 3.f);

		std::vector<Triplet> tripletArray;
		std::vector<double> filteredEdgeArray;
		for (int ithEdge = 0; ithEdge < edgeWeight.size(); ++ithEdge)
		{
			int src, tar;
			GraphUtility::getVtxFromEdge(vtxEdgeMatrix, ithEdge, src, tar);
			if (min(degreeVec[src], degreeVec[tar]) <= threshold)
			{
				tripletArray.push_back(Triplet(src, filteredEdgeArray.size() ,1.0));
				tripletArray.push_back(Triplet(tar, filteredEdgeArray.size() ,-1.0));

				filteredEdgeArray.push_back(edgeWeight[ithEdge]);
			}
		}
		SparseMatrix filteredVEMat(vtxEdgeMatrix.rows(), filteredEdgeArray.size());
		filteredVEMat.setFromTriplets(tripletArray.begin(), tripletArray.end());
		VectorXd filteredEdgeVec(filteredEdgeArray.size());
		memcpy(filteredEdgeVec.data(), &filteredEdgeArray[0], sizeof(double)*filteredEdgeArray.size());

		if (!ComponentLayouter::compute(&filteredVEMat, &filteredEdgeVec, m_childList, m_nodePos, m_nodeRadius, m_totalRadius))
			trivalLayout();
#else
		if (!ComponentLayouter::compute(&vtxEdgeMatrix, &edgeWeight, m_childList, m_nodePos, m_nodeRadius, m_totalRadius))
			trivalLayout();
#endif
		qDebug("compute edge routes");
		DelaunayCore::DelaunayRouter router;
		router.setSmoothParam(0.5, 4); 
		computeEdgeRoute(router);
	}

#else
	if (!ComponentLayouter::compute(NULL, NULL, m_childList, m_nodePos, m_nodeRadius, m_totalRadius))
		trivalLayout();
	if (!fuzzyAttr.isNull())
	{
		m_status &= ~WARNING_NO_EDGE;
		qDebug("compute edge routes");
		DelaunayCore::DelaunayRouter router;
		router.setSmoothParam(0.5, 4); 
		computeEdgeRoute(router);
	}
#endif

	if ((m_status & WARNING_TRIVAL_LAYOUT) == 0)
		computeVisualHull();

	return true;
}