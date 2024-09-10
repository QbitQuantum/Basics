/*" + gaycolor.red() + "," + gaycolor.green() + "," + gaycolor.blue() + "*/
PluginGeneratorGUI::PluginGeneratorGUI(PluginManager& pman,QWidget* parent )
:QDockWidget(parent),plugscriptname(),author(),mail(),init(false),finfo(QApplication::applicationDirPath()),doc(NULL),PM(pman)
{
	QFrame* f = new QFrame(this);
	QGridLayout* lay = new QGridLayout();
	tabs = new QTabWidget(this);
	tabs->setUsesScrollButtons(true);
	//setWidget(tabs);
	int openedtabs = tabs->count();
	if (openedtabs == 0)
		addNewFilter();
	else 
	{
		if (openedtabs > 1)
			for (int ii = 1;ii < openedtabs;++ii)
				tabs->removeTab(ii);
		addNewFilter();
	}
	lay->addWidget(tabs);
	lay->setAlignment(Qt::AlignVCenter);
	f->setLayout(lay);
	setWidget(f);
	createContextMenu();
	this->setVisible(false);
	//this->setScroll
}