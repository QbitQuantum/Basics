Handle<Value> Grid::view(const Arguments& args)
{
    HandleScope scope;

    if ( (args.Length() != 4) || (!args[0]->IsNumber() && !args[1]->IsNumber() && !args[2]->IsNumber() && !args[3]->IsNumber() ))
        return ThrowException(Exception::TypeError(
                                  String::New("requires 4 integer arguments: x, y, width, height")));

    unsigned x = args[0]->IntegerValue();
    unsigned y = args[1]->IntegerValue();
    unsigned w = args[2]->IntegerValue();
    unsigned h = args[3]->IntegerValue();

    Grid* g = ObjectWrap::Unwrap<Grid>(args.This());
    return scope.Close(GridView::New(g,x,y,w,h));
}