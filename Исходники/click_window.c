bool drag_bone_model_wind(Point start_pt)
{
	int						n,k,drag_handle;
	float					x,y,z,hx,hy,hz,org_ang,org_mov,
							bone_drag_handle_offset;
	float					*ang,*mov;
	Point					pt,last_pt;
	d3vct					vct;
	d3ang					hang,rot;
	model_draw_bone_type	*draw_bone;
	MouseTrackingResult		track;
	
	model_wind_play(FALSE,FALSE);
	
		// setup the draw pose
		
	draw_model_setup_pose(&model,&draw_setup,cur_pose);
	model_create_draw_bones(&model,&draw_setup);
	
		// setup transforms
		
	draw_model_gl_setup(&model);
	
		// click on any drag handles?
		
	drag_handle=drag_handle_none;
	
	if ((cur_pose==-1) || (cur_bone!=-1)) {
	
		draw_bone=&draw_setup.bones[cur_bone];
		
		x=draw_bone->fpnt.x+draw_setup.move.x;
		y=draw_bone->fpnt.y+draw_setup.move.y;
		z=draw_bone->fpnt.z+draw_setup.move.z;
		
		bone_drag_handle_offset=draw_model_bones_drag_handle_offset(&model);

		draw_model_bones_get_handle_rot(&model,&draw_setup,cur_bone,&rot);
		
			// x drag bone

		vct.x=bone_drag_handle_offset;
		vct.y=0;
		vct.z=0;
		hang.x=0;
		hang.y=rot.y;
		hang.z=rot.z;
		draw_model_bones_drag_handle_calc(x,y,z,&vct,&hang,&hx,&hy,&hz);
		if (draw_bone_model_wind_click_box(start_pt,hx,hy,hz)) drag_handle=drag_handle_x;
		
			// y drag bone
			
		vct.x=0;
		vct.y=bone_drag_handle_offset;
		vct.z=0;
		hang.x=rot.x;
		hang.y=0;
		hang.z=rot.z;
		draw_model_bones_drag_handle_calc(x,y,z,&vct,&hang,&hx,&hy,&hz);
		if (draw_bone_model_wind_click_box(start_pt,hx,hy,hz)) drag_handle=drag_handle_y;
		
			// z drag bone
			
		vct.x=0;
		vct.y=0;
		vct.z=bone_drag_handle_offset;
		hang.x=rot.x;
		hang.y=rot.y;
		hang.z=0;
		draw_model_bones_drag_handle_calc(x,y,z,&vct,&hang,&hx,&hy,&hz);
		if (draw_bone_model_wind_click_box(start_pt,hx,hy,hz)) drag_handle=drag_handle_z;
	}
	
		// click on any bones?
		
	if (drag_handle==drag_handle_none) {
	
		k=-1;
		draw_bone=draw_setup.bones;
			
		for (n=0;n!=model.nbone;n++) {
			x=draw_bone->fpnt.x+draw_setup.move.x;
			y=draw_bone->fpnt.y+draw_setup.move.y;
			z=draw_bone->fpnt.z+draw_setup.move.z;
			
			if (draw_bone_model_wind_click_box(start_pt,x,y,z)) {
				k=n;
				break;
			}

			draw_bone++;
		}
		
		if (k==-1) return(FALSE);
	
			// select as current bone
			
		cur_bone=k;
		reset_bone_list();
		draw_model_wind_pose(&model,cur_mesh,cur_pose);

		return(TRUE);
	}
	
		// get drag angle
		
	switch (drag_handle) {
	
		case drag_handle_x:
			ang=&model.poses[cur_pose].bone_moves[cur_bone].rot.x;
			mov=&model.poses[cur_pose].bone_moves[cur_bone].mov.x;
			break;
		
		case drag_handle_y:
			ang=&model.poses[cur_pose].bone_moves[cur_bone].rot.y;
			mov=&model.poses[cur_pose].bone_moves[cur_bone].mov.y;
			break;
			
		case drag_handle_z:
			ang=&model.poses[cur_pose].bone_moves[cur_bone].rot.z;
			mov=&model.poses[cur_pose].bone_moves[cur_bone].mov.z;
			break;
		
		default:
			return(TRUE);
			
	}

	reset_bone_list();
	
		// drag bone

	org_ang=*ang;
	org_mov=*mov;
	last_pt.h=last_pt.v=-1;
	
	undo_set_bone_move(cur_pose,cur_bone);
	
	SetCCursor(bone_drag_cursor);
		
	do {
		TrackMouseLocation(NULL,&pt,&track);
		model_wind_offset_click(&pt);
		
		if (memcmp(&last_pt,&pt,sizeof(Point))==0) continue;
	
		memmove(&last_pt,&pt,sizeof(Point));
		
		x=pt.h-start_pt.h;
		if (x<-180) x=-180;
		if (x>180) x=180;
		
		if (drag_bone_mode==drag_bone_mode_rotate) {
			*ang=org_ang+(((float)x)/2.0f);
		}
		else {
			*mov=org_mov+(((float)x)/20.0f);
		}
		
			// draw the model
			
		model_bone_drag_on=TRUE;
		draw_model_wind_pose(&model,cur_mesh,cur_pose);
		model_bone_drag_on=FALSE;
		
		reset_bone_list();
		redraw_bone_list();

	} while (track!=kMouseTrackingMouseReleased);

	InitCursor();

		// redraw model
		
	draw_model_wind_pose(&model,cur_mesh,cur_pose);

	return(TRUE);
}