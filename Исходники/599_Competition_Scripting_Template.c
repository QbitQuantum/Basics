//599 funcitons
void Autonomous599()
{
  while(true)
  {

    if((SensorValue[kill_sw] < 127)&& ENABLE_KILL_SWITCH) //kill button on robot is A/D port to save digital ports
    {

      if(script != no_script) // stop scripts by reinitializing
      {
        Initialize();
        bsingle_step_mode = false;
      }

      allMotorsOff();
      break;
    }
    Process_sensors(); // read and process sensors to get variables needed for functions

    Operator(); // read driver commands from joystick which are not under script control

    Select_autonomous_script();//call autonomous script based upon cortex input auto_select (in8) port status

    Run_scripts();// Runs the selected script from Select_autonomous_script() to get commnads from scripts

    //call core functions here that use commands from operator() and run_scripts() functions

    Core_functions();



  }//end while
}