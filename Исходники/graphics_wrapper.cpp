/**
 * Transfer our buffer into windows via StretchDIBits syscall.
 * @param *buffer A pointer to the buffer info struct. We use a pointer because
 *                it is a fairly big struct so that if the compiler doesn't inline
 *                the code, it would require a 'big' memory copy in the stack. So
 *                we send the pointer even though we do not modify the origin struct.
 */
internal void
Win32TransferBufferToWindows(HDC deviceContext,
                             win32_offscreen_buffer *buffer,
                             int windowWidth, int windowHeight)
{
  if((windowWidth >= 2 * buffer->width) &&
     (windowHeight >= 2 * buffer->height))
  {
    // If we can double stretch the buffer, we do it, because double-sampling
    // will not produce artifacts with StretchDIBits
    StretchDIBits(deviceContext,
                  /*
                  x, y, destWidth, destHeight,
                  x, y, originWidth, originHeight,
                  */
                  0, 0, 2 * buffer->width, 2 * buffer->height,
                  0, 0, buffer->width, buffer->height,
                  buffer->memory,
                  &buffer->info,
                  DIB_RGB_COLORS,
                  SRCCOPY);
  }
  else
  {
    int offsetX = 10;
    int offsetY = 10;

    // We have to clean the rectangles outside of our render target rectangle
    PatBlt(deviceContext, 0, 0, windowWidth, offsetY, BLACKNESS);
    PatBlt(deviceContext, 0, 0, offsetX, windowHeight, BLACKNESS);
    PatBlt(deviceContext, offsetX, offsetY + buffer->height,
                          windowWidth - offsetX, windowHeight - (offsetY + buffer->height),
                          BLACKNESS);
    PatBlt(deviceContext, offsetX + buffer->width, offsetY,
                          windowWidth - (offsetX + buffer->width), windowHeight - offsetY,
                          BLACKNESS);

    // NOTE(Cristián): For prototyping, we're are always going to blit 1-1 pixels
    // to make sure we don't introduce artifacts. This will change when the renderer
    // code is done.
    StretchDIBits(deviceContext,
                  /*
                  x, y, destWidth, destHeight,
                  x, y, originWidth, originHeight,
                  */
                  offsetX, offsetY, buffer->width, buffer->height,
                  0, 0, buffer->width, buffer->height,
                  buffer->memory,
                  &buffer->info,
                  DIB_RGB_COLORS,
                  SRCCOPY);
  }
}