			inline static
			Ptr
			create()
			{
				Ptr ptr = std::shared_ptr<PhongMaterial>(new PhongMaterial());

				ptr->initialize();

				return ptr;
			}