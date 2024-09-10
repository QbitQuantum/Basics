bool AnnotWriter::WriteAS(Ref& ref, Annotation* a) {
	if (is_empty_ref(ref)) return true;

	Object xobj;
	xobj.initDict(mXRef);
	// setup XObject dictionary
	AddName(&xobj, "Type", "XObject");
	AddName(&xobj, "Subtype", "Form");
	AddInteger(&xobj, "FormType", 1);
	PDFRectangle r = *a->GetRect();
	r.x2 -= r.x1; r.y2 -= r.y1;
	r.x1 = r.y1 = 0;
	AddRect(&xobj, "BBox", &r);
	// setup resource dictionary
	Object resources, array, name;
	resources.initDict(mXRef);
	array.initArray(mXRef);
	name.initName("PDF");
	array.arrayAdd(&name);
	resources.dictAdd(copyString("ProcSet"), &array);
	xobj.dictAdd(copyString("Resources"), &resources);

	// create appearance stream
	AnnotAppearance as;
	a->Visit(&as);

	// set length
	AddInteger(&xobj, "Length", as.GetLength());
	ASSERT(as.GetLength() > 0);

	// write form XObject
	WriteObject(ref, &xobj, as.GetStream());
	xobj.free();
	ref = empty_ref;
	return true;
}