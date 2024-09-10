			TreeView::ImageList::ImageList(const uint x,const uint y,const uint selected,const uint unselected)
			: handle(ImageList_Create(x,y,ILC_COLOR16|ILC_MASK,0,2))
			{
				if (handle)
				{
					try
					{
						if
						(
							ImageList_AddMasked( static_cast<HIMAGELIST>(handle), Resource::Bitmap( selected   ), 0 ) == -1 ||
							ImageList_AddMasked( static_cast<HIMAGELIST>(handle), Resource::Bitmap( unselected ), 0 ) == -1
						)
							throw Application::Exception( IDS_ERR_FAILED, L"ImageList_Add()" );
					}
					catch (const Application::Exception& exception)
					{
						ImageList_Destroy( static_cast<HIMAGELIST>(handle) );
						throw exception;
					}
				}
				else
				{
					throw Application::Exception( IDS_ERR_FAILED, L"ImageList_Create()" );
				}
			}