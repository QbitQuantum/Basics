QgsSqlExpressionCompiler::Result QgsDb2ExpressionCompiler::compileNode( const QgsExpressionNode *node, QString &result )
{
  QgsDebugMsg( QStringLiteral( "nodeType: %1" ).arg( nodeType( node ) ) );
  if ( node->nodeType() == QgsExpressionNode::ntColumnRef )
  {
    const QgsExpressionNodeColumnRef *n( static_cast<const QgsExpressionNodeColumnRef *>( node ) );
    QgsDebugMsg( QStringLiteral( "column ref node: " ) + n->dump() );
    // TODO - consider escaped names - not sure how to handle
    QString upperName = n->name().toUpper();
    int idx = mFields.indexFromName( upperName );
    QgsDebugMsg( QStringLiteral( "%1 - %2" ).arg( idx ).arg( upperName ) );
    if ( idx > -1 )
    {
      result = upperName;
      QgsDebugMsg( QStringLiteral( "return Complete" ) );
      return Complete;
    }
    QgsDebugMsg( QStringLiteral( "return Fail" ) );
    return Fail;
  }
// Seemed necessary in initial Python testing but can't identify failing case now
#if 0
  if ( node->nodeType() == QgsExpressionNode::ntLiteral )
  {
    const QgsExpression::NodeLiteral *n = static_cast<const QgsExpression::NodeLiteral *>( node );

    bool ok = false;
    if ( n->dump().toUpper() == "NULL" ) // expression compiler doesn't handle this correctly
    {
      result = "NULL";
      ok = true;
    }
    else
    {
      result = quotedValue( n->value(), ok );
    }
    QgsDebugMsg( QStringLiteral( "ok: %1; literal node: " ).arg( ok ) + n->value().toString() + "; result: " + result );
    QgsDebugMsg( QStringLiteral( "n->dump: " ) + n->dump() );
    QgsDebugMsg( QStringLiteral( "type: %1; typeName: %2" ).arg( n->value().type() ).arg( n->value().typeName() ) );
    if ( ok )
    {
      QgsDebugMsg( QStringLiteral( "return Complete" ) );
      return Complete;
    }
    else
    {
      QgsDebugMsg( QStringLiteral( "return Fail" ) );
      return Fail;
    }

  }
#endif
  if ( node->nodeType() == QgsExpressionNode::ntUnaryOperator )
  {
    const QgsExpressionNodeUnaryOperator *n = static_cast<const QgsExpressionNodeUnaryOperator *>( node );
    Result rr = Fail;
    switch ( n->op() )
    {
      case QgsExpressionNodeUnaryOperator::uoNot:
        rr = compileNode( n->operand(), result );
        if ( "NULL" == result.toUpper() )
        {
          result.clear();
          return Fail;
        }

        result = "NOT " + result;
        QgsDebugMsg( QStringLiteral( "NOT; result: %1; right: %2" ).arg( resultType( rr ), result ) );
        return rr;

      case QgsExpressionNodeUnaryOperator::uoMinus:
        break;
    }
  }

  if ( node->nodeType() == QgsExpressionNode::ntBinaryOperator )
  {
    const QgsExpressionNodeBinaryOperator *bin( static_cast<const QgsExpressionNodeBinaryOperator *>( node ) );
    QString left, right;

    Result lr = compileNode( bin->opLeft(), left );
    Result rr = compileNode( bin->opRight(), right );
    Result compileResult;
    QgsDebugMsg( "left: '" + left + "'; right: '" + right +
                 QString( "'; op: %1; lr: %2; rr: %3" ).arg( bin->op() ).arg( lr ).arg( rr ) );
    if ( lr == Fail || rr == Fail )
      return Fail;
// NULL can not appear on the left, only as part of IS NULL or IS NOT NULL
    if ( "NULL" == left.toUpper() ) return Fail;
// NULL can only be on the right for IS and IS NOT
    if ( "NULL" == right.toUpper() && ( bin->op() != QgsExpressionNodeBinaryOperator::boIs && bin->op() != QgsExpressionNodeBinaryOperator::boIsNot ) )
      return Fail;

    switch ( bin->op() )
    {
      case QgsExpressionNodeBinaryOperator::boMod:
        result = QStringLiteral( "MOD(%1,%2)" ).arg( left, right );
        compileResult = ( lr == Partial || rr == Partial ) ? Partial : Complete;
        QgsDebugMsg( QStringLiteral( "MOD compile status:  %1" ).arg( compileResult ) + "; " + result );
        return compileResult;

      case QgsExpressionNodeBinaryOperator::boPow:
        result = QStringLiteral( "power(%1,%2)" ).arg( left, right );
        compileResult = ( lr == Partial || rr == Partial ) ? Partial : Complete;
        QgsDebugMsg( QStringLiteral( "POWER compile status:  %1" ).arg( compileResult ) + "; " + result );
        return compileResult;

      case QgsExpressionNodeBinaryOperator::boRegexp:
        return Fail; //not supported, regexp syntax is too different to Qt

      case QgsExpressionNodeBinaryOperator::boConcat:
        result = QStringLiteral( "%1 || %2" ).arg( left, right );
        compileResult = ( lr == Partial || rr == Partial ) ? Partial : Complete;
        QgsDebugMsg( QStringLiteral( "CONCAT compile status:  %1" ).arg( compileResult ) + "; " + result );
        return compileResult;

      case QgsExpressionNodeBinaryOperator::boILike:
        QgsDebugMsg( QStringLiteral( "ILIKE is not supported by DB2" ) );
        return Fail;
      /*
        result = QString( "%1 LIKE %2" ).arg( left, right );
        compileResult = (lr == Partial || rr == Partial) ? Partial : Complete;
        QgsDebugMsg(QString("ILIKE compile status:  %1").arg(compileResult) + "; " + result);
        return compileResult;
        */

      case QgsExpressionNodeBinaryOperator::boNotILike:
        QgsDebugMsg( QStringLiteral( "NOT ILIKE is not supported by DB2" ) );
        return Fail;
      /*
        result = QString( "%1 NOT LIKE %2" ).arg( left, right );
        compileResult = (lr == Partial || rr == Partial) ? Partial : Complete;
        QgsDebugMsg(QString("NOT ILIKE compile status:  %1").arg(compileResult) + "; " + result);
        return compileResult;
        */

// We only support IS NULL if the operand on the left is a column
      case QgsExpressionNodeBinaryOperator::boIs:
        if ( "NULL" == right.toUpper() )
        {
          if ( bin->opLeft()->nodeType() != QgsExpressionNode::ntColumnRef )
          {
            QgsDebugMsg( "Failing IS NULL with non-column on left: " + left );
            return Fail;
          }
        }
        break;
// We only support IS NULL if the operand on the left is a column
      case QgsExpressionNodeBinaryOperator::boIsNot:
        if ( "NULL" == right.toUpper() )
        {
          if ( bin->opLeft()->nodeType() != QgsExpressionNode::ntColumnRef )
          {
            QgsDebugMsg( "Failing IS NOT NULL with non-column on left: " + left );
            return Fail;
          }
        }
        break;

      default:
        break;
    }
  }

  //fallback to default handling
  QgsDebugMsg( QStringLiteral( "fallback: %1 - " ).arg( nodeType( node ) ) );
  QgsSqlExpressionCompiler::Result rc = QgsSqlExpressionCompiler::compileNode( node, result );
  QgsDebugMsg( QStringLiteral( "fallback: %1 - " ).arg( resultType( rc ) ) + result );
  return rc;
}