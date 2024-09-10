// Here is where the real job is done
static PyObject*
ZBufferTo3D_recover(PyZBufferTo3D* self, PyObject* args)
{
    Py_buffer img_buffer;

    int i, pixel, npixels;
    double z_b;
    float z_n, z_e;
    float x, y;
    int u, v;
    float * fbuffer;

    // Read the incomming data as a buffer. It is originally a bgl.Buffer object
    if (!PyArg_ParseTuple(args, "w*", &img_buffer))
        return NULL;

    // check that there is no division by 0
    if (self->width == 0)
        return NULL;

    fbuffer = (float *) img_buffer.buf;
    npixels = img_buffer.len / 4; // rgba (sizeof float = 4B)

    for (i = 0, pixel = 0; pixel < npixels; pixel++)
    {
        z_b = fbuffer[pixel];
        if (z_b >= 1.0)
        {
            self->points[i] = nanf("");
            self->points[i+1] = nanf("");
            self->points[i+2] = nanf("");
            i += 3;
            continue; // nothing seen within the far clipping
        }


        z_n = 2.0 * z_b - 1.0;
        z_e = 2.0 * self->near * self->far / (self->far + self->near - z_n * (self->far - self->near));

        // The image we receive is stored as a single array of floats.
        // Pixel 0, 0 in the data is located at the bottom left, according to
        // the OpenGL conventions.
        // We need to convert this frame of reference to (u, v), starting at the
        // top left
        u = pixel % self->width;
        v = self->height - (pixel / self->width);

        // Use the intrinsic matrix of the camera view to get the 3D coordinates
        // corresponding to each pixel, with respect to the camera
        x = z_e * (u - self->u_0) / self->alpha_u;
        y = z_e * (v - self->v_0) / self->alpha_v;

        // Store the x, y, z coordinates in the buffer
        self->points[i] = x;
        self->points[i+1] = y;
        self->points[i+2] = z_e;
        i += 3;
    }

    // release the Python buffers
    PyBuffer_Release(&img_buffer);

    return PyMemoryView_FromMemory((char *)self->points, i*sizeof(float), PyBUF_READ);
}