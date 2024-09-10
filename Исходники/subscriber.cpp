int ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
  int status = 0;

#ifdef OPENDDS_SAFETY_PROFILE
  TheServiceParticipant->configure_pool ();
#endif

  try
    {
      ACE_DEBUG((LM_INFO,"(%P|%t) %T subscriber main\n"));

      dpf = TheParticipantFactoryWithArgs(argc, argv);

      // let the Service_Participant (in above line) strip out -DCPSxxx parameters
      // and then get application specific parameters.
      parse_args (argc, argv);

      init_listener ();
      init_dcps_objects (0);
      init_dcps_objects (1);

      // Indicate that the subscriber is ready
      FILE* readers_ready = ACE_OS::fopen (sub_ready_filename.c_str (), ACE_TEXT("w"));
      if (readers_ready == 0)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT("(%P|%t) ERROR: Unable to create subscriber completed file\n")));
        }

      // Wait for the publisher to be ready
      FILE* writers_ready = 0;
      do
        {
          ACE_Time_Value small_time(0,250000);
          ACE_OS::sleep (small_time);
          writers_ready = ACE_OS::fopen (pub_ready_filename.c_str (), ACE_TEXT("r"));
        } while (0 == writers_ready);

      ACE_OS::fclose(readers_ready);
      ACE_OS::fclose(writers_ready);

      int expected
        = num_datawriters * num_instances_per_writer * num_samples_per_instance;

      FILE* writers_completed = 0;
      int timeout_writes = 0;

      while ( num_reads < expected)
        {
          // Get the number of the timed out writes from publisher so we
          // can re-calculate the number of expected messages. Otherwise,
          // the blocking timeout test will never exit from this loop.
          if (writers_completed == 0)
            {
              writers_completed = ACE_OS::fopen (pub_finished_filename.c_str (), ACE_TEXT("r"));
              if (writers_completed != 0)
                {
                  //writers_completed = ACE_OS::fopen (pub_finished_filename.c_str (), ACE_TEXT("r"));
                  std::fscanf (writers_completed, "%d\n", &timeout_writes);
                  expected -= timeout_writes;
                  ACE_DEBUG((LM_DEBUG,
                             ACE_TEXT ("(%P|%t) timed out writes %d, we expect %d\n"),
                             timeout_writes, expected));
                }

            }
          ACE_OS::sleep (1);
        }

      // Indicate that the subscriber is done
      FILE* readers_completed = ACE_OS::fopen (sub_finished_filename.c_str (), ACE_TEXT("w"));
      if (readers_completed == 0)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT("(%P|%t) ERROR: Unable to create subscriber completed file\n")));
        }

      // Wait for the publisher to finish
      while (writers_completed == 0)
        {
          ACE_Time_Value small_time(0,250000);
          ACE_OS::sleep (small_time);
          writers_completed = ACE_OS::fopen (pub_finished_filename.c_str (), ACE_TEXT("r"));
        }

      ACE_OS::fclose(readers_completed);
      ACE_OS::fclose(writers_completed);
    }
  catch (const TestException&)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT("(%P|%t) TestException caught in main (). ")));
      status = 1;
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Exception caught in main ():");
      status = 1;
    }

  try
    {
      for (int i = 0; i < 2; ++i)
      {
        if (! CORBA::is_nil (participant[i].in ()))
          {
            participant[i]->delete_contained_entities();
          }
        if (! CORBA::is_nil (dpf.in ()))
          {
            dpf->delete_participant(participant[i].in ());
          }
      }
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Exception caught in cleanup.");
      status = 1;
    }

  shutdown ();

  return status;
}