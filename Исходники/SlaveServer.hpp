		virtual void addClient(std::shared_ptr<protocol::ClientDriver> driver) override
		{
			this->communicator_ = driver;
			driver->listen(this);
		};