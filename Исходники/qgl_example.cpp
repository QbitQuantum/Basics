//-----------------------------------------------------------------------------
void MainWindow::paintGL()
{
	gr->Clf();
	gr->SubPlot(1,1,0);
	gr->Rotate(40,60);
	gr->Light(true);
	gr->AddLight(0,mglPoint(0,0,10),mglPoint(0,0,-1));
	gr->Axis();
	gr->Box();
	gr->FPlot("sin(pi*x)","i2");
	gr->FPlot("cos(pi*x)","|");
	gr->FSurf("cos(2*pi*(x^2+y^2))");
	gr->Finish();
	swapBuffers();
}