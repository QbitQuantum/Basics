void StateMachineViewerWidgetNG::stateAdded(const StateId stateId, const StateId parentId, const bool hasChildren,
                                            const QString& label, const StateType type, const bool connectToInitial)
{
  Q_UNUSED(hasChildren);
  IF_DEBUG(qDebug() << "stateAdded" << stateId << parentId << label << type);

  if (m_idToStateMap.contains(stateId)) {
    return;
  }

  KDSME::State* parentState = m_idToStateMap.value(parentId);
  KDSME::State* state = 0;
  if (type == StateMachineState) {
    state = m_machine = new KDSME::StateMachine;
  } else if (type == GammaRay::FinalState) {
    state = new KDSME::FinalState(parentState);
  } else if (type == GammaRay::ShallowHistoryState) {
    state = new KDSME::HistoryState(KDSME::HistoryState::ShallowHistory, parentState);
  } else if (type == GammaRay::DeepHistoryState) {
    state = new KDSME::HistoryState(KDSME::HistoryState::DeepHistory, parentState);
  } else {
    state = new KDSME::State(parentState);
  }

  if (connectToInitial && parentState) {
    KDSME::State* initialState = new KDSME::PseudoState(KDSME::PseudoState::InitialState, parentState);
    initialState->setFlags(KDSME::Element::ElementIsSelectable);
    KDSME::Transition* transition = new KDSME::Transition(initialState);
    transition->setTargetState(state);
    transition->setFlags(KDSME::Element::ElementIsSelectable);
  }

  Q_ASSERT(state);
  state->setLabel(label);
  state->setInternalId(stateId);
  state->setFlags(KDSME::Element::ElementIsSelectable);
  m_idToStateMap[stateId] = state;
}