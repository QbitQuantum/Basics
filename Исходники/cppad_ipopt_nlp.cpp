/*!
Evaluate the objective fucntion f(x).

\param[in] n
is the dimension of the argument space for f(x); i.e., must be equal \c n_.

\param[in] x
is a vector of size \c n containing the point at which to evaluate
the function f(x).

\param[in] new_x
is false if the previous call to any one of the 
\ref Evaluation_Methods used the same value for \c x.

\param[out] obj_value
is the value of the objective f(x) at this value of \c x.

\return
The return value is always true; see \ref Evaluation_Methods.

\par Efficiency
This routine could be more efficient 
(for certain when when L[k] > 1 and retape[k] is true)
if the users also provided a version 
of the function <tt>fg_info->eval_r(k, u)</tt> where \c u was of type
\c NumberVector.
*/
bool cppad_ipopt_nlp::eval_f(
	Index n, const Number* x, bool new_x, Number& obj_value
)
{
	CPPAD_ASSERT_UNKNOWN(size_t(n) == n_ );

	size_t iobj, j, k, ell;

	// initialize summation
	obj_value = 0.;

	// update tape_ok_ flag
	for(k = 0; k < K_; k++) 
	{	if( retape_[k] && (new_x || L_[k] > 1) )
			tape_ok_[k] = false;
	}

	for(k = 0; k < K_; k++) for(ell = 0; ell < L_[k]; ell++)
	{	fg_info_->index(k, ell, I_, J_);
		for(iobj = 0; iobj < p_[k]; iobj++) if( I_[iobj] == 0 )
		{	if( ! tape_ok_[k] )
			{	// Record r_k for value of u corresponding to x
				fun_record(
					fg_info_        ,   // inputs
					k               ,
					p_              ,
					q_              ,
					n_              ,
					x               ,
					J_              ,
					r_fun_             // output
				);
				tape_ok_[k] = ! (retape_[k] || L_[k] > 1);
			}
			NumberVector u(q_[k]);
			NumberVector r(p_[k]);
			for(j = 0; j < q_[k]; j++)
			{	CPPAD_ASSERT_UNKNOWN( J_[j] < n_ );
				u[j]   = x[ J_[j] ];
			}
			r          = r_fun_[k].Forward(0, u);
			obj_value += r[iobj];
		}
	}
# if CPPAD_IPOPT_NLP_TRACE
	using std::printf;
	for(j = 0; j < n_; j++)
		printf("cppad_ipopt_nlp::eval_f::x[%d] = %20.14g\n", j, x[j]);
	printf("cppad_ipopt_nlp::eval_f::obj_value = %20.14g\n", obj_value);
# endif
# ifndef NDEBUG
	CPPAD_ASSERT_KNOWN(
		(-infinity_ < obj_value) && (obj_value < infinity_),
		"cppad_ipopt_nlp::eval_f:: objective value is not finite"
	);
# endif
	return true;
}