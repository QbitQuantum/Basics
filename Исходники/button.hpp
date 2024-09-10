			bool assemble(widget& parent_widget, std::string const& caption, rectangle& rect = rectangle(), button_function_t function_on_click = []() -> bool { return true; })
			{
				if (!this->create(WC_BUTTON, caption, rect, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, NULL, parent_widget.get_handle()))
				{
					return false;
				}
				
				this->function_on_click = function_on_click;
				this->set_message_handlers();
				return true;
			}