    size_t collide(CircleShape &circle1, CircleShape &circle2, float dt, Contact *pxContacts, size_t numMaxContacts)
    {
        dt, numMaxContacts;

        float rR = circle1.GetRadius() + circle2.GetRadius();
        const Point2f &p1 = circle1.body.getPosition();
        const Point2f &p2 = circle2.body.getPosition();
        Point2f d = p2 - p1;
        float len = d.Length();
        if (len > rR)
        {
            return 0;
        }
        d.Normalize();
        
        pxContacts[0] = Contact(p1 + d * circle1.GetRadius(), p1 + d * (len - circle1.GetRadius()), &circle1.body, &circle2.body);
        return 1;
    }