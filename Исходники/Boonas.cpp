void Boonas::doExtrude(QString num, QString filename) // extrudes and writes whilst extruding 
{
	float n = num.toFloat();
	float x, y, z, w;
	int numSides;
	Point* pa;
	Point* pb;
	Point* pc;
	Point pd;
	Point firstPoint;
	Vector va;
	Vector vb;
	Vector vn;
	bool again = true;
	filename.append(".poly");
	QFile* theDestination;
	theDestination = new QFile(filename);
	theDestination -> remove();
	theDestination -> open(QIODevice::ReadWrite | QIODevice::Text);
	QTextStream outStream( theDestination );
	
	do // do this loop while ther is more in orig
	{
		
		cursor = orig -> getCurrent(); // cursor is current
		cursor -> reset();
		
		//change color respectively for each object
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		
		if(colorValue != 0)
		{
			delete colorValue;
			colorValue = 0;
		}
		colorValue = new Point(x, y, z);
		
		cursor -> advance();
		
		if(!(orig -> isNotLast()))
		{
			again = false;
		}
		
		// get initial points in order to get unit vectior
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		
		pa = new Point(x, y, z);
		
		cursor -> advance();
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		
		pb = new Point(x, y, z);
		
		cursor -> advance();
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		
		pc = new Point(x, y, z);
		
		va = *pa - *pb;
		vb = *pb - *pc;
		
		vn = cross(va, vb);
		vn.normalize();
		
		//vn = vn * -1.0; // flip it
		
		vn = vn * n;
		// vn is vector!
		
		cursor -> reset(); // reset cursor so 2nd iteration starts from begining
		
		
		// skip color vector
		cursor -> advance();
		
		numSides = 0;
		
		outStream << "newObject" << endl;
		
		// put out color vector
		outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
		
		// first iteration, copy orig polygon, count number of sides
		do
		{
			numSides++;
			//qDebug() << "Test results";
			x = cursor -> getX(); // get point
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			
			outStream << x << " " << y << " " << z << " " << w << endl;
			
			cursor -> advance();
		}
		while(cursor -> hasNext()); // run through the points and mult!k
		
		numSides++;
		x = cursor -> getX(); // get point
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		
		outStream << x << " " << y << " " << z << " " << w << endl;
		//numsides is the number of points
		cursor -> reset();
		
		// skip color vector
		cursor -> advance();
		
		// second iteration, copy the top polygon
		outStream << "newObject" << endl;
		
		// put out color vector
		outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
		
		// second iteration, copy orig polygon to traversed points, count number of sides
		do
		{
			//qDebug() << "Test results";
			x = cursor -> getX(); // get point
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			
			delete pa;
			pa = new Point(x, y, z);
			pd = *pa + vn;
			outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl;
			
			cursor -> advance();
		}
		while(cursor -> hasNext()); // run through the points and mult!k
		
		x = cursor -> getX(); // get point
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		
		delete pa;
		pa = new Point(x, y, z);
		
		pd = *pa + vn;
		
		outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl;
		// start next run time for the sides yo
		cursor -> reset();
		
		// skip color vector
		cursor -> advance();
		
		
		for(int i = 0; i < (numSides - 1); i++) // run through this next bit for each side of the polygon except the last side
		{
			cursor -> reset();
			
			// skip color vector
			cursor -> advance();
			
			outStream << "newObject" << endl;
			
			// put out color vector
			outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
			
			for(int j = 0; j < i; j++) // advance cursor to get it to desired point
			{
				cursor -> advance();
			}
			
			x = cursor -> getX(); 
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			
			outStream << x << " " << y << " " << z << " " << w << endl; // out put orig point
			
			delete pa;
			pa = new Point(x, y, z);
			pd = *pa + vn;
			
			outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl; // out put mod point a
			
			cursor -> advance(); //advance to next point;
			
			x = cursor -> getX(); 
			y = cursor -> getY();
			z = cursor -> getZ();
			w = cursor -> getW();
			
			delete pa;
			pa = new Point(x, y, z);
			pd = *pa + vn;
			
			outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl; // out put mod point b

			outStream << x << " " << y << " " << z << " " << w << endl; // out put last point
		}
		// now we only have to deal with the last side
		
		outStream << "newObject" << endl;
		
		// put out color vector
		outStream << colorValue -> x() << " " << colorValue -> y() << " "<< colorValue -> z() << " 1" << endl;
		
		
		cursor -> reset();
		
		// skip color vector
		cursor -> advance();
		
		for(int i = 0; i < numSides; i++)
		{
			cursor -> advance(); // advance cursor to last point;
		}
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		
		outStream << x << " " << y << " " << z << " " << w << endl; // out put first point
		
		delete pa;
		pa = new Point(x, y, z);
		pd = *pa + vn;
		
		outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl; // out put mod point a
		
		cursor -> reset();
		
		// skip color vector
		cursor -> advance();
		
		x = cursor -> getX(); 
		y = cursor -> getY();
		z = cursor -> getZ();
		w = cursor -> getW();
		
		delete pa;
		pa = new Point(x, y, z);
		pd = *pa + vn;
		
		outStream << pd.x() << " " << pd.y() << " " << pd.z() << " " << w << endl; // out put mod point b
		
		outStream << x << " " << y << " " << z << " " << w << endl; // out put last point
		
		orig -> advance(); // advance what were working with
	}
	while(again);
	
	theDestination -> close();
	delete theDestination;
	delete pa;
	delete pb;
	delete pc;
}