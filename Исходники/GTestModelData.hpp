 virtual double          eval_gradients(const GEvent& event,
                                        const GObservation& obs) const {
                             double result = m_modelTps->eval_gradients(event.time());
                             return result;
                         }