void MyWindow::clicked (LONG x, LONG y, clicktype click)
{   WindowPS ps(window);
	double h;
	double scale=(double)width()/height();
	switch (rubberbox(x,y,click,R,5*scale,5,scale))
	{   case RUBBER_DONE :
			h=Xmin+R.x1()*(Xmax-Xmin)/width();
			Xmax=Xmin+R.x2()*(Xmax-Xmin)/width();
			Xmin=h;
			h=Ymin+R.y1()*(Ymax-Ymin)/height();
			Ymax=Ymin+R.y2()*(Ymax-Ymin)/height();
			Ymin=h;
			thread.start();
			break;
		case RUBBER_START :
			thread.suspend();
			break;
		case RUBBER_CANCEL :
			thread.resume();
			break;
	}
}