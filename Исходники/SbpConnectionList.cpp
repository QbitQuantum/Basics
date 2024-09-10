		void ConnectionActivated(Utils::SafeRef<ISbpConnection> src)
		{
			ESS_ASSERT(src.IsEqualIntf(m_connection.get()));
		}