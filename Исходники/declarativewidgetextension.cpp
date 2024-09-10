    void dataAppend(QObject *object)
    {
      DefaultObjectContainer::dataAppend(object);

      QWidget *widget = qobject_cast<QWidget*>(object);
      if (widget) {

        // restore widget flags for dialogs, menus
        const QVariant originalWindowFlags = widget->property("originalWindowFlags");
        if (originalWindowFlags.isValid() && originalWindowFlags.canConvert<Qt::WindowFlags>()) {
          widget->setParent(widget->parentWidget(), originalWindowFlags.value<Qt::WindowFlags>());
        }

        m_widgetContainer->addWidget(widget);
        return;
      }

      QLayout *layout = qobject_cast<QLayout*>(object);
      if (layout) {
        m_widgetContainer->setLayout(layout);
        return;
      }

      QAction *action = qobject_cast<QAction*>(object);
      if (action) {
        m_widgetContainer->addAction(action);
        return;
      }

      DeclarativeActionItem *actionItem = qobject_cast<DeclarativeActionItem*>(object);
      if (actionItem) {
        m_widgetContainer->addAction(actionItem->action());
        return;
      }
    }