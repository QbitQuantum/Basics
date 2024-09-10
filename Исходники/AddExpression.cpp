//						=======================
ExprResult				AddExpression::Evaluate
//						======================= 
(
	Context&			context
) const
{
	// Create a result, and initialise its type as error.
	ExprResult result( m_strPrecision );
	result.SetStatus( ExprResult::UNDEF_STATUS );

	// Evaluate the two operands of the addition expression.
	ExprResult left	 = m_pOperand1->Evaluate( context );
	ExprResult right = m_pOperand2->Evaluate( context );

	// Convert any possible variable to its contents.
	left.ConvertFromVar( context );
	right.ConvertFromVar( context );

	// Check if both the operands were evaluated as OK.
	if ( left.IsOK() && right.IsOK() )
	{
		// Check if both operands have either an arithmetic type or type
		// UNSPECIFIED which can be interpreted as an arithmetic type.
		if ( ( left.IsNumber() || ( left.IsUnspecified() && left.InterpretAsNumber() ) )
			&& ( right.IsNumber() || ( right.IsUnspecified() && right.InterpretAsNumber() ) ) )
		{
			// The (numerical) values of both operands can be added.
			result = Add( left, right );
		}
		else
		{
			// The values of both operands can be concatenated.
			result = Concatenate( left, right );
		}
	}
	else
	{
		// Check if an error was found in the left operand.
		if ( !left.IsOK() )
		{
			// Set as status and value of the result, those of the left operand.
			result.SetStatus( left.GetStatus() );
			result.SetValue( left.GetValue() );
		}
		else
		{
			// Set as status and value of the result, those of the right operand.
			result.SetStatus( right.GetStatus() );
			result.SetValue( right.GetValue() );
		}
	}
	
	return result;
}