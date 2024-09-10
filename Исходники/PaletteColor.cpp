Int32 PaletteColor::Message(const BaseContainer& msg, BaseContainer& result)
{
	if(msg.GetId() == BFM_DRAGRECEIVE){
		Int32 type = 0;
		void *object = NULL;
		GetDragObject(msg, &type, &object);
		if(type == DRAGTYPE_RGB){
			Vector *color = static_cast<Vector*>(object);
			if(msg.GetInt32(BFM_DRAG_FINISHED)){
                switch(m_hoverState){
                    case HOVER_LEFT:
                        Palette::InsertPaletteColor(m_palette, m_colorID, Color(*color).SetSource(COLOR_SOURCE_DISPLAY));
                        break;
                    case HOVER_RIGHT:
                        Palette::InsertPaletteColor(m_palette, m_colorID+1, Color(*color).SetSource(COLOR_SOURCE_DISPLAY));
                        break;
                    case HOVER_CENTER:
                        Palette::SetPaletteColor(m_palette, m_colorID, Color(*color).SetSource(COLOR_SOURCE_DISPLAY));
                        break;
                    case HOVER_DELETE:
                        Palette::RemovePaletteColor(m_palette, m_colorID);
                        break;
                }
                m_hoverState = HOVER_NONE;
			}
			else{
				if (msg.GetInt32(BFM_DRAG_LOST)){
					m_hoverState = HOVER_NONE;
					Redraw();
				}
				else{
                    BaseContainer state;
                    if(GetInputState(BFM_INPUT_MOUSE, BFM_INPUT_MOUSELEFT, state)){
                        if((*color)[0] <0.f && ((*color)[1] < 0.f && ((*color)[2] < 0.f))){
                            m_hoverState = HOVER_DELETE;
                        }else{
                            Float sideWidth = 0.2;
                            Int32 x = state.GetInt32(BFM_INPUT_X);
                            Int32 y = state.GetInt32(BFM_INPUT_Y);
                            Global2Local(&x,&y);
                            if(x < m_w*sideWidth){
                                m_hoverState = HOVER_LEFT;
                            }
                            else{
                                if(x > m_w*(1.0-sideWidth)){
                                    m_hoverState = HOVER_RIGHT;
                                }
                                else{
                                    m_hoverState = HOVER_CENTER;
                                }
                            }
                        }
                        Redraw();
                        GeUserArea::Message(msg, result);
                        return SetDragDestination(MOUSE_POINT_HAND);
                    }
				}
			}
		}
	}

	return GeUserArea::Message(msg, result);
}