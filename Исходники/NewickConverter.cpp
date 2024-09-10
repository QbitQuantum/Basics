TopologyNode* NewickConverter::createNode(const std::string &n, std::vector<TopologyNode*> &nodes, std::vector<double> &brlens) {
    
    // create a string-stream and throw the string into it
    std::stringstream ss (std::stringstream::in | std::stringstream::out);
    ss << n;
    
    char c;
    ss.get(c);
    
    // the initial character has to be '('
    if ( c != '(') {
        throw Exception("Error while converting Newick tree. We expected an opening parenthesis, but didn't get one.");
    }
    
    TopologyNode *node = new TopologyNode(); 
    while ( ss.good() && ss.peek() != ')' ) {
        
        TopologyNode *childNode;
        if (ss.peek() == '(' ) {
            // we received an internal node
            int depth = 0;
            std::string child = "";
            do {
                ss.get(c);
                child += c;
                if ( c == '(' ) {
                    depth++;
                }
                else if ( c == ')' ) {
                    depth--;
                }
            } while ( ss.good() && depth > 0 );
        
            // construct the child node
            childNode = createNode( child, nodes, brlens );
        }
        else {
            // construct the node
            childNode = new TopologyNode();
        }
        
        // set the parent child relationship
        node->addChild( childNode );
        childNode->setParent( node );
        
        // read the optional label
        std::string lbl = "";
        while ( ss.good() && (c = ss.peek()) != ':' && c != '[' && c != ';' && c != ',' && c != ')') {
            lbl += ss.get();
        }
        childNode->setName( lbl );
        
        // read the optional node parameters
        if ( ss.peek() == '[' ) {
            ss.ignore();
            
            do {
                
                // ignore the '&' before parameter name
                if ( ss.peek() == '&') 
                {
                    ss.ignore();
                }
                
                // read the parameter name
                std::string paramName = "";
                while ( ss.good() && (c = ss.peek()) != '=' && c != ',') 
                {
                    paramName += ss.get();
                }
                
                // ignore the equal sign between parameter name and value
                if ( ss.peek() == '=') 
                {
                    ss.ignore();
                }
                
                // read the parameter name
                std::string paramValue = "";
                while ( ss.good() && (c = ss.peek()) != ']' && c != ',') 
                {
                    paramValue += ss.get();
                }
                
                // \todo: Needs implementation
                //                childNode->addNodeParameter(paramName, paramValue);
                if(paramName == "index")
                	childNode->setIndex(atoi(paramValue.c_str()));
                
            } while ( (c = ss.peek()) == ',' );
            
            // ignore the final ']'
            if ( (c = ss.peek()) == ']' )
            {
                ss.ignore();
            }
            
        }
        
        // read the optional branch length
        if ( ss.peek() == ':' ) {
            ss.ignore();
            std::string time = "";
            while ( ss.good() && (c = ss.peek()) != ';' && c != ','  && c != ')' && c != ')' && c != '[') {
                time += ss.get();
            }
            
            std::istringstream stm;
            stm.str(time);
            double d;
            stm >> d;
            if(d < 1E-10 )
				d = 0.0;

            nodes.push_back( childNode );
            brlens.push_back( d );
        }else{