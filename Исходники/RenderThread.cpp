	bool RenderThread::update()
	{
		/*
		- Tant qu'il n'y a pas de command
		-> je pop des task
		- Une fois que j'ai mes commandes
		-> pour chacunes d'elles
		-> je regarde si c'est a moi de les traiter (ex : changement de scene)
		-> si ca n'est pas a moi de les traiter
		-> je les passe au render context actif
		-> si il n'y a pas de render context actif, c'est que j'ai fait une erreur, et j'assert dans ta face :D
		*/

		_registerId();

		_run = true;
		_insideRun = true;
		DWORD threadId = GetThreadId(static_cast<HANDLE>(_threadHandle.native_handle()));
		SetThreadName(threadId, this->_name.c_str());

		TMQ::MessageBase *task = nullptr;

		while (_run && _insideRun)
		{
			SCOPE_profile_cpu_i("RenderTimer", "Update");

			if (TMQ::TaskManager::RenderThreadGetTask(task))
			{
				SCOPE_profile_cpu_i("RenderTimer", "Execute task");
				auto success = execute(task); // we receive a task that we cannot treat
				AGE_ASSERT(success);
			}
		}
		return true;
	}