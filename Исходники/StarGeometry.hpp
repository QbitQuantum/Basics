			inline static
			Ptr
			create(std::shared_ptr<render::AbstractContext>	context, 
				   unsigned int								numBranches, 
				   float									outerRadius, 
				   float									innerRadius)
			{
				Ptr ptr = std::shared_ptr<StarGeometry>(new StarGeometry());

				ptr->initialize(context, numBranches, outerRadius, innerRadius);

				return ptr;
			}