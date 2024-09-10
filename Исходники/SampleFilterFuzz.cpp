static SkPath make_path() {
    SkPath path;
    int numOps = R(30);
    for (int i = 0; i < numOps; ++i) {
        switch (R(6)) {
            case 0:
                path.moveTo(make_scalar(), make_scalar());
                break;
            case 1:
                path.lineTo(make_scalar(), make_scalar());
                break;
            case 2:
                path.quadTo(make_scalar(), make_scalar(), make_scalar(), make_scalar());
                break;
            case 3:
                path.conicTo(make_scalar(), make_scalar(), make_scalar(), make_scalar(), make_scalar());
                break;
            case 4:
                path.cubicTo(make_scalar(), make_scalar(), make_scalar(),
                             make_scalar(), make_scalar(), make_scalar());
                break;
            case 5:
            default:
                path.arcTo(make_scalar(), make_scalar(), make_scalar(), make_scalar(), make_scalar());
                break;

        }
    }
    path.close();
    return path;
}