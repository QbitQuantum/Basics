        void iterate()
        {
            auto& zen = static_cast<zen_type&>(*this);
            zen.make_direction(); //
            zen.make_step_size(); //

            current_solution += step_size * direction;
            ++current_step;

            iteration_over_function( current_residual, current_solution.data() );
#if 0 
            std::cout << "\n\nstep is " << step_size;
            std::cout << "\ndirection is " << direction.transpose();
            std::cout << "\nresidual is " << current_residual;
            std::cout << "\ncurrent_solution is " << current_solution.transpose();
            std::cerr << "\nresidual is " << current_residual;
            //std::ofstream ofs( "solution.noisy.stro3_select_7_5.dat", std::fstream::app );
            //std::ofstream ofs( "solution.sto_accr.12.2.dat", std::fstream::app );
            //std::ofstream ofs( "solution.sto_accr.12.2.se.dat", std::fstream::app );
            //std::ofstream ofs( "solution.sto_accr.12.2.exp.dat", std::fstream::app );
            //std::ofstream ofs( "solution.9beam.12.2.dat", std::fstream::app );
            //std::ofstream ofs( "./solution.sto_accr.12.2.dat", std::fstream::app );
            //std::ofstream ofs( "./solution.sto_accr.12.2_abs_dec_1.dat", std::fstream::app );
            std::ofstream ofs( "./solution.sto_accr.12.2_thickness_dec_2.dat", std::fstream::app );
            //std::ofstream ofs( "solution.9beam.12.2.dat", std::fstream::app );
            //std::ofstream ofs( "new.solution.9beam.12.2.dat", std::fstream::app );
            //std::ofstream ofs( "solution.71.simple.derivative.10.0.dat", std::fstream::app );
            //std::ofstream ofs( "solution.9beams.derivative.10.0.dat", std::fstream::app );
            //std::ofstream ofs( "solution.9beams.derivative.10.0.dat", std::fstream::app );
            ofs << current_residual << "\t\t" << current_solution.transpose() << "\n";
            ofs.close();
#endif
        }