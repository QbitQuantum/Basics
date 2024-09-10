OverlaysEnum::OverlaysEnum(OverlaysContainer *pOverlays)
	: refCount(0)
{
	//	Create a copy of overlays.
	for each (Overlay *p in *pOverlays)
		overlays.push_back(p);

	Rewind();
}