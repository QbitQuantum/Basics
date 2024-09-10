void ScoreAccessibility::updateAccessibilityInfo()
      {
      currentInfoChanged();
      ScoreView* w = static_cast<MuseScore*>(mainWindow)->currentScoreView();

      //getInspector->isAncestorOf is used so that inspector doesn't lose focus
      //when this method is called
      if ( (qApp->focusWidget() != w) && !mscore->getInspector()->isAncestorOf(qApp->focusWidget())) {
            w->setFocus();
            }
      QObject* obj = static_cast<QObject*>(w);
      QAccessibleValueChangeEvent ev(obj, w->score()->accessibleInfo());
      QAccessible::updateAccessibility(&ev);
      }