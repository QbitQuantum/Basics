void destroyPlayback()
{
    if(_device){
        while(true){
            bool done = true;
            for(int i=0; i<BufferCount; i++){
                if(_buffers[i].isUsed){
                    done = false;
                }else{
                    if(_buffers[i].header.dwFlags & WHDR_PREPARED){
                        waveOutUnprepareHeader(_device, &_buffers[i].header, sizeof(WAVEHDR));
                    }
                }
            }
            if(done){
                break;
            }else{
                Sleep(10);
            }
        }
        waveOutClose(_device);
    }
}