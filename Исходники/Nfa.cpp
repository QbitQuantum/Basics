void Nfa::ConcatenateAllPreviousTillOperation(stack<RegularDefinition *> &solver) {
    vector<Nfa *> nfas_to_be_concatenated;
    while(solver.top()->type != RegularDefinition::kOperation) {
        nfas_to_be_concatenated.push_back(solver.top()->GetNfa());
        solver.pop();
    }
    reverse(nfas_to_be_concatenated.begin(), nfas_to_be_concatenated.end());
    solver.push(new RegularDefinition(RegularDefinition::kNfa, Concatenate(nfas_to_be_concatenated)));
}