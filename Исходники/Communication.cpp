void Communication::on_stateCounterChanged(int value)
{
    if(value > 2){
        emit connectionLost(true);
        ///when connection is lost, try opening port
        /// after informing the user.
        openPort();
    }

    if(value == 0){
        emit connectionLost(false);
    }
}