void WInteractWidget::updateDom(DomElement& element, bool all)
{
  bool updateKeyDown = false;

  WApplication *app = WApplication::instance();

  /*
   * -- combine enterPress, escapePress and keyDown signals
   */
  EventSignal<> *enterPress = voidEventSignal(ENTER_PRESS_SIGNAL, false);
  EventSignal<> *escapePress = voidEventSignal(ESCAPE_PRESS_SIGNAL, false);
  EventSignal<WKeyEvent> *keyDown = keyEventSignal(KEYDOWN_SIGNAL, false);

  updateKeyDown = (enterPress && enterPress->needsUpdate(all))
    || (escapePress && escapePress->needsUpdate(all))
    || (keyDown && keyDown->needsUpdate(all));

  if (updateKeyDown) {
    std::vector<DomElement::EventAction> actions;

    if (enterPress) {
      if (enterPress->needsUpdate(true)) {
	/*
	 * prevent enterPressed from triggering a changed event on all
	 * browsers except for Opera and IE
	 */
	std::string extraJS;

	const WEnvironment& env = app->environment();

	if (dynamic_cast<WFormWidget *>(this)
	    && !env.agentIsOpera() && !env.agentIsIE())
	  extraJS = "var g=this.onchange;"
	    ""      "this.onchange=function(){this.onchange=g;};";

	actions.push_back
	  (DomElement::EventAction("e.keyCode && (e.keyCode == 13)",
				   enterPress->javaScript() + extraJS,
				   enterPress->encodeCmd(),
				   enterPress->isExposedSignal()));
      }
      enterPress->updateOk();
    }

    if (escapePress) {
      if (escapePress->needsUpdate(true)) {
	actions.push_back
	  (DomElement::EventAction("e.keyCode && (e.keyCode == 27)",
				   escapePress->javaScript(),
				   escapePress->encodeCmd(),
				   escapePress->isExposedSignal()));
      }
      escapePress->updateOk();
    }

    if (keyDown) {
      if (keyDown->needsUpdate(true)) {
	actions.push_back
	  (DomElement::EventAction(std::string(),
				   keyDown->javaScript(),
				   keyDown->encodeCmd(),
				   keyDown->isExposedSignal()));
      }
      keyDown->updateOk();
    }

    if (!actions.empty())
      element.setEvent("keydown", actions);
    else if (!all)
      element.setEvent("keydown", std::string(), std::string());
  }

  /*
   * -- allow computation of dragged mouse distance
   */
  EventSignal<WMouseEvent> *mouseDown
    = mouseEventSignal(MOUSE_DOWN_SIGNAL, false);
  EventSignal<WMouseEvent> *mouseUp
    = mouseEventSignal(MOUSE_UP_SIGNAL, false);
  EventSignal<WMouseEvent> *mouseMove
    = mouseEventSignal(MOUSE_MOVE_SIGNAL, false);
  EventSignal<WMouseEvent> *mouseDrag
    = mouseEventSignal(MOUSE_DRAG_SIGNAL, false);

  bool updateMouseMove
    = (mouseMove && mouseMove->needsUpdate(all))
    || (mouseDrag && mouseDrag->needsUpdate(all));

  bool updateMouseDown
    = (mouseDown && mouseDown->needsUpdate(all))
    || updateMouseMove;

  bool updateMouseUp
    = (mouseUp && mouseUp->needsUpdate(all))
    || updateMouseMove;

  std::string CheckDisabled = "if($(o).hasClass('" +
    app->theme()->disabledClass() +
    "')){" WT_CLASS ".cancelEvent(e);return;}";

  if (updateMouseDown) {
    /*
     * when we have a mouseUp event, we also need a mouseDown event
     * to be able to compute dragDX/Y.
     *
     * When we have:
     *  - a mouseDrag
     *  - or a mouseDown + (mouseMove or mouseUp),
     * we need to capture everything after on mouse down, and keep track of the
     * down button if we have a mouseMove or mouseDrag
     */
    WStringStream js;

    js << CheckDisabled;

    if (mouseUp && mouseUp->isConnected())
      js << app->javaScriptClass() << "._p_.saveDownPos(event);";

    if ((mouseDrag && mouseDrag->isConnected())
	|| (mouseDown && mouseDown->isConnected()
	    && ((mouseUp && mouseUp->isConnected())
		|| (mouseMove && mouseMove->isConnected()))))
      js << WT_CLASS ".capture(this);";

    if ((mouseMove && mouseMove->isConnected())
	|| (mouseDrag && mouseDrag->isConnected()))
      js << WT_CLASS ".mouseDown(e);";

    if (mouseDown) {
      js << mouseDown->javaScript();
      element.setEvent("mousedown", js.str(),
		       mouseDown->encodeCmd(), mouseDown->isExposedSignal());
      mouseDown->updateOk();
    } else
      element.setEvent("mousedown", js.str(), std::string(), false);
  }

  if (updateMouseUp) {
    WStringStream js;

    /*
     * when we have a mouseMove or mouseDrag event, we need to keep track
     * of unpressing the button.
     */
    js << CheckDisabled;

    if ((mouseMove && mouseMove->isConnected())
	|| (mouseDrag && mouseDrag->isConnected()))
      js << WT_CLASS ".mouseUp(e);";
      
    if (mouseUp) {
      js << mouseUp->javaScript();
      element.setEvent("mouseup", js.str(),
		       mouseUp->encodeCmd(), mouseUp->isExposedSignal());
      mouseUp->updateOk();
    } else
      element.setEvent("mouseup", js.str(), std::string(), false);
  }

  if (updateMouseMove) {
    /*
     * We need to mix mouseDrag and mouseMove events.
     */
    std::vector<DomElement::EventAction> actions;
    
    if (mouseMove) {
      actions.push_back
	(DomElement::EventAction(std::string(),
				 mouseMove->javaScript(),
				 mouseMove->encodeCmd(),
				 mouseMove->isExposedSignal()));
      mouseMove->updateOk();
    }

    if (mouseDrag) {
      actions.push_back
	(DomElement::EventAction(WT_CLASS ".buttons",
				 mouseDrag->javaScript()
				 + WT_CLASS ".drag(e);",
				 mouseDrag->encodeCmd(),
				 mouseDrag->isExposedSignal()));
      mouseDrag->updateOk();
    }

    element.setEvent("mousemove", actions);
  }

  /*
   * -- mix mouseClick and mouseDblClick events in mouseclick since we
   *    only want to fire one of both
   */
  EventSignal<WMouseEvent> *mouseClick
    = mouseEventSignal(M_CLICK_SIGNAL, false);
  EventSignal<WMouseEvent> *mouseDblClick
    = mouseEventSignal(DBL_CLICK_SIGNAL, false);  

  bool updateMouseClick
    = (mouseClick && mouseClick->needsUpdate(all))
    || (mouseDblClick && mouseDblClick->needsUpdate(all));

  if (updateMouseClick) {
    WStringStream js;

    js << CheckDisabled;

    if (mouseDrag)
      js << "if (" WT_CLASS ".dragged()) return;";

    if (mouseDblClick && mouseDblClick->needsUpdate(all)) {
      /*
       * Click: if timer is running:
       *  - clear timer, dblClick()
       *  - start timer, clear timer and click()
       */

      /* We have to prevent this immediately ! */
      if (mouseClick) {
	if (mouseClick->defaultActionPrevented() ||
	    mouseClick->propagationPrevented()) {
	  js << WT_CLASS ".cancelEvent(e";
	  if (mouseClick->defaultActionPrevented() &&
	      mouseClick->propagationPrevented())
	    js << ");";
	  else if (mouseClick->defaultActionPrevented())
	    js << ",0x2);";
	  else
	    js << ",0x1);";
	}
      }

      js << "if(" WT_CLASS ".isDblClick(o, e)) {"
	 << mouseDblClick->javaScript();

      if (mouseDblClick->isExposedSignal())
	js << app->javaScriptClass()
		 << "._p_.update(o,'" << mouseDblClick->encodeCmd()
		 << "',e,true);";

      mouseDblClick->updateOk();

      js <<
	"}else{"
	"""if (" WT_CLASS ".isIElt9 && document.createEventObject) "
	""  "e = document.createEventObject(e);"
	"""o.wtE1 = e;"
	"""o.wtClickTimeout = setTimeout(function() {"
	""   "o.wtClickTimeout = null; o.wtE1 = null;";

      if (mouseClick) {
	js << mouseClick->javaScript();

	if (mouseClick->isExposedSignal()) {
	  js << app->javaScriptClass()
		   << "._p_.update(o,'" << mouseClick->encodeCmd()
		   << "',e,true);";
	}

	mouseClick->updateOk();
      }

      const Configuration& conf = app->environment().server()->configuration();
      js << "}," << conf.doubleClickTimeout() << ");}";
    } else {
      if (mouseClick && mouseClick->needsUpdate(all)) {
	js << mouseClick->javaScript();

	if (mouseClick->isExposedSignal()) {
	  js << app->javaScriptClass()
	     << "._p_.update(o,'" << mouseClick->encodeCmd()
	     << "',e,true);";
	}

	mouseClick->updateOk();
      }
    }

    element.setEvent(CLICK_SIGNAL, js.str(),
		     mouseClick ? mouseClick->encodeCmd() : "");

    if (mouseDblClick) {
      if (app->environment().agentIsIElt(9))
	element.setEvent("dblclick", "this.onclick()");
    }
  }

  /*
   * -- mouseOver with delay
   */
  EventSignal<WMouseEvent> *mouseOver
    = mouseEventSignal(MOUSE_OVER_SIGNAL, false);
  EventSignal<WMouseEvent> *mouseOut
    = mouseEventSignal(MOUSE_OUT_SIGNAL, false); 

  bool updateMouseOver = mouseOver && mouseOver->needsUpdate(all);

  if (mouseOverDelay_) {
    if (updateMouseOver) {
      WStringStream js;
      js << "o.over=setTimeout(function() {"
	 << "o.over = null;"
	 << mouseOver->javaScript();

      if (mouseOver->isExposedSignal()) {
	js << app->javaScriptClass()
	   << "._p_.update(o,'" << mouseOver->encodeCmd() << "',e,true);";
      }

      js << "}," << mouseOverDelay_ << ");";

      element.setEvent("mouseover", js.str(), "");

      mouseOver->updateOk();

      if (!mouseOut)
	mouseOut = mouseEventSignal(MOUSE_OUT_SIGNAL, true);

      element.setEvent("mouseout",
		       "clearTimeout(o.over); o.over=null;"
		       + mouseOut->javaScript(),
		       mouseOut->encodeCmd(), mouseOut->isExposedSignal());
      mouseOut->updateOk();
    }
  } else {
    if (updateMouseOver) {
      element.setEventSignal("mouseover", *mouseOver);
      mouseOver->updateOk();
    }

    bool updateMouseOut = mouseOut && mouseOut->needsUpdate(all);

    if (updateMouseOut) {
      element.setEventSignal("mouseout", *mouseOut);
      mouseOut->updateOk();
    }
  }

  updateEventSignals(element, all);

  WWebWidget::updateDom(element, all);
}