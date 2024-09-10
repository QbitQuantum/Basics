bool LogReader::update(uint8_t &type)
{
    uint8_t hdr[3];
    if (::read(fd, hdr, 3) != 3) {
        return false;
    }
    if (hdr[0] != HEAD_BYTE1 || hdr[1] != HEAD_BYTE2) {
        printf("bad log header\n");
        return false;
    }

    if (hdr[2] == LOG_FORMAT_MSG) {
        struct log_Format &f = formats[num_formats];
        memcpy(&f, hdr, 3);
        if (::read(fd, &f.type, sizeof(f)-3) != sizeof(f)-3) {
            return false;
        }
        num_formats++;
        type = f.type;
        return true;
    }

    uint8_t i;
    for (i=0; i<num_formats; i++) {
        if (formats[i].type == hdr[2]) break;
    }
    if (i == num_formats) {
        return false;
    }
    const struct log_Format &f = formats[i];
    
    uint8_t data[f.length];
    memcpy(data, hdr, 3);
    if (::read(fd, &data[3], f.length-3) != f.length-3) {
        return false;
    }

    switch (f.type) {
    case LOG_MESSAGE_MSG: {
        struct log_Message msg;
        if(sizeof(msg) != f.length) {
            printf("Bad MESSAGE length\n");
            exit(1);
        }
        memcpy(&msg, data, sizeof(msg));
        if (strncmp(msg.msg, "ArduPlane", strlen("ArduPlane")) == 0) {
            vehicle = VEHICLE_PLANE;
            ::printf("Detected Plane\n");
        } else if (strncmp(msg.msg, "ArduCopter", strlen("ArduCopter")) == 0) {
            vehicle = VEHICLE_COPTER;
            ::printf("Detected Copter\n");
        } else if (strncmp(msg.msg, "APMRover2", strlen("APMRover2")) == 0) {
            vehicle = VEHICLE_ROVER;
            ::printf("Detected Rover\n");
        }
        break;
    }

    case LOG_IMU_MSG: {
        struct log_IMU msg;
        if(sizeof(msg) != f.length) {
            printf("Bad IMU length\n");
            exit(1);
        }
        memcpy(&msg, data, sizeof(msg));
        wait_timestamp(msg.timestamp);
        if (gyro_mask & 1) {
            ins.set_gyro(0, Vector3f(msg.gyro_x, msg.gyro_y, msg.gyro_z));
        }
        if (accel_mask & 1) {
            ins.set_accel(0, Vector3f(msg.accel_x, msg.accel_y, msg.accel_z));
        }
        break;
    }

    case LOG_IMU2_MSG: {
        struct log_IMU msg;
        if(sizeof(msg) != f.length) {
            printf("Bad IMU2 length\n");
            exit(1);
        }
        memcpy(&msg, data, sizeof(msg));
        wait_timestamp(msg.timestamp);
        if (gyro_mask & 2) {
            ins.set_gyro(1, Vector3f(msg.gyro_x, msg.gyro_y, msg.gyro_z));
        }
        if (accel_mask & 2) {
            ins.set_accel(1, Vector3f(msg.accel_x, msg.accel_y, msg.accel_z));
        }
        break;
    }

    case LOG_GPS_MSG: {
        struct log_GPS msg;
        if(sizeof(msg) != f.length) {
            printf("Bad GPS length\n");
            exit(1);
        }
        memcpy(&msg, data, sizeof(msg));
        wait_timestamp(msg.apm_time);
        gps->setHIL(msg.status==3?GPS::FIX_3D:GPS::FIX_NONE,
                    msg.apm_time,
                    msg.latitude*1.0e-7f, 
                    msg.longitude*1.0e-7f, 
                    msg.altitude*1.0e-2f,
                    msg.ground_speed*1.0e-2f, 
                    msg.ground_course*1.0e-2f, 
                    0, 
                    msg.num_sats);
        if (msg.status == 3 && ground_alt_cm == 0) {
            ground_alt_cm = msg.altitude;
        }
        rel_altitude = msg.rel_altitude*0.01f;
        break;
    }

    case LOG_SIMSTATE_MSG: {
        struct log_AHRS msg;
        if(sizeof(msg) != f.length) {
            printf("Bad SIMSTATE length\n");
            exit(1);
        }
        memcpy(&msg, data, sizeof(msg));
        wait_timestamp(msg.time_ms);
        sim_attitude = Vector3f(msg.roll*0.01f, msg.pitch*0.01f, msg.yaw*0.01f);
        break;
    }

    case LOG_BARO_MSG: {
        struct log_BARO msg;
        if(sizeof(msg) != f.length) {
            printf("Bad LOG_BARO length\n");
            exit(1);
        }
        memcpy(&msg, data, sizeof(msg));
        wait_timestamp(msg.timestamp);
        baro.setHIL(msg.pressure, msg.temperature*0.01f);
        break;
    }

    case LOG_PARAMETER_MSG: {
        struct log_Parameter msg;
        if(sizeof(msg) != f.length) {
            printf("Bad LOG_PARAMETER length\n");
            exit(1);
        }
        memcpy(&msg, data, sizeof(msg));
        set_parameter(msg.name, msg.value);
        break;        
    }
        

    default:
        if (vehicle == VEHICLE_PLANE) {
            process_plane(f.type, data, f.length);
        } else if (vehicle == VEHICLE_COPTER) {
            process_copter(f.type, data, f.length);
        }
        break;
    }

    type = f.type;

    return true;
}