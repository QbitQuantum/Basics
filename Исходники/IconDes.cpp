void IconDes::SaveUndo()
{
	if(!IsCurrent())
		return;
	Slot& c = Current();
	Vector<Image> undo = UnpackImlData(c.undo);
	int maxn = minmax((single_mode ? 4000000 : 400000) / max(c.image.GetLength(), 1), 4, 128);
	while(undo.GetCount() > maxn)
		undo.Remove(0);
	if(undo.GetCount() && undo.Top() == c.image)
		return;
	sSetSsFlag(c.image, c.supersampling);
	undo.Add(c.image);
	c.undo = PackImlData(undo);
	c.redo.Clear();
	SetBar();
	undo.Clear();
	sRemoveSsFlag(c.image);
}