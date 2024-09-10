bool CTask::OnThreadDone()
{
	// Когда поток послал сообщение что он завершил работу
	// мы ждём когда его хендл просигнализирует
	WaitForSingleObject(m_pThread->GetHandle(), INFINITE);

	// и удалим класс, отвечающий за работу с потоком (CThread)
	delete m_pThread;
	m_pThread = NULL;

	// Установим состояние задачи в "бездействие"
	m_bState = TASK_STATE_NONE;

	// Скажем главному окну что задача завершена
	SendMessage(MainWindow, RegisterWindowMessage(TaskDoneMessage), (WPARAM) this, NULL);

	// Запишем в лог что задача завершена
	if (m_bAborted)
		Log->WriteLogLine(TEXT("[%s] Выполнение задачи прервано"), TEXT("i"), m_TaskInfo.sName);
	else
		Log->WriteLogLine(TEXT("[%s] Выполнение задачи завершено"), TEXT("i"), m_TaskInfo.sName);

	// Покажем окно с информацией о прогрессе
	if (Settings->bShowProgress)
	{
		m_hProgressWnd->Show();
		SetForegroundWindow(GetLastActivePopup(MainWindow));
	}

	return true;
}