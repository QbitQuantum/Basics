			inline static
			Ptr
			create(std::shared_ptr<render::AbstractContext> context)
			{
				Ptr ptr = std::shared_ptr<LineGeometry>(new LineGeometry());

				ptr->initialize(context);

				return ptr;
			}