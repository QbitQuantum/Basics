FlowControlDlg::FlowControlDlg(Target* tar)
	: QDialog(0)
	, m_curTarget(tar)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(RefreshPolicy()));

	DWORD preValue = DM->QueryTargetPluginStatus(m_curTarget->dwTargetID);

	ui.chkPlg1->setChecked(PLUGIN_ENABLE_1 & preValue);
	ui.chkPlg2->setChecked(PLUGIN_ENABLE_2 & preValue);
	ui.chkPlg4->setChecked(PLUGIN_ENABLE_4 & preValue);
}