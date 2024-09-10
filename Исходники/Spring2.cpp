void Spring2::apply(void)
    {
    Vector2 v = p1_->position() - p0_->position();
    float vlength = v.length();
    float forceMagnitude = springConstant_ * (vlength - restLength_);
    if (vlength > 0)
        v /= vlength;
    Vector2 f = v * forceMagnitude;
    p0_->applyForce(f);
    p1_->applyForce(-f);
    Vector2 dv = p1_->velocity() - p0_->velocity();
    f = damping_ * dv.dot(v) * v;
    p0_->applyForce(f);
    p1_->applyForce(-f);
    }