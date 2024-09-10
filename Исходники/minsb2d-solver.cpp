    virtual void draw(cairo_t *cr, std::ostringstream *notify, int width, int height, bool save, std::ostringstream *timer_stream) {

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

/*
        SBasis2d f = y_x2();
        D2<SBasis> true_solution(Linear(0,1),Linear(0,1));
        true_solution[Y].push_back(Linear(-1,-1));
        SBasis zero = SBasis(Linear(0.));
        Geom::Point A = true_solution(tA);
        Geom::Point B = true_solution(tB);
*/

        SBasis2d f = x2_plus_y2_1();
        D2<Piecewise<SBasis> > true_solution;
        true_solution[X] = cos(SBasis(Linear(0,3.141592/2)));
        true_solution[Y] = sin(SBasis(Linear(0,3.141592/2)));
        Piecewise<SBasis> zero = Piecewise<SBasis>(SBasis(Linear(0.)));
        //Geom::Point A(cos(tA*M_PI/2), sin(tA*M_PI/2));// = true_solution(tA);
        //Geom::Point B(cos(tB*M_PI/2), sin(tB*M_PI/2));// = true_solution(tB);
        Geom::Point A = true_solution(tA);
        Geom::Point B = true_solution(tB);
        Point dA(-sin(tA*M_PI/2), cos(tA*M_PI/2));
        Geom::Point dB(-sin(tB*M_PI/2), cos(tB*M_PI/2));
        SBasis2d dfdu = partial_derivative(f, 0);
        SBasis2d dfdv = partial_derivative(f, 1);
        Geom::Point dfA(dfdu.apply(A[X],A[Y]),dfdv.apply(A[X],A[Y]));
        Geom::Point dfB(dfdu.apply(B[X],B[Y]),dfdv.apply(B[X],B[Y]));
        dA = rot90(dfA);
        dB = rot90(dfB);

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
        for(int degree = 2; degree < 2; degree++) {
            D2<SBasis> zeroset = sb2dsolve(f,A,B,degree);
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
        if (1) {

            bits_n_bobs par = {&f, A, B, dA, dB};
            bits_n_bobs* bnb = &par;
            std::cout << f[0] << "= intial f \n";
            const gsl_multimin_fminimizer_type *T = 
                gsl_multimin_fminimizer_nmsimplex;
            gsl_multimin_fminimizer *s = NULL;
            gsl_vector *ss, *x;
            gsl_multimin_function minex_func;
     
            size_t iter = 0;
            int status;
            double size;
     
            /* Starting point */
            x = gsl_vector_alloc (2);
            gsl_vector_set (x, 0, 0.552); // magic number for quarter circle
            gsl_vector_set (x, 1, 0.552);
     
            /* Set initial step sizes to 1 */
            ss = gsl_vector_alloc (2);
            gsl_vector_set_all (ss, 0.1);
     
            /* Initialize method and iterate */
            minex_func.n = 2;
            minex_func.f = &my_f;
            minex_func.params = (void *)&par;
     
            s = gsl_multimin_fminimizer_alloc (T, 2);
            gsl_multimin_fminimizer_set (s, &minex_func, x, ss);
     
            do
            {
                iter++;
                status = gsl_multimin_fminimizer_iterate(s);
           
                if (status) 
                    break;
     
                size = gsl_multimin_fminimizer_size (s);
                status = gsl_multimin_test_size (size, 1e-7);
     
                if (status == GSL_SUCCESS)
                {
                    printf ("converged to minimum at\n");
                }
     
            }
            while (status == GSL_CONTINUE && iter < 100);
            printf ("%5lu %g %gf f() = %g size = %g\n", 
                    iter,
                    gsl_vector_get (s->x, 0), 
                    gsl_vector_get (s->x, 1), 
                    s->fval, size);
            {
                double x = gsl_vector_get(s->x, 0);
                double y = gsl_vector_get(s->x, 1);
                Bezier b0(bnb->B[0], bnb->B[0]+bnb->dB[0]*x, bnb->A[0]+bnb->dA[0]*y, bnb->A[0]);
                Bezier b1(bnb->B[1], bnb->B[1]+bnb->dB[1]*x, bnb->A[1]+bnb->dA[1]*y, bnb->A[1]);
            
                D2<SBasis> zeroset(b0.toSBasis(), b1.toSBasis());
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
       
            gsl_vector_free(x);
            gsl_vector_free(ss);
            gsl_multimin_fminimizer_free (s);
        }
        *notify << "Gray: f-graph and true solution,\n";
        *notify << "Red: solver solution,\n";
        *notify << "Purple: value of f over solver solution.\n";
        *notify << "  error: "<< error <<".\n";
        
        Toy::draw(cr, notify, width, height, save,timer_stream);
    }