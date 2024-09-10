	void NodeDomain::acceptClient(const std::shared_ptr<NodeClient> &client)
	{
		auto self = shared_from_this();
		std::lock_guard<std::recursive_mutex> lock(mutex);
		
		if (!acceptsClient) {
			client->reject();
			return;
		}
		
		std::weak_ptr<NodeDomain> weakSelf(self);
		client->onClosed.connect([this, weakSelf](const NodeClient::ptr& client) {
			auto self = weakSelf.lock();
			if (!self)
				return;
			std::lock_guard<std::recursive_mutex> lock(mutex);
			clients.erase(client->clientId());
		});
		
		clients.emplace(client->clientId(), client);
		
		auto success = client->accept();
		if (!success) {
			clients.erase(client->clientId());
			return;
		}
		
		if (!client->isOpen()) {
			clients.erase(client->clientId());
		}
		
	}