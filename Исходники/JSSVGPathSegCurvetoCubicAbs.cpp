JSValue* JSSVGPathSegCurvetoCubicAbs::getValueProperty(ExecState* exec, int token) const
{
    switch (token) {
    case XAttrNum: {
        SVGPathSegCurvetoCubicAbs* imp = static_cast<SVGPathSegCurvetoCubicAbs*>(impl());

        return jsNumber(imp->x());
    }
    case YAttrNum: {
        SVGPathSegCurvetoCubicAbs* imp = static_cast<SVGPathSegCurvetoCubicAbs*>(impl());

        return jsNumber(imp->y());
    }
    case X1AttrNum: {
        SVGPathSegCurvetoCubicAbs* imp = static_cast<SVGPathSegCurvetoCubicAbs*>(impl());

        return jsNumber(imp->x1());
    }
    case Y1AttrNum: {
        SVGPathSegCurvetoCubicAbs* imp = static_cast<SVGPathSegCurvetoCubicAbs*>(impl());

        return jsNumber(imp->y1());
    }
    case X2AttrNum: {
        SVGPathSegCurvetoCubicAbs* imp = static_cast<SVGPathSegCurvetoCubicAbs*>(impl());

        return jsNumber(imp->x2());
    }
    case Y2AttrNum: {
        SVGPathSegCurvetoCubicAbs* imp = static_cast<SVGPathSegCurvetoCubicAbs*>(impl());

        return jsNumber(imp->y2());
    }
    }
    return 0;
}