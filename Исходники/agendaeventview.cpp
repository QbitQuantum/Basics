/*!
	Queries user whether to delete whole series or just this single occurence
 */
void AgendaEventView::showDeleteOccurencePopup()
{
	OstTraceFunctionEntry0( AGENDAEVENTVIEW_SHOWDELETEOCCURENCEPOPUP_ENTRY );
	HbDialog *popUp = new HbDialog();
	// Set the parent for the dialog
	// Once the parent object is deleted the dialog will also be deleted
	popUp->setParent(this);
	popUp->setDismissPolicy(HbDialog::NoDismiss);
	popUp->setTimeout(HbDialog::NoTimeout);
	popUp->setAttribute( Qt::WA_DeleteOnClose, true );

	QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
	HbWidget *deleteWidget = new HbWidget(mViewer);
	deleteWidget->setLayout(layout);

	HbRadioButtonList *deleteButtonList = new HbRadioButtonList(mViewer);

	QStringList list;
	list << hbTrId("txt_calendar_info_this_occurrence_only") 
				<< hbTrId("txt_calendar_info_all_occurences");

	deleteButtonList->setItems(list);

	layout->addItem(deleteButtonList);

	popUp->setContentWidget(deleteWidget);
	popUp->setHeadingWidget(new HbLabel(
			hbTrId("txt_calendar_title_delete_repeated_entry")));

	connect(deleteButtonList, SIGNAL(itemSelected(int)), this,
											SLOT(handleDeleteOccurence(int)));
	connect(deleteButtonList, SIGNAL(itemSelected(int)), popUp, SLOT(close()));

	popUp->addAction(new HbAction(
			hbTrId("txt_common_button_cancel_singledialog")));

	// Show the popup
	popUp->open();

	OstTraceFunctionExit0( AGENDAEVENTVIEW_SHOWDELETEOCCURENCEPOPUP_EXIT );
}