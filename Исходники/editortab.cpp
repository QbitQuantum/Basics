void EditorTab::EnableAllSerialPorts(bool enable)
{
	QString currentPort = "None";
	if (workspace.GetCurrentProject() != NULL) {
		currentPort = workspace.GetCurrentProject()->serialPort;
	}
	for (int i=0; i < count(); i++) {
		if (tabType(i) == MM::serialTab) {		
			SerialMonitor * serial = (SerialMonitor *)widget(i);
			if (enable) {
				serial->OpenPort();
				if (serial->GetPort() == currentPort) {
					setCurrentIndex(i);
				}
			} else {
				serial->ClosePort();				
			}
		}
	}
}