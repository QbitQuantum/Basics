/* static sets the initial unchangeable structure */
struct tconfig_block *file_to_tconfig(const char *filename)
{
  FILE   *cfile;
  char   *fbuf   = NULL;
  char   *eip    = NULL;
  struct tconfig_block *block    = NULL;
  struct tconfig_block *head     = NULL;
  struct tconfig_block *search   = NULL;
  struct tconfig_block *tmp      = NULL;
  size_t  size   = 0;
  size_t  i      = 0;
	size_t  count  = 0;

  /* For debug purposes */
  int line       = 1;
  
  /* No memory allocated at this point, we don't need 
   * to die nicely
   */
  if ((cfile = fopen(filename,"r")) == NULL)
  {
    fprintf(stderr,"Could not open configuration file: %s\n",filename);
    return NULL;
  }

  fbuf = tmalloc0(BUFFER_SIZE);

  /* Read the entire file into memory */
  for(i=0;(count = fread(&fbuf[i],1,1024,cfile)) == 1024;i+=1024)
  {
    if ((fbuf = realloc(fbuf,i+1024+1024)) == NULL)
    {
      troll_debug(LOG_FATAL,"Could not allocate memory for config file, barfing.\n");
      exit(EXIT_FAILURE);
    }
  }

	/* Terminate it with a NULL */
	fbuf[i+count] = '\0';


  /* If NOT the end-of-file, we must have had an error of some sort, barf and die */
  if (!feof(cfile))
  {
    troll_debug(LOG_ERROR,"An error occurred while reading the config file");
    free(fbuf);
    return NULL;
  }
  fclose(cfile);

  block = tmalloc(sizeof(*block));

  block->parent = NULL;
  block->child  = NULL;
  block->prev   = NULL;
  block->next   = NULL;

  block->key    = NULL;
  block->value  = NULL;

  head = block;
    
  eip = fbuf;

