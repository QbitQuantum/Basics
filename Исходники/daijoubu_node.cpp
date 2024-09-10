		_daijoubu_node_factory::~_daijoubu_node_factory(void)
		{

			if(m_initialized) {
				uninitialize();
			}
		}