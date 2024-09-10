void PolycodeIDEApp::handleEvent(Event *event) {
	if(event->getDispatcher() == core) {
		switch(event->getEventCode()) {
			case Core::EVENT_CORE_RESIZE:
				frame->Resize(core->getXRes(), core->getYRes());
			break;
		}
	}
	
	if(event->getDispatcher()  == frame->getProjectBrowser()) {
		
		if(event->getEventType() == "PolycodeProjectBrowserEvent") {
			switch(event->getEventCode()) {
				case PolycodeProjectBrowserEvent::SHOW_MENU:
					dispatchEvent(new Event(), EVENT_SHOW_MENU);
				break;
			}
		}
		
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			BrowserUserData *selectedData = frame->getProjectBrowser()->getSelectedData();
						
			if(selectedData->type == 3) {
				projectManager->activeFolder = selectedData->parentProject->getRootFolder();
				projectManager->selectedFile = "";				
			} else if(selectedData->type == 0) {
				projectManager->activeFolder = "";
				projectManager->selectedFile = "";
			} else {
				projectManager->selectedFileEntry = selectedData->fileEntry;
				projectManager->selectedFile = selectedData->fileEntry.fullPath;
				if(selectedData->fileEntry.type == OSFileEntry::TYPE_FILE) {
					projectManager->activeFolder = selectedData->fileEntry.basePath;
				} else {
					projectManager->activeFolder = selectedData->fileEntry.fullPath;
				}			
			}
			
			projectManager->setActiveProject(selectedData->parentProject);
			
			if(selectedData->type == 0)
				return;			
			
			if(selectedData) {
			PolycodeEditor *editor;
			editor = editorManager->getEditorForPath(selectedData->fileEntry.fullPath);
			if(editor) {
				frame->showEditor(editor);				
			} else {
				editor = editorManager->createEditorForExtension(selectedData->fileEntry.extension);
				if(editor) {
					if(editor->openFile(selectedData->fileEntry.fullPath)) {
						frame->addEditor(editor);					
						frame->showEditor(editor);
					} else {
						delete editor;
						editor = NULL;
					}
				}
			}
				
				if(editor) {
					editorManager->setCurrentEditor(editor);
				}
				
			}
		}
	}
	
	if(event->getDispatcher() == frame->playButton) {	
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
			runProject();
		}
	}
	
	if(event->getDispatcher() == frame->textInputPopup) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			core->moveDiskItem(projectManager->selectedFileEntry.fullPath, projectManager->selectedFileEntry.basePath + "/" + frame->textInputPopup->getValue());			
			if(projectManager->getActiveProject()) {
				frame->getProjectBrowser()->refreshProject(projectManager->getActiveProject());
			}
			
			PolycodeEditor *editor = editorManager->getEditorForPath(projectManager->selectedFileEntry.fullPath);
			if(editor) {
				editor->setFilePath(projectManager->selectedFileEntry.basePath + "/" + frame->textInputPopup->getValue());
			}
			
			projectManager->selectedFileEntry.fullPath = projectManager->selectedFileEntry.basePath + "/" + frame->textInputPopup->getValue();
			projectManager->selectedFileEntry.name = frame->textInputPopup->getValue();
			
			
			frame->hideModal();			
		}
	}	
	
	if(event->getDispatcher() == frame->newProjectWindow) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			projectManager->createNewProject(frame->newProjectWindow->getTemplateFolder(), frame->newProjectWindow->getProjectName(), frame->newProjectWindow->getProjectLocation());
			frame->hideModal();			
		}
	}

	if(event->getDispatcher() == frame->newFileWindow) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			projectManager->createNewFile(frame->newFileWindow->getTemplatePath(), frame->newFileWindow->getFileName());
			frame->hideModal();			
			
			if(projectManager->getActiveProject()) {
				frame->projectBrowser->refreshProject(projectManager->getActiveProject());
			}			
		}
	}
	
	if(event->getDispatcher() == frame->exampleBrowserWindow) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			String fullPath = String(core->getDefaultWorkingDirectory()+"/"+frame->exampleBrowserWindow->getExamplePath());
			projectManager->openProject(fullPath);
			frame->hideModal();			
		}
	}	
}