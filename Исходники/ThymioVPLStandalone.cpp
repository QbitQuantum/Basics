	//! A new node has connected to the network.
	void ThymioVPLStandalone::nodeConnected(unsigned node)
	{
		// only allow a single node connected at a given time
		if (vpl)
		{
			QMessageBox::critical(
				this,
				tr("Thymio VPL Error"),
				tr("This application only supports a single robot at a time.")
			);
			close();
			return;
		}
			
		// save node information
		id = node;
		
		// create the VPL widget and add it
		vpl = new ThymioVisualProgramming(new ThymioVPLStandaloneInterface(this), false, debugLog, execFeedback);
		vplLayout->addWidget(vpl);
		
		// connect callbacks
		connect(vpl, SIGNAL(modifiedStatusChanged(bool)), SLOT(updateWindowTitle(bool)));
		connect(vpl, SIGNAL(compilationOutcome(bool)), editor, SLOT(setEnabled(bool)));
		
		// reload data
		if (!savedContent.isNull())
			vpl->loadFromDom(savedContent, false);
		
		// reset sizes
		resetSizes();
		
		// do a first compilation
		editorContentChanged();
		
		// read variables once to get PID
		target->getVariables(id, 0, allocatedVariablesCount);
		
		// stop timer if any
		if (getDescriptionTimer)
		{
			killTimer(getDescriptionTimer);
			getDescriptionTimer = 0;
		}
	}