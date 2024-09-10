static void deactivateHandle(SocketStreamHandle* handle)
{
    gActiveHandles.remove(handle->id());
}