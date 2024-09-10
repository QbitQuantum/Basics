		void enqueue( _Tx &item ) 
		{
			m_cs.Enter();
			m_queue.push( item );
			m_cs.Exit();
		}