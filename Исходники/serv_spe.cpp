void* Slave::SPEShuffler(void* p)
{
   Slave* self = ((Param5*)p)->serv_instance;
   string client_ip = ((Param5*)p)->client_ip;
   int client_port = ((Param5*)p)->client_ctrl_port;
   int client_data_port = ((Param5*)p)->client_data_port;
   string path = ((Param5*)p)->path;
   string localfile = ((Param5*)p)->filename;
   // int bucketnum = ((Param5*)p)->bucketnum;
   CGMP* gmp = ((Param5*)p)->gmp;
   string function = ((Param5*)p)->function;

   //set up data connection, for keep-alive purpose
   if (self->m_DataChn.connect(client_ip, client_data_port) < 0)
      return NULL;

   queue<Bucket>* bq = new queue<Bucket>;
   pthread_mutex_t* bqlock = new pthread_mutex_t;
   pthread_mutex_init(bqlock, NULL);
   pthread_cond_t* bqcond = new pthread_cond_t;
   pthread_cond_init(bqcond, NULL);
   int64_t* pendingSize = new int64_t;
   *pendingSize = 0;

   ((Param5*)p)->bq = bq;
   ((Param5*)p)->bqlock = bqlock;
   ((Param5*)p)->bqcond = bqcond;
   ((Param5*)p)->pending = pendingSize;

   pthread_t ex;
   pthread_create(&ex, NULL, SPEShufflerEx, p);
   pthread_detach(ex);

   // cout << "SPE Shuffler " << path << " " << localfile << " " << bucketnum << endl;

   while (true)
   {
      string speip;
      int speport;
      SectorMsg msg;
      int msgid;
      int r = gmp->recvfrom(speip, speport, msgid, &msg, false);

      // client releases the task or client has already been shutdown
      if (((r > 0) && (speip == client_ip) && (speport == client_port))
         || ((r < 0) && (!self->m_DataChn.isConnected(client_ip, client_data_port))))
      {
         Bucket b;
         b.totalnum = -1;
         b.totalsize = 0;
         pthread_mutex_lock(bqlock);
         bq->push(b);
         pthread_cond_signal(bqcond);
         pthread_mutex_unlock(bqlock);

         break;
      }

      if (r < 0)
         continue;

      if (*pendingSize > 256000000)
      {
         // too many incoming results, ask the sender to wait
         // the receiver buffer size threshold is set to 256MB. This prevents the shuffler from being overflowed
         // it also helps direct the traffic to less congested shuffler and leads to better load balance
         msg.setType(-msg.getType());
         gmp->sendto(speip, speport, msgid, &msg);
      }
      else
      {
         Bucket b;
         b.totalnum = *(int32_t*)(msg.getData() + 8);;
         b.totalsize = *(int32_t*)(msg.getData() + 12);
         b.src_ip = speip;
         b.src_dataport = *(int32_t*)msg.getData();
         b.session = *(int32_t*)(msg.getData() + 4);

         gmp->sendto(speip, speport, msgid, &msg);

         if (!self->m_DataChn.isConnected(speip, b.src_dataport))
            self->m_DataChn.connect(speip, b.src_dataport);

         pthread_mutex_lock(bqlock);
         bq->push(b);
         *pendingSize += b.totalsize;
         pthread_cond_signal(bqcond);
         pthread_mutex_unlock(bqlock);
      }
   }

   gmp->close();
   delete gmp;

   return NULL;
}