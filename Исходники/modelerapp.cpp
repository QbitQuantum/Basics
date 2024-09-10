void ModelerApplication::Init(ModelerViewCreator_f createView, 
                              const ModelerControl controls[], unsigned numControls)
{
    int i;

    m_animating   = false;
    m_numControls = numControls;

    // ********************************************************
    // Create the FLTK user interface
    // ********************************************************
    
    m_ui = new ModelerUserInterface();
    
    // Store pointers to the controls for manipulation
    m_controlLabelBoxes   = new Fl_Box*[numControls];
    m_controlValueSliders = new Fl_Value_Slider*[numControls];
    
    // Constants for user interface setup
    const int textHeight    = 20;
    const int sliderHeight  = 20;
    const int packWidth     = m_ui->m_controlsPack->w();

    m_ui->m_controlsPack->begin();
    // For each control, add appropriate objects to the user interface
    for (i=0; i<m_numControls; i++)
    {
        // Add the entry to the selection box
        m_ui->m_controlsBrowser->add(controls[i].m_name);

        // Add the label (but make it invisible for now)
        Fl_Box *box = new Fl_Box(0, 0, packWidth, textHeight, controls[i].m_name);
        box->labelsize(12);
        box->hide();
        box->box(FL_FLAT_BOX); // otherwise, Fl_Scroll messes up (ehsu)

        m_controlLabelBoxes[i] = box;

        // Add the slider (but make it invisible for now)
        Fl_Value_Slider *slider = new Fl_Value_Slider(0, 0, packWidth, sliderHeight,0);
        slider->type(FL_HOR_NICE_SLIDER);
        slider->range(controls[i].m_minimum, controls[i].m_maximum);
        slider->step(((int)(controls[i].m_stepsize * 100)) / 100.0);
        slider->value(controls[i].m_value);
        slider->labelsize(13);
        slider->align(FL_ALIGN_RIGHT);
        slider->hide(); 
        m_controlValueSliders[i] = slider;
        slider->callback((Fl_Callback*)ModelerApplication::SliderCallback);
    }
    m_ui->m_controlsPack->end();

	// Make sure that we remove the view from the
	// Fl_Group, otherwise, it'll blow up 
	// THIS BUG FIXED 04-18-01 ehsu
	m_ui->m_modelerWindow->remove(*(m_ui->m_modelerView));
	delete m_ui->m_modelerView;

	m_ui->m_modelerWindow->begin();
	m_ui->m_modelerView = createView(0, 0, m_ui->m_modelerWindow->w(), m_ui->m_modelerWindow->h() ,NULL);
	Fl_Group::current()->resizable(m_ui->m_modelerView);
	m_ui->m_modelerWindow->end();
}