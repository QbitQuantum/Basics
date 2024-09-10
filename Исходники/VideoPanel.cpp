      VideoPanel::VideoPanel(std::map<std::string, std::string>& p) : _parameter(p), Wt::Ext::Panel() {
        //        setLayout(new Wt::WFitLayout());
        Wt::WBorderLayout*l = new Wt::WBorderLayout();
        setLayout(l);
        std::set<std::string> avail_codecs;
        if (_parameter.count("available_codecs") > 0) {
          LOGDEBUG("Available codes" << _parameter["available_codecs"]);
          org::esb::util::StringTokenizer st(_parameter["available_codecs"], ",");
          while (st.hasMoreTokens()) {
            std::string codec_id = st.nextToken();
            avail_codecs.insert(codec_id);
            LOGDEBUG("avalable codec list" << codec_id);
          }
        }
        /*
         * Combobox for the Codec Selector
         */
        KeyValueModel * codec_model = new KeyValueModel();
        codec_model->addModelData("novideo", "No Video");
        codec_model->addModelData("copy", "Stream Copy");

        AVCodec *codec = NULL;
        int a = 0;
        while ((codec = av_codec_next(codec))) {
          if (codec->encode && codec->type == AVMEDIA_TYPE_VIDEO) {
            if (avail_codecs.count(codec->name) > 0) {
              codec_model->addModelData(codec->name, codec->long_name);
            } else {
              if (avail_codecs.size() == 0)
                codec_model->addModelData(codec->name, codec->long_name);
            }
          }
        }
        codec_model->sort(1);

        _codec = new ComboBox();

        _codec->setModel(codec_model);
        _codec->setModelColumn(1);
        _codec->setSelectedEntry(_parameter["codec_id"]);
        _codec->setTextSize(50);
        _codec->resize(300, Wt::WLength());


        _codec->activated().connect(SLOT(this, VideoPanel::codecSelected));


        main_panel = new Wt::Ext::Panel();
        Wt::WFitLayout * fit = new Wt::WFitLayout();
        main_panel->setLayout(fit);
        //main_panel->setBorder(false);

        l->addWidget(main_panel, Wt::WBorderLayout::Center);

        Wt::Ext::Panel * top_panel = new Wt::Ext::Panel();
        top_panel->resize(Wt::WLength(), 40);
        top_panel->setLayout(new Wt::WFitLayout());
        top_panel->setBorder(false);
        //        top_panel->layout()->addWidget(_codec);

        Wt::WContainerWidget *top = new Wt::WContainerWidget();
        top_panel->layout()->addWidget(top);
        Wt::WGridLayout * grid = new Wt::WGridLayout();
        top->setLayout(grid);
        top->resize(Wt::WLength(), 40);

        l->addWidget(top_panel, Wt::WBorderLayout::North);
        Wt::WLabel * label = new Wt::WLabel("Codec:");
        label->setBuddy(_codec);

        grid->addWidget(label, 0, 0);
        grid->addWidget(_codec, 0, 1);
        grid->addWidget(new Wt::WText(""), 0, 2);
        grid->setColumnStretch(1, 1);




        setCodecGui(_parameter["codec_id"]);
        //l->addWidget(builder,Wt::WBorderLayout::Center);
        //        return;
      }