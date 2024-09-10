        void VectorizerVisitorExpression::visit(const Nodecl::Div& n)
        {
            walk(n.get_lhs());
            walk(n.get_rhs());

            const Nodecl::VectorDiv vector_div =
                Nodecl::VectorDiv::make(
                        n.get_lhs().shallow_copy(),
                        n.get_rhs().shallow_copy(),
                        get_qualified_vector_to(n.get_type(), _vector_length),
                        n.get_locus());

            n.replace(vector_div);
        }