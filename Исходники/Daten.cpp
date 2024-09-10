void Daten::update_display()
	{
	CWinApp *a;
	CDocTemplate *t;
	CDocument *d;
	CView *v;
	POSITION p;

	a = AfxGetApp();
	p = a->GetFirstDocTemplatePosition();
	t = a->GetNextDocTemplate( p);
	p = t->GetFirstDocPosition();
	d = t->GetNextDoc( p);
	p = d->GetFirstViewPosition();
	v = d->GetNextView( p);
	v->RedrawWindow();
	}