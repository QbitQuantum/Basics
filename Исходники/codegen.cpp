std::string cpp_accessor_for_type(Type* type)
{
#if 0
    std::stringstream out;
    std::string indent = "    ";

    out << "struct " << get_cpp_type_name(type) << "\n";
    out << "{\n";
    out << indent << "Term* _term\n";
    out << "\n";
    out << indent << get_cpp_type_name(type) << "(Term* term) : _term(term) {}\n";
    out << "\n";

    Block* prototype = type->prototype;
    for (int i=0; i < prototype.length(); i++) {
        Term* field = prototype[i];
        out << indent << get_cpp_type_name(field->type) << "& " << field->name << "() ";
        out << "{ return " << get_cpp_type_accessor(field->type) << "(_term->field(" <<
            i << ")); }\n";
    }

    out << "};\n";
    return out.str();
#endif
    return "";
}