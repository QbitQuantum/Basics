	virtual FVec3 warp( FVec3 p ) {
		FVec3 ap = p;
		ap.sub( this->center );
		float apMag = ap.mag();

		FVec3 pnProj = p;
		pnProj.project( this->normal );
		float pnProjMag = pnProj.mag();

		float radius = Cloud_dwa;		
		float offset = exp( Cloud_dwd * -powf((apMag-radius),Cloud_dwb) ) * exp( Cloud_dwe * -powf(pnProjMag,Cloud_dwc) );

		ap.div( apMag );
		ap.mul( apMag + offset );
		ap.add( this->center );
		return ap;
	}