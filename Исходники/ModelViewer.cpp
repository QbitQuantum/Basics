void ModelViewer::SetupFilePicker()
{
	UI::Context *c = m_ui.Get();

	UI::List *list = c->List();
	UI::Button *quitButton = c->Button();
	UI::Button *loadButton = c->Button();
	quitButton->SetInnerWidget(c->Label("Quit"));
	loadButton->SetInnerWidget(c->Label("Load"));

	std::vector<std::string> models;
	collect_models(models);

	for (std::vector<std::string>::const_iterator it = models.begin(); it != models.end(); ++it) {
		list->AddOption(*it);
	}
	UI::Widget *fp =
	c->Grid(UI::CellSpec(1,3,1), UI::CellSpec(1,3,1))
		->SetCell(1,1,
			c->VBox(10)
				->PackEnd(c->Label("Select a model"))
				->PackEnd(c->Expand(UI::Expand::BOTH)->SetInnerWidget(c->Scroller()->SetInnerWidget(list)))
				->PackEnd(c->Grid(2,1)->SetRow(0, UI::WidgetSet(
					c->Align(UI::Align::LEFT)->SetInnerWidget(loadButton),
					c->Align(UI::Align::RIGHT)->SetInnerWidget(quitButton)
				)))
		);

	m_logScroller->Layout(); //issues without this
	c->SetInnerWidget(c->Grid(2,1)
		->SetRow(0, UI::WidgetSet(fp, m_logScroller.Get()))
	);

	c->Layout();

	loadButton->onClick.connect(sigc::bind(sigc::mem_fun(*this, &ModelViewer::OnPickModel), list));
	quitButton->onClick.connect(sigc::mem_fun(*this, &ModelViewer::OnQuit));
}