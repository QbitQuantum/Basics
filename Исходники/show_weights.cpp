/// Main Program
int main(int argc, char *argv[])
{
	CmdLine cmd;

    std::string combine;
    ParamDisparity p; // Parameters for adaptive weights
    cmd.add( make_option('R',p.radius) );
    cmd.add( make_option(0,p.gammaCol,"gcol") );
    cmd.add( make_option(0,p.gammaPos,"gpos") );
	cmd.add( make_option('c', combine) );

	try {
		cmd.process(argc, argv);
	} catch(std::string str) {
		std::cerr << "Error: " << str << std::endl<<std::endl;
        argc = 1; // To display usage
	}
	if(argc!=5 && argc!=7) {
		usage(argv[0]);
		return 1;
	}

    // Load images
    Image im1 = loadImage(argv[1]);
    Image im2;
    if(argc>5)
        im2 = loadImage(argv[5]);

	int x,y;
	if(! ((std::istringstream(argv[2])>>x).eof() &&
		  (std::istringstream(argv[3])>>y).eof())) {
        std::cerr << "Error reading x or y" << std::endl;
        return 1;
	}

	int disp=0;
	if(argc>6 && !((std::istringstream(argv[6])>>disp).eof()) ) {
        std::cerr << "Error reading disparity" << std::endl;
        return 1;
	}

    Comb* comb=0;
    if(cmd.used('c') && im2.channels()!=0) {
        if(combine == "left")
            comb = new Comb(left);
        else if(combine == "max")
            comb = new Comb(max);
        else if(combine == "min")
            comb = new Comb(min);
        else if(combine == "mult")
            comb = new Comb(mult);
        else if(combine == "plus")
            comb = new Comb(plus);
        else {
            std::cerr << "Unrecognized option for weights combination "
                      << "(should be left,max,min,mult or plus)" << std::endl;
            return 1;
        }
    }

    Image w = show_weights(im1, im2, x, y, x+disp, comb,
                           p.radius, p.gammaCol, p.gammaPos);
    rescale(w);
    if(io_png_write_f32(argv[4], &w(0,0), w.width(), w.height(), 1) != 0) {
        std::cerr << "Unable to write file " << argv[4] << std::endl;
        return 1;
    }

	return 0;
}