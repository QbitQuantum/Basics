	void ResAtlas::loadAtlas(CreateResourceContext &context)
	{
		//string path = context.walker.getCurrentFolder();

		pugi::xml_node node = context.walker.getNode(); 
		pugi::xml_node meta = context.walker.getMeta();

        int w = node.attribute("width").as_int(defaultAtlasWidth);
        int h = node.attribute("height").as_int(defaultAtlasHeight);
		const char *format = node.attribute("format").as_string("8888");

		atlas_data ad;


		TextureFormat tf = string2TextureFormat(format);

		pugi::xml_node meta_image = meta.child("atlas");
		
		bool compressed = false;

		while(meta_image)
		{
			const char *file = meta_image.attribute("file").value();

			int w = meta_image.attribute("w").as_int();
			int h = meta_image.attribute("h").as_int();

			const char *file_format = meta_image.attribute("format").as_string(0);
			TextureFormat ffmt = TF_UNDEFINED;
			if (file_format)
			{
				ffmt = string2TextureFormat(file_format);
				compressed = isCompressedFormat(ffmt);
			}

			std::string alpha_file = meta_image.attribute("alpha").as_string("");
			if (!alpha_file.empty())
			{
				alpha_file = *context.prebuilt_folder + alpha_file;
			}

			addAtlas(tf, *context.prebuilt_folder + file, alpha_file, w, h);

			meta_image = meta_image.next_sibling("atlas");
			context.walker.nextMeta();
		}

		//

		std::vector<ResAnim*> anims;
	
		
		while (true)
		{
			XmlWalker walker = context.walker.next();
			if (walker.empty())
				break;

			pugi::xml_node child_node = walker.getNode();
			pugi::xml_node meta_frames = walker.getMeta();

			const char *name = child_node.name();
			if (!strcmp(name, "image"))
			{
				std::string id = child_node.attribute("id").value();
				std::string file = child_node.attribute("file").value();

				if (file.empty())
				{
					ResAnim *ra = new ResAnim(this);
					ra->init(0, 0, 0, walker.getScaleFactor());
					init_resAnim(ra, file, child_node);
					ra->setParent(this);
					context.resources->add(ra);
					continue;
				}

				if (meta)
				{
					OX_ASSERT(meta_frames && "Did you recreate atlasses?");
				}
				
				MemoryTexture mt;
				ImageData im;

				int columns = 0;
				int rows = 0;
				int frame_width = 0;
				int frame_height = 0;
				float frame_scale = 1.0f;
				bool loaded = false;

				if (meta_frames  || meta)
				{
					const char *frame_size = meta_frames.attribute("fs").value();

					//int w = 0;
					//int h = 0;

					sscanf(frame_size, "%d,%d,%d,%d,%f", &columns, &rows, 
						&frame_width, &frame_height, 
						&frame_scale);
					loaded = true;
					//frame_scale = 0.
					//frame_scale /= walker.getScaleFactor();//todo! fix

					//im.w = w;
					//im.h = h;
				}
				else
				{
					file::buffer bf;
					file::read(walker.getPath("file").c_str(), bf);

					mt.init(bf, Renderer::getPremultipliedAlphaRender(), tf);
					im = mt.lock();
					if (im.w)
					{
						rows = child_node.attribute("rows").as_int();
						frame_width = child_node.attribute("frame_width").as_int();
						columns = child_node.attribute("cols").as_int();
						frame_height = child_node.attribute("frame_height").as_int();

						if (!rows)
							rows = 1;

						if (!columns)
							columns = 1;

						if (frame_width)
							columns = im.w / frame_width;				
						else
							frame_width = im.w / columns;


						if (frame_height)				
							rows = im.h / frame_height;
						else
							frame_height = im.h / rows;				

					}
				}

				if (columns)
				{
					animationFrames frames;
					int frames_count = rows * columns;
					frames.reserve(frames_count);
					
					ResAnim *ra = new ResAnim(this);

					if (meta)
					{
						OX_ASSERT(meta_frames);

						/*
						if (string(meta_frames.attribute("debug_image").as_string()) == "backleft.png")
						{

						}
						*/

						char *frames_data = (char*)meta_frames.first_child().value();

						const char *begin = frames_data;
						while(*frames_data)
						{
							if (*frames_data == ';')
							{
								*frames_data = 0;
								int id = 0;
								int x = 0;
								int y = 0;

								int bbox_x = 0;
								int bbox_y = 0;
								int bbox_w = 0;
								int bbox_h = 0;

								sscanf(begin, "%d,%d,%d,%d,%d,%d,%d", &id, &x, &y, &bbox_x, &bbox_y, &bbox_w, &bbox_h);

								begin = frames_data + 1;

								spNativeTexture &texture = _atlasses[id].base;
								spNativeTexture &alpha = _atlasses[id].alpha;

								float iw = 1.0f / texture->getWidth();
								float ih = 1.0f / texture->getHeight();

								RectF srcRect(x * iw, y * ih, bbox_w * iw, bbox_h * ih);

								float fs = frame_scale;
								RectF destRect(
									Vector2((float)bbox_x, (float)bbox_y) * fs,
									Vector2((float)bbox_w, (float)bbox_h) * fs
									);

								AnimationFrame frame;
								Diffuse df;
								df.base = texture;
								df.alpha = alpha;
								//compressed data could not be premultiplied 
								if (Renderer::getPremultipliedAlphaRender())
									df.premultiplied = !compressed;
								else
									df.premultiplied = true;//render should think that it is already premultiplied and don't worry about alpha

								frame.init(ra, df,
									srcRect, destRect, 
									Vector2((float)frame_width, (float)frame_height));

								frames.push_back(frame);
								if((int)frames.size() >= frames_count)
									break;
							}

							++frames_data;
						}
					}
					else
					{
						anims.push_back(ra);

						for (int y = 0; y < rows; ++y)
						{
							for (int x = 0; x < columns; ++x)
							{
								Rect src;
								src.pos = Point(x * frame_width, y * frame_height);
								src.size = Point(frame_width, frame_height);

								ImageData srcImage = im.getRect(src);

								Rect dest(0,0,0,0);

								if (!ad.texture)
								{
									std::string atlas_id = getName();
									next_atlas(w, h, tf, ad, atlas_id.c_str());
								}

								bool s = ad.atlas.add(&ad.mt, srcImage, dest);
								if (s == false)
								{
									apply_atlas(ad);
									next_atlas(w, h, tf, ad, walker.getCurrentFolder().c_str());
									s = ad.atlas.add(&ad.mt, srcImage, dest);
									OX_ASSERT(s);
								}

								/*
								float iw = 1.0f / ad.mt.getWidth();
								float ih = 1.0f / ad.mt.getHeight();
								*/

								float iw = 1.0f;
								float ih = 1.0f;
								
								RectF srcRect(dest.pos.x * iw, dest.pos.y * ih, dest.size.x * iw, dest.size.y * ih);

								Vector2 sizeScaled = Vector2((float)dest.size.x, (float)dest.size.y) * walker.getScaleFactor();
								RectF destRect(Vector2(0, 0), sizeScaled);

								AnimationFrame frame;
								Diffuse df;
								df.base = ad.texture;
								df.premultiplied = true;//!Renderer::getPremultipliedAlphaRender();
								frame.init(ra, df, srcRect, destRect, Vector2((float)frame_width, (float)frame_height) * walker.getScaleFactor());
								frames.push_back(frame);
							}
						}
					}	


					
					init_resAnim(ra, file, child_node);
					
					ra->init(frames, columns, walker.getScaleFactor());					
					ra->setParent(this);
					context.resources->add(ra);
				}
			}
		}

		apply_atlas(ad);

		for (std::vector<ResAnim*>::iterator i = anims.begin(); i != anims.end(); ++i)
		{
			ResAnim *rs = *i;
			int num = rs->getTotalFrames();

			for (int n = 0; n < num; ++n)
			{
				AnimationFrame &frame = const_cast<AnimationFrame&>(rs->getFrame(n));
				
				float iw = 1.0f / frame.getDiffuse().base->getWidth();
				float ih = 1.0f / frame.getDiffuse().base->getHeight();

				RectF rect = frame.getSrcRect();
				rect.pos.x *= iw;
				rect.pos.y *= ih;
				rect.size.x *= iw;
				rect.size.y *= ih;
				frame.setSrcRect(rect);
			}
		}
	}