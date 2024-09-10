      PresetFilterPanel::PresetFilterPanel(org::esb::hive::PresetReader::FilterList &filter) :_filterlist(filter),  Wt::Ext::Panel() {
        setLayout(new Wt::WFitLayout());

        Wt::WContainerWidget * main = new Wt::WContainerWidget();
        grid = new Wt::WGridLayout();
        main->setLayout(grid);
        layout()->addWidget(main);

        grid->addWidget(filter_table = new PresetFilterTable(filter), 0, 0);
        _cont=new Wt::WContainerWidget();
        _cont->setLayout(new Wt::WBorderLayout());
        _cont->resize(600,300);
        grid->addWidget(_cont, 1, 0);
        filter_table->itemSelectionChanged().connect(SLOT(this,PresetFilterPanel::filterSelected));
      }