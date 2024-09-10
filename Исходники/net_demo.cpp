/**
 * Stop recording a demo.
 */
void Demo_StopRecording(int playerNum)
{
    client_t       *cl = clients + playerNum;

    // A demo is not being recorded?
    if(!cl->recording)
        return;

    // Close demo file.
    lzClose(cl->demo);
    cl->demo = 0;
    cl->recording = false;
}