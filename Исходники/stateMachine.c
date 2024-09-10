/*
 * State Machine Procedure
 */
void sm_run(void) {

    /* 
     * STANDBY STATE 
     * The system starts by this state and wait command to Turn on (b_On = 1)
     */
    if (us_State == 1U) 
    {
        /* If system is ON */
        if (b_On == 1U) 
        {
            /* Change State to IBIT */
            us_State = 2U;
        }
        /* If emergency active */
        if (b_Emergency == 1U) 
        {
            /* Show Emergency Alert */
            /* (" --EMERGENCY ACTIVATED-- ") */
        }
    }
        /* 
         * The system check the state
         */
    else 
    {
        /* 
         * OPERATIONAL STATE
         */
        if (us_State == 7U) 
        {
            /* If operational ON */
            if (b_Operational == 1U) 
            {
                /* Call OPERATIONAL state */
                operational(b_Fail);
            } 
            else 
            {
                /* Call to Close Panel */
                shutdown(b_Fail);

                /* If fail is active */
                if (b_Fail == 1U) 
                {
                    /* Return to Fail state */
                    us_State = 3U;
                } 
                else 
                {
                    /* Return to READY state */
                    us_State = 4U;
                }
            }

            /* Call Health Monitoring
             * return: state if changed */
            us_State = powerMonitoring(us_State);
        }
            /*
             * BIT STATE 
             */
        else if (us_State == 2U) 
        {
            /* Call Built-in Test */
            us_State = bit();

            /* Call Health Monitoring
             * return: state if changed */
            us_State = powerMonitoring(us_State);
        }
            /*
             * FAIL STATE 
             */
        else if (us_State == 3U) 
        {
            /* Alert system to FAIL */
            b_Fail = 1U;

            /* If system is ON */
            if (b_On == 0U) 
            {
                /*Change State to STANDBY*/
                us_State = 1U;
            }

            if (b_Operational == 1U) 
            {
                /* Change State to OPERATIONAL REDUCED */
                us_State = 7U;

                /* Initialize operational variables */
                operational_init();
            }

            /* Call Health Monitoring
             * return: state if changed */
            us_State = powerMonitoring(us_State);
        }
            /*
             * READY STATE 
             */
        else if (us_State == 4U) 
        {
            /* If system is ON */
            if (b_On == 0U) 
            {
                /*Change State to STANDBY*/
                us_State = 1U;
            }

            if (b_Maintenance == 1U) 
            {
                /*Change State to MAINTENANCE*/
                us_State = 6U;
            }

            if (b_Operational == 1U) 
            {
                /*Change State to Operational*/
                us_State = 7U;

                /* Initialize operational variables */
                operational_init();
            }

            /* Call Health Monitoring
             * return: state if changed */
            us_State = powerMonitoring(us_State);
        }
            /*
             * MAINTENANCE STATE 
             */
        else if (us_State == 6U) 
        {
            /* If maintenance active */
            if (b_Maintenance == 0U) 
            {
                /* Call to Close Panel */
                shutdown(b_Fail);

                /* Change State to READY */
                us_State = 4U;
            } 
            else {
                /* State MAINTENANCE */
                maintenance();
            }

            /* Call Health Monitoring
             * return: state if changed */
            us_State = powerMonitoring(us_State);
        } else 
        {
            /*
             * EMERGENCY STATE 
             */
            if (us_State == 9U) 
            {
                /* System Turn OFF */
                b_On = 0U;

                /* Set FAIL Alert to OFF */
                b_Fail = 0U;

                /* Change state to STANDBY */
                us_State = 1U;

                /* Emergency Active */
                b_Emergency = 1U;

                /* Operational OFF */
                b_Operational = 0U;

                /* Shutdown System Safely */
                shutdown(b_Fail);
            }
        }
    }
}