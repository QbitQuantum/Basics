int proto_enter_home_op(home_proto_t* p_proto)
{
	CHECK_BODY_LEN_GE(p_proto->len, sizeof(home_proto_t) + sizeof(sprite_base_info_t));

	KDEBUG_LOG(p_proto->id,"ENTER HOME: [homeid=%x %u]", HI32(p_proto->homeid), LO32(p_proto->homeid));

	home_t* p_home	= (home_t*)g_hash_table_lookup(all_home, &p_proto->homeid);
    if(!p_home) {
        p_home   = add_home(p_proto->homeid);
        if (!p_home) {
            KDEBUG_LOG(p_proto->id,"ENTER HOME FAILED [onlineid=%u map=%x %u]",p_proto->onlineid, HI32(p_proto->homeid), LO32(p_proto->homeid));
            return 0;
        }
    }

	sprite_ol_t* p =(sprite_ol_t*) g_hash_table_lookup(p_home->sprites, &p_proto->id);
	if (!p) {
		p = add_sprite_ol(p_home, p_proto);
		if (!p) {
			KDEBUG_LOG(p_proto->id,"ADD PLAYER FAILED [onlineid=%u map=%x %u]", p_proto->onlineid,HI32(p_proto->homeid), LO32(p_proto->homeid));
			return 0;
		}
	}

	memcpy(&p->sprite_info, p_proto->body, sizeof(sprite_base_info_t));
	if (p->sprite_info.pet_followed) {
		memcpy(&p->pet_sinfo, p_proto->body + sizeof(sprite_base_info_t), sizeof(pet_simple_info_t));
	}

	send_all_users_to_self(p->id, p->onlineid, p_home);

	//pvp 处理	
	g_pvp[0].cd_map(p_proto->homeid, p->id );
	g_pvp[1].cd_map(p_proto->homeid, p->id );
	//trade 进入交易房间
    g_market.cd_room(p->id);
	return 0;
}