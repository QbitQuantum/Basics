void ElevatorSimRenderWindow::rayCasting(int x, int y) {
   SimulationState& simState = SimulationState::acquire();

   float fovX = (GLWindow_width/GLWindow_height) * 45.f;

   float mx = (float)((x - GLWindow_width * 0.5) *
            (1.0 / GLWindow_width) * fovX * 0.5);
   float my = (float)((y - GLWindow_height * 0.5) *
            (1.0 / GLWindow_width) * fovX * 0.5);
   Vec3f dx = simState.getCameraManager().getRight() * mx;
   Vec3f dy = simState.getCameraManager().GetCameraUp() * my;

   Vec3f dir = simState.getCameraManager().GetCameraLookAt() + (dx + dy) * 2.0;
   dir.Normalize();

   const int eachFloorHeight = simState.getBuilding().gfxEachFloorHeight;
   std::vector<Elevator*> & elevators = simState.getBuilding().getElevators();

   std::for_each(
            elevators.begin(),
            elevators.end(),
            [this, &eachFloorHeight] ( const Elevator* thisElev ) {
      float pos = 1.0f + thisElev->getYVal() /
               Floor::YVALS_PER_FLOOR * eachFloorHeight;

      (void) pos;
   });
}