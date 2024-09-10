void DrawShape::paintMap(WPaintDevice *paintDevice)
{
	WPainter painter(paintDevice);
	painter.setRenderHint(WPainter::LowQualityShadows);
	painter.save();
	if(!sfile.empty()) {

		vector<LABELS> label_list;
		OGRDataSource       *poDS,*PointDS;
		string dfile = sfile  + ".shp";
		string shp = "g_4326/" + sfile + ".shp";
		poDS = OGRSFDriverRegistrar::Open(shp.c_str(), FALSE );  //comment till here

		if(poDS==NULL)
		{
			printf( "Open failed.\n" );
			exit( 1 );
		}
		OGRLayer  *poLayer;
		poLayer = poDS->GetLayerByName( sfile.c_str() ); // comment here 
		OGRFeature *poFeature;
		OGREnvelope *   	 psExtent = new OGREnvelope();

		poLayer->GetExtent(psExtent);
		double xMin = psExtent->MinX;
		double yMin = psExtent->MinY;
		double xMax = psExtent->MaxX;
		double yMax = psExtent->MaxY;

		stringstream strm;
		strm << xMin;
		string exp;
		double scaleFactor;
		string bound_string = strm.str();
		int size = bound_string.size();
		size_t found=bound_string.find("+");
		if (found!=string::npos) {
			exp =  bound_string.substr(found+1,size);     
		}

		if(exp.empty()) {

			stringstream strExtent;
			strExtent << yMin;
			bound_string = strExtent.str();
			size = bound_string.size();
			found = bound_string.find("+");
			if(found!=string::npos) {
				exp = bound_string.substr(found+1,size); 
			}
		}
		if(exp.empty()) {
			stringstream strExtent;
			strExtent << xMax;
			bound_string = strExtent.str();
			size = bound_string.size();
			found = bound_string.find("+");
			if(found!=string::npos) {
				exp = bound_string.substr(found+1,size); 
			}
		}
		if(exp.empty()) {
			stringstream strExtent;
			strExtent << yMax;
			bound_string = strExtent.str();
			size = bound_string.size();
			found = bound_string.find("+");
			if(found!=string::npos) {
				exp = bound_string.substr(found+1,size); 
			}
		}
		//cout << "EXXP: " << exp << endl;
		if(!exp.empty()) {
			int exponent  = boost::lexical_cast<int>(exp);

			exponent-=3;
			scaleFactor = pow (10,exponent);
		}
		else
		{
			//cout << "EXXP is empty " << exp << endl;
			scaleFactor = 1;
		}

		xMin/=scaleFactor;
		xMax/=scaleFactor;
		yMin/=scaleFactor;
		yMax/=scaleFactor;

		double gWidth = xMax - xMin;
		double gHeight = yMax - yMin;
		double widthFactor = 1;
		double pwidth = abs(gWidth-gHeight);
		double s = gWidth - gHeight;
		if(s<0.16)
			gWidth = gHeight + 0.16;

		double ratio=gWidth/gHeight;
		//for zoom n pan
		if(increase_width<100 && increase_height<100){
			painter.setWindow(xMin +(-x_pos_shift+increase_width/2)/100*gWidth* widthFactor, yMax+(y_pos_shift-increase_height/2)/100*gHeight * widthFactor, gWidth* widthFactor*(100-increase_width)/100, gHeight * widthFactor*(-1+increase_height/100));

			brush.setStyle(SolidPattern);
			brush.setColor(backcolor);
			painter.setBrush(brush);
			painter.drawRect(xMin +(-x_pos_shift+increase_width/2)/100*gWidth* widthFactor, yMax+(y_pos_shift-increase_height/2)/100*gHeight * widthFactor, gWidth* widthFactor*(100-increase_width)/100, gHeight * widthFactor*(-1+increase_height/100));
}
		else{
			painter.setWindow(xMin +x_pos_shift, yMax-y_pos_shift, 0, 0);
}

		// for normal picture

		//painter.setWindow(xMin , yMax, gWidth* widthFactor, -gHeight * widthFactor);
		pwidth/=480;
		pwidth*=4;
		//if(iwidth<0.06)
		//		iwidth=0.06;
		if(iwidth == 0.0015){
			pen.setWidth(pwidth);
		}
		else
		{
			pen.setWidth(iwidth);
		}

		//std::cerr<<pwidth<<" "<<iwidth<<"\n";
		pen.setColor(bordercolor);
		brush.setStyle(SolidPattern);
		brush.setColor(fillcolor);
		font= new WFont();
		font->setSize(WLength(labelpercentage*gWidth*widthFactor));
		painter.setFont(*font);
		painter.setPen(pen);
		painter.setBrush(brush);
		WPainterPath path;
		poLayer->ResetReading();


		OGRPoint *centroid = new OGRPoint();
		char label[100];
		while( (poFeature = poLayer->GetNextFeature()) != NULL )
		{
			centroid->empty();
			label[0]=0;
			if(labelindex>0)
			{
				OGRFeatureDefn *PointFDefn = poLayer->GetLayerDefn();
				OGRFieldDefn *PointFieldDefn = PointFDefn->GetFieldDefn(labelindex-1);
				if( PointFieldDefn->GetType() == OFTInteger )
					sprintf(label, "%d", poFeature->GetFieldAsInteger(labelindex-1) );
				else if( PointFieldDefn->GetType() == OFTReal )
					sprintf(label, "%.3f", poFeature->GetFieldAsDouble(labelindex-1) );
				else if( PointFieldDefn->GetType() == OFTString )
					sprintf(label, "%s", poFeature->GetFieldAsString(labelindex-1) );
				else
					sprintf(label, "%s", poFeature->GetFieldAsString(labelindex-1) );
			}
			OGRGeometry *poGeometry;

			poGeometry = poFeature->GetGeometryRef();

			if( poGeometry != NULL && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
			{
				OGRPoint *poPoint = (OGRPoint *) poGeometry;
				double x = poPoint->getX();
				double y = poPoint->getY();
				//painter.drawPoint(x/scaleFactor,y/scaleFactor);
				painter.drawEllipse(x/scaleFactor-0.005*gWidth*widthFactor,y/scaleFactor-0.005*gWidth*widthFactor,0.01*gWidth*widthFactor,0.01*gWidth*widthFactor);
				poGeometry->Centroid(centroid);

			} //end wkbpoint

			else if( poGeometry != NULL  && wkbFlatten(poGeometry->getGeometryType()) == wkbLineString  )
			{
				OGRLineString *poPoint = (OGRLineString *) poGeometry;

				for(int i=0;i<poPoint->getNumPoints();i++)
				{
					double x=poPoint->getX(i) ;
					double y = poPoint->getY(i);
					x/=scaleFactor; y/=scaleFactor;

					if(i==0)
						path = WPainterPath( WPointF(x, y));
					else
						path.lineTo( x , y);
				}

				painter.drawPath(path); 
				poGeometry->Centroid(centroid); 
			}

			else if( (poGeometry != NULL)  &&  wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon) 
			{
				OGRPolygon *poPoint = (OGRPolygon *) poGeometry;
				OGRLinearRing *extring = poPoint->getExteriorRing();

				int n = extring->getNumPoints();
				double x, y;
				for(int i=0;i<n;i++)
				{
					x = extring->getX(i);   y = extring->getY(i);
					x/=scaleFactor; y/=scaleFactor;
					if(i==0)
						path = WPainterPath( WPointF(x , y));

					else
						path.lineTo( x , y);
				}
				painter.drawPath(path);
				poGeometry->Centroid(centroid);

			}
			else if( (poGeometry != NULL)  &&  wkbFlatten(poGeometry->getGeometryType()) == wkbMultiPolygon) 
			{
				double x, y;
				OGRMultiPolygon *poPoint = (OGRMultiPolygon *) poGeometry;
				int p = poPoint->getNumGeometries();
				for(int k=0;k<p;k++) {
					OGRGeometry* geom = poPoint->getGeometryRef(k);
					OGRPolygon *poly = (OGRPolygon *) geom;
					OGRLinearRing  *ring = poly->getExteriorRing();

					for(int i=0;i<ring->getNumPoints();i++)
					{
						x = ring->getX(i);   y = ring->getY(i);
						x/=scaleFactor; y/=scaleFactor;
						if(i==0)
							path = WPainterPath( WPointF(x , y));
						else
							path.lineTo( x , y);

					}
					painter.drawPath(path); 
					poGeometry->Centroid(centroid);


				}

			}
			if(labelindex>0 && !centroid->IsEmpty()){
				LABELS l={centroid->getX(),centroid->getY(),label};
				label_list.push_back(l);
			}
		}
		painter.restore(); 


		//labelling the contents
if(increase_width<100 && increase_height<100){
		painter.setWindow(0.0, 0.0, (paintDevice->width()).value(),(paintDevice->height()).value());
		font= new WFont(WFont::SansSerif);
		font->setSize(WLength(10*labelpercentage));
		painter.setFont(*font);
		pen.setColor(labelcolor);
		painter.setPen(pen);
		std::vector<LABELS>::iterator the_iterator = label_list.begin();
		double x, y, minx=(xMin+(-x_pos_shift+increase_width/2)/100*gWidth* widthFactor),miny=(yMax+(y_pos_shift-increase_height/2)/100*gHeight*widthFactor);
		
		double multx=(paintDevice->width().value())/(gWidth* widthFactor*(100-increase_width)/100);
		double multy=(paintDevice->height().value())/(gHeight*widthFactor*(-1+increase_height/100));

		while( the_iterator != label_list.end() ) {
		
		x=((*the_iterator).x/scaleFactor-minx)*multx;
		y=((*the_iterator).y/scaleFactor-miny)*multy;
	
		painter.drawText(WRectF( x-(*the_iterator).label.size()*5*labelpercentage, y-5*labelpercentage, (*the_iterator).label.size()	*10*labelpercentage,10*labelpercentage),AlignCenter,(*the_iterator).label);
			++the_iterator;
		}
		pen.setColor(red);
		painter.setPen(pen);
		painter.setFont(*font);
		//painter.drawText(WRectF(paintDevice->width().value()-dfile.size()*10*labelpercentage,paintDevice->height().value()-10*labelpercentage*(paintDevice->height()).value(), dfile.size()*10*labelpercentage,10*labelpercentage ),AlignCenter,dfile); //this text is not seen in the picture when painted.
}
	}					



}