CFlexMeters::~CFlexMeters()
{
	Uninitialize();
    if (memDC) {
        DeleteDC(memDC);
    }
    if (memBM) {
        DeleteObject(memBM);
    }
}