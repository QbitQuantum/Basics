	bool MainMenuWindow::handleChooseModule(MenuItem* it, ContentModule* module)
	{
		MenuBase* modulesMenu = getMenu("MainMenu/Modules/Menu");

		ItemEntry* itOld = NULL;
		for (size_t i=0; i<modulesMenu->getItemCount(); i++)
		{
			ItemEntry* curr = modulesMenu->getItemFromIndex(i);
			if (curr->getText().compare(mActiveModule->getName()+" *") == 0)
			{
				itOld = curr;
				break;
			}
		}
		itOld->setText(mActiveModule->getName());

		mActiveModule = module;
		it->setText(module->getName()+" *");

		return true;
	}