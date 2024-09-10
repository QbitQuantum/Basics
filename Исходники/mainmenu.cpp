void menu_main::handle()
{
	/* process the menu */
	const event *menu_event = process(0);
	if (menu_event != nullptr && menu_event->iptkey == IPT_UI_SELECT) {
		switch((long long)(menu_event->itemref)) {
		case INPUT_GROUPS:
			menu::stack_push<menu_input_groups>(ui(), container());
			break;

		case INPUT_SPECIFIC:
			menu::stack_push<menu_input_specific>(ui(), container());
			break;

		case SETTINGS_DIP_SWITCHES:
			menu::stack_push<menu_settings_dip_switches>(ui(), container());
			break;

		case SETTINGS_DRIVER_CONFIG:
			menu::stack_push<menu_settings_driver_config>(ui(), container());
			break;

		case ANALOG:
			menu::stack_push<menu_analog>(ui(), container());
			break;

		case BOOKKEEPING:
			menu::stack_push<menu_bookkeeping>(ui(), container());
			break;

		case GAME_INFO:
			menu::stack_push<menu_game_info>(ui(), container());
			break;

		case IMAGE_MENU_IMAGE_INFO:
			menu::stack_push<menu_image_info>(ui(), container());
			break;

		case IMAGE_MENU_FILE_MANAGER:
			menu::stack_push<menu_file_manager>(ui(), container(), nullptr);
			break;

		case TAPE_CONTROL:
			menu::stack_push<menu_tape_control>(ui(), container(), nullptr);
			break;

		case PTY_INFO:
			menu::stack_push<menu_pty_info>(ui(), container());
			break;

		case SLOT_DEVICES:
			menu::stack_push<menu_slot_devices>(ui(), container());
			break;

		case NETWORK_DEVICES:
			menu::stack_push<menu_network_devices>(ui(), container());
			break;

		case KEYBOARD_MODE:
			menu::stack_push<menu_keyboard_mode>(ui(), container());
			break;

		case SLIDERS:
			menu::stack_push<menu_sliders>(ui(), container(), false);
			break;

		case VIDEO_TARGETS:
			menu::stack_push<menu_video_targets>(ui(), container());
			break;

		case VIDEO_OPTIONS:
			menu::stack_push<menu_video_options>(ui(), container(), machine().render().first_target());
			break;

		case CROSSHAIR:
			menu::stack_push<menu_crosshair>(ui(), container());
			break;

		case CHEAT:
			menu::stack_push<menu_cheat>(ui(), container());
			break;

		case PLUGINS:
			menu::stack_push<menu_plugin>(ui(), container());
			break;

		case SELECT_GAME:
			if (machine().options().ui() == emu_options::UI_SIMPLE)
				menu::stack_push<simple_menu_select_game>(ui(), container(), nullptr);
			else
				menu::stack_push<menu_select_game>(ui(), container(), nullptr);
			break;

		case BIOS_SELECTION:
			menu::stack_push<menu_bios_selection>(ui(), container());
			break;

		case BARCODE_READ:
			menu::stack_push<menu_barcode_reader>(ui(), container(), nullptr);
			break;

		case EXTERNAL_DATS:
			menu::stack_push<menu_dats_view>(ui(), container());
			break;

		case ADD_FAVORITE:
			mame_machine_manager::instance()->favorite().add_favorite(machine());
			reset(reset_options::REMEMBER_POSITION);
			break;

		case REMOVE_FAVORITE:
			mame_machine_manager::instance()->favorite().remove_favorite(machine());
			reset(reset_options::REMEMBER_POSITION);
			break;

		case QUIT_GAME:
			stack_pop();
			ui().request_quit();
			break;

		default:
			fatalerror("ui::menu_main::handle - unknown reference\n");
		}
	}
}