 Operators get_symmetry_operators(size_t dim, const VectorF& center) {
     Operators ops;
     if (dim == 2) {
         Operators reflective_ops = generate_reflective_symmetry_operators<2>(center);
         Operators rotational_ops = generate_rotational_symmetry_operators<2>(center);
         ops.insert(ops.end(), reflective_ops.begin(), reflective_ops.end());
         ops.insert(ops.end(), rotational_ops.begin(), rotational_ops.end());
     } else if (dim == 3) {
         Operators reflective_ops = generate_reflective_symmetry_operators<3>(center);
         Operators rotational_ops = generate_rotational_symmetry_operators<3>(center);
         ops.insert(ops.end(), reflective_ops.begin(), reflective_ops.end());
         ops.insert(ops.end(), rotational_ops.begin(), rotational_ops.end());
     } else {
         throw NotImplementedError(
                 "Symmetry operations only supports 2D and 3D");
     }
     return ops;
 }