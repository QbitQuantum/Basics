void group_moves_synch_with_host(network_reply_group_synch *synch)
{
	int				group_idx,flags;
	d3pnt			cuml_mov_add;
	d3ang			cuml_rot_add;
	group_type		*group;

		// get the group

	group_idx=(int)ntohs(synch->group_idx);
	group=&map.group.groups[group_idx];

		// fix the movement

	flags=ntohl(synch->flags);

	group->run.on=((flags&net_group_synch_flag_on)!=0);
	group->run.freeze=((flags&net_group_synch_flag_freeze)!=0);
	group->run.main_move=((flags&net_group_synch_flag_main_move)!=0);

	group->run.count=(int)ntohs(synch->count);
	group->run.user_id=(int)ntohs(synch->user_id);
	group->run.movement_idx=(int)ntohs(synch->movement_idx);
	group->run.movement_move_idx=(int)ntohs(synch->movement_move_idx);

	group->run.f_mov_add.x=ntohf(synch->fp_mov_add_x);
	group->run.f_mov_add.y=ntohf(synch->fp_mov_add_y);
	group->run.f_mov_add.z=ntohf(synch->fp_mov_add_z);
	
	group->run.f_mov_accum_add.x=ntohf(synch->fp_mov_accum_add_x);
	group->run.f_mov_accum_add.y=ntohf(synch->fp_mov_accum_add_y);
	group->run.f_mov_accum_add.z=ntohf(synch->fp_mov_accum_add_z);

	group->run.rot_add.x=ntohf(synch->fp_rot_add_x);
	group->run.rot_add.y=ntohf(synch->fp_rot_add_y);
	group->run.rot_add.z=ntohf(synch->fp_rot_add_z);

		// synch the commulative moves

		// if there's already been movement, get rid
		// of that before synching all commulative
		// movement

	cuml_mov_add.x=ntohl(synch->cuml_mov_add_x)-group->run.cuml_mov_add.x;
	cuml_mov_add.y=ntohl(synch->cuml_mov_add_y)-group->run.cuml_mov_add.y;
	cuml_mov_add.z=ntohl(synch->cuml_mov_add_z)-group->run.cuml_mov_add.z;

	cuml_rot_add.x=ntohf(synch->fp_cuml_rot_add_x)-group->run.cuml_rot_add.x;
	cuml_rot_add.y=ntohf(synch->fp_cuml_rot_add_y)-group->run.cuml_rot_add.y;
	cuml_rot_add.z=ntohf(synch->fp_cuml_rot_add_z)-group->run.cuml_rot_add.z;

	group_move_and_rotate(group,&cuml_mov_add,&cuml_rot_add,FALSE);
}