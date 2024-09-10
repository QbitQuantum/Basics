bool CDxfRead::ReadEllipse(bool undoably)
{
	double c[3]; // centre
	double m[3]; //major axis point
	double ratio=0; //ratio of major to minor axis
	double start=0; //start of arc
	double end=0;  // end of arc

	while(!((*m_ifs).eof()))
	{
		get_line();
		int n;
		if(sscanf_s(m_str, "%d", &n) != 1)return false;
		std::istringstream ss;
		ss.imbue(std::locale("C"));
		switch(n){
			case 0:
				// next item found, so finish with Ellipse
				OnReadEllipse(c, m, ratio, start, end, undoably);
				return true;
			case 10:
				// centre x
				get_line();
				ss.str(m_str); ss >> c[0]; if(ss.fail()) return false;
				break;
			case 20:
				// centre y
				get_line();
				ss.str(m_str); ss >> c[1]; if(ss.fail()) return false;
				break;
			case 30:
				// centre z
				get_line();
				ss.str(m_str); ss >> c[2]; if(ss.fail()) return false;
				break;
			case 11:
				// major x
				get_line();
				ss.str(m_str); ss >> m[0]; if(ss.fail()) return false;
				break;
			case 21:
				// major y
				get_line();
				ss.str(m_str); ss >> m[1]; if(ss.fail()) return false;
				break;
			case 31:
				// major z
				get_line();
				ss.str(m_str); ss >> m[2]; if(ss.fail()) return false;
				break;
			case 40:
				// ratio
				get_line();
				ss.str(m_str); ss >> ratio; if(ss.fail()) return false;
				break;
			case 41:
				// start
				get_line();
				ss.str(m_str); ss >> start; if(ss.fail()) return false;
				break;
			case 42:
				// end
				get_line();
				ss.str(m_str); ss >> end; if(ss.fail()) return false;
				break;	
			case 100:
			case 210:
			case 220:
			case 230:
				// skip the next line
				get_line();
				break;
			default:
				// skip the next line
				get_line();
				break;
		}
	}
	OnReadEllipse(c, m, ratio, start, end, undoably);
	return false;
}