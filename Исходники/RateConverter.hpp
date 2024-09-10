            /**
             * Compute maximum dissolution and evaporation ratios at
             * average hydrocarbon pressure.
             *
             * Uses the pressure value computed by averagePressure()
             * and must therefore be called *after* that method.
             */
            void
            calcRmax()
            {
                Rmax_.setZero();

                const PhaseUsage& pu = props_.phaseUsage();

                if (Details::PhaseUsed::oil(pu) &&
                    Details::PhaseUsed::gas(pu))
                {
                    const Eigen::ArrayXXd::Index
                        io = Details::PhasePos::oil(pu),
                        ig = Details::PhasePos::gas(pu);

                    // Note: Intentionally does not take capillary
                    // pressure into account.  This facility uses the
                    // average *hydrocarbon* pressure rather than
                    // average phase pressure.
                    typedef BlackoilPropsAdInterface::ADB ADB;
                    Rmax_.col(io) = props_.rsSat(ADB::constant(p_avg_), ADB::constant(T_avg_), repcells_).value();
                    Rmax_.col(ig) = props_.rvSat(ADB::constant(p_avg_), ADB::constant(T_avg_), repcells_).value();
                }
            }