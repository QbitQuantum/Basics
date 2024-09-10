void qspn_reset(u_char levels)
{
	setzero(qspn_b, sizeof(struct qspn_buffer *)*levels);
	setzero(qspn_send_mutex, sizeof(int)*levels);
	setzero(me.cur_qspn_id, sizeof(int)*levels);
	
	qspn_reset_counters(levels);
}