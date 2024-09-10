void OS_X11::process_xevents() {

	//printf("checking events %i\n", XPending(x11_display));

	do_mouse_warp=false;

	while (XPending(x11_display) > 0) {
		XEvent event;
		XNextEvent(x11_display, &event);

		switch (event.type) {
		case Expose:
			Main::force_redraw();
			break;

		case NoExpose:
			minimized = true;
			break;

		case VisibilityNotify: {
			XVisibilityEvent * visibility = (XVisibilityEvent *)&event;
			minimized = (visibility->state == VisibilityFullyObscured);
		} break;
		case LeaveNotify: {

			if (main_loop && mouse_mode!=MOUSE_MODE_CAPTURED)
				main_loop->notification(MainLoop::NOTIFICATION_WM_MOUSE_EXIT);
			if (input)
				input->set_mouse_in_window(false);

		} break;
		case EnterNotify: {

			if (main_loop && mouse_mode!=MOUSE_MODE_CAPTURED)
				main_loop->notification(MainLoop::NOTIFICATION_WM_MOUSE_ENTER);
			if (input)
				input->set_mouse_in_window(true);
		} break;
		case FocusIn:
			minimized = false;
#ifdef NEW_WM_API
			if(current_videomode.fullscreen) {
				set_wm_fullscreen(true);
			}
#endif
			main_loop->notification(MainLoop::NOTIFICATION_WM_FOCUS_IN);
			if (mouse_mode==MOUSE_MODE_CAPTURED) {
				XGrabPointer(x11_display, x11_window, True,
						    ButtonPressMask | ButtonReleaseMask |
						    PointerMotionMask, GrabModeAsync, GrabModeAsync,
						    x11_window, None, CurrentTime);
			}
			break;

		case FocusOut:
#ifdef NEW_WM_API
			if(current_videomode.fullscreen) {
				set_wm_fullscreen(false);
				set_window_minimized(true);
			}
#endif
			main_loop->notification(MainLoop::NOTIFICATION_WM_FOCUS_OUT);
			if (mouse_mode==MOUSE_MODE_CAPTURED) {
				//dear X11, I try, I really try, but you never work, you do whathever you want.
				XUngrabPointer(x11_display, CurrentTime);
			}
			break;

		case ConfigureNotify:
		/* call resizeGLScene only if our window-size changed */

			if ((event.xconfigure.width == current_videomode.width) &&
			(event.xconfigure.height == current_videomode.height))
				break;

			current_videomode.width=event.xconfigure.width;
			current_videomode.height=event.xconfigure.height;
			break;
		case ButtonPress:
		case ButtonRelease: {

			/* exit in case of a mouse button press */
			last_timestamp=event.xbutton.time;
			if (mouse_mode==MOUSE_MODE_CAPTURED) {
				event.xbutton.x=last_mouse_pos.x;
				event.xbutton.y=last_mouse_pos.y;
			}

			InputEvent mouse_event;
			mouse_event.ID=++event_id;
			mouse_event.type = InputEvent::MOUSE_BUTTON;
			mouse_event.device=0;
			mouse_event.mouse_button.mod = get_key_modifier_state(event.xbutton.state);
			mouse_event.mouse_button.button_mask = get_mouse_button_state(event.xbutton.state);
			mouse_event.mouse_button.x=event.xbutton.x;
			mouse_event.mouse_button.y=event.xbutton.y;
			mouse_event.mouse_button.global_x=event.xbutton.x;
			mouse_event.mouse_button.global_y=event.xbutton.y;
			mouse_event.mouse_button.button_index=event.xbutton.button;
			if (mouse_event.mouse_button.button_index==2)
				mouse_event.mouse_button.button_index=3;
			else if (mouse_event.mouse_button.button_index==3)
				mouse_event.mouse_button.button_index=2;

			mouse_event.mouse_button.pressed=(event.type==ButtonPress);


			if (event.type==ButtonPress && event.xbutton.button==1) {

				uint64_t diff = get_ticks_usec()/1000 - last_click_ms;

				if (diff<400 && Point2(last_click_pos).distance_to(Point2(event.xbutton.x,event.xbutton.y))<5) {

					last_click_ms=0;
					last_click_pos = Point2(-100,-100);
					mouse_event.mouse_button.doubleclick=true;
					mouse_event.ID=++event_id;

				} else {
					last_click_ms+=diff;
					last_click_pos = Point2(event.xbutton.x,event.xbutton.y);
				}
			}

			input->parse_input_event( mouse_event);


		} break;
		case MotionNotify: {

			// F**K YOU X11 API YOU SERIOUSLY GROSS ME OUT
			// YOU ARE AS GROSS AS LOOKING AT A PUTRID PILE
			// OF POOP STICKING OUT OF A CLOGGED TOILET
			// HOW THE F**K I AM SUPPOSED TO KNOW WHICH ONE
			// OF THE MOTION NOTIFY EVENTS IS THE ONE GENERATED
			// BY WARPING THE MOUSE POINTER?
			// YOU ARE FORCING ME TO FILTER ONE BY ONE TO FIND IT
			// PLEASE DO ME A FAVOR AND DIE DROWNED IN A FECAL
			// MOUNTAIN BECAUSE THAT'S WHERE YOU BELONG.


			while(true) {
				if (mouse_mode==MOUSE_MODE_CAPTURED && event.xmotion.x==current_videomode.width/2 && event.xmotion.y==current_videomode.height/2) {
					//this is likely the warp event since it was warped here
					center=Vector2(event.xmotion.x,event.xmotion.y);
					break;
				}

				if (XPending(x11_display) > 0) {
					XEvent tevent;
					XPeekEvent(x11_display, &tevent);
					if (tevent.type==MotionNotify) {
						XNextEvent(x11_display,&event);
					} else {
						break;
					}
				} else {
					break;
				}
			}

			last_timestamp=event.xmotion.time;

			// Motion is also simple.
			// A little hack is in order
			// to be able to send relative motion events.
			Point2i pos( event.xmotion.x, event.xmotion.y );

			if (mouse_mode==MOUSE_MODE_CAPTURED) {
#if 1
				//Vector2 c = Point2i(current_videomode.width/2,current_videomode.height/2);
				if (pos==Point2i(current_videomode.width/2,current_videomode.height/2)) {
					//this sucks, it's a hack, etc and is a little inaccurate, etc.
					//but nothing I can do, X11 sucks.

					center=pos;
					break;
				}

				Point2i new_center = pos;
				pos = last_mouse_pos + ( pos - center );
				center=new_center;
				do_mouse_warp=true;
#else
				//Dear X11, thanks for making my life miserable

				center.x = current_videomode.width/2;
				center.y = current_videomode.height/2;
				pos = last_mouse_pos + ( pos-center );
				if (pos==last_mouse_pos)
					break;
				XWarpPointer(x11_display, None, x11_window,
					      0,0,0,0, (int)center.x, (int)center.y);
#endif
			}

			if (!last_mouse_pos_valid) {

				last_mouse_pos=pos;
				last_mouse_pos_valid=true;
			}

			Point2i rel = pos - last_mouse_pos;

#ifdef NEW_WM_API
			if (mouse_mode==MOUSE_MODE_CAPTURED) {
				pos.x = current_videomode.width / 2;
				pos.y = current_videomode.height / 2;
			}
#endif

			InputEvent motion_event;
			motion_event.ID=++event_id;
			motion_event.type=InputEvent::MOUSE_MOTION;
			motion_event.device=0;

			motion_event.mouse_motion.mod = get_key_modifier_state(event.xmotion.state);
			motion_event.mouse_motion.button_mask = get_mouse_button_state(event.xmotion.state);
			motion_event.mouse_motion.x=pos.x;
			motion_event.mouse_motion.y=pos.y;
			input->set_mouse_pos(pos);
			motion_event.mouse_motion.global_x=pos.x;
			motion_event.mouse_motion.global_y=pos.y;
			motion_event.mouse_motion.speed_x=input->get_mouse_speed().x;
			motion_event.mouse_motion.speed_y=input->get_mouse_speed().y;

			motion_event.mouse_motion.relative_x=rel.x;
			motion_event.mouse_motion.relative_y=rel.y;

			last_mouse_pos=pos;

			// printf("rel: %d,%d\n", rel.x, rel.y );

			input->parse_input_event( motion_event);

		} break;
		case KeyPress:
		case KeyRelease: {

			last_timestamp=event.xkey.time;

			// key event is a little complex, so
			// it will be handled in it's own function.
			handle_key_event( (XKeyEvent*)&event );
		} break;
		case SelectionRequest: {

			XSelectionRequestEvent *req;
			XEvent e, respond;
			e = event;

			req=&(e.xselectionrequest);
			if (req->target == XA_STRING || req->target == XInternAtom(x11_display, "COMPOUND_TEXT", 0) ||
				req->target == XInternAtom(x11_display, "UTF8_STRING", 0))
			{
				CharString clip = OS::get_clipboard().utf8();
				XChangeProperty (x11_display,
					req->requestor,
					req->property,
					req->target,
					8,
					PropModeReplace,
					(unsigned char*)clip.get_data(),
					clip.length());
				respond.xselection.property=req->property;
			} else if (req->target == XInternAtom(x11_display, "TARGETS", 0)) {

				Atom data[2];
				data[0] = XInternAtom(x11_display, "UTF8_STRING", 0);
				data[1] = XA_STRING;
				XChangeProperty (x11_display, req->requestor, req->property, req->target,
						 8, PropModeReplace, (unsigned char *) &data,
						 sizeof (data));
				respond.xselection.property=req->property;

			} else {
				printf ("No String %x\n",
					(int)req->target);
				respond.xselection.property= None;
			}
			respond.xselection.type= SelectionNotify;
			respond.xselection.display= req->display;
			respond.xselection.requestor= req->requestor;
			respond.xselection.selection=req->selection;
			respond.xselection.target= req->target;
			respond.xselection.time = req->time;
			XSendEvent (x11_display, req->requestor,0,0,&respond);
			XFlush (x11_display);
		} break;


		case ClientMessage:

			if ((unsigned int)event.xclient.data.l[0]==(unsigned int)wm_delete)
				main_loop->notification(MainLoop::NOTIFICATION_WM_QUIT_REQUEST);
			break;
		default:
			break;
		}
	}

	XFlush(x11_display);

	if (do_mouse_warp) {

		XWarpPointer(x11_display, None, x11_window,
		 	      0,0,0,0, (int)current_videomode.width/2, (int)current_videomode.height/2);

		/*
		Window root, child;
		int root_x, root_y;
		int win_x, win_y;
		unsigned int mask;
		XQueryPointer( x11_display, x11_window, &root, &child, &root_x, &root_y, &win_x, &win_y, &mask );

		printf("Root: %d,%d\n", root_x, root_y);
		printf("Win: %d,%d\n", win_x, win_y);
		*/
	}
}