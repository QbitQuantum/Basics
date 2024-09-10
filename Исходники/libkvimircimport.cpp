void KviRemoteMircServerImportWizard::getListTerminated(bool bSuccess)
{
	if(!m_pRequest)return;
	if(bSuccess)
	{
		m_pOutput->setText(__tr2qs("File downloaded: processing ..."));
		m_pOutput->repaint();

		int iCount = m_pFilter->doImport(m_szTmpFileName);

		QString tmp;
		if(iCount > 0)
			tmp = __tr2qs("%1 servers imported successfully").arg(iCount);
		else
			tmp = __tr2qs("No servers imported");
		m_pOutput->setText(tmp);

		QDir d;
		d.remove(m_szTmpFileName);
	} else m_pOutput->setText(m_pRequest->lastError());

	delete m_pRequest;
	m_pRequest = 0;
	cancelButton()->setEnabled(false);
	finishButton()->setEnabled(true);
}