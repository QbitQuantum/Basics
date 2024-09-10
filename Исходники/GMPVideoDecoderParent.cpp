bool
GMPVideoDecoderParent::RecvShutdown()
{
    Shutdown();
    return true;
}