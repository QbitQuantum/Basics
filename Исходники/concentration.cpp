# include <math.h>

# include "sparse-adjacency.h"
# include "motif-search.h"
# include "nauty_interface.h"
# include "graphical-models.h"

# include <R.h>
# include <Rinternals.h> 
# include <Rdefines.h>

# include "concentration.h"

# define MSG 0

static double Pi        = acos(-1.0);
static double TwoPi     =  2*Pi;
static double FourPi    =  4*Pi;
static double SixteenPi = 16*Pi;


// Struture to handle the sort on the canonic form
typedef struct{
  int *canonic;
  int *occurrence;
} canonic_list_t;

// Structure to handle the 2nd sort on the occurrences U 
typedef struct{
  int *occurrence;
  int remove;