double area_vis(Shape& shape)
{
    struct Visitor : ShapeVisitor
    {
	    virtual void visit(const Circle& s)   { result = 3.14 * s.radius * s.radius; }
	    virtual void visit(const Square& s)   { result = s.side * s.side; }
	    virtual void visit(const Triangle& s) { result = heron(s.first,s.second,s.third); }
        double result;
    };

    Visitor v;
    shape.accept(v);
    return v.result;
}