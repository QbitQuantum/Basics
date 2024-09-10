void WAbstractToggleButton::updateDom(DomElement& element, bool all)
{
  WApplication *app = WApplication::instance();
  const WEnvironment& env = app->environment();

  DomElement *input = 0;
  DomElement *span = 0;
  DomElement *label = 0;

  // Already apply theme here because it may determine its organization
  if (all)
    app->theme()->apply(this, element, 1);

  if (element.type() == DomElement_INPUT)
    input = &element;
  else {
    if (all) {
      input = DomElement::createNew(DomElement_INPUT);
      input->setName("in" + id());

      span = DomElement::createNew(DomElement_SPAN);
      span->setName("t" + id());
 
      if (element.type() != DomElement_LABEL) {
	label = DomElement::createNew(DomElement_LABEL);
	label->setName("l" + id());
      }
    } else {
      input = DomElement::getForUpdate("in" + id(), DomElement_INPUT);
      span = DomElement::getForUpdate("t" + id(), DomElement_SPAN);
    }
  }

  if (all)
    updateInput(*input, all);

  EventSignal<> *check = voidEventSignal(CHECKED_SIGNAL, false);
  EventSignal<> *uncheck = voidEventSignal(UNCHECKED_SIGNAL, false);
  EventSignal<> *change = voidEventSignal(CHANGE_SIGNAL, false);
  EventSignal<WMouseEvent> *click = mouseEventSignal(M_CLICK_SIGNAL, false);

  /*
   * We piggy-back the checked and uncheck signals on the change signal.
   *
   * If agent is IE, then we piggy-back the change on the clicked signal.
   */
  bool piggyBackChangeOnClick = env.agentIsIE();

  bool needUpdateChangeSignal =
    (change && change->needsUpdate(all))
    || (check && check->needsUpdate(all))
    || (uncheck && uncheck->needsUpdate(all));

  bool needUpdateClickedSignal =
    (click && click->needsUpdate(all))
     || (piggyBackChangeOnClick && needUpdateChangeSignal);

  WFormWidget::updateDom(*input, all);

  /*
   * Copy all properties to the exterior element, as they relate to style,
   * etc... We ignore here attributes (except for tooltip),
   * see WWebWidget: other attributes need not be moved.
   *
   * But -- bug #423, disabled and readonly are properties that should be
   * kept on the interior element.
   */
  if (&element != input) {
    if (element.properties().find(PropertyClass) != element.properties().end())
      input->addPropertyWord(PropertyClass, element.getProperty(PropertyClass));
    element.setProperties(input->properties());
    input->clearProperties();

    std::string v = element.getProperty(Wt::PropertyDisabled);
    if (!v.empty()) {
      input->setProperty(Wt::PropertyDisabled, v);
      element.removeProperty(Wt::PropertyDisabled);
    }

    v = element.getProperty(Wt::PropertyReadOnly);
    if (!v.empty()) {
      input->setProperty(Wt::PropertyReadOnly, v);
      element.removeProperty(Wt::PropertyReadOnly);
    }

    v = input->getAttribute("title");
    if (!v.empty())
      element.setAttribute("title", v);
  }

  if (flags_.test(BIT_STATE_CHANGED) || all) {
    input->setProperty(Wt::PropertyChecked,
		       state_ == Unchecked ? "false" : "true");

    if (supportsIndeterminate(env))
      input->setProperty(Wt::PropertyIndeterminate,
			 state_ == PartiallyChecked ? "true" : "false");
    else
      input->setProperty(Wt::PropertyStyleOpacity,
			 state_ == PartiallyChecked ? "0.5" : "");

	flags_.reset(BIT_STATE_CHANGED);
  }

  std::vector<DomElement::EventAction> changeActions;

  if (needUpdateChangeSignal
      || (piggyBackChangeOnClick && needUpdateClickedSignal)
      || all) {
    std::string dom = "o";

    if (check) {
      if (check->isConnected())
	changeActions.push_back
	  (DomElement::EventAction(dom + ".checked",
				   check->javaScript(),
				   check->encodeCmd(),
				   check->isExposedSignal()));
      check->updateOk();
    }

    if (uncheck) {
      if (uncheck->isConnected())
	changeActions.push_back
	  (DomElement::EventAction("!" + dom + ".checked",
				   uncheck->javaScript(),
				   uncheck->encodeCmd(),
				   uncheck->isExposedSignal()));
      uncheck->updateOk();
    }

    if (change) {
      if (change->isConnected())
	changeActions.push_back
	  (DomElement::EventAction(std::string(),
				   change->javaScript(),
				   change->encodeCmd(),
				   change->isExposedSignal()));
      change->updateOk();
    }

    if (!piggyBackChangeOnClick) {
      if (!(all && changeActions.empty()))
	input->setEvent("change", changeActions);
    }
  }

  if (needUpdateClickedSignal || all) {
    if (piggyBackChangeOnClick) {
      if (click) {
	changeActions.push_back
	  (DomElement::EventAction(std::string(),
				   click->javaScript(),
				   click->encodeCmd(),
				   click->isExposedSignal()));
	click->updateOk();
      }

      if (!(all && changeActions.empty()))
	input->setEvent(CLICK_SIGNAL, changeActions);
    } else
      if (click)
	updateSignalConnection(*input, *click, CLICK_SIGNAL, all);
  }

  if (span) {
    if (all || flags_.test(BIT_TEXT_CHANGED)) {
      span->setProperty(PropertyInnerHTML, text_.formattedText());
	  if(all || flags_.test(BIT_WORD_WRAP_CHANGED)) {
		span->setProperty(PropertyStyleWhiteSpace, flags_.test(BIT_WORD_WRAP) ? "normal" : "nowrap");
		flags_.reset(BIT_WORD_WRAP_CHANGED);
	  }
	  flags_.reset(BIT_TEXT_CHANGED);
    }
  }

  if (&element != input) {
    if (label) {
      label->addChild(input);
      label->addChild(span);
      element.addChild(label);
    } else {
      element.addChild(input);
      element.addChild(span);
    }
  }
}