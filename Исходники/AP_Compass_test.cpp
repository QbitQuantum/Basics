static void loop()
{
    static const uint8_t compass_count = compass.get_count();
    static float min[COMPASS_MAX_INSTANCES][3];
    static float max[COMPASS_MAX_INSTANCES][3];
    static float offset[COMPASS_MAX_INSTANCES][3];

    if ((AP_HAL::micros() - timer) > 100000L) {
        timer = AP_HAL::micros();
        compass.read();
        const uint32_t read_time = AP_HAL::micros() - timer;

        for (uint8_t i = 0; i < compass_count; i++) {
            float heading;

            hal.console->printf("Compass #%u: ", i);

            if (!compass.healthy()) {
                hal.console->printf("not healthy\n");
                continue;
            }

            Matrix3f dcm_matrix;
            // use roll = 0, pitch = 0 for this example
            dcm_matrix.from_euler(0, 0, 0);
            heading = compass.calculate_heading(dcm_matrix, i);

            const Vector3f &mag = compass.get_field(i);

            // capture min
            min[i][0] = MIN(mag.x, min[i][0]);
            min[i][1] = MIN(mag.y, min[i][1]);
            min[i][2] = MIN(mag.z, min[i][2]);

            // capture max
            max[i][0] = MAX(mag.x, max[i][0]);
            max[i][1] = MAX(mag.y, max[i][1]);
            max[i][2] = MAX(mag.z, max[i][2]);

            // calculate offsets
            offset[i][0] = -(max[i][0] + min[i][0]) / 2;
            offset[i][1] = -(max[i][1] + min[i][1]) / 2;
            offset[i][2] = -(max[i][2] + min[i][2]) / 2;

            // display all to user
            hal.console->printf("Heading: %.2f (%3d, %3d, %3d)",
                                (double)ToDeg(heading),
                                (int)mag.x,
                                (int)mag.y,
                                (int)mag.z);

            // display offsets
            hal.console->printf(" offsets(%.2f, %.2f, %.2f)",
                                (double)offset[i][0],
                                (double)offset[i][1],
                                (double)offset[i][2]);

            hal.console->printf(" t=%u", (unsigned)read_time);

            hal.console->printf("\n");
        }
    } else {
        hal.scheduler->delay(1);
    }
}