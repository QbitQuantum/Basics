	void shape_def::update(float delta_time, character_ptr instance)
	{
		// XXX optimize this.
		static bool first = true;
		if(first) {
			first = false;

			auto vgraph = std::dynamic_pointer_cast<KRE::Vector::Context>(instance->get_render_object());
			auto& mat = instance->get_matrix_transform();
			auto vmat = vgraph->createMatrix();
			vmat->init(mat.scale_x.to_double()/20.0, mat.rotate_skew1.to_double(), 
				mat.rotate_skew0.to_double(), mat.scale_y.to_double()/20.0, 
				mat.translate_x - bounds_.x1()/20.0, mat.translate_y - bounds_.y1()/20.0);
			//vmat->scale(1.0f/20.0, 1.0f/20.0);
			vgraph->setMatrix(vmat);

			auto path = vgraph->NewPath();
			for(auto& sr : shape_records_) {
				switch(sr->get_type())
				{
				case ShapeRecordTypes::MOVE: {
					//std::cerr << "Bounds: " << bounds_ << " : " << (bounds_/20.0) << "\n";
					path->MoveTo(sr->get_delta().delta_x, sr->get_delta().delta_y);
					//auto p = vmat->transformPoint(sr->get_delta().delta_x, sr->get_delta().delta_y);
					//std::cerr << "POINT: " << p << "\n";
					//ASSERT_LOG(false, "");
					break;
				}
				case ShapeRecordTypes::LINE:
					path->LineTo(sr->get_delta().delta_x, sr->get_delta().delta_y);
					break;
				case ShapeRecordTypes::CURVE: {
					auto cr = std::dynamic_pointer_cast<curve_edge_record>(sr);
					ASSERT_LOG(cr != nullptr, "Type was curve. cast was null.");
					path->QuadraticCurveTo(cr->control().delta_x, cr->control().delta_y, 
						cr->anchor().delta_x+cr->control().delta_x, cr->anchor().delta_y+cr->control().delta_y, 
						true);
					break;
				}
				case ShapeRecordTypes::STYLE_CHANGE: {
					/*auto scr = std::dynamic_pointer_cast<style_change_record>(sr);
					if(scr->has_linestyle_change()) {
						auto ls = get_line_style(scr->get_line_style());
						// XXX if ls->end_cap_style != ls->start_cap_style we need to split the line.
						// or something.
						switch(ls->end_cap_style) {
						case line_style::CAP_STYLE_NONE: 
							vgraph->SetLineCap(KRE::Vector::LineCap::LINE_CAP_BUTT);
							break;
						case line_style::CAP_STYLE_SQUARE:
							vgraph->SetLineCap(KRE::Vector::LineCap::LINE_CAP_SQUARE);
							break;
						case line_style::CAP_STYLE_ROUND:
							vgraph->SetLineCap(KRE::Vector::LineCap::LINE_CAP_ROUND);
							break;
						default: break;
						}
						vgraph->SetLineWidth(static_cast<double>(ls->width) / instance->get_player()->get_twips());
						switch(ls->join_style) {
						case line_style::JOIN_STYLE_BEVEL:
							vgraph->SetLineJoin(KRE::Vector::LineJoin::LINE_JOIN_BEVEL);
							break;
						case line_style::JOIN_STYLE_MITER:
							vgraph->SetLineJoin(KRE::Vector::LineJoin::LINE_JOIN_MITER);
							vgraph->SetMiterLimit(ls->miter_limit_factor);
							break;
						case line_style::JOIN_STYLE_ROUND:
							vgraph->SetLineJoin(KRE::Vector::LineJoin::LINE_JOIN_ROUND);
							break;
						}
						if(ls->has_fill_flag) {
							// apply fill change
						}
						vgraph->SetSourceColor(ls->color.r, ls->color.g, ls->color.b, ls->color.a);
					}
					break;*/
				}
				default: break;
				}
			}
			vgraph->AddPath(path);
			vgraph->Stroke(true);
			vgraph->Fill();
		}
	}