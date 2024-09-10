void
tcp_fasttimo(void)
{
	register struct socket *so;
	register struct tcpcb *tp;

	DEBUG_CALL("tcp_fasttimo");

	so = tcb.so_next;
	if (so)
	for (; so != &tcb; so = so->so_next)
		if ((tp = (struct tcpcb *)so->so_tcpcb) &&
		    (tp->t_flags & TF_DELACK)) {
			tp->t_flags &= ~TF_DELACK;
			tp->t_flags |= TF_ACKNOW;
			STAT(tcpstat.tcps_delack++);
			(void) tcp_output(tp);
		}
}