void receiveMessages ()
{

  cleanBuffers ();

  do
    {

      if (! atLeastOneActiveThread ())
        {
          waitMessage ();
        }

      int src, tag;

      while (probeMessage (src, tag))
        {
          receiveMessage (src, tag);
          initMessage ();

          switch (tag)
            {

            case RUNNER_STOP_TAG:
              unpackTerminationOfRunner ();
              break;

            case SYNCHRONIZE_REQ_TAG:
              unpackSynchronRequest ();
              break;

            case SYNCHRONIZED_TAG:
            {
              RUNNER_ID runner_id;
              unpack (runner_id);

              COOP_ID coop_id;
              unpack (coop_id);

              getCooperative (coop_id) -> notifySynchronized ();
              break;
            }

            case COOP_TAG:
              COOP_ID coop_id;
              unpack (coop_id);
              getCooperative (coop_id) -> unpack ();
              getCooperative (coop_id) -> notifyReceiving ();
              break;

            case SCHED_REQUEST_TAG:
              unpackResourceRequest ();
              break;

            case SCHED_RESULT_TAG:
            {
              /* Unpacking the resource */
              SERVICE_ID serv_id;
              unpack (serv_id);
              Service * serv = getService (serv_id);
              int dest;
              unpack (dest);
              WORKER_ID worker_id;
              unpack (worker_id);

              /* Going back ... */
              initMessage ();
              pack (worker_id);
              pack (serv_id);
              serv -> packData ();
              serv -> notifySendingData ();
              sendMessage (dest, TASK_DATA_TAG);
              break;
            }

            case TASK_DATA_TAG:
            {
              WORKER_ID worker_id;
              unpack (worker_id);
              Worker * worker = getWorker (worker_id);
              worker -> setSource (src);
              worker -> unpackData ();
              worker -> wakeUp ();

              break;
            }

            case TASK_RESULT_TAG:
            {
              SERVICE_ID serv_id;
              unpack (serv_id);
              Service * serv = getService (serv_id);
              serv -> unpackResult ();
              break;
            }

            case TASK_DONE_TAG:
              unpackTaskDone ();
              break;

            default:
              ;
            };
        }

    }
  while ( ! atLeastOneActiveThread () && atLeastOneActiveRunner () /*&& ! allResourcesFree ()*/ );
}