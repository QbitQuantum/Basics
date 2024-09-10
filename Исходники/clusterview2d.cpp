ClusterView2D::ClusterView2D(int x, int y, int w, int h, int inResolution, cxVolume * pVolume) : Fl_Gl_Window(x, y, w, h-COLOR_CHOOSER_HEIGHT){

	//mode(FL_ALPHA | FL_DEPTH | FL_DOUBLE | FL_RGB8 );
	//	Fl::add_idle(&idle_cp, (void*)this);
	opacityDisp = 0;
	histogram1D = 0;
	m_dataPts = NULL;
	m_cluster = NULL;
	m_ctrs = NULL;
	m_pVolume = pVolume;
	
	m_percentHeight = (float)COLOR_CHOOSER_HEIGHT / (float) h;
	m_percentWidth = (float)COLOR_CHOOSER_WIDTH / (float) w;
	ClusterView2D *ihateptrs = this; // this is necessary because &this doesnt work.
		
	//m_buttonA = new Fl_Button(x+MARGIN+COLOR_CHOOSER_WIDTH, y+(h-COLOR_CHOOSER_HEIGHT)+MARGIN, BUTTON_WIDTH,BUTTON_HEIGHT, "Reset");
	//m_buttonA->callback((Fl_Callback*)cb_buttonA, this);
	//m_buttonA->resizable(0);
	

	Fl_Group* o = new Fl_Group(	2,
								y+(h-COLOR_CHOOSER_HEIGHT)+MARGIN,
								COLOR_CHOOSER_WIDTH*3,
								COLOR_CHOOSER_HEIGHT*4,"K-Means settings");
    o->box(FL_ENGRAVED_FRAME);
    o->align(FL_ALIGN_TOP_LEFT);

	m_pInputA = new Fl_Input(	o->x()+3,
								o->y()+MARGIN,
								BUTTON_WIDTH*2 + 3*2,
								BUTTON_HEIGHT,"Filename");
    m_pInputA->value("");
	m_pInputA->align(FL_ALIGN_RIGHT);
	
	m_pButtonChooser = new Fl_Button(	(m_pInputA->x()+m_pInputA->w()),
										o->y()+ MARGIN, 
										BUTTON_WIDTH, BUTTON_HEIGHT,"Browse..");
    m_pButtonChooser->callback((Fl_Callback *)cb_ButtonChooser, this);
	
	m_pFileChooser = NULL;
	
	m_inp_tch = new Fl_Input(o->x() + 3, m_pInputA->y()+ BUTTON_HEIGHT*2, BUTTON_WIDTH, BUTTON_HEIGHT, "timesteps intervals");
	m_inp_tch->align(FL_ALIGN_TOP_LEFT);
	m_inp_tch->value("12");
	
	m_inp_t = new Fl_Input(o->x() + 3, m_pInputA->y()+ BUTTON_HEIGHT*3 + MARGIN, BUTTON_WIDTH, BUTTON_HEIGHT, "algorithm");
    m_inp_t->align(FL_ALIGN_TOP_LEFT);
	m_inp_t->value("0");
	
	m_inp_k = new Fl_Input(m_inp_tch->x()+m_inp_tch->w() + 3, m_pInputA->y()+ BUTTON_HEIGHT*2, BUTTON_WIDTH, BUTTON_HEIGHT, "clusters");
	m_inp_k->align(FL_ALIGN_TOP_LEFT);
	m_inp_k->value("3");
	
	m_inp_s = new Fl_Input(m_inp_t->x()+m_inp_t->w() + 3, m_pInputA->y()+ BUTTON_HEIGHT*3 + MARGIN, BUTTON_WIDTH, BUTTON_HEIGHT, "stages");
	m_inp_s->align(FL_ALIGN_TOP_LEFT);
	m_inp_s->value("300");
	
	m_inp_start_time = new Fl_Input(m_inp_k->x()+m_inp_k->w() + 3, m_pInputA->y()+ BUTTON_HEIGHT*2, 
									BUTTON_WIDTH, BUTTON_HEIGHT, "start timestep");
	m_inp_start_time->align(FL_ALIGN_TOP_LEFT);
	m_inp_start_time->value("0");

	m_inp_total_time = new Fl_Input(m_inp_s->x()+m_inp_s->w() + 3, m_pInputA->y()+ BUTTON_HEIGHT*3 + 
									MARGIN, BUTTON_WIDTH, BUTTON_HEIGHT, "number of timesteps");
	m_inp_total_time->align(FL_ALIGN_TOP_LEFT);
	m_inp_total_time->value("120");


	Fl_Button* bt_save = new Fl_Button(	m_inp_tch->x()+m_inp_tch->w() + 3,
										m_pInputA->y()+ BUTTON_HEIGHT*5 + MARGIN*3, 
										BUTTON_WIDTH, BUTTON_HEIGHT,"Create new cluster");
	bt_save->callback((Fl_Callback *)cb_ButtonSave, this);

	Fl_Button* bt_load = new Fl_Button(	bt_save->x()+bt_save->w()+3,
										m_pInputA->y()+ BUTTON_HEIGHT*5 + MARGIN*3, 
										BUTTON_WIDTH, BUTTON_HEIGHT,"Load cluster");
	bt_load->callback((Fl_Callback *)cb_ButtonLoad, this);	

	
	o->end();
	m_pLB = new Fl_Light_Button(o->x() + o->w() + 3,
			 	    (y+(h-COLOR_CHOOSER_HEIGHT)+MARGIN), 
				    BUTTON_WIDTH,BUTTON_HEIGHT, "Show all clusters");
    //m_pLB->labelsize(TEXTSIZE);
    m_pLB->callback((Fl_Callback *)cb_LB, this);
	m_pLB->set();
	m_bshowall = true; 

	m_pButtonNext = new Fl_Button(	o->x() + o->w() + 3,
									(y+(h-COLOR_CHOOSER_HEIGHT)+MARGIN + BUTTON_HEIGHT + 3),
									BUTTON_WIDTH, BUTTON_HEIGHT,"Next Cluster");
    m_pButtonNext->callback((Fl_Callback *)cb_ButtonNext, this);

#ifdef CHANGES
	m_pButtonClear = new Fl_Light_Button(	o->x() + o->w() + 3,
									(y+(h-COLOR_CHOOSER_HEIGHT)+MARGIN + BUTTON_HEIGHT*2 + 6),
									BUTTON_WIDTH, BUTTON_HEIGHT,"Clear Cluster");
    m_pButtonClear->callback((Fl_Callback *)cb_ButtonClear, this);
	m_pButtonClear->set();
	m_bClear = true;
#endif	
/*
	int tch     = 0;        // use all timesteps in calculating KMeans (use only 1 chunk) -tch
int alg     = 0;        // use Lloyd by default  -t option
int	k		= 4;		// number of centers     -k option
int	dim		= 2;		// dimension            
int	stages		= 1000;		// number of stages  -s option

	strcpy(params[0],"");
	strcpy(params[1],"-t");
	strcpy(params[2],"3");
	strcpy(params[3],"-tch");
	strcpy(params[4],"12");
	strcpy(params[5],"-tac");
	strcpy(params[6],filename);
	strcpy(params[7],"-k");
	strcpy(params[8],"3");
	strcpy(params[9],"-s");
	strcpy(params[10],"300");
	main_cluster(nparams, params);
	*/

	m_total_size = 0;
	m_dim = 0;
	m_selcluster = 0;
	m_bInit = false;
	m_nClusters = 0;

	m_xblock = 1;
	m_yblock = 1;
	m_zblock = 1;

	m_datamin = -100;
	m_datamax = 100;
#ifdef SHOW_CLUSTER
	pVolume->SetClusterView(this);
#endif

	srand((unsigned)time( NULL ));
}