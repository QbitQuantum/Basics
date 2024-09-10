//========== DRAW ================= DRAW =================== DRAW ====================
void LCDST7565::drawMenu() {
	uint8_t i, label_len;
	this->clear();
	//this->fillrect(0, 0, 128, 7, BLACK);
	this->drawstring(centerString(_title), 0, _title);
	invertRect(0,0,128,8);
	  i=0;
	  while ((i<N_LINES-1) & (i<_n_items)) {
	    this->drawstring(LEFT_MARGIN, i+1, _menu_items[_draw_index+i].label);
	    switch(_menu_items[_draw_index+i].type)
	    {
	    case MENU_ITEM_TYPE_CHECK:
	    {
	    	uint8_t y = (i+1) * 8;
	    	drawrect(GUI_CHECKBOX_X, y, 7, 7, BLACK);
	    	if(_menu_items[_draw_index+i].checked)
	    	{
	    		drawline(GUI_CHECKBOX_X, y, GUI_CHECKBOX_X + 6, y + 6, BLACK);
	    		drawline(GUI_CHECKBOX_X, y + 6, GUI_CHECKBOX_X + 6, y, BLACK);
	    	}
	    	break;
	    }
	    case MENU_ITEM_TYPE_RADIO:
	    {
	    	uint8_t y = (i+1) * 8 + 4;
	    	if(_menu_items[_draw_index+i].checked)
	    	{
	    		fillcircle(GUI_RADIO_X, y, 2, BLACK);
	    	}
	    	else
	    	{
	    		drawcircle(GUI_RADIO_X, y, 2, BLACK);
	    	}
	    	break;
	    }
	    case MENU_ITEM_TYPE_INLINE_INT:
	    {
	    	char s[8];
	    	sprintf(s, "%i", _menu_items[_draw_index+i].inlineValue);
		    this->drawstring(122 - strlen(s) * 6, i+1, s);
	    	break;
	    }
	    }
	    i++;
	  }

	  /*// Draw arrow to indicate current item:
	  this->drawline(0, 11+(8*_current_line), LEFT_MARGIN-5,
	                                                11+(8*_current_line), BLACK);
	  this->drawline(LEFT_MARGIN-5, 8+(8*_current_line), LEFT_MARGIN-2,
	                                                11+(8*_current_line), BLACK);
	  this->drawline(LEFT_MARGIN-5, 14+(8*_current_line), LEFT_MARGIN-2,
	                                                11+(8*_current_line), BLACK);
	  this->drawline(LEFT_MARGIN-5, 14+(8*_current_line), LEFT_MARGIN-5,
	                                                8+(8*_current_line), BLACK);*/
	  this->drawbitmap(0, 8 * (_current_line+1), menu_arrow, 16, 8, BLACK);


	  // Draw up arrow if there are items above view
	  if (_draw_index > 0) {
	    this->drawline(123, 11, 125, 8, BLACK);
	    this->drawline(127, 11, 125, 8, BLACK);
	  }
	  // Draw down arrow if there are items below view
	  if ((_n_items - _draw_index) >= N_LINES) {
	    this->drawline(123, DOWN_ARROW_Y, 125, DOWN_ARROW_Y + 3, BLACK);
	    this->drawline(127, DOWN_ARROW_Y, 125, DOWN_ARROW_Y + 3, BLACK);
	  }

	  this->drawMenuButton(BUT_DOWN, 0);
	  this->drawMenuButton(BUT_UP, 1);
	  switch( _menu_items[_item_index].type )
	  {
	  case MENU_ITEM_TYPE_CHECK:
	  case MENU_ITEM_TYPE_RADIO:
	  {
		  this->drawMenuButton(BUT_BACK, 2);
		  this->drawMenuButton(BUT_SET, 3);
		  break;
	  }
	  case MENU_ITEM_TYPE_INLINE_INT:
	  {
		  this->drawMenuButton(BUT_LEFT, 2);
		  this->drawMenuButton(BUT_RIGHT, 3);
		  break;
	  }
	  default:
	  {
		  this->drawMenuButton(BUT_BACK, 2);
		  this->drawMenuButton(BUT_OK, 3);
		  break;
	  }
	  }
	  this->display();
}