    void shader(ci::Vec3f& rgb, const PixelInfo& p)
    {
		if(mSurf){
			Vec2f pt = Vec2f((p.point.x),(p.point.y));
			//pt.x = pt.x/4.f;
			//pt.x += mSection;
			auto colorval = mSurf.getPixel(Vec2i(pt.x*mSurf.getWidth(),pt.y*mSurf.getHeight()));
			rgb = Vec3f(colorval.r/255.f,colorval.g/255.f,colorval.b/255.f);
		}
		else 
			rgb = Vec3f(0,0,0);
        
	}