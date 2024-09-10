		/**
		 * Add a newly connected remote client.
		 * 
		 * When a {@link ClientDriver remote client} connects to this *server* {@link ExternalClientArray} object, 
		 * then this {@link ExternalClientArray} creates a child {@link ExternalSystem external client} object through 
		 * the {@link createExternalClient createExternalClient()} method and {@link insert inserts} it.
		 * 
		 * @param driver A communicator for external client.
		 */
		virtual void addClient(std::shared_ptr<protocol::ClientDriver> driver) override final
		{
			std::shared_ptr<ExternalSystem> system(createExternalClient(driver));
			if (system == nullptr)
				return;

			system->communicator_ = driver;
			{
				library::UniqueWriteLock uk(getMutex());
				push_back(system);
			}
			driver->listen(system.get());

			for (size_t i = 0; i < size(); i++)
				if (at(i) == system)
				{
					library::UniqueWriteLock uk(getMutex());

					erase(begin() + i);
					break;
				}
		};