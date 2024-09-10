Vector STriangle::Normal(void) {
    Vector ab = b.Minus(a), bc = c.Minus(b);
    return ab.Cross(bc);
}