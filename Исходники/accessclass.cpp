AccessClass::AccessClass(RubyValue className, RubyValue methodInfos, RubyValue signalInfos, RubyValue propertyInfos)
{
    setClassName(className.to<QByteArray>());
    protect([&] {
        rb_check_array_type(methodInfos);
        rb_check_array_type(signalInfos);
        rb_check_array_type(propertyInfos);
    });
    for (int i = 0; i < RARRAY_LEN(VALUE(methodInfos)); ++i) {
        RubyValue info = RARRAY_AREF(VALUE(methodInfos), i);
        auto nameSym = info.send("name");
        addMethod(nameSym.to<QByteArray>(),
                  nameSym.toID(),
                  info.send("params").to<QList<QByteArray>>());
    }
    for (int i = 0; i < RARRAY_LEN(VALUE(signalInfos)); ++i) {
        RubyValue info = RARRAY_AREF(VALUE(signalInfos), i);
        auto nameSym = info.send("name");
        addSignal(nameSym.to<QByteArray>(),
                  nameSym.toID(),
                  info.send("params").to<QList<QByteArray>>());
    }
    for (int i = 0; i < RARRAY_LEN(VALUE(propertyInfos)); ++i) {
        RubyValue info = RARRAY_AREF(VALUE(propertyInfos), i);
        addProperty(info.send("name").to<QByteArray>(),
                    info.send("getter").toID(),
                    info.send("setter").toID(),
                    Property::Flag::Readable | Property::Flag::Writable,
                    true,
                    info.send("notifier").toID());
    }
}