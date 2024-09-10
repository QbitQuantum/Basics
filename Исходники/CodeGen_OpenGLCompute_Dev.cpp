void CodeGen_OpenGLCompute_Dev::CodeGen_OpenGLCompute_C::add_kernel(Stmt s,
                                                                    Target target,
                                                                    const string &name,
                                                                    const vector<GPU_Argument> &args) {

    debug(2) << "Adding OpenGLCompute kernel " << name << "\n";
    cache.clear();

    if (target.os == Target::Android) {
        stream << "#version 310 es\n"
               << "#extension GL_ANDROID_extension_pack_es31a : require\n";
    } else {
        stream << "#version 430\n";
    }
    stream << "float float_from_bits(int x) { return intBitsToFloat(int(x)); }\n";

    for (size_t i = 0; i < args.size(); i++) {
        if (args[i].is_buffer) {
            //
            // layout(binding = 10) buffer buffer10 {
            //     vec3 data[];
            // } inBuffer;
            //
            stream << "layout(binding=" << i << ")"
                   << " buffer buffer" << i << " { "
                   << print_type(args[i].type) << " data[]; } "
                   << print_name(args[i].name) << ";\n";
        } else {
            stream << "uniform " << print_type(args[i].type)
                   << " " << print_name(args[i].name) << ";\n";
        }
    }

    // Find all the shared allocations and declare them at global scope.
    FindSharedAllocations fsa;
    s.accept(&fsa);
    for (const Allocate *op : fsa.allocs) {
        internal_assert(op->extents.size() == 1 && is_const(op->extents[0]));
        stream << "shared "
               << print_type(op->type) << " "
               << print_name(op->name) << "["
               << op->extents[0] << "];\n";
    }

    // We'll figure out the workgroup size while traversing the stmt
    workgroup_size[0] = 0;
    workgroup_size[1] = 0;
    workgroup_size[2] = 0;

    stream << "void main()\n{\n";
    indent += 2;
    print(s);
    indent -= 2;
    stream << "}\n";

    // Declare the workgroup size.
    indent += 2;
    stream << "layout(local_size_x = " << workgroup_size[0];
    if (workgroup_size[1] > 1) { stream << ", local_size_y = " << workgroup_size[1]; }
    if (workgroup_size[2] > 1) { stream << ", local_size_z = " << workgroup_size[2]; }
    stream << ") in;\n// end of kernel " << name << "\n";
}