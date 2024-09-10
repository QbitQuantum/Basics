static void appendSourceToError(CallFrame* callFrame, ErrorInstance* exception, unsigned bytecodeOffset)
{
    ErrorInstance::SourceAppender appender = exception->sourceAppender();
    exception->clearSourceAppender();
    RuntimeType type = exception->runtimeTypeForCause();
    exception->clearRuntimeTypeForCause();

    if (!callFrame->codeBlock()->hasExpressionInfo())
        return;
    
    int startOffset = 0;
    int endOffset = 0;
    int divotPoint = 0;
    unsigned line = 0;
    unsigned column = 0;

    CodeBlock* codeBlock;
    CodeOrigin codeOrigin = callFrame->codeOrigin();
    if (codeOrigin && codeOrigin.inlineCallFrame)
        codeBlock = baselineCodeBlockForInlineCallFrame(codeOrigin.inlineCallFrame);
    else
        codeBlock = callFrame->codeBlock();

    codeBlock->expressionRangeForBytecodeOffset(bytecodeOffset, divotPoint, startOffset, endOffset, line, column);
    
    int expressionStart = divotPoint - startOffset;
    int expressionStop = divotPoint + endOffset;

    StringView sourceString = codeBlock->source()->source();
    if (!expressionStop || expressionStart > static_cast<int>(sourceString.length()))
        return;
    
    VM* vm = &callFrame->vm();
    JSValue jsMessage = exception->getDirect(*vm, vm->propertyNames->message);
    if (!jsMessage || !jsMessage.isString())
        return;
    
    String message = asString(jsMessage)->value(callFrame);
    if (expressionStart < expressionStop)
        message = appender(message, codeBlock->source()->getRange(expressionStart, expressionStop).toString(), type, ErrorInstance::FoundExactSource);
    else {
        // No range information, so give a few characters of context.
        int dataLength = sourceString.length();
        int start = expressionStart;
        int stop = expressionStart;
        // Get up to 20 characters of context to the left and right of the divot, clamping to the line.
        // Then strip whitespace.
        while (start > 0 && (expressionStart - start < 20) && sourceString[start - 1] != '\n')
            start--;
        while (start < (expressionStart - 1) && isStrWhiteSpace(sourceString[start]))
            start++;
        while (stop < dataLength && (stop - expressionStart < 20) && sourceString[stop] != '\n')
            stop++;
        while (stop > expressionStart && isStrWhiteSpace(sourceString[stop - 1]))
            stop--;
        message = appender(message, codeBlock->source()->getRange(start, stop).toString(), type, ErrorInstance::FoundApproximateSource);
    }
    exception->putDirect(*vm, vm->propertyNames->message, jsString(vm, message));

}