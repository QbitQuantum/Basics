void lae_graphics_present(lae_graphics_t* device)
{
    SwapBuffers(device->dc);
    UNUSED_PARAMETER(device);
}