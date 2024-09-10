bool formsDominoChain(Vector<Domino> &dominos, Vector<Domino> toBeSorted, Vector<Domino> &solution) {
    if (solution.size() >= dominos.size() && isValidChain(solution)) {
        cout << solution << endl;
        return true;
    }
    for (int i = 0; i < toBeSorted.size(); i++) {
        for (int j = 0; j < 2; j++) {
            Vector<Domino> tester;
            tester += solution[solution.size() - 1];
            tester += toBeSorted[i];
            if (j == 0 && isValidChain(tester)) {
                solution += toBeSorted[i];
                if (formsDominoChain(dominos, subtract(dominos, solution), solution)) {
                    return true;
                }
                solution.remove(solution.size() - 1);
            }
            tester.clear();
            tester += solution[solution.size() - 1];
            tester += toBeSorted[i];
            tester[tester.size() - 1].flip();
            if (j == 1 && isValidChain(tester)) {
                solution += toBeSorted[i];
                Vector<Domino> flippedSolution = solution;
                flippedSolution[flippedSolution.size() - 1].flip();
                if (formsDominoChain(dominos, subtract(dominos, solution), flippedSolution)) {
                    return true;
                }
                solution.remove(solution.size() - 1);
            }
        }
    }
    return false;

}