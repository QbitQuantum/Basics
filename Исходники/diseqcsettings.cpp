// import old diseqc configuration into tree
bool convert_diseqc_db(void)
{
    MSqlQuery cquery(MSqlQuery::InitCon());
    cquery.prepare(
        "SELECT cardid, dvb_diseqc_type "
        "FROM capturecard"
        "WHERE dvb_diseqc_type IS NOT NULL AND "
        "      diseqcid IS NULL");

    // iterate through cards
    if (!cquery.exec())
        return false;

    MSqlQuery iquery(MSqlQuery::InitCon());
    iquery.prepare(
        "SELECT cardinputid,    diseqc_port, diseqc_pos, "
        "       lnb_lof_switch, lnb_lof_hi,  lnb_lof_lo  "
        "FROM cardinput "
        "WHERE cardinput.cardid = :CARDID");

    while (cquery.next())
    {
        uint cardid = cquery.value(0).toUInt();
        OLD_DISEQC_TYPES type = (OLD_DISEQC_TYPES) cquery.value(1).toUInt();

        DiSEqCDevTree    tree;
        DiSEqCDevDevice *root     = NULL;
        uint             add_lnbs = 0;
        DiSEqCDevLNB::dvbdev_lnb_t lnb_type =
            DiSEqCDevLNB::kTypeVoltageAndToneControl;

        // create root of tree
        switch (type)
        {
            case DISEQC_SINGLE:
            {
                // single LNB
                root = DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeLNB);
                break;
            }

            case DISEQC_MINI_2:
            {
                // tone switch + 2 LNBs
                root = DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeSwitch);
                DiSEqCDevSwitch *sw = dynamic_cast<DiSEqCDevSwitch*>(root);
                if (sw)
                {
                    sw->SetType(DiSEqCDevSwitch::kTypeTone);
                    sw->SetNumPorts(2);
                    add_lnbs = 2;
                }
                break;
            }

            case DISEQC_SWITCH_2_1_0:
            case DISEQC_SWITCH_2_1_1:
            {
                // 2 port diseqc + 2 LNBs
                root = DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeSwitch);
                DiSEqCDevSwitch *sw = dynamic_cast<DiSEqCDevSwitch*>(root);
                if (sw)
                {
                    sw->SetType(DiSEqCDevSwitch::kTypeDiSEqCCommitted);
                    sw->SetAddress(0x10);
                    sw->SetNumPorts(2);
                    add_lnbs = 2;
                }
                break;
            }

            case DISEQC_SWITCH_4_1_0:
            case DISEQC_SWITCH_4_1_1:
            {
                // 4 port diseqc + 4 LNBs
                root = DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeSwitch);
                DiSEqCDevSwitch *sw = dynamic_cast<DiSEqCDevSwitch*>(root);
                if (sw)
                {
                    sw->SetType(DiSEqCDevSwitch::kTypeDiSEqCCommitted);
                    sw->SetAddress(0x10);
                    sw->SetNumPorts(4);
                    add_lnbs = 4;
                }
                break;
            }

            case DISEQC_POSITIONER_1_2:
            {
                // non-usals positioner + LNB
                root = DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeRotor);
                DiSEqCDevRotor *rotor = dynamic_cast<DiSEqCDevRotor*>(root);
                if (rotor)
                {
                    rotor->SetType(DiSEqCDevRotor::kTypeDiSEqC_1_2);
                    add_lnbs = 1;
                }
                break;
            }

            case DISEQC_POSITIONER_X:
            {
                // usals positioner + LNB (diseqc_pos)
                root = DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeRotor);
                DiSEqCDevRotor *rotor = dynamic_cast<DiSEqCDevRotor*>(root);
                if (rotor)
                {
                    rotor->SetType(DiSEqCDevRotor::kTypeDiSEqC_1_3);
                    add_lnbs = 1;
                }
                break;
            }

            case DISEQC_POSITIONER_1_2_SWITCH_2:
            {
                // 10 port uncommitted switch + 10 LNBs
                root = DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeSwitch);
                DiSEqCDevSwitch *sw = dynamic_cast<DiSEqCDevSwitch*>(root);
                if (sw)
                {
                    sw->SetType(DiSEqCDevSwitch::kTypeDiSEqCUncommitted);
                    sw->SetNumPorts(10);
                    add_lnbs = 10;
                }
                break;
            }

            case DISEQC_SW21:
            {
                // legacy SW21 + 2 fixed lnbs
                root = DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeSwitch);
                DiSEqCDevSwitch *sw = dynamic_cast<DiSEqCDevSwitch*>(root);
                if (sw)
                {
                    sw->SetType(DiSEqCDevSwitch::kTypeLegacySW21);
                    sw->SetNumPorts(2);
                    add_lnbs = 2;
                    lnb_type = DiSEqCDevLNB::kTypeFixed;
                }
                break;
            }

            case DISEQC_SW64:
            {
                // legacy SW64 + 3 fixed lnbs
                root = DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeSwitch);
                DiSEqCDevSwitch *sw = dynamic_cast<DiSEqCDevSwitch*>(root);
                if (sw)
                {
                    sw->SetType(DiSEqCDevSwitch::kTypeLegacySW64);
                    sw->SetNumPorts(3);
                    add_lnbs = 3;
                    lnb_type = DiSEqCDevLNB::kTypeFixed;
                }
                break;
            }

            default:
            {
                LOG(VB_GENERAL, LOG_ERR, "Unknown DiSEqC device type " +
                        QString("%1 ignoring card %2").arg(type).arg(cardid));
                break;
            }
        }

        if (!root)
            continue;

        tree.SetRoot(root);

        // create LNBs
        for (uint i = 0; i < add_lnbs; i++)
        {
            DiSEqCDevLNB *lnb = dynamic_cast<DiSEqCDevLNB*>
                (DiSEqCDevDevice::CreateByType(
                    tree, DiSEqCDevDevice::kTypeLNB));
            if (lnb)
            {
                lnb->SetType(lnb_type);
                lnb->SetDescription(QString("LNB #%1").arg(i+1));
                if (!root->SetChild(i, lnb))
                    delete lnb;
            }
        }

        // save the tree to get real device ids
        tree.Store(cardid);

        // iterate inputs
        DiSEqCDevSettings set;
        iquery.bindValue(":CARDID", cardid);

        if (!iquery.exec())
            return false;

        while (iquery.next())
        {
            uint inputid = iquery.value(0).toUInt();
            uint port = iquery.value(1).toUInt();
            double pos = iquery.value(2).toDouble();
            DiSEqCDevLNB *lnb = NULL;

            // configure LNB and settings
            switch (type)
            {
                case DISEQC_SINGLE:
                    lnb = dynamic_cast<DiSEqCDevLNB*>(root);
                    break;

                case DISEQC_MINI_2:
                case DISEQC_SWITCH_2_1_0:
                case DISEQC_SWITCH_2_1_1:
                case DISEQC_SWITCH_4_1_0:
                case DISEQC_SWITCH_4_1_1:
                case DISEQC_SW21:
                case DISEQC_SW64:
                case DISEQC_POSITIONER_1_2_SWITCH_2:
                    lnb = dynamic_cast<DiSEqCDevLNB*>(root->GetChild(port));
                    set.SetValue(root->GetDeviceID(), port);
                    break;

                case DISEQC_POSITIONER_1_2:
                case DISEQC_POSITIONER_X:
                    lnb = dynamic_cast<DiSEqCDevLNB*>(root->GetChild(0));
                    set.SetValue(root->GetDeviceID(), pos);
                    break;

                default:
                    break;
            }

            // configure lnb
            if (lnb)
            {
                lnb->SetLOFSwitch(iquery.value(3).toUInt());
                lnb->SetLOFHigh(iquery.value(4).toUInt());
                lnb->SetLOFLow(iquery.value(5).toUInt());
            }

            // save settings
            set.Store(inputid);
        }

        // save any LNB changes
        tree.Store(cardid);

        // invalidate cached devices
        DiSEqCDev trees;
        trees.InvalidateTrees();
    }

    return true;
}