/*!
	Creates the custom widget.
 */
HbWidget* CalenEditorCustomItem::createCustomWidget()
{
	OstTraceFunctionEntry0( CALENEDITORCUSTOMITEM_CREATECUSTOMWIDGET_ENTRY );
	HbDataFormModelItem::DataItemType itemType =
			static_cast<HbDataFormModelItem::DataItemType> (modelIndex() .data(
					HbDataFormModelItem::ItemTypeRole).toInt());

	switch (itemType) {
		case CustomWidgetFrom:
		{
			// Set the property so that the custom item layout
			// will be the same for both portrait and landscape
			setProperty("expandItem", true);
			// Create the widget
			HbWidget *widgetTop = new HbWidget();
			QGraphicsLinearLayout *layoutTop =
								new QGraphicsLinearLayout(Qt::Horizontal);
			layoutTop->setContentsMargins(0, 0, 0, 0);

			widgetTop->setLayout(layoutTop);

			// Set the button spacing.
			HbDeviceProfile deviceProfile;
			// The layout guide specifies the spacing as 2 u.
			qreal spacing = deviceProfile.unitValue() * 2 ;
			layoutTop->setSpacing(spacing);
			// Calculate the button width.
			qreal right = 0.0;
			qreal left = 0.0;
			style()->parameter("hb-param-margin-gene-right", right);
			style()->parameter("hb-param-margin-gene-left", left);
			qreal screenWidth = 0.0;
			style()->parameter("hb-param-screen-short-edge", screenWidth);
			qreal buttonWidth = (screenWidth - right - left - spacing) / 2;

			mPushButtonTime = new HbPushButton();
			mPushButtonTime->setPreferredWidth(buttonWidth);
			mPushButtonTime->setObjectName("startTime");
			connect(mPushButtonTime, SIGNAL(clicked()),
													this, SLOT(handleTime()));
			layoutTop->addItem(mPushButtonTime);

			mPushButtonDate = new HbPushButton();
			mPushButtonDate->setPreferredWidth(buttonWidth);
			mPushButtonDate->setObjectName("startDate");
			connect(mPushButtonDate, SIGNAL(clicked()),
													this, SLOT(handleDate()));
			layoutTop->addItem(mPushButtonDate);
			OstTraceFunctionExit0( CALENEDITORCUSTOMITEM_CREATECUSTOMWIDGET_EXIT );
			return widgetTop;
		}


		case CustomWidgetTo:
		{
			// Set the property so that the custom item layout
			// will be the same for both portrait and landscape
			setProperty("expandItem", true);
			// Create the widget
			HbWidget *widgetBottom = new HbWidget();
			
			QGraphicsLinearLayout *layoutBottom = 
					new QGraphicsLinearLayout(Qt::Horizontal);
			layoutBottom->setContentsMargins(0, 0, 0, 0);
			widgetBottom->setLayout(layoutBottom);

			// Set the button spacing.
			HbDeviceProfile deviceProfile;
			// The layout guide specifies the spacing as 2 u.
			qreal spacing = deviceProfile.unitValue() * 2 ;
			layoutBottom->setSpacing(spacing);
			// Calculate the button width.
			qreal right = 0.0;
			qreal left = 0.0;
			style()->parameter("hb-param-margin-gene-right", right);
			style()->parameter("hb-param-margin-gene-left", left);
			qreal screenWidth = 0.0;
			style()->parameter("hb-param-screen-short-edge", screenWidth);
			qreal buttonWidth = (screenWidth - right - left - spacing) / 2;

			mPushButtonTime = new HbPushButton(this);
			mPushButtonTime->setPreferredWidth(buttonWidth);
			mPushButtonTime->setObjectName("endTime");
			connect(mPushButtonTime, SIGNAL(clicked()),
													this, SLOT(handleTime()));
			layoutBottom->addItem(mPushButtonTime);

			mPushButtonDate = new HbPushButton(this);
			mPushButtonDate->setPreferredWidth(buttonWidth);
			mPushButtonDate->setObjectName("endDate");
			connect(mPushButtonDate, SIGNAL(clicked()),
													this, SLOT(handleDate()));
			layoutBottom->addItem(mPushButtonDate);
			OstTraceFunctionExit0( DUP1_CALENEDITORCUSTOMITEM_CREATECUSTOMWIDGET_EXIT );
			return widgetBottom;
		}
				
		case CustomWidgetLocation:
		{
			setProperty("expandItem", false);
			HbWidget *widgetLocation = new HbWidget();
			QGraphicsLinearLayout *layoutLocation = 
										new QGraphicsLinearLayout(Qt::Horizontal);
			layoutLocation->setContentsMargins(0, 0, 0, 0);
			widgetLocation->setLayout(layoutLocation);
			
			// Set the spacing between LineEdit and PushButton
			qreal spacing = 0.0;
			style()->parameter(
							"hb-param-margin-gene-middle-horizontal", spacing);
			layoutLocation->setSpacing(spacing);
			
			mLocationLineEdit = new HbLineEdit(this);
			mLocationLineEdit->setObjectName("locationLineEdit");
			mLocationLineEdit->setMaxRows(MaxRowsInTextItem);
			connect(mLocationLineEdit, SIGNAL(textChanged(const QString)),
						this, SLOT(handleLocationTextChange(const QString)));
			connect(mLocationLineEdit, SIGNAL(editingFinished()),
						this, SLOT(handleEditingFinished()));
			layoutLocation->addItem(mLocationLineEdit);
			
			mLocationPushButton = new HbPushButton(this);
			
			HbDeviceProfile deviceProfile;
			// The layout guide specifies the spacing as 9.5 u 
			// and the height as 7.4 u
			qreal width = deviceProfile.unitValue() * 9.5;
			qreal height = deviceProfile.unitValue() * 7.4 ;
			mLocationPushButton->setPreferredSize(width, height);
			mLocationPushButton->setSizePolicy(
										QSizePolicy::Fixed, QSizePolicy::Fixed);
			mLocationPushButton->setIcon( HbIcon("qtg_mono_location"));
			mLocationPushButton->setObjectName("locationIcon");
			connect(mLocationPushButton, SIGNAL(clicked()), this, 
												SLOT(launchLocationPicker()));
			layoutLocation->addItem(mLocationPushButton);
			OstTraceFunctionExit0( DUP2_CALENEDITORCUSTOMITEM_CREATECUSTOMWIDGET_EXIT );
			return widgetLocation;
		}
		
		case RepeatUntilOffset:
		{
			setProperty("expandItem", false);
			mRepeatUntilWidget = new HbPushButton(this);
			mRepeatUntilWidget->setObjectName("repeatUntilItem");
			OstTraceFunctionExit0( DUP3_CALENEDITORCUSTOMITEM_CREATECUSTOMWIDGET_EXIT );
			return mRepeatUntilWidget;
		}
				
		case ReminderTimeOffset:
		{
			setProperty("expandItem", false);
			mReminderTimeWidget = new HbPushButton(this);
			mReminderTimeWidget->setObjectName("remainderTimeItem");
			OstTraceFunctionExit0( DUP4_CALENEDITORCUSTOMITEM_CREATECUSTOMWIDGET_EXIT );
			return mReminderTimeWidget;
		}
		
		default:
			return 0;
	}
}