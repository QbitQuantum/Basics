static int clamp_thread(void *arg)
{
	int cpunr = (unsigned long)arg;
	DEFINE_TIMER(wakeup_timer, noop_timer, 0, 0);
	static const struct sched_param param = {
		.sched_priority = MAX_USER_RT_PRIO/2,
	};
	unsigned int count = 0;
	unsigned int target_ratio;

	set_bit(cpunr, cpu_clamping_mask);
	set_freezable();
	init_timer_on_stack(&wakeup_timer);
	sched_setscheduler(current, SCHED_FIFO, &param);

	while (true == clamping && !kthread_should_stop() &&
		cpu_online(cpunr)) {
		int sleeptime;
		unsigned long target_jiffies;
		unsigned int guard;
		unsigned int compensation = 0;
		int interval; /* jiffies to sleep for each attempt */
		unsigned int duration_jiffies = msecs_to_jiffies(duration);
		unsigned int window_size_now;

		try_to_freeze();
		/*
		 * make sure user selected ratio does not take effect until
		 * the next round. adjust target_ratio if user has changed
		 * target such that we can converge quickly.
		 */
		target_ratio = set_target_ratio;
		guard = 1 + target_ratio/20;
		window_size_now = window_size;
		count++;

		/*
		 * systems may have different ability to enter package level
		 * c-states, thus we need to compensate the injected idle ratio
		 * to achieve the actual target reported by the HW.
		 */
		compensation = get_compensation(target_ratio);
		interval = duration_jiffies*100/(target_ratio+compensation);

		/* align idle time */
		target_jiffies = roundup(jiffies, interval);
		sleeptime = target_jiffies - jiffies;
		if (sleeptime <= 0)
			sleeptime = 1;
		schedule_timeout_interruptible(sleeptime);
		/*
		 * only elected controlling cpu can collect stats and update
		 * control parameters.
		 */
		if (cpunr == control_cpu && !(count%window_size_now)) {
			should_skip =
				powerclamp_adjust_controls(target_ratio,
							guard, window_size_now);
			smp_mb();
		}

		if (should_skip)
			continue;

		target_jiffies = jiffies + duration_jiffies;
		mod_timer(&wakeup_timer, target_jiffies);
		if (unlikely(local_softirq_pending()))
			continue;
		/*
		 * stop tick sched during idle time, interrupts are still
		 * allowed. thus jiffies are updated properly.
		 */
		preempt_disable();
		tick_nohz_idle_enter();
		/* mwait until target jiffies is reached */
		while (time_before(jiffies, target_jiffies)) {
			unsigned long ecx = 1;
			unsigned long eax = target_mwait;

			/*
			 * REVISIT: may call enter_idle() to notify drivers who
			 * can save power during cpu idle. same for exit_idle()
			 */
			local_touch_nmi();
			stop_critical_timings();
			mwait_idle_with_hints(eax, ecx);
			start_critical_timings();
			atomic_inc(&idle_wakeup_counter);
		}
		tick_nohz_idle_exit();
		preempt_enable_no_resched();
	}
	del_timer_sync(&wakeup_timer);
	clear_bit(cpunr, cpu_clamping_mask);

	return 0;
}

/*
 * 1 HZ polling while clamping is active, useful for userspace
 * to monitor actual idle ratio.
 */
static void poll_pkg_cstate(struct work_struct *dummy);
static DECLARE_DELAYED_WORK(poll_pkg_cstate_work, poll_pkg_cstate);
static void poll_pkg_cstate(struct work_struct *dummy)
{
	static u64 msr_last;
	static u64 tsc_last;
	static unsigned long jiffies_last;

	u64 msr_now;
	unsigned long jiffies_now;
	u64 tsc_now;
	u64 val64;

	msr_now = pkg_state_counter();
	rdtscll(tsc_now);
	jiffies_now = jiffies;

	/* calculate pkg cstate vs tsc ratio */
	if (!msr_last || !tsc_last)
		pkg_cstate_ratio_cur = 1;
	else {
		if (tsc_now - tsc_last) {
			val64 = 100 * (msr_now - msr_last);
			do_div(val64, (tsc_now - tsc_last));
			pkg_cstate_ratio_cur = val64;
		}
	}

	/* update record */
	msr_last = msr_now;
	jiffies_last = jiffies_now;
	tsc_last = tsc_now;

	if (true == clamping)
		schedule_delayed_work(&poll_pkg_cstate_work, HZ);
}

static int start_power_clamp(void)
{
	unsigned long cpu;
	struct task_struct *thread;

	/* check if pkg cstate counter is completely 0, abort in this case */
	if (!has_pkg_state_counter()) {
		pr_err("pkg cstate counter not functional, abort\n");
		return -EINVAL;
	}

	set_target_ratio = clamp(set_target_ratio, 0U, MAX_TARGET_RATIO - 1);
	/* prevent cpu hotplug */
	get_online_cpus();

	/* prefer BSP */
	control_cpu = 0;
	if (!cpu_online(control_cpu))
		control_cpu = smp_processor_id();

	clamping = true;
	schedule_delayed_work(&poll_pkg_cstate_work, 0);

	/* start one thread per online cpu */
	for_each_online_cpu(cpu) {
		struct task_struct **p =
			per_cpu_ptr(powerclamp_thread, cpu);

		thread = kthread_create_on_node(clamp_thread,
						(void *) cpu,
						cpu_to_node(cpu),
						"kidle_inject/%ld", cpu);
		/* bind to cpu here */
		if (likely(!IS_ERR(thread))) {
			kthread_bind(thread, cpu);
			wake_up_process(thread);
			*p = thread;
		}

	}
	put_online_cpus();

	return 0;
}