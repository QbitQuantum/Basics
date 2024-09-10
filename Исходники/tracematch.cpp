Tracematch::Tracematch(string n,
                       TRACEMATCH_MODE m,
                       UINT32 v,
                       TracematchSymbolNames s_n,
                       const TracematchRegexTokens& regex_tokens)
    : name(n), mode(m), variables(v), symbol_names(s_n)
{
    /* Create a Thompson NFA from the regex tokens */
    stack<GraphProperties> graph_properties_stack;

    for (TracematchRegexTokens::const_iterator i = regex_tokens.begin();
         i != regex_tokens.end(); ++i) {
        if (i->token == SYMBOL) {
            GraphProperties gp(boost::add_vertex(graph),
                               boost::add_vertex(graph));
            EdgeProperties ep(i-> value);
            boost::add_edge(gp.start, gp.end, ep, graph);
            graph_properties_stack.push(gp);
        }
        else if (i->token == QUESTION) {
            if (graph_properties_stack.size() < 1) {
                output << format_prefix(ERROR) << "Invalid regular expression."
                       << endl;
                exit(EXIT_FAILURE);
            }

            GraphProperties gp1 = graph_properties_stack.top();
            graph_properties_stack.pop();
            GraphProperties gp(boost::add_vertex(graph),
                               boost::add_vertex(graph));
            EdgeProperties ep(SYMBOL_ID_EPSILON);
            boost::add_edge(gp.start, gp1.start, ep, graph);
            boost::add_edge(gp1.end, gp.end, ep, graph);
            boost::add_edge(gp.start, gp.end, ep, graph);
            graph_properties_stack.push(gp);
        }
        else if (i->token == PLUS) {
            if (graph_properties_stack.size() < 1) {
                output << format_prefix(ERROR) << "Invalid regular expression."
                       << endl;
                exit(EXIT_FAILURE);
            }

            GraphProperties gp1 = graph_properties_stack.top();
            graph_properties_stack.pop();
            GraphProperties gp(gp1.start, boost::add_vertex(graph));
            EdgeProperties ep(SYMBOL_ID_EPSILON);
            boost::add_edge(gp1.end, gp.start, ep, graph);
            boost::add_edge(gp1.end, gp.end, ep, graph);
            graph_properties_stack.push(gp);
        }
        else if (i->token == STAR) {
            if (graph_properties_stack.size() < 1) {
                output << format_prefix(ERROR) << "Invalid regular expression."
                       << endl;
                exit(EXIT_FAILURE);
            }

            GraphProperties gp1 = graph_properties_stack.top();
            graph_properties_stack.pop();
            GraphProperties gp(boost::add_vertex(graph),
                               boost::add_vertex(graph));
            EdgeProperties ep(SYMBOL_ID_EPSILON);
            boost::add_edge(gp.start, gp1.start, ep, graph);
            boost::add_edge(gp1.end, gp.start, ep, graph);
            boost::add_edge(gp.start, gp.end, ep, graph);
            graph_properties_stack.push(gp);
        }
        else if (i->token == CONSTANT) {
            if (graph_properties_stack.size() < 1 || i->value < 1) {
                output << format_prefix(ERROR) << "Invalid regular expression."
                       << endl;
                exit(EXIT_FAILURE);
            }

            GraphProperties gp = graph_properties_stack.top();
            graph_properties_stack.pop();

            list<GraphProperties> copies;

            for (UINT32 j = 0; j < (i->value - 1); ++j) {
                /* Copy the current tracematch value - 1 times */
                GraphProperties gp_copy(boost::add_vertex(graph),
                                        boost::add_vertex(graph));
                unordered_map<Vertex, Vertex> vertex_copy_map;
                vertex_copy_map[gp.start] = gp_copy.start;
                vertex_copy_map[gp.end] = gp_copy.end;
                copy_dfs_visitor vis(vertex_copy_map, graph);
                boost::depth_first_search(graph, visitor(vis));
                copies.push_back(gp_copy);
            }

            /* Then */
            EdgeProperties ep(SYMBOL_ID_EPSILON);
            for (UINT32 j = 0; j < (i->value - 1); ++j) {
                GraphProperties gp_copy = copies.front();
                boost::add_edge(gp.end, gp_copy.start, ep, graph);
                gp.end = gp_copy.end;
                copies.pop_front();
            }

            graph_properties_stack.push(gp);
        }
        else if (i->token == OR) {
            if (graph_properties_stack.size() < 2) {
                output << format_prefix(ERROR) << "Invalid regular expression."
                       << endl;
                exit(EXIT_FAILURE);
            }

            GraphProperties gp1 = graph_properties_stack.top();
            graph_properties_stack.pop();
            GraphProperties gp2 = graph_properties_stack.top();
            graph_properties_stack.pop();
            GraphProperties gp(boost::add_vertex(graph),
                               boost::add_vertex(graph));
            EdgeProperties ep(SYMBOL_ID_EPSILON);
            boost::add_edge(gp.start, gp1.start, ep, graph);
            boost::add_edge(gp.start, gp2.start, ep, graph);
            boost::add_edge(gp1.end, gp.end, ep, graph);
            boost::add_edge(gp2.end, gp.end, ep, graph);
            graph_properties_stack.push(gp);
        }
        else if (i->token == THEN) {
            if (graph_properties_stack.size() < 2) {
                output << format_prefix(ERROR) << "Invalid regular expression."
                       << endl;
                exit(EXIT_FAILURE);
            }

            GraphProperties gp1 = graph_properties_stack.top();
            graph_properties_stack.pop();
            GraphProperties gp2 = graph_properties_stack.top();
            graph_properties_stack.pop();
            GraphProperties gp;
            gp.start = gp2.start;
            gp.end = gp1.end;
            EdgeProperties ep(SYMBOL_ID_EPSILON);
            boost::add_edge(gp2.end, gp1.start, ep, graph);
            graph_properties_stack.push(gp);
        }
    }

    if (graph_properties_stack.size() != 1) {
        output << format_prefix(ERROR) << "Invalid regular expression."
               << endl;
        exit(EXIT_FAILURE);
    }

    graph_properties = graph_properties_stack.top();
    graph_properties_stack.pop();
}