    v8::Handle<v8::Value> setCursor(const v8::Arguments& args) {

        ALLEGRO_SYSTEM_MOUSE_CURSOR cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT;
        if (args.Length() > 0) {
            cursor = (ALLEGRO_SYSTEM_MOUSE_CURSOR)ToInt32(args[0]);
        }

        if (al_set_system_mouse_cursor(Game::allegro.display, cursor)) {
            return v8::True();
                
        } else {
            return v8::False();
        }

    }