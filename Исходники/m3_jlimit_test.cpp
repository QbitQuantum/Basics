static void* rt_system_thread(void * arg)
{	
  SEM * status_sem;
  SEM * command_sem;
  RT_TASK *task;
	
  M3Sds * sds = (M3Sds *)arg;
  printf("Starting real-time thread\n");
		
	
  sds_status_size = sizeof(M3TorqueShmSdsStatus);
  sds_cmd_size = sizeof(M3TorqueShmSdsCommand);
	
  task = rt_task_init_schmod(nam2num("TSHMP"), 0, 0, 0, SCHED_FIFO, 0xF);
  rt_allow_nonroot_hrt();
  if (task==NULL)
    {
      printf("Failed to create RT-TASK TSHMP\n");
      return 0;
    }
  status_sem=(SEM*)rt_get_adr(nam2num(TORQUE_STATUS_SEM));
  command_sem=(SEM*)rt_get_adr(nam2num(TORQUE_CMD_SEM));
  if (!status_sem)
    {
      printf("Unable to find the %s semaphore.\n",TORQUE_STATUS_SEM);
      rt_task_delete(task);
      return 0;
    }
  if (!command_sem)
    {
      printf("Unable to find the %s semaphore.\n",TORQUE_CMD_SEM);
      rt_task_delete(task);
      return 0;
    }
	
	
  RTIME tick_period = nano2count(RT_TIMER_TICKS_NS_TORQUE_SHM); 
  RTIME now = rt_get_time();
  rt_task_make_periodic(task, now + tick_period, tick_period); 
  mlockall(MCL_CURRENT | MCL_FUTURE);
  rt_make_hard_real_time();
  long long start_time, end_time, dt;
  long long step_cnt = 0;
  sys_thread_active=1;
  
  bool first_iteration(true);
  time_t trigger_goal_change;
  Vector goal[2];
  size_t next_goal;
  
  while(!sys_thread_end)
    {
      start_time = nano2count(rt_get_cpu_time_ns());
      rt_sem_wait(status_sem);
      memcpy(&shm_status, sds->status, sds_status_size);		
      rt_sem_signal(status_sem);

      //////////////////////////////////////////////////
      // BEGIN control algo
      
      SetTimestamp(GetTimestamp()); //Pass back timestamp as a heartbeat
      
      State state(7, 7, 0);
      
      for (unsigned int ii(0); ii < 7; ++ii) {
	state.position_[ii] = M_PI * shm_status.right_arm.theta[ii] / 180.0;
	state.velocity_[ii] = M_PI * shm_status.right_arm.thetadot[ii] / 180.0;
      }
      
      model->update(state);
      
      if (first_iteration) {
	bool ok(true);
	Status status(controller->init(*model));
	if ( ! status) {
	  warnx("ERROR: controller failed to initialize: %s",
		status.errstr.c_str());
	  ok = false;
	}
	if (ok) {
	  status = jgoal_p->set(jgoal);
	  if ( ! status) {
	    warnx("ERROR: jgoal setting failed (did you specify one?): %s",
		  status.errstr.c_str());
	    controller_errstr = "jgoal: " + status.errstr;
	    ok = false;
	  }
	}
	
	if ( ! ok) {
	  endme(42);
	  sys_thread_end=1;
	  break;
	}
	
	first_iteration = false;
      }
      
      Vector tau;
      tau.setZero(7);
      Status status(controller->computeCommand(*model, tau));
      if ( ! status) {
	controller_errstr = status.errstr;
	tau = - 10.0 * model->getState().velocity_;
      }
      
      for (unsigned int ii(0); ii < 7; ++ii) {
	SetTorque_mNm(RIGHT_ARM, ii, 1e3 * tau[ii]);
      }
      
      // END control algo
      //////////////////////////////////////////////////
      
      rt_sem_wait(command_sem);
      memcpy(sds->cmd, &shm_cmd, sds_cmd_size);		
      rt_sem_signal(command_sem);
      
      end_time = nano2count(rt_get_cpu_time_ns());
      dt=end_time-start_time;
      /*
	Check the time it takes to run components, and if it takes
	longer than our period, make us run slower. Otherwise this
	task locks up the CPU.*/
      if (dt > tick_period && step_cnt>10) 
	{
	  printf("Step %lld: Computation time of components is too long. Forcing all components to state SafeOp.\n",step_cnt);
	  printf("Previous period: %f. New period: %f\n", (double)count2nano(tick_period),(double)count2nano(dt));
	  tick_period=dt;
	  rt_task_make_periodic(task, end + tick_period,tick_period);			
	}
      step_cnt++;
      rt_task_wait_period();
    }	
  printf("Exiting RealTime Thread...\n");
  rt_make_soft_real_time();
  rt_task_delete(task);
  sys_thread_active=0;
  return 0;
}