void wrap_send(boost::shared_ptr<message_queue> p_self, object buffer, unsigned int priority)
{
    Py_buffer pybuf = get_buffer(buffer);
    p_self->send(pybuf.buf, pybuf.len, priority);
}