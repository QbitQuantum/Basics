bool ClientCartesianController::getPose(const int axis, Vector &x, Vector &o,
                                        Stamp *stamp)
{
    if (!connected)
        return false;

    Bottle command, reply;
    command.addVocab(IKINCARTCTRL_VOCAB_CMD_GET);
    command.addVocab(IKINCARTCTRL_VOCAB_OPT_POSE);
    command.addInt(axis);

    if (!portRpc.write(command,reply))
    {
        yError("unable to get reply from server!");
        return false;
    }

    if (reply.get(0).asVocab()==IKINCARTCTRL_VOCAB_REP_ACK)
    {
        if (Bottle *posePart=reply.get(1).asList())
        {
            x.resize(3);
            o.resize(posePart->size()-x.length());

            for (size_t i=0; i<x.length(); i++)
                x[i]=posePart->get(i).asDouble();

            for (size_t i=0; i<o.length(); i++)
                o[i]=posePart->get(x.length()+i).asDouble();

            if ((reply.size()>2) && (stamp!=NULL))
            {
                if (Bottle *stampPart=reply.get(2).asList())
                {
                    Stamp tmpStamp(stampPart->get(0).asInt(),
                                   stampPart->get(1).asDouble());

                    *stamp=tmpStamp;
                }
            }

            return true;
        }
    }

    return false;
}