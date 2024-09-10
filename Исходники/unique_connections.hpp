			const my_type& operator=(my_type&& My_){
				hmLib_assert(Connections.size() == 0, inquiry_exception, "Connections already have a connection");
				Connections.swap(My_.Connections);
				return *this;
			}