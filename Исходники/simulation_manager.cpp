void
nest::SimulationManager::update_()
{
  // to store done values of the different threads
  std::vector< bool > done;
  bool done_all = true;
  delay old_to_step;
  exit_on_user_signal_ = false;

  std::vector< lockPTR< WrappedThreadException > > exceptions_raised(
    kernel().vp_manager.get_num_threads() );
  bool exception_raised = false; // none raised on any thread

// parallel section begins
#pragma omp parallel
  {
    const int thrd = kernel().vp_manager.get_thread_id();

    do
    {
      if ( print_time_ )
      {
        gettimeofday( &t_slice_begin_, NULL );
      }

      if ( kernel().sp_manager.is_structural_plasticity_enabled()
        && ( clock_.get_steps() + from_step_ )
            % kernel().sp_manager.get_structural_plasticity_update_interval()
          == 0 )
      {
        for ( std::vector< Node* >::const_iterator i =
                kernel().node_manager.get_nodes_on_thread( thrd ).begin();
              i != kernel().node_manager.get_nodes_on_thread( thrd ).end();
              ++i )
        {
          ( *i )->update_synaptic_elements(
            Time( Time::step( clock_.get_steps() + from_step_ ) ).get_ms() );
        }
#pragma omp barrier
#pragma omp single
        {
          kernel().sp_manager.update_structural_plasticity();
        }
        // Remove 10% of the vacant elements
        for ( std::vector< Node* >::const_iterator i =
                kernel().node_manager.get_nodes_on_thread( thrd ).begin();
              i != kernel().node_manager.get_nodes_on_thread( thrd ).end();
              ++i )
        {
          ( *i )->decay_synaptic_elements_vacant();
        }
      }


      if ( from_step_ == 0 ) // deliver only at beginning of slice
      {
        kernel().event_delivery_manager.deliver_events( thrd );
#ifdef HAVE_MUSIC
// advance the time of music by one step (min_delay * h) must
// be done after deliver_events_() since it calls
// music_event_out_proxy::handle(), which hands the spikes over to
// MUSIC *before* MUSIC time is advanced

// wait until all threads are done -> synchronize
#pragma omp barrier
// the following block is executed by the master thread only
// the other threads are enforced to wait at the end of the block
#pragma omp master
        {
          // advance the time of music by one step (min_delay * h) must
          // be done after deliver_events_() since it calls
          // music_event_out_proxy::handle(), which hands the spikes over to
          // MUSIC *before* MUSIC time is advanced
          if ( slice_ > 0 )
          {
            kernel().music_manager.advance_music_time();
          }

          // the following could be made thread-safe
          kernel().music_manager.update_music_event_handlers(
            clock_, from_step_, to_step_ );
        }
// end of master section, all threads have to synchronize at this point
#pragma omp barrier
#endif
      }

      // preliminary update of nodes that use waveform relaxtion
      if ( kernel().node_manager.wfr_is_used() )
      {
#pragma omp single
        {
          // if the end of the simulation is in the middle
          // of a min_delay_ step, we need to make a complete
          // step in the wfr_update and only do
          // the partial step in the final update
          // needs to be done in omp single since to_step_ is a scheduler
          // variable
          old_to_step = to_step_;
          if ( to_step_ < kernel().connection_manager.get_min_delay() )
          {
            to_step_ = kernel().connection_manager.get_min_delay();
          }
        }

        bool max_iterations_reached = true;
        const std::vector< Node* >& thread_local_wfr_nodes =
          kernel().node_manager.get_wfr_nodes_on_thread( thrd );
        for ( long n = 0; n < wfr_max_iterations_; ++n )
        {
          bool done_p = true;

          // this loop may be empty for those threads
          // that do not have any nodes requiring wfr_update
          for ( std::vector< Node* >::const_iterator i =
                  thread_local_wfr_nodes.begin();
                i != thread_local_wfr_nodes.end();
                ++i )
          {
            done_p = wfr_update_( *i ) && done_p;
          }

// add done value of thread p to done vector
#pragma omp critical
          done.push_back( done_p );
// parallel section ends, wait until all threads are done -> synchronize
#pragma omp barrier

// the following block is executed by a single thread
// the other threads wait at the end of the block
#pragma omp single
          {
            // set done_all
            for ( size_t i = 0; i < done.size(); i++ )
            {
              done_all = done[ i ] && done_all;
            }

            // gather SecondaryEvents (e.g. GapJunctionEvents)
            kernel().event_delivery_manager.gather_events( done_all );

            // reset done and done_all
            //(needs to be in the single threaded part)
            done_all = true;
            done.clear();
          }

          // deliver SecondaryEvents generated during wfr_update
          // returns the done value over all threads
          done_p = kernel().event_delivery_manager.deliver_events( thrd );

          if ( done_p )
          {
            max_iterations_reached = false;
            break;
          }
        } // of for (wfr_max_iterations) ...

#pragma omp single
        {
          to_step_ = old_to_step;
          if ( max_iterations_reached )
          {
            std::string msg = String::compose(
              "Maximum number of iterations reached at interval %1-%2 ms",
              clock_.get_ms(),
              clock_.get_ms() + to_step_ * Time::get_resolution().get_ms() );
            LOG( M_WARNING, "SimulationManager::wfr_update", msg );
          }
        }

      } // of if(wfr_is_used)
      // end of preliminary update

      const std::vector< Node* >& thread_local_nodes =
        kernel().node_manager.get_nodes_on_thread( thrd );
      for (
        std::vector< Node* >::const_iterator node = thread_local_nodes.begin();
        node != thread_local_nodes.end();
        ++node )
      {
        // We update in a parallel region. Therefore, we need to catch
        // exceptions here and then handle them after the parallel region.
        try
        {
          if ( not( *node )->is_frozen() )
          {
            ( *node )->update( clock_, from_step_, to_step_ );
          }
        }
        catch ( std::exception& e )
        {
          // so throw the exception after parallel region
          exceptions_raised.at( thrd ) = lockPTR< WrappedThreadException >(
            new WrappedThreadException( e ) );
        }
      }

// parallel section ends, wait until all threads are done -> synchronize
#pragma omp barrier

// the following block is executed by the master thread only
// the other threads are enforced to wait at the end of the block
#pragma omp master
      {
        // check if any thread in parallel section raised an exception
        for ( index thrd = 0; thrd < kernel().vp_manager.get_num_threads();
              ++thrd )
        {
          if ( exceptions_raised.at( thrd ).valid() )
          {
            exception_raised = true;
            break;
          }
        }

        // gather only at end of slice
        if ( to_step_ == kernel().connection_manager.get_min_delay() )
        {
          kernel().event_delivery_manager.gather_events( true );
        }

        advance_time_();

        if ( SLIsignalflag != 0 )
        {
          LOG( M_INFO,
            "SimulationManager::update",
            "Simulation exiting on user signal." );
          exit_on_user_signal_ = true;
        }

        if ( print_time_ )
        {
          gettimeofday( &t_slice_end_, NULL );
          print_progress_();
        }
      }
// end of master section, all threads have to synchronize at this point
#pragma omp barrier

    } while (
      to_do_ > 0 and not exit_on_user_signal_ and not exception_raised );

    // End of the slice, we update the number of synaptic elements
    for ( std::vector< Node* >::const_iterator i =
            kernel().node_manager.get_nodes_on_thread( thrd ).begin();
          i != kernel().node_manager.get_nodes_on_thread( thrd ).end();
          ++i )
    {
      ( *i )->update_synaptic_elements(
        Time( Time::step( clock_.get_steps() + to_step_ ) ).get_ms() );
    }

  } // end of #pragma parallel omp

  // check if any exceptions have been raised
  for ( index thrd = 0; thrd < kernel().vp_manager.get_num_threads(); ++thrd )
  {
    if ( exceptions_raised.at( thrd ).valid() )
    {
      simulating_ = false; // must mark this here, see #311
      inconsistent_state_ = true;
      throw WrappedThreadException( *( exceptions_raised.at( thrd ) ) );
    }
  }
}