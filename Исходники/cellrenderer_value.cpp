void
CellRenderer_ValueBase::render_vfunc(
		const Glib::RefPtr<Gdk::Drawable>& window,
		Gtk::Widget& widget,
		const Gdk::Rectangle& background_area,
		const Gdk::Rectangle& ca,
		const Gdk::Rectangle& expose_area,
		Gtk::CellRendererState flags)
{
	if(!window)
		return;
//	const unsigned int cell_xpad = property_xpad();
//	const unsigned int cell_ypad = property_ypad();

	//int x_offset = 0, y_offset = 0;
//	int	width = ca.get_width();
	int	height = ca.get_height();
//	get_size(widget, ca, x_offset, y_offset, width, height);

//	width  -= cell_xpad * 2;
//	height -= cell_ypad * 2;

//	if(width <= 0 || height <= 0)
//		return;

	Gtk::StateType state = Gtk::STATE_INSENSITIVE;
	if(property_editable())
		state = Gtk::STATE_NORMAL;
	if((flags & Gtk::CELL_RENDERER_SELECTED) != 0)
		state = (widget.has_focus()) ? Gtk::STATE_SELECTED : Gtk::STATE_ACTIVE;

	ValueBase data=property_value_.get_value();

	Type &type(data.get_type());
	if (type == type_real)
	{
		if(((synfig::ParamDesc)property_param_desc_).get_is_distance())
		{
			Distance x(data.get(Real()),Distance::SYSTEM_UNITS);
			x.convert(App::distance_system,get_canvas()->rend_desc());
			property_text()=(Glib::ustring)x.get_string(6).c_str();
		}
		else
			property_text()=(Glib::ustring)strprintf("%.6f",data.get(Real()));
	}
	else
	if (type == type_time)
	{
		property_text()=(Glib::ustring)data.get(Time()).get_string(get_canvas()->rend_desc().get_frame_rate(),App::get_time_format());
	}
	else
	if (type == type_angle)
	{
		property_text()=(Glib::ustring)strprintf("%.2fᵒ",(Real)Angle::deg(data.get(Angle())).get());
	}
	else
	if (type == type_integer)
	{
		String param_hint, child_param_hint;
		param_hint=get_param_desc().get_hint();
		child_param_hint=get_child_param_desc().get_hint();
		if(param_hint!="enum" && child_param_hint!="enum")
		{
			property_text()=(Glib::ustring)strprintf("%i",data.get(int()));
		}
		else
		{
			property_text()=(Glib::ustring)strprintf("(%i)",data.get(int()));
			std::list<synfig::ParamDesc::EnumData> enum_list;
			if(param_hint=="enum")
				enum_list=((synfig::ParamDesc)property_param_desc_).get_enum_list();
			else if(child_param_hint=="enum")
				enum_list=((synfig::ParamDesc)property_child_param_desc_).get_enum_list();
			std::list<synfig::ParamDesc::EnumData>::iterator iter;
			for(iter=enum_list.begin();iter!=enum_list.end();iter++)
				if(iter->value==data.get(int()))
				{
					// don't show the key_board s_hortcut under_scores
					String local_name = iter->local_name;
					String::size_type pos = local_name.find_first_of('_');
					if (pos != String::npos)
						property_text() = local_name.substr(0,pos) + local_name.substr(pos+1);
					else
						property_text() = local_name;
					break;
				}
		}
	}
	else
	if (type == type_vector)
	{
		Vector vector=data.get(Vector());
		Distance x(vector[0],Distance::SYSTEM_UNITS),y(vector[1],Distance::SYSTEM_UNITS);
		x.convert(App::distance_system,get_canvas()->rend_desc());
		y.convert(App::distance_system,get_canvas()->rend_desc());
		property_text()=static_cast<Glib::ustring>(strprintf("%s,%s",x.get_string(6).c_str(),y.get_string(6).c_str()));
	}
	else
	if (type == type_transformation)
	{
		const Transformation &transformation=data.get(Transformation());
		const Vector &offset = transformation.offset;
		const Angle::deg angle(transformation.angle);
		const Vector &scale = transformation.scale;
		Distance x(offset[0],Distance::SYSTEM_UNITS),y(offset[1],Distance::SYSTEM_UNITS);
		x.convert(App::distance_system,get_canvas()->rend_desc());
		y.convert(App::distance_system,get_canvas()->rend_desc());
		Distance sx(scale[0],Distance::SYSTEM_UNITS),sy(scale[1],Distance::SYSTEM_UNITS);
		sx.convert(App::distance_system,get_canvas()->rend_desc());
		sy.convert(App::distance_system,get_canvas()->rend_desc());
		property_text()=static_cast<Glib::ustring>(strprintf(
			"%s,%s,%.2fᵒ,%s,%s",
			x.get_string(6).c_str(), y.get_string(6).c_str(),
			(Real)angle.get(),
			sx.get_string(6).c_str(), sy.get_string(6).c_str()
		));
	}
	else
	if (type == type_string)
	{
		if(data.get_type()==type_string)
		{
			if(!data.get(synfig::String()).empty())
				property_text()=static_cast<Glib::ustring>(data.get(synfig::String()));
			else
				property_text()=Glib::ustring("<empty>");
		}
	}
	else
	if (type == type_canvas)
	{
		if(data.get(etl::handle<synfig::Canvas>()))
		{
			if(data.get(etl::handle<synfig::Canvas>())->is_inline())
				property_text()=_("<Group>");
			else
				property_text()=(Glib::ustring)data.get(etl::handle<synfig::Canvas>())->get_id();
		}
		else
			property_text()=_("<No Image Selected>");
	}
	else
	if (type == type_color)
	{
		render_color_to_window(window,ca,data.get(Color()));
		return;
	}
	else
	if (type == type_bool)
	{
		widget.get_style()->paint_check(
			Glib::RefPtr<Gdk::Window>::cast_static(window), state,
			data.get(bool())?Gtk::SHADOW_IN:Gtk::SHADOW_OUT,
			ca, widget, "cellcheck",
			ca.get_x()/* + x_offset + cell_xpad*/,
			ca.get_y()/* + y_offset + cell_ypad*/,
			height-1,height-1);
		return;
	}
	else
	if (type == type_nil)
	{
		//property_text()=(Glib::ustring)" ";
		return;
	}
	else
	if (type == type_gradient)
	{
		render_gradient_to_window(window,ca,data.get(Gradient()));
		return;
	}
	else
	if (type == type_bone_object
	 || type == type_segment
	 || type == type_list
	 || type == type_bline_point
	 || type == type_width_point
	 || type == type_dash_item)
	{
		property_text()=(Glib::ustring)(data.get_type().description.local_name);
	}
	else
	if (type == type_bone_valuenode)
	{
		ValueNode_Bone::Handle bone_node(data.get(ValueNode_Bone::Handle()));
		String name(_("No Parent"));

		if (!bone_node->is_root())
		{
			name = (*(bone_node->get_link("name")))(get_canvas()->get_time()).get(String());
			if (name.empty())
				name = bone_node->get_guid().get_string();
		}

		property_text()=(Glib::ustring)(name);
	}
	else
	{
		property_text()=static_cast<Glib::ustring>(type.description.local_name);
	}

	CellRendererText::render_vfunc(window,widget,background_area,ca,expose_area,flags);
}