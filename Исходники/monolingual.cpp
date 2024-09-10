vec MonolingualModel::negSamplingUpdate(const HuffmanNode& node, const vec& hidden, float alpha, bool update) {
    int dimension = config.dimension;
    vec temp(dimension, 0);

    for (int d = 0; d < config.negative + 1; ++d) {
        int label;
        const HuffmanNode* target;

        if (d == 0) { // 1 positive example
            target = &node;
            label = 1;
        } else { // n negative examples
            target = getRandomHuffmanNode();
            if (*target == node) continue;
            label = 0;
        }

        float x = hidden.dot(output_weights[target->index]);

        float pred;
        if (x >= MAX_EXP) {
            pred = 1;
        } else if (x <= -MAX_EXP) {
            pred = 0;
        } else {
            pred = sigmoid(x);
        }
        float error = alpha * (label - pred);

        temp += error * output_weights[target->index];

        if (update && !config.freeze) {
            output_weights[target->index] += error * hidden;
        }
    }

    return temp;
}