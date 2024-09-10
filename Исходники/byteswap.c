/* ARGSUSED */
static int hton_position_update(packet *pu, size_t s)
{
    if (s < sizeof(position_update))
        return 0;
    pu->pos.sequence = htonll(pu->pos.sequence);
    pu->pos.object_id = htonll(pu->pos.object_id);
    pu->pos.frame_number = htons(pu->pos.frame_number);
    pu->pos.x_pos = htonll(pu->pos.x_pos);
    pu->pos.y_pos = htonll(pu->pos.y_pos);
    pu->pos.z_pos = htonll(pu->pos.z_pos);
    pu->pos.x_orient = htonl(pu->pos.x_orient);
    pu->pos.y_orient = htonl(pu->pos.y_orient);
    pu->pos.z_orient = htonl(pu->pos.z_orient);
    pu->pos.w_orient = htonl(pu->pos.z_orient);
    pu->pos.x_look = htonl(pu->pos.x_look);
    pu->pos.y_look = htonl(pu->pos.y_look);
    pu->pos.z_look = htonl(pu->pos.z_look);
    return 1;
}