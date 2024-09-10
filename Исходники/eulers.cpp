void test_frame_transforms(void)
{
    Vector3f v, v2;
    Quaternion q;
    Matrix3f m;

    hal.console->println("frame transform tests\n");

    q.from_euler(ToRad(45), ToRad(45), ToRad(45));
    q.normalize();
    m.from_euler(ToRad(45), ToRad(45), ToRad(45));

    v2 = v = Vector3f(0, 0, 1);
    q.earth_to_body(v2);
    hal.console->printf("%f %f %f\n", v2.x, v2.y, v2.z);
    v2 = m * v;
    hal.console->printf("%f %f %f\n\n", v2.x, v2.y, v2.z);

    v2 = v = Vector3f(0, 1, 0);
    q.earth_to_body(v2);
    hal.console->printf("%f %f %f\n", v2.x, v2.y, v2.z);
    v2 = m * v;
    hal.console->printf("%f %f %f\n\n", v2.x, v2.y, v2.z);

    v2 = v = Vector3f(1, 0, 0);
    q.earth_to_body(v2);
    hal.console->printf("%f %f %f\n", v2.x, v2.y, v2.z);
    v2 = m * v;
    hal.console->printf("%f %f %f\n", v2.x, v2.y, v2.z);
}