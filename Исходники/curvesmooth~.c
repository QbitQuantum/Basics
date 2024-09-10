//this gets called when the object is created; everytime the user types in new args, this will get called
void *curvesmooth_new(t_symbol *s, long argc, t_atom *argv)
{
	int i, j;
    
    long upsmooth;      // in ms
    long downsmooth;    // in ms
    double upcoeff;
    double downcoeff;
    
    // deal with incoming values
    if (argc > 0) {
        upsmooth = atom_getlong(argv);
    } else {
        upsmooth = 0;
    }
	
    if (argc > 1) {
        downsmooth = atom_getlong(argv+1);
    } else {
        downsmooth = 0;
    }
	
    if (argc > 2) {
        upcoeff = atom_getfloat(argv+2);
    } else {
        upcoeff = 0;
    }
	
    if (argc > 3) {
        downcoeff = atom_getfloat(argv+3);
    } else {
        downcoeff = 0;
    }
    
    // post("us: %ld, ds: %ld, uc: %f, dc: %f", upsmooth, downsmooth, upcoeff, downcoeff);
    
    //leave this; creates our object
    t_curvesmooth *x = (t_curvesmooth *)object_alloc(curvesmooth_class);
    
    //zero out the struct, to be careful (takk to jkclayton)
    if (x) { 
        for(i=sizeof(t_pxobject);i<sizeof(t_curvesmooth);i++) {
            ((char *)x)[i]=0;
        }
	
        x->num_inputs = 5;
        x->num_outputs = 1;

        //setup up inputs and outputs, for audio
        
        //inputs
        dsp_setup((t_pxobject *)x, x->num_inputs);
        //if you just need one input for message (not using audio), you can just set num_inputs = 1
        //i don't think this causes a performance hit.
        
        //outputs
        for (i=0;i<x->num_outputs;i++) {
            outlet_new((t_object *)x, "signal");
        }   
        //can use intin, floatout, listout, etc... for setting up non-audio ins and outs.
        //but, the order in which you call these funcs is important.
        //for instance, from gQ~
        /*    
        x->outfloat = floatout((t_object *)x);
        x->outlist = listout((t_object *)x);
        outlet_new((t_object *)x, "signal");
        outlet_new((t_object *)x, "signal");
       */
       //this will create four outputs, *rightmost* created first, so the outlets, from left to right, will look like
       //(signal) (signal) (list) (float)
       //when you instantiate gQ~ in Max/MSP.
        
        //initialize some variables; important to do this!
        for (i=0;i<x->num_inputs;i++){
            x->in[i] = 0.;
            x->in_connected[i] = 0;
        }
        x->power = 1;

        x->in[1] = (double)upsmooth;
        x->in[2] = (double)downsmooth;
        x->in[3] = (double)upcoeff;
        x->in[4] = (double)downcoeff;
        x->c = 0.;
        x->update_D = 1;
        x->current_direction = 1;
        x->D = 0.;
        
        //lookup table alloc and init
        for(i=0;i<TABLE_SIZE;i++) {
            //x->s_table_k_exp[i]= t_getbytes(TABLE_SIZE*sizeof(double));
            x->s_table_k_exp[i]= (double *)sysmem_newptr(TABLE_SIZE*sizeof(double));
            if (!x->s_table_k_exp[i]) {
                error("curvesmooth~: out of memory");
                return NULL;
            }
                
            //x->s_table_k_log[i] = t_getbytes(TABLE_SIZE*sizeof(double));
            x->s_table_k_log[i] = (double *)sysmem_newptr(TABLE_SIZE*sizeof(double));
            if (!x->s_table_k_log[i]) {
                error("curvesmooth~: out of memory");
                return NULL;
            }
        }
        for(i=2;i<TABLE_SIZE;i++) { //k, indices 2 to 1000 (exp) and 1 to 1000 (log, so .001 to 1, though we should never use 1)
            for(j=1;j<TABLE_SIZE;j++) { //d or d/D, 0 to 1
                x->s_table_k_exp[i][j] = (i-1.) / ((powf(i, j*.001) - 1.));
                x->s_table_k_log[i-1][j] = ((i-1.)*.001 - 1.) / ((powf((i-1.)*.001, j*.001) - 1.));
            }
            x->s_table_k_exp[i][0] = 0.;
            x->s_table_k_log[i][0] = 0.;
        }

        //occasionally this line is necessary if you are doing weird asynchronous things with the in/out vectors
        //x->x_obj.z_misc = Z_NO_INPLACE;
    }

    return (x);
}