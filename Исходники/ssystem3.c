static void ssystem3_playfield_write(running_machine &machine, int reset, int signal)
{
	ssystem3_state *state = machine.driver_data<ssystem3_state>();
  int d=FALSE;

  if (!reset) {
    state->m_playfield.count=0;
    state->m_playfield.bit=0;
    state->m_playfield.started=FALSE;
    state->m_playfield.signal=signal;
    state->m_playfield.time=machine.time();
  }
  if (!signal && state->m_playfield.signal) {
    attotime t=machine.time();
    state->m_playfield.high_time=t - state->m_playfield.time;
    state->m_playfield.time=t;

    //    logerror("%.4x playfield %d lowtime %s hightime %s\n",(int)activecpu_get_pc(), state->m_playfield.count,
    //       state->m_playfield.low_time.as_string(7), state->m_playfield.high_time.as_string(7) );

    if (state->m_playfield.started) {
      // 0 twice as long low
      // 1 twice as long high
      if (state->m_playfield.low_time > state->m_playfield.high_time) d=TRUE;

      state->m_playfield.data&=~(1<<(state->m_playfield.bit^7));
      if (d) state->m_playfield.data|=1<<(state->m_playfield.bit^7);
      state->m_playfield.bit++;
      if (state->m_playfield.bit==8) {
	logerror("%.4x playfield wrote %d %02x\n", (int)cpu_get_pc(machine.device("maincpu")), state->m_playfield.count, state->m_playfield.data);
	state->m_playfield.u.data[state->m_playfield.count]=state->m_playfield.data;
	state->m_playfield.bit=0;
	state->m_playfield.count=(state->m_playfield.count+1)%ARRAY_LENGTH(state->m_playfield.u.data);
	if (state->m_playfield.count==0) state->m_playfield.started=FALSE;
      }
    }

  } else if (signal && !state->m_playfield.signal) {
    attotime t=machine.time();
    state->m_playfield.low_time= t - state->m_playfield.time;
    state->m_playfield.time=t;
    state->m_playfield.started=TRUE;
  }
  state->m_playfield.signal=signal;
}