Handle<Value> Expression::New(const Arguments& args)
{
    HandleScope scope;
    if (!args.IsConstructCall())
        return ThrowException(String::New("Cannot call constructor as function, you need to use 'new' keyword"));

    if (args[0]->IsExternal())
    {
        //std::clog << "external!\n";
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Expression* e = static_cast<Expression*>(ptr);
        e->Wrap(args.This());
        return args.This();
    }

    mapnik::expression_ptr e_ptr;
    try
    {
        if (args.Length() == 1 && args[0]->IsString()){
            e_ptr = mapnik::parse_expression(TOSTR(args[0]),"utf8");

        } else {
            return ThrowException(Exception::Error(
                                      String::New("invalid arguments: accepts a single argument of string type")));
        }
    }
    catch (std::exception const& ex)
    {
        return ThrowException(Exception::Error(
                                  String::New(ex.what())));
    }

    if (e_ptr)
    {
        Expression* e = new Expression();
        e->Wrap(args.This());
        e->this_ = e_ptr;
        return args.This();
    }
    else
    {
        return ThrowException(Exception::Error(
                                  String::New("unknown exception happened, please file bug")));
    }

    return Undefined();
}