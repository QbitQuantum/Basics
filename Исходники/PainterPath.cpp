Painter& Painter::Path(CParser& p)
{
	Pointf current(0, 0);
	while(!p.IsEof()) {
		int c = p.GetChar();
		p.Spaces();
		bool rel = IsLower(c);
		Pointf t, t1, t2;
		switch(ToUpper(c)) {
		case 'M':
			current = ReadPoint(p, current, rel);
			Move(current);
		case 'L':
			while(p.IsDouble2()) {
				current = ReadPoint(p, current, rel);
				Line(current);
			}
			break;
		case 'Z':
			Close();
			break;
		case 'H':
			while(p.IsDouble2()) {
				current.x = p.ReadDouble() + rel * current.x;
				Line(current);
			}
			break;
		case 'V':
			while(p.IsDouble2()) {
				current.y = p.ReadDouble() + rel * current.y;
				Line(current);
			}
			break;
		case 'C':
			while(p.IsDouble2()) {
				t1 = ReadPoint(p, current, rel);
				t2 = ReadPoint(p, current, rel);
				current = ReadPoint(p, current, rel);
				Cubic(t1, t2, current);
			}
			break;
		case 'S':
			while(p.IsDouble2()) {
				t2 = ReadPoint(p, current, rel);
				current = ReadPoint(p, current, rel);
				Cubic(t2, current);
			}
			break;
		case 'Q':
			while(p.IsDouble2()) {
				t1 = ReadPoint(p, current, rel);
				current = ReadPoint(p, current, rel);
				Quadratic(t1, current);
			}
			break;
		case 'T':
			while(p.IsDouble2()) {
				current = ReadPoint(p, current, rel);
				Quadratic(current);
			}
			break;
		case 'A':
			while(p.IsDouble2()) {
				t1 = ReadPoint(p, Pointf(0, 0), false);
				double xangle = ReadDouble(p);
				bool large = ReadBool(p);
				bool sweep = ReadBool(p);
				current = ReadPoint(p, current, rel);
				SvgArc(t1, xangle * M_PI / 180.0, large, sweep, current);
			}
			break;
		default:
			return *this;
		}
	}
	return *this;
}