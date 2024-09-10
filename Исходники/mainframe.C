	bool Mainframe::eventFilter(QObject* sender, QEvent* event) 
	{
		if (event->type() != QEvent::KeyPress) return false;

		QKeyEvent* e = dynamic_cast<QKeyEvent*>(event);

		if (e->key() == Qt::Key_Escape &&
				HelpViewer::getInstance("BALLView Docu")->isWhatsThisEnabled())
		{
			HelpViewer::getInstance("BALLView Docu")->exitWhatsThisMode();
		}

		QPoint point = QCursor::pos();
		QWidget* widget = qApp->widgetAt(point);
		if (widget == scene_ &&
 				qApp->focusWidget() != scene_)
		{
 			scene_->keyPressEvent(e);
			return true;
		}

 		if (e->key() == Qt::Key_Delete &&
                RTTI::isKindOf<QTreeWidget>(sender))
 		{
 			deleteClicked();
			return true;
 		}

		if (e->key() == Qt::Key_Enter) 
		{
			if (composite_manager_.getNumberOfComposites() == 0) return false;

			if (getMolecularControlSelection().size() == 0)
			{
				control_selection_.push_back(*composite_manager_.begin());
			}
				
			MolecularStructure::getInstance(0)->centerCamera();
			return true;
		}

		// check all menu entries if Alt or CTRL is pressed to enable shortcuts
		if (e->key() == Qt::Key_Alt ||
				e->key() == Qt::Key_Control)				
		{
			checkMenus();
			return false;
		}

		#ifdef BALL_PYTHON_SUPPORT
 			PyWidget::getInstance(0)->reactTo(*e);
			e->accept();
		#endif

		return false;
	}