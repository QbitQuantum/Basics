void BedroomSignalAdapter::
        run ()
{
    Bedroom::Bed bed = bedroom_->getBed();
    while (!stop_flag_) {
        DEBUGINFO TaskInfo("BedroomSignalAdapter wakeup");
        emit wakeup();

        try {
            bed.sleep ();
        } catch (const BedroomClosed&) {
            stop_flag_ = true;
        }
    }

    DEBUGINFO TaskInfo("BedroomSignalAdapter finished");
}