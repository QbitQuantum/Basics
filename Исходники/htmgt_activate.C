    //Sends the user selected power limit to the master OCC
    errlHndl_t sendOccUserPowerCap()
    {
        errlHndl_t err = NULL;
        Target* sys = NULL;
        bool active = false;
        uint16_t limit = 0;
        uint16_t min = 0;
        uint16_t max = 0;
        targetService().getTopLevelTarget(sys);
        assert(sys != NULL);

        do
        {
#ifdef CONFIG_BMC_IPMI
            err = SENSOR::getUserPowerLimit(limit, active);
            if (err)
            {
                TMGT_ERR("sendOccUserPowerCap: Error getting user "
                         "power limit");
                break;
            }
#endif

            TMGT_INF("SENSOR::getUserPowerLimit returned %d, active = %d",
                     limit, active);

            if (active)
            {
                //Make sure this value is between the min & max allowed
                min = sys->getAttr<ATTR_OPEN_POWER_MIN_POWER_CAP_WATTS>();
                max = sys->
                  getAttr<ATTR_OPEN_POWER_N_PLUS_ONE_BULK_POWER_LIMIT_WATTS>();

                if ((limit != 0) && (limit < min))
                {
                    TMGT_INF("sendOccUserPowerCap:  User power cap %d is below"
                             " the minimum of %d, clipping value",
                             limit, min);
                    limit = min;
                }
                else if (limit > max)
                {
                    TMGT_INF("sendOccUserPowerCap:  User power cap %d is above"
                             " the maximum of %d, clipping value",
                             limit, min);
                    limit = max;
                }
            }
            else
            {
                //The OCC knows cap isn't active by getting a value of 0.
                limit = 0;
            }


            Occ* occ = occMgr::instance().getMasterOcc();
            if (occ)
            {
                uint8_t data[2];
                data[0] = limit >> 8;
                data[1] = limit & 0xFF;

                TMGT_INF("sendOccUserPowerCap:  Sending power cap %d to OCC %d",
                         limit, occ->getInstance());
                if (limit > 0)
                {
                    TMGT_CONSOLE("User power limit has been set to %dW",
                                 limit);
                }

                OccCmd cmd(occ, OCC_CMD_SET_POWER_CAP, 2, data);

                err = cmd.sendOccCmd();
                if (err)
                {
                    TMGT_ERR("sendOccUserPowerCap: Failed sending command "
                             "to OCC %d with rc = 0x%04X",
                             occ->getInstance(), err->reasonCode());
                    break;
                }
            }
            else
            {
                //Other code deals with a missing master
                TMGT_ERR("sendOccUserPowerCap: No Master OCC found");
            }

        } while (0);