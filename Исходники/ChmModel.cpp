ChmModel::ChmModel(ControllerCallback *cb) : Controller(cb),
    doc(nullptr), htmlWindow(nullptr), htmlWindowCb(nullptr), tocTrace(nullptr),
    currentPageNo(1), initZoom(INVALID_ZOOM)
{
    InitializeCriticalSection(&docAccess);
}