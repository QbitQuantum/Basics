void Quad::split()
{
	if(is_split())
		return;

	quads[0][0] = new Quad(V);
	quads[0][1] = new Quad(V);
	quads[1][0] = new Quad(V);
	quads[1][1] = new Quad(V);
	
	quads[0][0]->set_range( *x1(), *x_mid(), *y1(), *y_mid() );
	quads[0][1]->set_range( *x_mid(), *x2(), *y1(), *y_mid() );
	quads[1][0]->set_range( *x1(), *x_mid(), *y_mid(), *y2() );
	quads[1][1]->set_range( *x_mid(), *x2(), *y_mid(), *y2() );
}