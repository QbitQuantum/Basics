void DXFOutput::printEllipse(const BRepAdaptor_Curve& c, int id, std::ostream& out)
{
    gp_Elips ellp = c.Ellipse();
    const gp_Pnt& p= ellp.Location();
    double r1 = ellp.MajorRadius();
    double r2 = ellp.MinorRadius();
    double f = c.FirstParameter();
    double l = c.LastParameter();
    gp_Pnt s = c.Value(f);
    gp_Pnt m = c.Value((l+f)/2.0);
    gp_Pnt e = c.Value(l);

    gp_Vec v1(m,s);
    gp_Vec v2(m,e);
    gp_Vec v3(0,0,1);
    double a = v3.DotCross(v1,v2);

    // a full ellipse
   /* if (s.SquareDistance(e) < 0.001) {
        out << "<ellipse cx =\"" << p.X() << "\" cy =\"" 
            << p.Y() << "\" rx =\"" << r1 << "\"  ry =\"" << r2 << "\"/>";
    }
    // arc of ellipse
    else {
        // See also https://developer.mozilla.org/en/SVG/Tutorial/Paths
        gp_Dir xaxis = ellp.XAxis().Direction();
        Standard_Real angle = xaxis.Angle(gp_Dir(1,0,0));
        angle = Base::toDegrees<double>(angle);
        char las = (l-f > D_PI) ? '1' : '0'; // large-arc-flag
        char swp = (a < 0) ? '1' : '0'; // sweep-flag, i.e. clockwise (0) or counter-clockwise (1)
        out << "<path d=\"M" << s.X() <<  " " << s.Y()
            << " A" << r1 << " " << r2 << " "
            << angle << " " << las << " " << swp << " "
            << e.X() << " " << e.Y() << "\" />";
    }*/
        gp_Dir xaxis = ellp.XAxis().Direction();
        double angle = xaxis.Angle(gp_Dir(1,0,0));
        //double rotation = Base::toDegrees<double>(angle);


	double ax = s.X() - p.X();
	double ay = s.Y() - p.Y();
	double bx = e.X() - p.X();
	double by = e.Y() - p.Y();

	double start_angle = atan2(ay, ax) * 180/D_PI;
	double end_angle = atan2(by, bx) * 180/D_PI;

	double major_x;double major_y;
	
	major_x = r1 * sin(angle*90);
	major_y = r1 * cos(angle*90);

	double ratio = r2/r1;

	if(a > 0){
		double temp = start_angle;
		start_angle = end_angle;
		end_angle = temp;
	}
	out << 0			<< endl;
	out << "ELLIPSE"		<< endl;
	out << 8			<< endl;	// Group code for layer name
	out << "sheet_layer"	<< endl;	// Layer number
	out << 10			<< endl;	// Centre X
	out << p.X()		<< endl;	// X in WCS coordinates
	out << 20			<< endl;
	out << p.Y()		<< endl;	// Y in WCS coordinates
	out << 30			<< endl;
	out << 0		<< endl;	// Z in WCS coordinates
	out << 11			<< endl;	//
	out << major_x		<< endl;	// Major X
	out << 21			<< endl;
	out << major_y		<< endl;	// Major Y
	out << 31			<< endl;
	out << 0		<< endl;	// Major Z
	out << 40			<< endl;	//
	out << ratio		<< endl;	// Ratio
	out << 41		<< endl;
	out << start_angle	<< endl;	// Start angle
	out << 42		<< endl;
	out << end_angle	<< endl;	// End angle
}