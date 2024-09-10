Annotations* PageRenderer::GetAnnotationsForPage(int pageNo) {
	int i = pageNo-1;
	if (mAnnotations.Get(i) == NULL) {
		Object annotsDict;
		mDoc->getCatalog()->getPage(pageNo)->getAnnots(&annotsDict);
		mAnnotations.Set(i, new Annotations(&annotsDict, mBePDFAcroForm));
		annotsDict.free();
	}
	return mAnnotations.Get(i);
}