/*
 * This function behaves in the same way that a main one, except that it does
 * not invoke the setBufferMode function.
 */
int main_LocateTfst(int argc,char* const argv[]) {
if (argc==1) {
   usage();
   return SUCCESS_RETURN_CODE;
}

VersatileEncodingConfig vec=VEC_DEFAULT;
int val,index=-1;
char text[FILENAME_MAX]="";
char alphabet[FILENAME_MAX]="";
int is_korean=0;
int tilde_negation_operator=1;
int selected_negation_operator=0;
int tagging=0;
int single_tags_only=0;
int match_word_boundaries=1;
MatchPolicy match_policy=LONGEST_MATCHES;
OutputPolicy output_policy=IGNORE_OUTPUTS;
AmbiguousOutputPolicy ambiguous_output_policy=ALLOW_AMBIGUOUS_OUTPUTS;
VariableErrorPolicy variable_error_policy=IGNORE_VARIABLE_ERRORS;
int search_limit=NO_MATCH_LIMIT;
char foo;
vector_ptr* injected=new_vector_ptr();
bool only_verify_arguments = false;
UnitexGetOpt options;
while (EOF!=(val=options.parse_long(argc,argv,optstring_LocateTfst,lopts_LocateTfst,&index))) {
   switch(val) {
   case 't': if (options.vars()->optarg[0]=='\0') {
                error("You must specify a non empty .tfst name\n");
                free_vector_ptr(injected);
                return USAGE_ERROR_CODE;
             }
             strcpy(text,options.vars()->optarg);
             break;
   case 'a': if (options.vars()->optarg[0]=='\0') {
                error("You must specify a non empty alphabet name\n");
                free_vector_ptr(injected);
                return USAGE_ERROR_CODE;
             }
             strcpy(alphabet,options.vars()->optarg);
             break;
   case 'K': is_korean=1;
   	   	   	  match_word_boundaries=0;
              break;
   case 'l': search_limit=NO_MATCH_LIMIT; break;
   case 'g': if (options.vars()->optarg[0]=='\0') {
                error("You must specify an argument for negation operator\n");
                free_vector_ptr(injected);
                return USAGE_ERROR_CODE;
             }
             selected_negation_operator=1;
             if ((strcmp(options.vars()->optarg,"minus")==0) || (strcmp(options.vars()->optarg,"-")==0)) {
                 tilde_negation_operator=0;
             }
             else
             if ((strcmp(options.vars()->optarg,"tilde")!=0) && (strcmp(options.vars()->optarg,"~")!=0)) {
                 error("You must specify a valid argument for negation operator\n");
                 free_vector_ptr(injected);
                 return USAGE_ERROR_CODE;                 
             }
             break;
   case 'n': if (1!=sscanf(options.vars()->optarg,"%d%c",&search_limit,&foo) || search_limit<=0) {
                /* foo is used to check that the search limit is not like "45gjh" */
                error("Invalid search limit argument: %s\n",options.vars()->optarg);
                free_vector_ptr(injected);
                return USAGE_ERROR_CODE;                
             }
             break;
   case 'S': match_policy=SHORTEST_MATCHES; break;
   case 'L': match_policy=LONGEST_MATCHES; break;
   case 'A': match_policy=ALL_MATCHES; break;
   case 'I': output_policy=IGNORE_OUTPUTS; break;
   case 'M': output_policy=MERGE_OUTPUTS; break;
   case 'R': output_policy=REPLACE_OUTPUTS; break;
   case 'X': variable_error_policy=EXIT_ON_VARIABLE_ERRORS; break;
   case 'Y': variable_error_policy=IGNORE_VARIABLE_ERRORS; break;
   case 'Z': variable_error_policy=BACKTRACK_ON_VARIABLE_ERRORS; break;
   case 'b': ambiguous_output_policy=ALLOW_AMBIGUOUS_OUTPUTS; break;
   case 'z': ambiguous_output_policy=IGNORE_AMBIGUOUS_OUTPUTS; break;
   case 'V': only_verify_arguments = true;
             break;
   case 'h': usage(); 
             return SUCCESS_RETURN_CODE;
   case 1: tagging=1; break;
   case 2: single_tags_only=1; break;
   case 3: match_word_boundaries=0; break;
   case 'k': if (options.vars()->optarg[0]=='\0') {
                error("Empty input_encoding argument\n");
                free_vector_ptr(injected);
                return USAGE_ERROR_CODE;                
             }
             decode_reading_encoding_parameter(&(vec.mask_encoding_compatibility_input),options.vars()->optarg);
             break;
   case 'q': if (options.vars()->optarg[0]=='\0') {
                error("Empty output_encoding argument\n");
                free_vector_ptr(injected);
                return USAGE_ERROR_CODE;                
             }
             decode_writing_encoding_parameter(&(vec.encoding_output),&(vec.bom_output),options.vars()->optarg);
             break;
   case 'v': {
	   unichar* key=u_strdup(options.vars()->optarg);
	   unichar* value=u_strchr(key,'=');
	   if (value==NULL) {
		   error("Invalid variable injection: %s\n",options.vars()->optarg);
       free_vector_ptr(injected);
       return USAGE_ERROR_CODE;       
	   }
	   (*value)='\0';
	   value++;
	   value=u_strdup(value);
	   vector_ptr_add(injected,key);
	   vector_ptr_add(injected,value);
	   break;
   }
   case ':': index==-1 ? error("Missing argument for option -%c\n",options.vars()->optopt) :
                         error("Missing argument for option --%s\n",lopts_LocateTfst[index].name);
             free_vector_ptr(injected);
             return USAGE_ERROR_CODE;
   case '?': index==-1 ? error("Invalid option -%c\n",options.vars()->optopt) :
                         error("Invalid option --%s\n",options.vars()->optarg);
             free_vector_ptr(injected);
             return USAGE_ERROR_CODE;
             break;
   }
   index=-1;
}

if (options.vars()->optind!=argc-1) {
   error("Invalid arguments: rerun with --help\n");
   free_vector_ptr(injected);
   return USAGE_ERROR_CODE;
}

if (only_verify_arguments) {
  // freeing all allocated memory
  free_vector_ptr(injected);
  return SUCCESS_RETURN_CODE;
}

if (selected_negation_operator==0) {
    get_graph_compatibility_mode_by_file(&vec,&tilde_negation_operator);
}

char grammar[FILENAME_MAX];
char output[FILENAME_MAX];
strcpy(grammar,argv[options.vars()->optind]);
get_path(text,output);
strcat(output,"concord.ind");

int OK=locate_tfst(text,
                   grammar,
                   alphabet,
                   output,
                   &vec,
                   match_policy,
                   output_policy,
                   ambiguous_output_policy,
                   variable_error_policy,
                   search_limit,
                   is_korean,
                   tilde_negation_operator,
                   injected,
                   tagging,
                   single_tags_only,
                   match_word_boundaries);

free_vector_ptr(injected);

return (!OK);
}