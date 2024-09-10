	bool TaskSchedulerImpl::Initialize(std::size_t workerCount)
	{
		if (IsInitialized())
			return true; // Déjà initialisé

		#if NAZARA_CORE_SAFE
		if (workerCount == 0)
		{
			NazaraError("Invalid worker count ! (0)");
			return false;
		}
		#endif

		s_workerCount = workerCount;
		s_doneEvents.reset(new HANDLE[workerCount]);
		s_workers.reset(new Worker[workerCount]);
		s_workerThreads.reset(new HANDLE[workerCount]);

		// L'identifiant de chaque worker doit rester en vie jusqu'à ce que chaque thread soit correctement lancé
		std::unique_ptr<std::size_t[]> workerIDs(new std::size_t[workerCount]);

		for (std::size_t i = 0; i < workerCount; ++i)
		{
			// On initialise les évènements, mutex et threads de chaque worker
			Worker& worker = s_workers[i];
			InitializeCriticalSection(&worker.queueMutex);
			worker.wakeEvent = CreateEventW(nullptr, false, false, nullptr);
			worker.running = true;
			worker.workCount = 0;

			s_doneEvents[i] = CreateEventW(nullptr, true, false, nullptr);

			// Le thread va se lancer, signaler qu'il est prêt à travailler (s_doneEvents) et attendre d'être réveillé
			workerIDs[i] = i;
			s_workerThreads[i] = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, &WorkerProc, &workerIDs[i], 0, nullptr));
		}

		// On attend que les workers se mettent en attente
		WaitForMultipleObjects(s_workerCount, &s_doneEvents[0], true, INFINITE);

		return true;
	}