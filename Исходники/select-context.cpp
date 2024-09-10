static gint
sp_select_context_item_handler(SPEventContext *event_context, SPItem *item, GdkEvent *event)
{
    gint ret = FALSE;

    SPDesktop *desktop = event_context->desktop;
    SPSelectContext *sc = SP_SELECT_CONTEXT(event_context);
    Inkscape::SelTrans *seltrans = sc->_seltrans;

    Inkscape::Preferences *prefs = Inkscape::Preferences::get();
    tolerance = prefs->getIntLimited("/options/dragtolerance/value", 0, 0, 100);

    // make sure we still have valid objects to move around
    if (sc->item && SP_OBJECT_DOCUMENT( SP_OBJECT(sc->item))==NULL) {
        sp_select_context_abort(event_context);
    }

    switch (event->type) {
        case GDK_BUTTON_PRESS:
            if (event->button.button == 1 && !event_context->space_panning) {
                /* Left mousebutton */

                // save drag origin
                xp = (gint) event->button.x;
                yp = (gint) event->button.y;
                within_tolerance = true;

                // remember what modifiers were on before button press
                sc->button_press_shift = (event->button.state & GDK_SHIFT_MASK) ? true : false;
                sc->button_press_ctrl = (event->button.state & GDK_CONTROL_MASK) ? true : false;
                sc->button_press_alt = (event->button.state & GDK_MOD1_MASK) ? true : false;

                if (event->button.state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) {
                    // if shift or ctrl was pressed, do not move objects;
                    // pass the event to root handler which will perform rubberband, shift-click, ctrl-click, ctrl-drag
                } else {
                    sc->dragging = TRUE;
                    sc->moved = FALSE;

                    desktop->setCursor(SP_SELECT_D_CURSOR);
                    
                    desktop->canvas->force_full_redraw_after_interruptions(5);

                    // remember the clicked item in sc->item:
                    if (sc->item) {
                        sp_object_unref(sc->item, NULL);
                        sc->item = NULL;
                    }
                    sc->item = sp_event_context_find_item (desktop,
                                              Geom::Point(event->button.x, event->button.y), event->button.state & GDK_MOD1_MASK, FALSE);
                    sp_object_ref(sc->item, NULL);

                    rb_escaped = drag_escaped = 0;

                    if (sc->grabbed) {
                        sp_canvas_item_ungrab(sc->grabbed, event->button.time);
                        sc->grabbed = NULL;
                    }
                    sp_canvas_item_grab(SP_CANVAS_ITEM(desktop->drawing),
                                        GDK_KEY_PRESS_MASK | GDK_KEY_RELEASE_MASK | GDK_BUTTON_RELEASE_MASK | GDK_BUTTON_PRESS_MASK |
                                        GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK,
                                        NULL, event->button.time);
                    sc->grabbed = SP_CANVAS_ITEM(desktop->drawing);

                    desktop->canvas->force_full_redraw_after_interruptions(5);

                    ret = TRUE;
                }
            } else if (event->button.button == 3) {
                // right click; do not eat it so that right-click menu can appear, but cancel dragging & rubberband
                sp_select_context_abort(event_context);
            }
            break;

        case GDK_ENTER_NOTIFY:
        {
            if (!desktop->isWaitingCursor() && !sc->dragging) {
                desktop->setCursor(SP_SELECT_CURSOR);
            }
            break;
        }

        case GDK_LEAVE_NOTIFY:
            if (!desktop->isWaitingCursor() && !sc->dragging)
                desktop->setCursor(event_context->cursor_shape);
            break;

        case GDK_KEY_PRESS:
            if (get_group0_keyval (&event->key) == GDK_space) {
                if (sc->dragging && sc->grabbed) {
                    /* stamping mode: show content mode moving */
                    seltrans->stamp();
                    ret = TRUE;
                }
            }
            break;

        default:
            break;
    }

    if (!ret) {
        if (((SPEventContextClass *) parent_class)->item_handler)
            ret = ((SPEventContextClass *) parent_class)->item_handler(event_context, item, event);
    }

    return ret;
}