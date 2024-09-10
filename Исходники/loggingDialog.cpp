BOOST_FOREACH( std::list< qt4::QMessage>::const_reference message, messageList ) {
		QListWidgetItem *item = new QListWidgetItem();
		std::stringstream logStream;
		logStream << message.m_module << "(" << message.time_str << ") -> " << message.message ;
		item->setText( logStream.str().c_str() );

		switch ( message.m_level ) {
		case error:

			if( m_Interface.errorCheck->checkState() == Qt::Checked ) {
				item->setTextColor( Qt::red );
				m_Interface.logList->addItem( item );
			}

			break;
		case warning:

			if( m_Interface.warningCheck->checkState() == Qt::Checked ) {
				item->setTextColor( QColor( 218, 165, 32 ) );
				m_Interface.logList->addItem( item );
			}

			break;
		case info:

			if( m_Interface.infoCheck->checkState() == Qt::Checked ) {
				item->setTextColor( Qt::darkBlue );
				m_Interface.logList->addItem( item );
			}

			break;
		case verbose_info:

			if( m_Interface.verboseCheck->checkState() == Qt::Checked ) {
				item->setTextColor( Qt::black );
				m_Interface.logList->addItem( item );
			}

			break;
		case notice:

			if( m_Interface.noticeCheck->checkState() == Qt::Checked ) {
				item->setTextColor( QColor( 34, 139, 34 ) );
				m_Interface.logList->addItem( item );
			}

			break;
		}

	}