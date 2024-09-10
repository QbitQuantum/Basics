 bool RenderingManager::InitializeView(vtkRenderWindow * renderWindow, const BaseGeometry * geometry, bool initializeGlobalTimeSNC)
 {
   ProportionalTimeGeometry::Pointer propTimeGeometry = ProportionalTimeGeometry::New();
   propTimeGeometry->Initialize(dynamic_cast<BaseGeometry *>(geometry->Clone().GetPointer()), 1);
   return InitializeView(renderWindow, propTimeGeometry, initializeGlobalTimeSNC);
 }