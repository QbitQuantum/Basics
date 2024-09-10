// __glDrvOpenGLCmd
//   Stub OpenGLCmd routine. Can only get here before OpenGL driver is loaded.
//
// Synopsis:
//   BOOL __glDrvOpenGLCmd(SURFOBJ *pso,
//                         ULONG    cjIn,
//                         VOID    *pvIn,
//                         ULONG    cjOut,
//                         VOID    *pvOut)
ULONG __glDrvOpenGLCmd(SURFOBJ *pso,
                      ULONG    cjIn,
                      VOID    *pvIn,
                      ULONG    cjOut,
                      VOID    *pvOut)
{
    // Control should never get here. GDI
    // should have called DescribePixelFormat first,
    // which should have caused the driver to be loaded,
    // which should have caused ppdev->pOpenGLCmd to
    // be replaced by the real entry point in the
    // driver.

    DISPDBG ((0, "TGA!OPENGL_CMD called unexectedly - %d\n",
                     EngGetLastError()));
    return ESC_FAILURE;
}