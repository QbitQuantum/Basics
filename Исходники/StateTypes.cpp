bool
StateType::Set( CommandInterpreter& inInterpreter )
{
  string name;
  State::ValueType value = 0;
  ostringstream oss;
  {
    Lock lock( inInterpreter.StateMachine() );
    State& state = GetState( inInterpreter );
    name = state.Name();
    value = ::atoi( inInterpreter.GetToken().c_str() );
    if( !inInterpreter.StateMachine().SetStateValue( name.c_str(), value ) )
      throw bciexception( "Could not set state " << name << " to " << value );
    // StateMachine::SetStateValue() does not set the value of the state object in its state list.
    state.SetValue( value );
    oss << state;
  }
  inInterpreter.StateMachine().ExecuteCallback( BCI_OnState, oss.str().c_str() );
  inInterpreter.Log() << "Set state " << name << " to " << value;
  return true;
}