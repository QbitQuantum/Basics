// ----------------------------------------------------------------------------
// Description:
// Timer set on each render step. Handle mouse, keyboard and gamepad movement and move the camera accordingly.
void vtkInteractorStyleGame::OnTimer()
{
    vtkRenderWindowInteractor *rwi = this->Interactor;
    vtkXOpenGLRenderWindow *rw = static_cast<vtkXOpenGLRenderWindow *>(rwi->GetRenderWindow());
    int *size = rw->GetSize();
    Window Win = rw->GetWindowId();
    Display* Disp = rw->GetDisplayId();

    if (this->gamepad->IsActive())
    {
        // Get updated gamepad state
        this->handleGamepadState(this->gamepad->getGamepadState());
    }

    double dt = ((double)(clock() - t))/CLOCKS_PER_SEC;
    t = clock();

    if(this->gamepadSpeed.y != 0 || this->keyboardSpeed.y != 0)
        this->MoveToFocalPoint(dt);
    if(this->gamepadSpeed.x != 0 || this->keyboardSpeed.x != 0)
        this->Pan(dt);

    if(this->gamepadRoll != 0 || this->keyboardRoll != 0)
        this->CameraRoll(dt);
    if(this->gamepaddt.x !=0)
        //this->ModelRotate(dt);
        this->CameraYaw(dt);
    if(this->gamepaddt.y !=0)
        this->Up(dt);
        //this->CameraPitch(dt);

    if(this->flying)
        this->Fly(dt);

    if (this->modelRotateSpeed != 0)
    {
        //printf("modelRotateSpeed = %g\n", this->modelRotateSpeed);
        this->ModelRotate(dt);
    }

    //if(this->rotate)
        //this->Rotate(dt);

    mousedt.x = 0;
    mousedt.y = 0;
    XWarpPointer(Disp, Win, Win, 0,0,size[0],size[1], roundl(size[0]/2), roundl(size[1]/2));
}