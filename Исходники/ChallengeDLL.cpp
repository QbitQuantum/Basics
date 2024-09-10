void SearchContext::queryNode(int l, int ix, int iy, const Rect& nodeBounds, const Rect& qrect, vector<Point>*& results, vector<Point>*& buf, int nresults){

	auto toplist = _toplists[nodeOffset(l, ix, iy)];

	if (toplist == NULL || toplist->numItems == 0)
		return;

	if (results->size() >= nresults && toplist->items[0].rank >= ((*results)[results->size() - 1].rank)) {
		return;
	}

	bool contained = false;
	if (qrect.contains(nodeBounds)){


		_ncontains++;
		contained = true;

		mergepts(results, buf, nresults, toplist->begin(), toplist->end(), [](const Point* p) { return true; });

	}
	if ((contained && results->size()<nresults) || qrect.intersects(nodeBounds)){

		_nintersects++;

		mergepts(results, buf, nresults, toplist->begin(), toplist->end(), [&](const Point* p) { return qrect.contains(*p); });

		if (l < _levels - 1){

			_ndescend++;

			queryNode(l + 1, ix * 2, iy * 2, nodeBounds.ll(), qrect, results, buf, nresults);
			queryNode(l + 1, ix * 2 + 1, iy * 2, nodeBounds.lr(), qrect, results, buf, nresults);
			queryNode(l + 1, ix * 2, iy * 2 + 1, nodeBounds.hl(), qrect, results, buf, nresults);
			queryNode(l + 1, ix * 2 + 1, iy * 2 + 1, nodeBounds.hr(), qrect, results, buf, nresults);

		}

	}
}