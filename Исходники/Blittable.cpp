	void Blittable::preRender(const WindowPtr& wm)
	{
		if(changed_) {
			changed_ = false;

			if(draw_rect_.w() == 0 || draw_rect_.h() == 0) {
				draw_rect_ = rectf(0.0f, 0.0f, static_cast<float>(getTexture()->surfaceWidth()), static_cast<float>(getTexture()->surfaceHeight()));
			}

			float offs_x = 0.0f;
			float offs_y = 0.0f;
			switch(centre_) {
				case Centre::MIDDLE:		
					offs_x = -draw_rect_.w()/2.0f;
					offs_y = -draw_rect_.h()/2.0f;
					break;
				case Centre::TOP_LEFT: break;
				case Centre::TOP_RIGHT:
					offs_x = -draw_rect_.w();
					offs_y = 0;
					break;
				case Centre::BOTTOM_LEFT:
					offs_x = 0;
					offs_y = -draw_rect_.h();
					break;
				case Centre::BOTTOM_RIGHT:
					offs_x = -draw_rect_.w();
					offs_y = -draw_rect_.h();
					break;
				case Centre::MANUAL:
					offs_x = centre_offset_.x;
					offs_y = centre_offset_.y;
					break;
			}

			const float vx1 = (vertical_mirrored_ ? draw_rect_.x2() : draw_rect_.x()) + offs_x;
			const float vy1 = (horizontal_mirrored_ ? draw_rect_.y2() : draw_rect_.y()) + offs_y;
			const float vx2 = (vertical_mirrored_ ? draw_rect_.x() : draw_rect_.x2()) + offs_x;
			const float vy2 = (horizontal_mirrored_ ? draw_rect_.y() : draw_rect_.y2()) + offs_y;

			const rectf& r = getTexture()->getSourceRectNormalised();

			std::vector<vertex_texcoord> vertices;
			vertices.emplace_back(glm::vec2(vx1,vy1), glm::vec2(r.x(),r.y()));
			vertices.emplace_back(glm::vec2(vx2,vy1), glm::vec2(r.x2(),r.y()));
			vertices.emplace_back(glm::vec2(vx1,vy2), glm::vec2(r.x(),r.y2()));
			vertices.emplace_back(glm::vec2(vx2,vy2), glm::vec2(r.x2(),r.y2()));
			getAttributeSet().back()->setCount(vertices.size());
			attribs_->update(&vertices);
		}
	}