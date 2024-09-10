Node* ScriptableNodeFactory::getNode( const QString &tagContent, Parser *p ) const
{
  if ( m_scriptEngine->hasUncaughtException() ) {
    throw Grantlee::Exception( TagSyntaxError, m_scriptEngine->uncaughtExceptionBacktrace().join( QChar::fromLatin1( ' ' ) ) );
  }
  ScriptableParser *sp = new ScriptableParser( p, m_scriptEngine );
  QScriptValue parserObject = m_scriptEngine->newQObject( sp );

  QScriptValueList args;
  args << tagContent;
  args << parserObject;

  QScriptValue factory = m_factoryMethod;

  QScriptValue scriptNode = factory.call( factory, args );
  if ( m_scriptEngine->hasUncaughtException() )
    throw Grantlee::Exception( TagSyntaxError, m_scriptEngine->uncaughtExceptionBacktrace().join( QChar::fromLatin1( ' ' ) ) );

  Node* node = qscriptvalue_cast<Node*>( scriptNode );
  node->setParent( p );
  return node;
}