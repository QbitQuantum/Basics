Wt::WContainerWidget*
Application::instantiateMainTabs() {
    Wt::WContainerWidget *mainTabContainer = new Wt::WContainerWidget;
    Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout;
    mainTabContainer->setLayout(vbox);

    wMainTabs_ = new Wt::WTabWidget;
    wMainTabs_->currentChanged().connect(boost::bind(&Application::changeTab2, this, _1));
    vbox->addWidget(wMainTabs_, 1 /*stretch*/);

    for (size_t i=0; i<NMainTabs; ++i) {
        Wt::WString tabName;
        Wt::WContainerWidget *tabContent = NULL;
        switch ((MainTab)i) {
        case PartitionerTab: {
            tabName = "Partitioner";
            tabContent = wPartitioner_ = new WPartitioner(ctx_);
            wPartitioner_->specimenParsed().connect(boost::bind(&Application::handleSpecimenParsed, this, _1));
            wPartitioner_->specimenLoaded().connect(boost::bind(&Application::handleSpecimenLoaded, this, _1));
            wPartitioner_->specimenPartitioned().connect(boost::bind(&Application::handleSpecimenPartitioned, this, _1));
            break;
        }
        case MemoryMapTab: {
            tabName = "Memory Map";
            tabContent = wMemoryMap_ = new WMemoryMap;
            wMemoryMap_->mapChanged().connect(boost::bind(&Application::memoryMapChanged, this));
            wMemoryMap_->allowDownloads(ctx_.settings.allowDownloads);
            break;
        }
        case FunctionListTab: {
            tabName = "Functions";
            tabContent = wFunctionList_ = new WFunctionList(ctx_);
            wFunctionList_->functionChanged().connect(boost::bind(&Application::changeFunction, this, _1));
            wFunctionList_->functionRowDoubleClicked()
            .connect(boost::bind(&Application::changeFunctionDoubleClick, this, _1));
            break;
        }
        case FunctionSummaryTab: {
            tabName = "Summary";
            tabContent = wFunctionSummary_ = new WFunctionSummary(ctx_);
            break;
        }
        case FunctionCfgTab: {
            tabName = "CFG";
            tabContent = wFunctionCfg_ = new WFunctionCfg(ctx_);
            wFunctionCfg_->functionChanged().connect(boost::bind(&Application::changeFunction, this, _1));
            wFunctionCfg_->functionClicked().connect(boost::bind(&Application::changeFunction, this, _1));
            wFunctionCfg_->addressClicked().connect(boost::bind(&Application::showHexDumpAtAddress, this, _1));
            wFunctionCfg_->basicBlockClicked().connect(boost::bind(&Application::changeBasicBlock, this, _1));
            break;
        }
        case AssemblyTab: {
            tabName = "Assembly";
            tabContent = wAssembly_ = new WAssemblyListing(ctx_);
            break;
        }
        case HexDumpTab: {
            tabName = "Hexdump";
            tabContent = wHexDump_ = new WHexDump;
            wHexDump_->byteClicked().connect(boost::bind(&Application::updateAddressCrossReferences, this, _1));
            break;
        }
        case MagicTab: {
            tabName = "Magic";
            tabContent = wMagic_ = new WMagic;
            break;
        }
        case StringsTab: {
            tabName = "Strings";
            tabContent = wStrings_ = new WStrings;
            wStrings_->stringClicked().connect(boost::bind(&Application::updateStringCrossReferences, this, _1));
            break;
        }
        case StatusTab: {
            tabName = "Status";
            tabContent = wStatus_ = new WStatus(ctx_);
            break;
        }
        default:
            ASSERT_not_reachable("invalid main tab");
        }
        ASSERT_not_null(tabContent);
        ASSERT_forbid(tabName.empty());
        wMainTabs_->addTab(tabContent, tabName);
    }
    return mainTabContainer;
}