void JuliaImageSequential::refreshAll(const DomaineMaths& domainNew){
    int w = getW();
    int h = getH();

    float dx = (float) (domainNew.dx / (float) w);
    float dy = (float) (domainNew.dy / (float) h);
    float y = domainNew.y0;

    for(int i = 1; i <= h; ++i){
	float x = domainNew.x0;

	for(int j = 1; j <= w; ++j){
	    float h = julia(x, y);

	    //setFloatRGBA(i, j, h, h, h);
	    if(h == 0){
		setHSB(i, j, 0, 0, 0);
	    } else {
		setHSB(i, j, h, 1.0, 1.0);
	    }

	    x += dx;
	}

	y += dy;
    }
}