  while(*eip)
  {
    switch (*eip)
    {
      case '{':
        if (block->child != NULL)
        {
          block = block->child;
          break;
        }
        block->child = tmalloc(sizeof(struct tconfig_block));

        block->child->parent = block;
        block                = block->child;
        block->child         = NULL;
        block->prev          = NULL;
        block->next          = NULL;
        block->key           = NULL;
        block->value         = NULL;

        break;
      
      /* The very left element in tree should have the parent */
      case '}':
        /* Rewind the list the very left */
        while (block->prev != NULL)
          block = block->prev;    
   
        if (block->parent == NULL)
        {
          fprintf(stderr, "Mismatched } around line: %d\n",line);
          exit(EXIT_FAILURE);
        }
  
        block              = block->parent;
        break;

      /* Ugly comment parsing routines */
      case '/':
        if (*(eip+1) != '*' && *(eip+1) != '/')
        {
          fprintf(stderr,"Stray / on line: %d\n",line);
          exit(EXIT_FAILURE);
        }

        /* If comment takes C form */
        if (*(eip+1) == '*')
        {
          /* Skip over / and * */
          eip+=2;

          /* Go until terminating -> */
          while (*eip != '\0') 
          {
            if (*(eip+1) == '\0')
            {
              fprintf(stderr,"Reached end of file while looking for */\n");
              exit(EXIT_FAILURE);
            }

            if (*eip == '*' && *(eip+1) == '/')
            {
              /* loop increases eip, so only add 1 */
              eip++;
              break; /* Found end of comment */
            } 

            if (*eip == '\r' && *(eip+1) == '\n')
            {
              eip++;
              line++;
            }
            else if (*eip == '\n')
            {
              line++;
            }
            else if (*eip == '\r')
            {
              line++;
            }

            eip++;
          }

          if (eip == '\0')
          {
            return head;
          }   
        }
        else /* // comment, go until \r\n, \n, or \r */
        {
          eip+=2; /* Skip over // */
         
          while (*eip != '\0')
          {
            if (*eip == '\r')
            {
              /* This just means the file is over, not an error */
              if (*(eip+1) == '\0')
                return head;

              if (*(eip+1) != '\n')
              {
                eip++;
                line++;
                break;
              }
              else
              {
                line++;
                break;
              }
            }
            else if (*eip == '\n')
            {
              line++;
              break;
            }

            eip++;  
          }

          if (*eip == '\0')
            return head;                
        }

        break;
      case '\r':
        if (*(eip+1) == '\n')
        {
          eip++;
          line++;
        }
        else
          line++;

        if (eip == '\0')
          return head;


        break;
      case '\n':
        line++;
          
        break;
      case '\t':
        break;
      case ' ':
        break;
      default:
        tmp        = tmalloc(sizeof(*tmp));

        /* Do a wasteful scan so I don't have to deal with realloc */
        if (*eip == '"')
        {
          eip++; /* Skip the first " */
          for (i=0;*(eip+i) != '\0' && *(eip+i) != '\n' && *(eip+i) != '\r' &&
                   *(eip+i) != '"';i++);

          if (*(eip+i) != '"')
          {
            fprintf(stderr, "Unmatched \" on line %d\n",line);
            exit(EXIT_FAILURE);
          }
        }
        else
        { 
          for (i=0;*(eip+i) != '\0' && *(eip+i) != ' ' && *(eip+i) != '\t';i++);
            
          if (*(eip+i) != ' ' && *(eip+i) != '\t')
          {
            fprintf(stderr, "Unmatched key on line %d\n",line);
            exit(EXIT_FAILURE);
          }
        }

        size = i;
  
        tmp->key = tmalloc0(size+1);

        for (i=0;i<size;i++)
        {
          *(tmp->key+i) = *(eip++);
        }
   
        /* Skip over trailing " if exists, this could be a problem if key is next to value */
        if (*eip == '"')
          eip++;

        /* Skip over whitespace, print error if EOF or there's a newline reached before text */
        while(*eip == '\t' || *eip == ' ' || *eip == '\r' || *eip == '\n' || *eip == '\0')
        {
          if (*eip == '\0')
          {
            fprintf(stderr, "Reached end of file looking for %s's value on line %d\n",block->key,line);
            exit(EXIT_FAILURE);
          }

          if (*eip == '\r' || *eip == '\n')
          {
            fprintf(stderr, "Reached end of line looking for %s's value on line %d\n",block->key,line);
            exit(EXIT_FAILURE);
          }
    
          eip++;
        }

        /* Now to scan the value */
        /* Do a wasteful scan so I don't have to deal with realloc */
        if (*eip == '"')
        {
          eip++; /* Skip the first " */
          for (i=0;*(eip+i) != '\0' && *(eip+i) != '\n' && *(eip+i) != '\r' &&
                   *(eip+i) != '"';i++);

          if (*(eip+i) != '"')
          {
            fprintf(stderr, "Unmatched \" on line %d\n",line);
            exit(EXIT_FAILURE);
          }
        }
        else
        {
          for (i=0;*(eip+i) != '\0' && *(eip+i) != ' ' && *(eip+i) != '\t' &&
                   *(eip+i) != '\r' && *(eip+i) != '\n';i++);

          if (*(eip+i) != ' ' && *(eip+i) != '\t' && *(eip+i) != '\r' && *(eip+i) != '\n')
          {
            fprintf(stderr, "Unmatched key on line %d\n",line);
            exit(EXIT_FAILURE);
          }
        }

        size = i;

        tmp->value = tmalloc0(size+1);

        for (i=0;i<size;i++)
        {
          *(tmp->value+i) = *(eip++);
        }

        tmp->value[size] = '\0';
 
        /* Rewind list */
        search = block;

        while (search->prev != NULL)
          search = search->prev;

        while (search != NULL)
        {
          if (search->key != NULL && search->value != NULL)
          {
            if (!strcmp(search->key,tmp->key) && !strcmp(search->value,tmp->value))
            {
              /* Same block and key, if previous block was a block with children,
               * jump into that block, elsewise, put in a dupe 
               */
              free(tmp->key);
              free(tmp->value);
              free(tmp);
              tmp = NULL;
              block = search;
              break;
            } 
          }

          block  = search;

          search = search->next;
        }

        if (tmp != NULL)
        {
          if (block->key == NULL && block->value == NULL)
          {
            block->key   = tmp->key;
            block->value = tmp->value;
 
            /* Keeping above memory */
            free(tmp);            
          } 
          else
          {
            /* Make a new block */
            block->next = tmp;
            tmp->prev   = block;
            tmp->next   = NULL;
            tmp->parent = NULL;
            tmp->child  = NULL;
            block       = block->next;
          }
        }

        break;          
    }   

    eip++; /* While loop increase */
  }

  free(fbuf);
  return head;
}