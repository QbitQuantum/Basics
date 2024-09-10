void SoftBodyBullet::get_first_node_origin(btVector3 &p_out_origin) const {
	if (bt_soft_body && bt_soft_body->m_nodes.size()) {
		p_out_origin = bt_soft_body->m_nodes[0].m_x;
	} else {
		p_out_origin.setZero();
	}
}