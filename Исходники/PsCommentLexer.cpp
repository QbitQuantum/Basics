bool PSCommentLexer::parse(QIODevice& fin)
{
    char c;

    m_buffer.clear();
    m_curState = State_Start;

    parsingStarted();

    while (!fin.atEnd()) {
        fin.getChar(&c);

//    qDebug ("got %c", c);

        State newState;
        Action action;

        nextStep(c, &newState, &action);

        switch (action) {
        case Action_Copy :
            m_buffer.append(c);
            break;
        case Action_CopyOutput :
            m_buffer.append(c);
            doOutput();
            break;
        case Action_Output :
            doOutput();
            break;
        case Action_OutputUnget :
            doOutput();
            fin.ungetChar(c);
            break;
        case Action_Ignore :
            /* ignore */
            break;
        case Action_Abort :
            qWarning("state %s / %s char %c (%d)" , statetoa(m_curState), statetoa(newState), c, c);
            parsingAborted();
            return false;
            break;
        case Action_InitTemp :
            m_temp.clear();
            break;
        case Action_CopyTemp :
            m_temp.append(c);
            break;
        case Action_DecodeUnget :
            m_buffer.append(decode());
            fin.ungetChar(c);
            break;
        default :
            qWarning("unknown action: %d ", action);
        }

        m_curState = newState;
    }

    parsingFinished();
    return true;
}