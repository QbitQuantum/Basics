void TBag::run()
{
	for (int i = 0; i < _num_proc; ++i)
	{
		_events[i]._offset=i;

		_tasks[i] = createTask();
		_tasks[i]->offset=i;
		_bids.push(_tasks[i]);
	}

	Evt *e;
	Task *task;
	double duration;

	_busy=false;
	_curr_time = 0.0;
	_user_time=0.0;
	_event._type = MASTER;
	plan(&_event, 0.0);

	///////// установка привязки
	if(!SetThreadAffinityMask(GetCurrentThread(),0x1)){
		printf("\nSetThreadAffinityMask FAILED\n");return;
	}

	///////// установка приоритета
	if(!SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_HIGHEST)){
		printf("\nTHREAD_PRIORITY_ABOVE_NORMAL FAILED\n");return;
	}

	LARGE_INTEGER frequency;
	LARGE_INTEGER t1,t2;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);

	while(!_calendar.empty())
	{
		e=_calendar.top();
		_calendar.pop();
		
		assert(_curr_time <= e->_plan_time);

		_curr_time=e->_plan_time;
		e->_planed=false;

		switch(e->_type)
		{
			case MASTER:
				if (!_results.empty())
				{
					_busy=true;

					task = _results.front();
					_results.pop();

					put(task,duration);
					_user_time+=duration;

					_events[task->offset]._type=PUT;
					plan(&_events[task->offset],duration);
				}
				else if(!_bids.empty())
				{
					_busy=true;

					task = _bids.front();
					_bids.pop();

					_events[task->offset]._if_job=if_job(duration);
					_user_time+=duration;

					_events[task->offset]._type=IF_JOB;
					plan(&_events[task->offset],duration);
				}
				
				e->_type=DEFAULT;
				break;
			
			case IF_JOB:
				if(e->_if_job){
					get(_tasks[e->_offset],duration);
					_user_time+=duration;

					e->_type=GET;
					plan(e,duration);
				}
				else{
					_bids.push(_tasks[e->_offset]);
					e->_type=DEFAULT;

					_busy=false;
				}
				break;

			case PUT:
				e->_if_job=if_job(duration);
				_user_time+=duration;

				e->_type=IF_JOB;
				plan(e,duration);
				break;

			case GET:
				proc(_tasks[e->_offset],duration);
				_user_time+=duration;
				
				e->_type=PROC;
				plan(e,duration);

				_event._type=MASTER;
				plan(&_event,0);

				_busy=false;
				break;
				
			case PROC:
				_results.push(_tasks[e->_offset]);
				e->_type=DEFAULT;
				
				if(!_busy && _event._type==DEFAULT){
					_event._type=MASTER;
					plan(&_event,0);
				}
				break;

			case DEFAULT: 
				assert(0);
				break;
		}
	}
	
	QueryPerformanceCounter(&t2);
	_duration=(double)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart;

	for (int i = 0; i < _num_proc; ++i)	delete _tasks[i];
}