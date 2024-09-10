int spiSlaveRequest(uint8_t busId, const struct SpiMode *mode,
        struct SpiDevice **dev_out)
{
    int ret = 0;

    struct SpiDeviceState *state = heapAlloc(sizeof(*state));
    if (!state)
        return -ENOMEM;
    struct SpiDevice *dev = &state->dev;

    ret = spiRequest(dev, busId);
    if (ret < 0)
        goto err_request;

    if (!dev->ops->slaveIdle || !dev->ops->slaveRxTx) {
        ret = -EOPNOTSUPP;
        goto err_opsupp;
    }

    state->mode = *mode;
    state->err = 0;

    ret = spiSlaveStart(state, mode);
    if (ret < 0)
        goto err_opsupp;

    *dev_out = dev;
    return 0;

err_opsupp:
    if (dev->ops->release)
        dev->ops->release(dev);
err_request:
    heapFree(state);
    return ret;
}