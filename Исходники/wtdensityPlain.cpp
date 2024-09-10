// The env argument contains information about the new session, and the initial request. 
// It must be passed to the WApplication // constructor so it is typically also an argument
// for your custom application constructor.
DensityApp::DensityApp(const WEnvironment& env, RInside & R) : WApplication(env), R_(R) {

    setTitle("Witty WebApp With RInside");			// application title

    std::string tfcmd = "tfile <- tempfile(pattern=\"img\", tmpdir=\"/tmp\", fileext=\".png\")";	
    tempfile_ = Rcpp::as<std::string>(R_.parseEval(tfcmd));  	// assign to 'tfile' in R, and report back
    bw_ = 100; 
    kernel_ = 0;						// parameters used to estimate the density
    cmd_ = "c(rnorm(100,0,1), rnorm(50,5,1))";			// random draw command string
   
    Wt::WGroupBox *wc = new Wt::WGroupBox("Density Estimation", root());

    Wt::WHBoxLayout *layout = new Wt::WHBoxLayout();
    Wt::WContainerWidget *midbox = new Wt::WContainerWidget(root());
    layout->addWidget(midbox);
    Wt::WContainerWidget *container = new Wt::WContainerWidget(root());
    layout->addWidget(container);

    wc->setLayout(layout, AlignTop | AlignJustify);

    midbox->addWidget(new WText("Density estimation scale factor (div. by 100)"));
    midbox->addWidget(new WBreak());                       	// insert a line break
    spin_ = new WSpinBox(midbox);
    spin_->setRange(5, 200);
    spin_->setValue(bw_);
    spin_->valueChanged().connect(this, &DensityApp::reportSpinner);

    midbox->addWidget(new WBreak());                       	// insert a line break
    midbox->addWidget(new WText("R Command for data generation"));  // show some text
    midbox->addWidget(new WBreak());                       	// insert a line break
    codeEdit_ = new WLineEdit(midbox);                     	// allow text input
    codeEdit_->setTextSize(30);
    codeEdit_->setText(cmd_); 
    codeEdit_->setFocus();                                 	// give focus
    codeEdit_->enterPressed().connect(this, &DensityApp::reportEdit);

    group_ = new Wt::WButtonGroup(container);		    	// use button group to arrange radio buttons

    Wt::WRadioButton *button;
    button = new Wt::WRadioButton("Gaussian", container);
    new Wt::WBreak(container);
    group_->addButton(button, Gaussian);

    button = new Wt::WRadioButton("Epanechnikov", container);
    new Wt::WBreak(container);
    group_->addButton(button, Epanechnikov);

    button = new Wt::WRadioButton("Rectangular", container);
    new Wt::WBreak(container);
    group_->addButton(button, Rectangular);

    button = new Wt::WRadioButton("Triangular", container);
    new Wt::WBreak(container);
    group_->addButton(button, Triangular);

    button = new Wt::WRadioButton("Cosine", container);
    new Wt::WBreak(container);
    group_->addButton(button, Cosine);

    group_->setCheckedButton(group_->button(kernel_));
    group_->checkedChanged().connect(this, &DensityApp::reportButton);

    Wt::WGroupBox *botbox = new Wt::WGroupBox("Resulting chart", root());
    imgfile_ = new Wt::WFileResource("image/png", tempfile_);
    imgfile_->suggestFileName("density.png");  // name the clients sees of datafile
    img_ = new Wt::WImage(imgfile_, "PNG version", botbox);

    Wt::WGroupBox *stbox = new Wt::WGroupBox("Status", root());
    greeting_ = new WText(stbox);                         	// empty text
    greeting_->setText("Setting up...");
  
    reportEdit();						// create a new RNG draw in Yvec_
    plot();							// and draw a new density plot
}