void BallsView::Init(){
	camera.Init();
	camera.SwitchCamMode(true);
	camera.MoveA(vector3f(0,0,0));
	camera.RotateA(vector3f(0,M_PI/4,0));
	camera.ZoomR(-3);
}