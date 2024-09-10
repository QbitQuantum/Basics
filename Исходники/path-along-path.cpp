    void draw(cairo_t *cr, std::ostringstream *notify, int width, int height, bool save, std::ostringstream *timer_stream) {
        D2<SBasis> skeleton = skel_handles.asBezier();
        D2<SBasis> pattern  = pat_handles.asBezier();


        cairo_set_line_width(cr,1.);
        cairo_pw_d2_sb(cr, Piecewise<D2<SBasis> >(skeleton));
        cairo_set_source_rgba(cr,0.0,0.0,1.0,1.0);
        cairo_stroke(cr);

        cairo_pw_d2_sb(cr, Piecewise<D2<SBasis> >(pattern));
        cairo_set_source_rgba(cr,1.0,0.0,1.0,1.0);
        cairo_stroke(cr);

        origin_handle.pos[0]=150;
        Geom::Point origin = origin_handle.pos;

        Piecewise<D2<SBasis> > uskeleton = arc_length_parametrization(Piecewise<D2<SBasis> >(skeleton),2,.1);
        uskeleton = remove_short_cuts(uskeleton,.01);
        Piecewise<D2<SBasis> > n = rot90(derivative(uskeleton));
        n = force_continuity(remove_short_cuts(n,.1));
        
        Piecewise<SBasis> x=Piecewise<SBasis>(pattern[0]-origin[0]);
        Piecewise<SBasis> y=Piecewise<SBasis>(pattern[1]-origin[1]);
        Interval pattBnds = *bounds_exact(x);
        int nbCopies = int(uskeleton.cuts.back()/pattBnds.extent());

        //double pattWidth = uskeleton.cuts.back()/nbCopies;
        double pattWidth = pattBnds.extent();
        
        double offs = 0;
        x-=pattBnds.min();
        //x*=pattWidth/pattBnds.extent();
        
        Piecewise<D2<SBasis> >output;
        for (int i=0; i<nbCopies; i++){
            output.concat(compose(uskeleton,x+offs)+y*compose(n,x+offs));
            offs+=pattWidth;
        }

        //Perform cut for last segment
        double tt = uskeleton.cuts.back() - offs;
        if(tt > 0.) {
            vector<double> rs = roots(x - tt);
            rs.push_back(0); rs.push_back(1);  //regard endpoints
            std::sort(rs.begin(), rs.end());
            std::unique(rs.begin(), rs.end());
            //enumerate indices of sections to the left of the line
            for(unsigned i = (x[0].at0()>tt ? 1 : 0); i < rs.size()-1; i+=2) {
                Piecewise<SBasis> port = portion(x+offs, rs[i], rs[i+1]);
                output.concat(compose(uskeleton,port)+portion(y, rs[i], rs[i+1])*compose(n,port));
            }
        }

        cairo_pw_d2_sb(cr, output);
        cairo_set_source_rgba(cr,1.0,0.0,1.0,1.0);
        cairo_stroke(cr);

        Toy::draw(cr, notify, width, height, save,timer_stream);
    }        