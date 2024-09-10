    void WriteDolfinFormat (const Mesh & mesh, const string & filename)
    {
        cout << "start writing dolfin export" << endl;

        int np = mesh.GetNP();
        int ne = mesh.GetNE();
        int nse = mesh.GetNSE();
        int nsd = mesh.GetDimension(); 

        ofstream outfile(filename.c_str());

        outfile.precision(8);
        outfile.setf(ios::fixed, ios::floatfield);
        outfile.setf(ios::showpoint);

        if (nsd == 3) {
            outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            outfile << "<dolfin xmlns:dolfin=\"http://www.fenics.org/wiki/DOLFIN\">\n";
            outfile << "  <mesh celltype=\"tetrahedron\" dim=\"3\">\n";
            outfile << "    <vertices size=\""<<np<<"\">\n";
            for (int i = 1; i <= np; i++) { 
                const Point3d & p = mesh.Point(i);
                outfile << "      <vertex index=\""<<i-1<<"\" x=\""<<p.X()<<"\" y=\""<<p.Y()<<"\" z=\""<<p.Z()<<"\"/>\n";
            }
            outfile << "    </vertices>\n";

            outfile << "    <cells size=\""<<ne<<"\">\n";
            for (int i = 1; i <= ne; i++) {
                Element el = mesh.VolumeElement(i);
                if (mparam.inverttets) el.Invert();
                ELEMENT_TYPE type = el.GetType();
                if (type == TET || type == TET10)
                    outfile << "      <tetrahedron index=\""<<i-1<<"\" v0=\""<<el.PNum(1)-1<<"\" v1=\""<<el.PNum(2)-1<<"\" v2=\""<<el.PNum(3)-1<<"\" v3=\""<<el.PNum(4)-1<<"\"/>\n";
                else if (type == HEX)
                    outfile << "      <hexahedron index=\""<<i-1<<"\" v0=\""<<el.PNum(1)-1<<"\" v1=\""<<el.PNum(2)-1<<"\" v2=\""<<el.PNum(3)-1<<"\" v3=\""<<el.PNum(4)-1
                                                                 <<"\" v4=\""<<el.PNum(5)-1<<"\" v5=\""<<el.PNum(6)-1<<"\" v6=\""<<el.PNum(7)-1<<"\" v7=\""<<el.PNum(8)-1<<"\"/>\n";
                else
                    cout << "Warning unsupported element." << endl;
            }
            outfile << "    </cells>\n"; 
            outfile << "  </mesh>\n"; 
            outfile << "</dolfin>"; 
        }
        else if (nsd == 2) {
            outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            outfile << "<dolfin xmlns:dolfin=\"http://www.fenics.org/wiki/DOLFIN\">\n";
            outfile << "  <mesh celltype=\"triangle\" dim=\"2\">\n"; 
            outfile << "    <vertices size=\""<<np<<"\">\n"; 
            for (int i = 1; i <= np; i++) { 
                const Point3d & p = mesh.Point(i);
                outfile << "      <vertex index=\""<<i-1<<"\" x=\""<<p.X()<<"\" y=\""<<p.Y()<<"\"/>\n"; 
            }
            outfile << "    </vertices>\n";

            outfile << "    <cells size=\""<<nse<<"\">\n"; 
            for (int i = 1; i <= nse; i++) {
                Element2d el = mesh.SurfaceElement(i);
                if (mparam.inverttrigs) el.Invert();
                ELEMENT_TYPE type = el.GetType();
                if (type == TRIG || type == TRIG6)
                    outfile << "      <triangle index=\""<<i-1<<"\" v0=\""<<el.PNum(1)-1<<"\" v1=\""<<el.PNum(2)-1<<"\" v2=\""<<el.PNum(3)-1<<"\"/>\n"; 
                else if (type == QUAD || type == QUAD8)
                    outfile << "      <quadilateral index=\""<<i-1<<"\" v0=\""<<el.PNum(1)-1<<"\" v1=\""<<el.PNum(2)-1<<"\" v2=\""<<el.PNum(3)-1<<"\" v3=\""<<el.PNum(4)-1<<"\"/>\n"; 
                else
                    cout << "Warning unsupported element." << endl;
            }
            outfile << "    </cells>\n";
            outfile << "  </mesh>\n";
            outfile << "</dolfin>";
        }
        outfile.close();
        cout << "done writing dolfin export" << endl;
    }