    Tempo_Point_Editor ( float *tempo ) : Fl_Menu_Window(  75, 58, "Edit Tempo" )
        {
            _sucess = false;
            _tempo = tempo;

            set_modal();

            Fl_Float_Input *fi = _fi = new Fl_Float_Input( 12, 0 + 24, 50, 24, "Tempo:" );
            fi->align( FL_ALIGN_TOP );
            fi->when( FL_WHEN_NOT_CHANGED | FL_WHEN_ENTER_KEY );
            fi->callback( &Tempo_Point_Editor::enter_cb, (void*)this );

            char pat[10];
            snprintf( pat, sizeof( pat ), "%.1f", *tempo );

            fi->value( pat );

            end();

            show();

            while ( shown() )
                Fl::wait();
        }