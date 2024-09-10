    void work(void)
    {
        //number of elements to work with
        auto elems = this->workInfo().minElements;
        if (elems == 0) return;

        //access to input ports and output port
        const std::vector<Pothos::InputPort *> &inputs = this->inputs();
        Pothos::OutputPort *output = this->output(0);

        //establish pointers to buffers
        auto out = Pothos::BufferChunk(output->buffer()).as<Type *>();
        auto in0 = inputs[0]->buffer().as<const Type *>();
        if (out == in0) _numInlineBuffers++; //track buffer inlining

        //loop through available ports
        for (size_t i = 1; i < inputs.size(); i++)
        {
            auto *inX = inputs[i]->buffer().as<const Type *>();
            Operator(in0, inX, out, elems*output->dtype().dimension());
            in0 = out; //operate on output array next loop
            inputs[i]->consume(elems); //consume on ith input port
        }

        //produce and consume on 0th ports
        inputs[0]->consume(elems);
        output->produce(elems);
    }