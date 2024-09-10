Vector SDKGradientClass::Output(BaseShader *sh, ChannelData *sd)
{
	Vector p=sd->p;
	Real	 r=0.0,angle,xx,yy;

	if (gdata.turbulence>0.0)
	{
		Vector	res;
		Real		scl=5.0*gdata.scale,tt=sd->t*gdata.freq*0.3;

		res = Vector(Turbulence(p*scl,tt,gdata.octaves,TRUE),Turbulence((p+Vector(0.34,13.0,2.43))*scl,tt,gdata.octaves,TRUE),0.0);

		if (gdata.absolute)
		{
			p.x  = Mix(p.x,res.x,gdata.turbulence);
			p.y  = Mix(p.y,res.y,gdata.turbulence);
		}
		else
		{
			p.x += (res.x-0.5)*gdata.turbulence;
			p.y += (res.y-0.5)*gdata.turbulence;
		}
	}

	// rotation
	p.x -= 0.5;
	p.y -= 0.5;

	xx = gdata.ca*p.x-gdata.sa*p.y + 0.5;
	yy = gdata.sa*p.x+gdata.ca*p.y + 0.5;

	p.x = xx;
	p.y = yy;

	if (gdata.mode<=SDKGRADIENTSHADER_MODE_CORNER && gdata.cycle && (sd->texflag&TEX_TILE))
	{
		if (sd->texflag & TEX_MIRROR)
		{
			p.x = Modulo(p.x,RCO 2.0);
			if (p.x>=1.0) p.x=2.0-p.x;

			p.y = Modulo(p.y,RCO 2.0);
			if (p.y>= 1.0) p.y=2.0-p.y;
		}
		else
		{
			p.x = Modulo(p.x, RCO 1.0);
			p.y = Modulo(p.y, RCO 1.0);
		}
	}

	switch (gdata.mode)
	{
		case SDKGRADIENTSHADER_MODE_U:
			r = p.x; 
			break;

		case SDKGRADIENTSHADER_MODE_V:
			r = 1.0-p.y; 
			break;

		case SDKGRADIENTSHADER_MODE_DIAGONAL:
			r = (p.x+p.y)*0.5; 
			break;

		case SDKGRADIENTSHADER_MODE_RADIAL:
			p.x-=0.5;
			p.y-=0.5;
			if (p.x==0.0) p.x=0.00001;

			angle = ATan(p.y/p.x);
			if (p.x<0.0) angle+=pi;
			if (angle<0.0) angle+=pi2;
			r = angle/pi2;
			break;

		case SDKGRADIENTSHADER_MODE_CIRCULAR:
			p.x-=0.5;
			p.y-=0.5;
			r = Sqrt(p.x*p.x+p.y*p.y)*2.0;
			break;

		case SDKGRADIENTSHADER_MODE_BOX:
			p.x = Abs(p.x - 0.5);
			p.y = Abs(p.y - 0.5);
			r   = FMax(p.x,p.y)*2.0;
			break;

		case SDKGRADIENTSHADER_MODE_STAR:
			p.x = Abs(p.x - 0.5)-0.5;
			p.y = Abs(p.y - 0.5)-0.5;
			r   = Sqrt(p.x*p.x+p.y*p.y) * 1.4142;
			break;

		case SDKGRADIENTSHADER_MODE_CORNER:
		{
			Real		cx;
			Vector	ca,cb;

			cx = FCut01(p.x);
			ca = Mix(gdata.c[0],gdata.c[1],cx);
			cb = Mix(gdata.c[2],gdata.c[3],cx);

			return Mix(ca,cb,FCut01(p.y));
			break;
		}
	}

	return gdata.gradient->CalcGradientPixel(FCut01(r));
}