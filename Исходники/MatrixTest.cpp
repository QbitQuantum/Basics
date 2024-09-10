int
main(int /*argc*/, char** /*argv*/)
{
    // 
    // Test boost types, SWFMatrix design is rely on this.
    // 
    // Note: If any of the following tests fails, your boost library
    // is bogus or hasn't been installed properly.
    // 
    check_equals(sizeof(boost::int8_t),   1);
    check_equals(sizeof(boost::uint8_t),  1);
    check_equals(sizeof(boost::int16_t),  2);
    check_equals(sizeof(boost::uint16_t), 2);
    check_equals(sizeof(boost::int32_t),  4);
    check_equals(sizeof(boost::uint32_t), 4);
    check_equals(sizeof(boost::int64_t),  8);
    check_equals(sizeof(boost::uint64_t), 8);

    // 
    //  Test identity SWFMatrix.
    // 
    SWFMatrix identity; 
    check(identity.is_valid());
    check_equals(identity.get_x_scale(), 1);
    check_equals(identity.get_y_scale(), 1);
    check_equals(identity.get_rotation(), 0);
    check_equals(identity.get_x_translation(), 0);
    check_equals(identity.get_y_translation(), 0);

    check_equals(identity.invert(), identity);

    //
    // Test parameter setting and getting, interfaces for AS.
    //
    SWFMatrix m1;
    m1.set_scale_rotation(1, 3, 0);
    check_equals(m1.get_x_scale(), 1);
    check_equals(m1.get_y_scale(), 3);
    check_equals(m1.get_rotation(), 0);
    check_equals(m1.get_x_translation(), 0);
    check_equals(m1.get_y_translation(), 0);

    m1.set_scale(1.5, 2.5);
    check_equals(D(m1.get_x_scale()), 1.5);
    check_equals(D(m1.get_y_scale()), 2.5);
    check_equals(D(m1.get_rotation()), 0);
    check_equals(m1.get_x_translation(), 0);
    check_equals(m1.get_y_translation(), 0);

    m1.set_scale(34, 4);
    check_equals(D(m1.get_x_scale()), 34);
    check_equals(D(m1.get_y_scale()), 4);
    check_equals(D(m1.get_rotation()), 0);
    check_equals(m1.get_x_translation(), 0);
    check_equals(m1.get_y_translation(), 0);

    m1.set_scale_rotation(1, 1, 2);
    check_equals(D(m1.get_x_scale()), 1);
    check_equals(D(m1.get_y_scale()), 1);
    check_equals(D(m1.get_rotation()), 2);
    check_equals(m1.get_x_translation(), 0);
    check_equals(m1.get_y_translation(), 0);

    m1.set_x_scale(2);
    check_equals(D(m1.get_x_scale()), 2);
    check_equals(D(m1.get_y_scale()), 1);
    check_equals(D(m1.get_rotation()), 2);
    check_equals(m1.get_x_translation(), 0);
    check_equals(m1.get_y_translation(), 0);

    m1.set_scale(1, 2);
    check_equals(D(m1.get_x_scale()), 1);
    check_equals(D(m1.get_y_scale()), 2);
    check_equals(D(m1.get_rotation()), 2);
    check_equals(m1.get_x_translation(), 0);
    check_equals(m1.get_y_translation(), 0);

    m1.set_rotation(0);
    check_equals(D(m1.get_x_scale()), 1);
    check_equals(D(m1.get_y_scale()), 2);
    check_equals(D(m1.get_rotation()), 0);
    check_equals(m1.get_x_translation(), 0);
    check_equals(m1.get_y_translation(), 0);

    m1.set_translation(5, 6);
    check_equals(D(m1.get_x_scale()), 1);
    check_equals(D(m1.get_y_scale()), 2);
    check_equals(D(m1.get_rotation()), 0);
    check_equals(m1.get_x_translation(), 5);
    check_equals(m1.get_y_translation(), 6);

    m1.set_rotation(2);
    check_equals(D(m1.get_x_scale()), 1);
    check_equals(D(m1.get_y_scale()), 2);
    check_equals(D(m1.get_rotation()), 2);
    check_equals(m1.get_x_translation(), 5);
    check_equals(m1.get_y_translation(), 6);

    SWFMatrix m2;
    check_equals(D(m2.get_rotation()), 0);
    m2.set_x_scale(16);
    check_equals(D(m2.get_x_scale()), 16);
    check_equals(D(m2.get_y_scale()), 1);
    check_equals(D(m2.get_rotation()), 0);
    m2.set_x_scale(-16);
    check_equals(D(m2.get_x_scale()), 16);
    check_equals(D(m2.get_y_scale()), 1);
    check_equals(D(m2.get_rotation()), 3.14159);
    m2.set_x_scale(16);
    check_equals(D(m2.get_x_scale()), 16);
    check_equals(D(m2.get_y_scale()), 1);
    check_equals(D(m2.get_rotation()), 3.14159);
    m2.set_x_scale(16);
    m2.set_y_scale(-64);
    check_equals(D(m2.get_x_scale()), 16);
    check_equals(D(m2.get_y_scale()), 64);
    check_equals(D(m2.get_rotation()), 3.14159);
    m2.set_x_scale(16);
    m2.set_x_scale(-128);
    check_equals(D(m2.get_x_scale()), 128);
    check_equals(D(m2.get_y_scale()), 64);
    check_equals(D(m2.get_rotation()), 0);

    //
    // Test SWFMatrix concatenation
    //
    m1.concatenate_scale(2, 2);
    check_equals(D(m1.get_x_scale()), 2);
    check_equals(D(m1.get_y_scale()), 4);
    check_equals(D(m1.get_rotation()), 2);
    check_equals(m1.get_x_translation(), 5);
    check_equals(m1.get_y_translation(), 6);

    m1.concatenate_scale(3, 3);
    check_equals(D(m1.get_x_scale()), 6);
    check_equals(D(m1.get_y_scale()), 12);
    check_equals(D(m1.get_rotation()), 2);
    check_equals(m1.get_x_translation(), 5);
    check_equals(m1.get_y_translation(), 6);

    m1.concatenate_scale(2, 1);
    check_equals(D(m1.get_x_scale()), 12);
    check_equals(D(m1.get_y_scale()), 12);
    check_equals(D(m1.get_rotation()), 2);
    check_equals(m1.get_x_translation(), 5);
    check_equals(m1.get_y_translation(), 6);

    //
    // Test SWFMatrix transformations
    //
    point p1(0, 0);
    point p2(64, 64);
    point r;

    m1.set_identity();
    // Make a distance of 64 become a distance of 20 .. 
    m1.set_scale(20.0/64, 20.0/64);

    m1.transform(&r, p1);
    check_equals(r.x, 0);
    check_equals(r.y, 0);
   
    m1.transform(&r, p2);
    check_equals(r.x, 20);
    check_equals(r.y, 20);

    // Translate points to have the origin at 32,32
    // (coordinates expressed in prior-to-scaling SWFMatrix)
    m1.concatenate_translation(-32, -32);

    m1.transform(&r, p1);
    check_equals(r.x, -10);
    check_equals(r.y, -10);

    m1.transform(&r, p2);
    check_equals(r.x, 10);
    check_equals(r.y, 10);

    //  Apply a final scaling by 10 keeping the current origin 
    // (reached after translation)
    SWFMatrix final;
    final.set_scale(10, 10);