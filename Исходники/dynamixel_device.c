// radians [-pi, pi]
// speedfrac [0,1]
// torquefrac [0,1]
void
dynamixel_set_joint_goal_default(dynamixel_device_t *device,
                                 int pmask,
                                 double radians,
                                 double speedfrac,
                                 double torquefrac)
{
    assert (!device->rotation_mode && (pmask == 0xfff || pmask == 0x3ff));

    // Ensure proper ranges
    radians = mod2pi(radians);
    speedfrac = dmax(0.0, dmin(1.0, dabs(speedfrac)));
    torquefrac = dmax(0.0, dmin(1.0, torquefrac));

    double min = device->get_min_position_radians(device);
    double max = device->get_max_position_radians(device);
    radians = dmax(min, dmin(max, radians));

    int stop = speedfrac < (1.0/0x3ff);

    int posv = ((int) round((radians - min) / (max - min) * pmask)) & pmask;
    // in joint-mode, speed == 0 --> maxspeed
    int speedv = stop ? 0x1 : (int)(speedfrac * 0x3ff);
    int torquev = (int)(torquefrac * 0x3ff);

    dynamixel_msg_t *msg = dynamixel_msg_create(7);
    msg->buf[0] = 0x1e;
    msg->buf[1] = posv & 0xff;
    msg->buf[2] = (posv >> 8) & 0xff;
    msg->buf[3] = speedv & 0xff;
    msg->buf[4] = (speedv >> 8) & 0xff;
    msg->buf[5] = torquev & 0xff;
    msg->buf[6] = (torquev >> 8) & 0xff;
    dynamixel_msg_t *resp = device->write_to_RAM(device, msg, 1);

    dynamixel_msg_destroy(msg);
    if (resp != NULL);
        dynamixel_msg_destroy(resp);

    // Handle speed == 0 case (after slowing down, above) by relaying current
    // position back to servo. Do not set torque == 0, b/c that is possibly not
    // desired...
    if (stop) {
        msg = dynamixel_msg_create(2);
        msg->buf[0] = 0x24;
        msg->buf[1] = 2;
        resp = device->bus->send_command(device->bus,
                                         device->id,
                                         INST_READ_DATA,
                                         msg,
                                         1);
        dynamixel_msg_destroy(msg);
        if (resp != NULL) {
            dynamixel_msg_destroy(resp);
            posv = (resp->buf[1] & 0xff) + ((resp->buf[2] & 0xff) << 8);
            msg = dynamixel_msg_create(3);
            msg->buf[0] = 0x1e;
            msg->buf[1] = posv & 0xff;
            msg->buf[2] = (posv > 8) & 0xff;
            resp = device->write_to_RAM(device, msg, 1);
        }

        if (resp != NULL)
            dynamixel_msg_destroy(resp);
    }
}