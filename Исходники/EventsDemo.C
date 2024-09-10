WWidget *EventsDemo::wMouseEvent()
{
  WContainerWidget *result = new WContainerWidget();

  topic("WMouseEvent", result);
  addText(tr("events-WMouseEvent"), result);
  WContainerWidget *c = new WContainerWidget(result);
  WHBoxLayout *hlayout = new WHBoxLayout;
  c->setLayout(hlayout);
  WContainerWidget *l = new WContainerWidget;
  WContainerWidget *r = new WContainerWidget;
  new WText("clicked<br/>doubleClicked<br/>mouseWentOut<br/>mouseWentOver",
	    l);
  new WText("mouseWentDown<br/>mouseWentUp<br/>mouseMoved<br/>mouseWheel", r);
  hlayout->addWidget(l);
  hlayout->addWidget(r);
  c->resize(600, 300);
  l->decorationStyle().setBackgroundColor(Wt::gray);
  r->decorationStyle().setBackgroundColor(Wt::gray);
  // prevent that firefox interprets drag as drag&drop action
  l->setStyleClass("unselectable");
  r->setStyleClass("unselectable");
  l->clicked().connect(this, &EventsDemo::showClicked);
  l->doubleClicked().connect(this, &EventsDemo::showDoubleClicked);
  l->mouseWentOut().connect(this, &EventsDemo::showMouseWentOut);
  l->mouseWentOver().connect(this, &EventsDemo::showMouseWentOver);
  r->mouseMoved().connect(this, &EventsDemo::showMouseMoved);
  r->mouseWentUp().connect(this, &EventsDemo::showMouseWentUp);
  r->mouseWentDown().connect(this, &EventsDemo::showMouseWentDown);
  r->mouseWheel().connect(this, &EventsDemo::showMouseWheel);
  r->mouseWheel().preventDefaultAction(true);

  l->setAttributeValue
    ("oncontextmenu",
     "event.cancelBubble = true; event.returnValue = false; return false;");
  r->setAttributeValue
    ("oncontextmenu",
     "event.cancelBubble = true; event.returnValue = false; return false;");

  new WBreak(result);
  new WText("Last event: ", result);
  mouseEventType_ = new WText(result);
  new WBreak(result);
  mouseEventDescription_ = new WText(result);

  return result;
}