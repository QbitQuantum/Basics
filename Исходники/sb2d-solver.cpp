    virtual void draw(cairo_t *cr, std::ostringstream *notify, int width, int height, bool save) {

        double slider_top = width/4.;
        double slider_bot = width*3./4.;
        double slider_margin = width/8.;
        if(hand.pts.empty()) {
            hand.pts.push_back(Geom::Point(width*3./16., 3*width/4.));
            hand.pts.push_back(hand.pts[0] + Geom::Point(width/2., 0));
            hand.pts.push_back(hand.pts[0] + Geom::Point(width/8., -width/12.));
            hand.pts.push_back(hand.pts[0] + Geom::Point(0,-width/4.));
            hand.pts.push_back(Geom::Point(slider_margin,slider_bot));
            hand.pts.push_back(Geom::Point(width-slider_margin,slider_top));
        }
        
        hand.pts[4][X] = slider_margin;
        if (hand.pts[4][Y]<slider_top) hand.pts[4][Y] = slider_top; 
        if (hand.pts[4][Y]>slider_bot) hand.pts[4][Y] = slider_bot; 
        hand.pts[5][X] = width-slider_margin;
        if (hand.pts[5][Y]<slider_top) hand.pts[5][Y] = slider_top; 
        if (hand.pts[5][Y]>slider_bot) hand.pts[5][Y] = slider_bot; 

        double tA = (slider_bot-hand.pts[4][Y])/(slider_bot-slider_top);
        double tB = (slider_bot-hand.pts[5][Y])/(slider_bot-slider_top);

        cairo_move_to(cr,Geom::Point(slider_margin,slider_bot));
        cairo_line_to(cr,Geom::Point(slider_margin,slider_top));
        cairo_move_to(cr,Geom::Point(width-slider_margin,slider_bot));
        cairo_line_to(cr,Geom::Point(width-slider_margin,slider_top));
        cairo_set_line_width(cr,.5);
        cairo_set_source_rgba (cr, 0., 0.3, 0., 1.);
        cairo_stroke(cr);
        
        Frame frame;
        frame.O = hand.pts[0];//
        frame.x = hand.pts[1]-hand.pts[0];//
        frame.y = hand.pts[2]-hand.pts[0];//
        frame.z = hand.pts[3]-hand.pts[0];// 

#if 0
        SBasis2d f = y_x2();
        D2<SBasis> true_solution(Linear(0,1),Linear(0,1));
        true_solution[Y].push_back(Linear(-1,-1));
        SBasis zero = SBasis(Linear(0.));
        Geom::Point A = true_solution(tA);
        Geom::Point B = true_solution(tB);

#else
        SBasis2d f = x2_plus_y2_1();
        D2<Piecewise<SBasis> > true_solution;
        true_solution[X] = cos(SBasis(Linear(0,3.14/2)));
        true_solution[Y] = sin(SBasis(Linear(0,3.14/2)));
        Piecewise<SBasis> zero = Piecewise<SBasis>(SBasis(Linear(0.)));
        Geom::Point A = true_solution(tA);
        Geom::Point B = true_solution(tB);
#endif

        plot3d(cr,Linear(0,1),Linear(0,0),Linear(0,0),frame);
        plot3d(cr,Linear(0,1),Linear(1,1),Linear(0,0),frame);
        plot3d(cr,Linear(0,0),Linear(0,1),Linear(0,0),frame);
        plot3d(cr,Linear(1,1),Linear(0,1),Linear(0,0),frame);
        cairo_set_line_width(cr,.2);
        cairo_set_source_rgba (cr, 0., 0., 0., 1.);
        cairo_stroke(cr);

        plot3d_top(cr,f,frame);
        cairo_set_line_width(cr,1);        
        cairo_set_source_rgba (cr, .5, 0.5, 0.5, 1.);
        cairo_stroke(cr);
        plot3d(cr,f,frame);
        cairo_set_line_width(cr,.2);        
        cairo_set_source_rgba (cr, .5, 0.5, 0.5, 1.);
        cairo_stroke(cr);

        plot3d(cr, true_solution[X], true_solution[Y], zero, frame);
        cairo_set_line_width(cr,.5);
        cairo_set_source_rgba (cr, 0., 0., 0., 1.);
        cairo_stroke(cr);
        double error;
        for(int degree = 1; degree < 4; degree++) {
            //D2<SBasis> zeroset = sb2dsolve(f,A,B,degree);
            D2<SBasis> zeroset = sb2d_cubic_solve(f,A,B);
            plot3d(cr, zeroset[X], zeroset[Y], SBasis(Linear(0.)),frame);
            cairo_set_line_width(cr,1);        
            cairo_set_source_rgba (cr, 0.9, 0., 0., 1.);
            cairo_stroke(cr);
            
            SBasis comp = compose(f,zeroset);
            plot3d(cr, zeroset[X], zeroset[Y], comp, frame);
            cairo_set_source_rgba (cr, 0.7, 0., 0.7, 1.);
            cairo_stroke(cr);
            //Fix Me: bounds_exact does not work here?!?!
            Interval bounds = *bounds_fast(comp);
            error = (bounds.max()>-bounds.min() ? bounds.max() : -bounds.min() );
        }
        *notify << "Gray: f-graph and true solution,\n";
        *notify << "Red: solver solution,\n";
        *notify << "Purple: value of f over solver solution.\n";
        *notify << "  error: "<< error <<".\n";
                
        Toy::draw(cr, notify, width, height, save);
    }