				inline static
				Ptr
				create(AssetLibraryPtr assets)
				{
					Ptr ptr = std::shared_ptr<ColliderDebug>(new ColliderDebug(assets));

					ptr->initialize();

					return ptr;
				}