void PropertyEditor::Private::loadFromCurrentElement()
{
    State *state = current<State>();
    if (state && state->type() != Element::PseudoStateType) {
        m_stateWidget->labelLineEdit->setText(state->label());
        m_stateWidget->initialStateComboBox->clear();
        m_stateWidget->defaultStateComboBox->clear();

        m_stateWidget->initialStateLabel->setVisible(state->isComposite());
        m_stateWidget->initialStateComboBox->setVisible(state->isComposite());
        m_stateWidget->defaultStateLabel->setVisible(state->type() == Element::HistoryStateType);
        m_stateWidget->defaultStateComboBox->setVisible(state->type() == Element::HistoryStateType);
        m_stateWidget->childModeLabel->setVisible(state->isComposite());
        m_stateWidget->childModeEdit->setVisible(state->isComposite());

        if (state->isComposite()) {
            m_stateWidget->initialStateComboBox->addItems(childStates(state));
            State* initialState = ElementUtil::findInitialState(state);
            if (initialState)
                m_stateWidget->initialStateComboBox->setCurrentText(initialState->label());
            else
                m_stateWidget->initialStateComboBox->setCurrentIndex(0);

            m_stateWidget->childModeEdit->setCurrentIndex(state->childMode());
        }

        if (state->type() == Element::HistoryStateType) {
            m_stateWidget->defaultStateComboBox->addItems(allStates(state->machine()));
            State *defaultState = qobject_cast<HistoryState*>(state)->defaultState();
            m_stateWidget->defaultStateComboBox->setCurrentText(defaultState ? defaultState->label() : "");
        }

        m_stateWidget->onEntryEditor->setPlainText(state->onEntry());
        m_stateWidget->onExitEditor->setPlainText(state->onExit());

        HistoryState *historyState = current<HistoryState>();
        m_stateWidget->historyTypeLabel->setVisible(historyState);
        m_stateWidget->historyTypeEdit->setVisible(historyState);
        if (historyState)
            m_stateWidget->historyTypeEdit->setCurrentIndex(historyState->historyType());

        q->setCurrentIndex(m_stateWidgetIndex); // State page

    } else if (Transition *transition = current<Transition>()) {
        m_transitionWidget->labelLineEdit->setText(transition->label());

        m_transitionWidget->sourceStateComboBox->clear();
        State* sourceState = transition->sourceState();
        Q_ASSERT(sourceState);
        m_transitionWidget->sourceStateComboBox->addItems(allStates(sourceState->machine()));
        if (sourceState)
            m_transitionWidget->sourceStateComboBox->setCurrentText(sourceState->label());
        else
            m_transitionWidget->sourceStateComboBox->setCurrentText(QString());

        m_transitionWidget->targetStateComboBox->clear();
        State* targetState = transition->targetState();
        m_transitionWidget->targetStateComboBox->addItems(allStates(sourceState->machine()));
        if (targetState)
            m_transitionWidget->targetStateComboBox->setCurrentText(targetState->label());
        else
            m_transitionWidget->targetStateComboBox->setCurrentText(QString());

        m_transitionWidget->guardEditor->setPlainText(transition->guard());
        q->setCurrentIndex(m_transitionWidgetIndex); // Transition page

        SignalTransition *signalTransition = current<SignalTransition>();
        m_transitionWidget->signalLabel->setVisible(signalTransition);
        m_transitionWidget->signalEdit->setVisible(signalTransition);
        if (signalTransition)
            m_transitionWidget->signalEdit->setText(signalTransition->signal());

        TimeoutTransition *timeoutTransition = current<TimeoutTransition>();
        m_transitionWidget->timeoutLabel->setVisible(timeoutTransition);
        m_transitionWidget->timeoutEdit->setVisible(timeoutTransition);
        if (timeoutTransition)
            m_transitionWidget->timeoutEdit->setValue(timeoutTransition->timeout());

    } else {
        q->setCurrentIndex(m_noWidgetIndex);
    }
}