static void
clockintr(Ureg*, void*)
{
	Clock0link *lp;
	static int blip, led;

	if(++blip >= HZ){
		blip = 0;
		ledset(led ^= 1);
	}
	m->ticks++;

	checkalarms();

	if(canlock(&clock0lock)){
		for(lp = clock0link; lp; lp = lp->link)
			if(lp->clock)
				lp->clock();
		unlock(&clock0lock);
	}

	/* round robin time slice is done by trap.c and proc.c */
}