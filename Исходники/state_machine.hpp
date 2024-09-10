	//Process an event, advance the state apply onExit of old state and onEntry on the new state
	bool process(event to_process){
		std::map<State*, std::map<event, State*>>::const_iterator transition;
		transition=_transition_table.find(_current_state);
		if(transition!=_transition_table.end()){
			std::map<event, State*>::const_iterator new_state;
			new_state=transition->second.find(to_process);

			if(new_state!=transition->second.end()){
				if(new_state->second==NULL){
					std::cerr<<"ERROR: Target state is NULL"<<std::endl;
					return false;
				}
				if(_current_state->hasAction()) _current_state->stopAction();
				_current_state->onExit(to_process);
				_current_state=new_state->second;
				_current_state->onEntry(to_process);
				if(_current_state->hasAction()) _current_state->startAction();
			} //else stay in state
		}else{
			std::cerr<<"ERROR: Invalid current state"<<std::endl;
			return false;
		}
		return true;
	}