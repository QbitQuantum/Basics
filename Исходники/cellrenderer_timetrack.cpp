void
CellRenderer_TimeTrack::render_vfunc(
	const ::Cairo::RefPtr< ::Cairo::Context>& cr,
	Gtk::Widget& /* widget */,
	const Gdk::Rectangle& /* background_area */,
	const Gdk::Rectangle& cell_area,
	Gtk::CellRendererState /* flags */)
{
	if(!cr)
		return;

	Glib::RefPtr<Gtk::Adjustment> adjustment=get_adjustment();
	// Gtk::StateType state = Gtk::STATE_ACTIVE;
	// Gtk::ShadowType shadow;

	Gdk::Color
		curr_time_color("#0000ff"),
		inactive_color("#000000"),
		keyframe_color("#a07f7f");
	Gdk::Color activepoint_color[2];

	activepoint_color[0]=Gdk::Color("#ff0000");
	activepoint_color[1]=Gdk::Color("#00ff00");

	int stride = Cairo::ImageSurface::format_stride_for_width(Cairo::FORMAT_A1, 2);
	std::vector<unsigned char> stipple_xpm(2*stride, 0);
	stipple_xpm[0] = 2;
	Cairo::RefPtr<Cairo::ImageSurface> inactive_mask_img = Cairo::ImageSurface::create(&stipple_xpm.front(), Cairo::FORMAT_A1, 2, 2, stride);

	synfig::Canvas::Handle canvas(property_canvas().get_value());

	synfigapp::ValueDesc value_desc = property_value_desc().get_value();
	synfig::ValueNode *base_value = value_desc.get_value_node().get();
	// synfig::ValueNode_Animated *value_node=dynamic_cast<synfig::ValueNode_Animated*>(base_value);

	synfig::ValueNode_DynamicList *parent_value_node(0);
	if(property_value_desc().get_value().parent_is_value_node())
		parent_value_node=dynamic_cast<synfig::ValueNode_DynamicList*>(property_value_desc().get_value().get_parent_value_node().get());

	// If the canvas is defined, then load up the keyframes
	if(canvas)
	{
		const synfig::KeyframeList& keyframe_list(canvas->keyframe_list());
		synfig::KeyframeList::const_iterator iter;

		for(iter=keyframe_list.begin();iter!=keyframe_list.end();++iter)
		{
			if(!iter->get_time().is_valid())
				continue;

			const int x((int)((float)cell_area.get_width()/(adjustment->get_upper()-adjustment->get_lower())*(iter->get_time()-adjustment->get_lower())));
			if(iter->get_time()>=adjustment->get_lower() && iter->get_time()<adjustment->get_upper())
			{
				cr->set_source_rgb(keyframe_color.get_red_p(), keyframe_color.get_green_p(), keyframe_color.get_blue_p());
				cr->rectangle(cell_area.get_x()+x, cell_area.get_y(), 1, cell_area.get_height()+1);
				cr->fill();
			}
		}
	}

	//render all the time points that exist
	{
		const synfig::Node::time_set *tset = get_times_from_vdesc(value_desc);

		if(tset)
		{
			const synfig::Time time_offset = get_time_offset_from_vdesc(value_desc);
			synfig::Node::time_set::const_iterator	i = tset->begin(), end = tset->end();

			float 	lower = adjustment->get_lower(),
					upper = adjustment->get_upper();

			Gdk::Rectangle area(cell_area);

			bool valselected = sel_value.get_value_node() == base_value && !sel_times.empty();

			float cfps = get_canvas()->rend_desc().get_frame_rate();

			vector<Time>	drawredafter;

			Time diff = actual_time - actual_dragtime;//selected_time-drag_time;
			for(; i != end; ++i)
			{
				//find the coordinate in the drawable space...
				Time t_orig = i->get_time();
				if(!t_orig.is_valid()) continue;
				Time t = t_orig - time_offset;
				if(t<adjustment->get_lower() || t>adjustment->get_upper()) continue;

				//if it found it... (might want to change comparison, and optimize
				//					 sel_times.find to not produce an overall nlogn solution)

				bool selected=false;
				//not dragging... just draw as per normal
				//if move dragging draw offset
				//if copy dragging draw both...

				if(valselected && sel_times.find(t_orig) != sel_times.end())
				{
					if(dragging) //skip if we're dragging because we'll render it later
					{
						if(mode & COPY_MASK) // draw both blue and red moved
						{
							drawredafter.push_back(t + diff.round(cfps));
						}else if(mode & DELETE_MASK) //it's just red...
						{
							selected=true;
						}else //move - draw the red on top of the others...
						{
							drawredafter.push_back(t + diff.round(cfps));
							continue;
						}
					}else
					{
						selected=true;
					}
				}

				//synfig::info("Displaying time: %.3f s",(float)t);
				const int x = (int)((t-lower)*area.get_width()/(upper-lower));

				//should draw me a grey filled circle...
				Gdk::Rectangle area2(
					area.get_x() - area.get_height()/2 + x + 1,
					area.get_y() + 1,
					area.get_height()-2,
					area.get_height()-2
				);
				render_time_point_to_window(cr,area2,*i - time_offset,selected);
			}

			{
				vector<Time>::iterator i = drawredafter.begin(), end = drawredafter.end();
				for(; i != end; ++i)
				{
					//find the coordinate in the drawable space...
					Time t = *i;

					if(!t.is_valid())
						continue;

					//synfig::info("Displaying time: %.3f s",(float)t);
					const int x = (int)((t-lower)*area.get_width()/(upper-lower));

					//should draw me a grey filled circle...

					Gdk::Rectangle area2(
						area.get_x() - area.get_height()/2 + x + 1,
						area.get_y() + 1,
						area.get_height()-2,
						area.get_height()-2
					);
					render_time_point_to_window(cr,area2,*i,true);
				}
			}
		}
	}

	Gdk::Rectangle area(cell_area);
	// If the parent of this value node is a dynamic list, then
	// render the on and off times
	if(parent_value_node)
	{
		const int index(property_value_desc().get_value().get_index());
		const synfig::ValueNode_DynamicList::ListEntry& list_entry(parent_value_node->list[index]);
		const synfig::ValueNode_DynamicList::ListEntry::ActivepointList& activepoint_list(list_entry.timing_info);
		synfig::ValueNode_DynamicList::ListEntry::ActivepointList::const_iterator iter,next;

		bool is_off(false);
		if(!activepoint_list.empty())
			is_off=!activepoint_list.front().state;

		int xstart(0);

		int x=0 /*,prevx=0*/;
		for(next=activepoint_list.begin(),iter=next++;iter!=activepoint_list.end();iter=next++)
		{
			x=((int)((float)area.get_width()/(adjustment->get_upper()-adjustment->get_lower())*(iter->time-adjustment->get_lower())));
			if(x<0)x=0;
			if(x>area.get_width())x=area.get_width();

			bool status_at_time=0;
			if(next!=activepoint_list.end())
			{
				status_at_time=!list_entry.status_at_time((iter->time+next->time)/2.0);
			}
			else
				status_at_time=!list_entry.status_at_time(Time::end());

			if(!is_off && status_at_time)
			{
				xstart=x;
				is_off=true;
			}
			else
			if(is_off && !status_at_time)
			{
				cr->set_source_rgb( inactive_color.get_red_p(),
									inactive_color.get_green_p(),
									inactive_color.get_red_p() );
				cr->mask(inactive_mask_img, 0, 0);
				cr->rectangle(area.get_x()+xstart, area.get_y(), x-xstart, area.get_height());
				cr->fill();
				is_off=false;
			}

			if(iter->time>=adjustment->get_lower() && iter->time<adjustment->get_upper())
			{
				int w(1);
				if(selected==*iter)
					w=3;
				cr->set_source_rgb( activepoint_color[iter->state].get_red_p(),
									activepoint_color[iter->state].get_green_p(),
									activepoint_color[iter->state].get_red_p() );
				cr->rectangle(area.get_x()+x-w/2, area.get_y(), w, area.get_height());
				cr->fill();
			}
			//prevx=x;
		}
		if(is_off)
		{
			cr->set_source_rgb( inactive_color.get_red_p(),
								inactive_color.get_green_p(),
								inactive_color.get_red_p() );
			cr->mask(inactive_mask_img, 0, 0);
			cr->rectangle(area.get_x()+xstart, area.get_y(), area.get_width()-xstart, area.get_height());
			cr->fill();
		}
	}

	// Render a line that defines the current tick in time
	{
		const int x((int)((float)area.get_width()/(adjustment->get_upper()-adjustment->get_lower())*(adjustment->get_value()-adjustment->get_lower())));
		if(adjustment->get_value()>=adjustment->get_lower() && adjustment->get_value()<adjustment->get_upper())
		{
			cr->set_source_rgb( curr_time_color.get_red_p(),
								curr_time_color.get_green_p(),
								curr_time_color.get_red_p() );
			cr->rectangle(area.get_x()+x, area.get_y(), 1, area.get_height());
			cr->fill();
		}
	}
}