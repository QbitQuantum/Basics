/*
 * Compute the target congestion window for the next RTT according to 
 * cubic equation when an ack is received.
 *
 * W(t) = C(t-K)^3 + W(last_max)
 */
static uint32_t
tcp_cubic_update(struct tcpcb *tp, u_int32_t rtt)
{
	float K, var;
	u_int32_t elapsed_time, win;

	win = min(tp->snd_cwnd, tp->snd_wnd);
	if (tp->t_ccstate->cub_last_max == 0)
		tp->t_ccstate->cub_last_max = tp->snd_ssthresh;

	if (tp->t_ccstate->cub_epoch_start == 0) {
		/*
		 * This is the beginning of a new epoch, initialize some of
		 * the variables that we need to use for computing the 
		 * congestion window later.
		 */
		tp->t_ccstate->cub_epoch_start = tcp_now;
		if (tp->t_ccstate->cub_epoch_start == 0)
			tp->t_ccstate->cub_epoch_start = 1;
		if (win < tp->t_ccstate->cub_last_max) {

			VERIFY(current_task() == kernel_task);

			/*
			 * Compute cubic epoch period, this is the time
			 * period that the window will take to increase to
			 * last_max again after backoff due to loss.
			 */
			K = (tp->t_ccstate->cub_last_max - win)
			    / tp->t_maxseg / tcp_cubic_coeff;
			K = cbrtf(K);
			tp->t_ccstate->cub_epoch_period = K * TCP_RETRANSHZ;
			/* Origin point */
			tp->t_ccstate->cub_origin_point = 
				tp->t_ccstate->cub_last_max;
		} else {
			tp->t_ccstate->cub_epoch_period = 0;
			tp->t_ccstate->cub_origin_point = win;
		}
		tp->t_ccstate->cub_target_win = 0;
	}
	
	VERIFY(tp->t_ccstate->cub_origin_point > 0);	
	/*
	 * Compute the target window for the next RTT using smoothed RTT
	 * as an estimate for next RTT.
	 */
	elapsed_time = timer_diff(tcp_now, 0, 
		tp->t_ccstate->cub_epoch_start, 0);

	if (tcp_cubic_use_minrtt)
		elapsed_time += max(tcp_cubic_use_minrtt, rtt);
	else
		elapsed_time += rtt;
	var = (elapsed_time  - tp->t_ccstate->cub_epoch_period) / TCP_RETRANSHZ;
	var = var * var * var * (tcp_cubic_coeff * tp->t_maxseg);

	tp->t_ccstate->cub_target_win = tp->t_ccstate->cub_origin_point + var;
	return (tp->t_ccstate->cub_target_win);
}