void 
LatencyPingerI::calcStats( const int objSize )
{
    // RRT values
    std::vector<double> rrt;
    int lostCount = 0;
    for ( int i=0; i<config_.count; ++i ) {
        if ( ids_[i] != -1 ) {
            IceUtil::Time dt = receives_[i] - sends_[i];
            if ( dt < IceUtil::Time() ) {
                std::cout<<i<<" : negative time! "<<std::endl;
            }
            rrt.push_back( dt.toSecondsDouble() / double(config_.preload) );

            // debug
            std::cout<<i<<" snd "<<sends_[i].toSeconds()<<":"<<sends_[i].toMicroSeconds()-sends_[i].toSeconds()*1000000
                        <<" rcv "<<receives_[i].toSeconds()<<":"<<receives_[i].toMicroSeconds()-receives_[i].toSeconds()*1000000
                        <<" rtt "<<rrt.back()<<" "<<std::endl;
            // debug
            //double dd = rrt.back();
            //std::cout<<"object "<<i<<" rtt: "<<rrt.back()<<"s "<<dd<<"s "<<1000.0*dd<<"ms"<<std::endl;
        }
        else {
            ++lostCount;
            //std::cout<<"object "<<i<<" was lost"<<std::endl;
        }
    }

    // check for empty vector
    if ( rrt.empty() ) {
        std::cout<<"No statistics. All packets lost?"<<std::endl;
        return;
    }

#ifdef WIN32
    // under windows, times under 1ms cannot be measured apparently
    for ( unsigned int i=0; i<rrt.size(); ++i ) {
        if ( rrt[i] == 0 ) {
            // set to sensing limit: 1ms
            rrt[i] = 1.0e-3;
        }
    }
#endif

    // find min / max RRT's
    double rrtmin = *(std::min_element( rrt.begin()+1, rrt.end() ));
    double rrtmax = *(std::max_element( rrt.begin()+1, rrt.end() ));
    // find average RRT
    double rrtavg = 0.0;
    // ignore the first result, it's always an outlier (because the Serializer is adjusting its size)
    for ( unsigned int i=1; i<rrt.size(); ++i ) {
        rrtavg += rrt[i];
    }
    rrtavg /= (rrt.size()-1);

    // print out results (ping style)
    std::cout<<"size "<<objSize<<" bytes"<<std::endl;
    std::cout<<config_.count<<" packets transmitted, "
            <<config_.count-lostCount<<" received, "
            <<(double)lostCount/(double)config_.count*100.00<<"% packet loss, time "<<"?"<<"ms"<<std::endl;

    std::cout<<"rtt min/avg/max/mdev = "
            <<rrtmin*1000.0<<"/"<<rrtavg*1000.0<<"/"<<rrtmax*1000.0<<"/? ms"<<std::endl<<std::endl;

    // log results
    *logfile_ <<objSize<<" "
            << (rrtmin*1000.0)<<" "<<(rrtavg*1000.0)<<" "<<(rrtmax*1000.0)<<" "<<-1.0;
    // log individual rrt's
    for ( unsigned int i=1; i<rrt.size(); ++i ) {
        *logfile_ << " " << rrt[i]*1000.0;
        // debug
        //std::cout<<rrt[i]<<" ";
    }
    for ( unsigned int i=0; i<(config_.count-rrt.size()); ++i ) {
        *logfile_<< " " << -1;
    }
    *logfile_ << std::endl;

    std::cout<<std::endl;
    std::cout<<std::endl;
   
}