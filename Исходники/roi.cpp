        bool ROI::mouse_move_event () 
        { 
          if (!in_insert_mode)
            return false;

          QModelIndexList indices = list_view->selectionModel()->selectedIndexes();
          if (!indices.size()) {
            WARN ("FIXME: shouldn't be here!");
            return false;
          }
          ROI_Item* roi = dynamic_cast<ROI_Item*> (list_model->get (indices[0]));

          const Projection* proj = window().get_current_mode()->get_current_projection();
          if (!proj) 
            return false;

          Point<> pos =  proj->screen_to_model (window().mouse_position(), window().focus());
          Point<> slice_axis (0.0, 0.0, 0.0);
          slice_axis[current_axis] = current_axis == 2 ? 1.0 : -1.0;
          slice_axis = roi->transform().image2scanner_dir (slice_axis);
          float l = (current_slice_loc - pos.dot (slice_axis)) / proj->screen_normal().dot (slice_axis);
          window().set_focus (window().focus() + l * proj->screen_normal());
          const Point<> pos_adj = pos + l * proj->screen_normal();

          if (brush_button->isChecked()) {
            if (brush_size_button->isMin())
              roi->current().draw_line (*roi, prev_pos, pos_adj, insert_mode_value);
            else {
              const float diameter = brush_size_button->value();
              roi->current().draw_thick_line (*roi, prev_pos, pos_adj, insert_mode_value, diameter);
              roi->current().draw_circle (*roi, pos_adj, insert_mode_value, diameter);
            }
          } else if (rectangle_button->isChecked()) {
            roi->current().draw_rectangle (*roi, current_origin, pos_adj, insert_mode_value);
          } else if (fill_button->isChecked()) {
            // Do nothing
          }

          updateGL();
          prev_pos = pos_adj;
          return true; 
        }