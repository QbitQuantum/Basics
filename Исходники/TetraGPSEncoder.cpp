QString TetraGPSEncoder::generate(TGPSReal lat, TGPSReal lon, TGPSReal precMeters){
	const Vec coord(cos(lat)*cos(lon), cos(lat)*sin(lon), sin(lat));
	qDebug()<<"COORD:"<<coord<<coord.length()<<coord.latlon();
	QVector<Tri> faces;
	const TGPSReal ma=(M_PI*2.0)/3.0;
	const Vec north(    +0.0,                                    +1.0,      +0.0);
	const Vec prime(    +0.0,                                    +sin(-ma), +cos(-ma));
	const Vec meridian2(prime.x()*cos(+ma) - prime.z()*sin(+ma), prime.y(), prime.z()*cos(+ma) + prime.x()*sin(+ma));
	const Vec meridian3(prime.x()*cos(-ma) - prime.z()*sin(-ma), prime.y(), prime.z()*cos(-ma) + prime.x()*sin(-ma));
	qDebug()<<"north=    "<<north<<north.length();
	qDebug()<<"prime=    "<<prime<<prime.length();
	qDebug()<<"meridian2="<<meridian2<<meridian2.length();
	qDebug()<<"meridian3="<<meridian3<<meridian3.length();
	faces.push_back(Tri(north,prime,meridian2, 1));
	faces.push_back(Tri(north,prime,meridian3, 2));
	faces.push_back(Tri(north,meridian2,meridian3, 3));
	faces.push_back(Tri(prime,meridian2,meridian3, 4));
	TGPSReal score=1000.0;
	QStringList ret;
	int sub=0;
	Tri best,second;
	while((score*planetRadiusMeters)>precMeters && sub++<9){
		//qDebug()<<"----ROUND "<<sub<< score;
		TGPSReal eps=1000.0;
		for(auto tri:faces) {
			TGPSReal delta=(tri.center-coord).length();
			//qDebug()<<"DELTA: "<<delta<<tri.center<<tri.center.length();
			if(delta<eps){
				if(delta<score){
					score=delta;
				}
				eps=delta;
				best=tri;
				qDebug()<<"NEW BEST: "<<best<<"!";
			}
		}
		QString name=best.name();
		//if("0"==name){			break;		}
		ret<<name;
		faces=best.subdivide();

		if(best!=second){
			second=best;
		}
		else{
			break;
		}
	}
	TGPSReal d=(coord-best.center).length()/best.reach();
	qDebug()<<"BEST: "<<best<<" with "<< d<<" normalized distance from center and " << (score*planetRadiusMeters)<<" meters after "<<sub<<" iterations";
	return ret.join(".");
}