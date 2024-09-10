MatrixPluginGUI::MatrixPluginGUI(int w, int h,MatrixPlugin *o,ChannelHandler *ch,const HostInfo *Info) :
SpiralPluginGUI(w,h,o,ch),
m_LastLight(0),
m_LastPatSeqLight(0)
{
	//size_range(10,10);
	m_Pattern = new Fl_Counter (5, 20, 40, 20, "View");
        m_Pattern->labelsize (10);
	m_Pattern->type (FL_SIMPLE_COUNTER);
        m_Pattern->box (FL_PLASTIC_UP_BOX);
        m_Pattern->color (Info->GUI_COLOUR);
        m_Pattern->step (1);
        m_Pattern->minimum (0);
        m_Pattern->maximum (NUM_PATTERNS-1);
	m_Pattern->value (0);
	m_Pattern->callback ((Fl_Callback*)cb_Pattern);
	add (m_Pattern);

	m_PlayPattern = new Fl_Counter (50, 20, 40, 20, "Play");
        m_PlayPattern->labelsize (10);
	m_PlayPattern->type (FL_SIMPLE_COUNTER);
        m_PlayPattern->box (FL_PLASTIC_UP_BOX);
        m_PlayPattern->color (Info->GUI_COLOUR);
	m_PlayPattern->step (1);
        m_PlayPattern->minimum (0);
        m_PlayPattern->maximum (NUM_PATTERNS-1);
	m_PlayPattern->value (0);
	m_PlayPattern->callback ((Fl_Callback*)cb_PlayPattern);
	add (m_PlayPattern);

        m_Length = new Fl_Counter (5, 55, 40, 20, "Length");
        m_Length->labelsize (10);
	m_Length->type (FL_SIMPLE_COUNTER);
        m_Length->box (FL_PLASTIC_UP_BOX);
        m_Length->color (Info->GUI_COLOUR);
	m_Length->step (1);
	m_Length->value (64);
	m_Length->minimum (1);
	m_Length->maximum (64);
	m_Length->callback ((Fl_Callback*)cb_Length);
	add (m_Length);

	m_Octave = new Fl_Counter(5, 90, 40, 20, "Octave");
        m_Octave->labelsize(10);
	m_Octave->type (FL_SIMPLE_COUNTER);
        m_Octave->box (FL_PLASTIC_UP_BOX);
        m_Octave->color (Info->GUI_COLOUR);
        m_Octave->minimum (0);
        m_Octave->maximum (6);
	m_Octave->step (1);
	m_Octave->value (0);
	m_Octave->callback((Fl_Callback*)cb_Octave);
	add (m_Octave);

        m_Speed = new Fl_Knob (50, 60, 40, 40, "Speed");
        m_Speed->color (Info->GUI_COLOUR);
	m_Speed->type (Fl_Knob::DOTLIN);
        m_Speed->labelsize (10);
        m_Speed->minimum (0);
        m_Speed->maximum (400);
        m_Speed->step (0.01);
        m_Speed->value (8);
	m_Speed->callback ((Fl_Callback*)cb_Speed);
	add (m_Speed);

	m_SpeedVal = new Fl_Counter (5, 125, 85, 20, "");
	m_SpeedVal->labelsize (10);
	m_SpeedVal->value (10);
	m_SpeedVal->type (FL_SIMPLE_COUNTER);
        m_SpeedVal->box (FL_PLASTIC_UP_BOX);
        m_SpeedVal->color (Info->GUI_COLOUR);
	m_SpeedVal->step (1);
	m_SpeedVal->maximum (400);
	m_SpeedVal->minimum (0);
        m_SpeedVal->value (8);
	m_SpeedVal->callback ((Fl_Callback*)cb_SpeedVal);
	add (m_SpeedVal);

        m_CopyBtn = new Fl_Button (5, 150, 40, 20, "Copy");
	m_CopyBtn->labelsize (10);
        m_CopyBtn->box (FL_PLASTIC_UP_BOX);
        m_CopyBtn->color (Info->GUI_COLOUR);
        m_CopyBtn->selection_color (Info->GUI_COLOUR);
        m_CopyBtn->callback ((Fl_Callback*)cb_CopyBtn);
	add (m_CopyBtn);

	m_PasteBtn = new Fl_Button (50, 150, 40, 20, "Paste");
	m_PasteBtn->labelsize (10);
        m_PasteBtn->box (FL_PLASTIC_UP_BOX);
        m_PasteBtn->color (Info->GUI_COLOUR);
        m_PasteBtn->selection_color (Info->GUI_COLOUR);
	m_PasteBtn->deactivate();
	m_PasteBtn->callback ((Fl_Callback*)cb_PasteBtn);
	add (m_PasteBtn);

	m_ClearBtn = new Fl_Button (5, 175, 85, 20, "Clear");
	m_ClearBtn->labelsize (10);
        m_ClearBtn->box (FL_PLASTIC_UP_BOX);
        m_ClearBtn->color (Info->GUI_COLOUR);
        m_ClearBtn->selection_color (Info->GUI_COLOUR);
	m_ClearBtn->callback ((Fl_Callback*)cb_ClearBtn);
	add (m_ClearBtn);

	m_TransUpBtn = new Fl_Button (5, 200, 40, 20, "Up");
	m_TransUpBtn->labelsize (10);
        m_TransUpBtn->box (FL_PLASTIC_UP_BOX);
        m_TransUpBtn->color (Info->GUI_COLOUR);
        m_TransUpBtn->selection_color (Info->GUI_COLOUR);
	m_TransUpBtn->callback ((Fl_Callback*)cb_TransUpBtn);
	add (m_TransUpBtn);

	m_TransDnBtn = new Fl_Button (50, 200, 40, 20, "Down");
	m_TransDnBtn->labelsize (10);
        m_TransDnBtn->box (FL_PLASTIC_UP_BOX);
        m_TransDnBtn->color (Info->GUI_COLOUR);
        m_TransDnBtn->selection_color (Info->GUI_COLOUR);
	m_TransDnBtn->callback ((Fl_Callback*)cb_TransDnBtn);
	add (m_TransDnBtn);

	m_TransLbl = new Fl_Box (5, 216, 85, 20, "Transpose");
	m_TransLbl->labelsize(10);
	add (m_TransLbl);

      	m_NoteCut = new Fl_Button (5, h-30, 85, 20, "NoteCut");
	m_NoteCut->type (FL_TOGGLE_BUTTON);
        m_NoteCut->box (FL_PLASTIC_UP_BOX);
        m_NoteCut->color (Info->GUI_COLOUR);
        m_NoteCut->selection_color (Info->GUI_COLOUR);
	m_NoteCut->labelsize (10);
	m_NoteCut->value (0);
	m_NoteCut->callback ((Fl_Callback*)cb_NoteCut);
	add (m_NoteCut);

        int xoff=105;
	int yoff=40;
	int butsize=7;
	int n=0;

	fl_color(150,150,150);
	int markercol=fl_color();

	fl_color(170,170,170);
	int blcolour=fl_color();

	for(int x=0; x<MATX; x++)
	for(int y=0; y<MATY; y++)
	{
		Numbers[n]=n;
		m_Matrix[x][y] = new Fl_MatrixButton(xoff+x*butsize,yoff+((MATY-1)*butsize)-(y*butsize),butsize+1,butsize+1,"");
		m_Matrix[x][y]->type(1);
		m_Matrix[x][y]->box(FL_BORDER_BOX);
                m_Matrix[x][y]->SetSelColour (Info->GUI_COLOUR);
		if ((x%8)==0) m_Matrix[x][y]->color(markercol);
		else if ((y%12)==1 || (y%12)==3 || (y%12)==6 || (y%12)==8 || (y%12)==10) m_Matrix[x][y]->color(blcolour);
		else m_Matrix[x][y]->color(FL_GRAY);

		m_Matrix[x][y]->selection_color(FL_WHITE);
		m_Matrix[x][y]->callback((Fl_Callback*)cb_Matrix,(void*)&Numbers[n]);
		m_Matrix[x][y]->SetVolCallback((Fl_Callback*)cb_MatVol,(void*)&Numbers[n]);
		add(m_Matrix[x][y]);
		n++;
	}

	yoff=37;
	for(int y=0; y<MATY; y++)
	{
		Fl_Box *box = new Fl_Box(90,yoff+((MATY-1)*butsize)-(y*butsize),15,15,NoteText[y%12]);
		box->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT);
		box->labelsize(8);
	}

	xoff=103;
	for(int x=0; x<MATX; x++)
	{
		m_Flash[x] = new Fl_LED_Button(xoff+x*butsize,20,15,15,"");
		m_Flash[x]->selection_color(FL_WHITE);
		add(m_Flash[x]);
	}

	xoff=560;
	yoff=40;
	int height=12,gap=2;

	Fl_Box *patseqlabel = new Fl_Box(xoff,yoff-15,30,10,"Pat Seq");
	patseqlabel->labelsize(10);
	add(patseqlabel);

	for(int y=0; y<NUM_PATSEQ; y++)
	{
		m_PatSeq[y]= new Fl_Counter(xoff,yoff+y*(height+gap),25,height);
		m_PatSeq[y]->type(FL_SIMPLE_COUNTER);
		m_PatSeq[y]->step(1);
		m_PatSeq[y]->textsize(8);
                if (y==0) m_PatSeq[y]->minimum (0);
                else m_PatSeq[y]->minimum (-1);
                m_PatSeq[y]->value (m_PatSeq[y]->minimum ());
                m_PatSeq[y]->maximum (NUM_PATTERNS-1);
		m_PatSeq[y]->callback((Fl_Callback*)cb_PatSeq,(void*)&Numbers[y]);
		add(m_PatSeq[y]);

		m_PatSeqFlash[y] = new Fl_LED_Button(xoff+25,yoff+y*(height+gap),15,15,"");
		m_PatSeqFlash[y]->selection_color(FL_WHITE);
		add(m_PatSeqFlash[y]);
	}

	end();
}