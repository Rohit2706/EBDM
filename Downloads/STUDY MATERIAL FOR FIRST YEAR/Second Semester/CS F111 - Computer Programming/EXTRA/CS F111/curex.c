#include <stdio.h>
#include <math.h>

#include "ordList.h"

/* Each currency is a single word of at most 9 characters */
#define SYMLEN MAX_STRLEN
typedef char curSym[SYMLEN];  

/******************************/
/* Create a list of currencies */
/******************************/

/* Maximum number of currencies stored */
#define MAXCUR  200
curSym Currencies[MAXCUR];

/* Currently numCur currencies are stored */
unsigned int numCur = 0;

/* Read a list of currencies terminated by a # */
void initCurList() 
{
  int j;
  curSym buffer;
  printf("\nEnter a list of currencies: use space to separate, # to terminate");          
  for (j=0; j<MAXCUR; j++) {
    /* BAD I/O: PRAY scanf does not overwrite? */
    scanf("%s",buffer);
    if (buffer[SYMLEN-1] != '\0') buffer[SYMLEN-1] = '\0';
    if (strcmp(buffer,"#")==0) break;
    else insertInOrderStr(buffer, Currencies, j+1);
  }
  numCur = j;
}

/**************************************************/
/* Create an exchange table of size MAXCUR*MAXCUR */
/**************************************************/

float exTab[MAXCUR][MAXCUR];

/* Read the exchange rates: assume symmetery */
void initExTab()
{
  int j,k;
  for (j=0; j<numCur; j++) {
    exTab[j][j] = 1.00;
    for (k=j+1; k < numCur; k++) {
        printf("\nRate for %s to %s:", Currencies[j], Currencies[k]); 
        scanf("%f", &exTab[j][k]);
        exTab[k][j] = 1.0 / exTab[j][k];
    }
  }
}

/* Lookup the rate for c1 to c2 */
/** Pre-condition: c1 and c2 are valid currencies listed in Currencies
 *  Returns: value in c2 equivalent to 1 unit of c1
 */

float rateLookup(curSym c1, curSym c2) 
{
   unsigned int index1, index2;
   index1 = binSearchStr(c1, Currencies, numCur);
   index2 = binSearchStr(c2, Currencies, numCur);
   if (index1 < 0 || index2 < 0) return 0.0;  /* currencies not found */
   else return exTab[index1][index2];
}

/* Perform a chain of conversions given: a sequence of currencies  and an initial value of curseq[0] */
/* Pre-condition: for all j curseq[j] is valid i.e. occurs in Currencies
 * Returns: value in curseq[seqLen-1] equivalent to initVal units of curseq[0] */
float convertChain(curSym curseq[], int seqLen, float initVal)
{
  int j;
  float curVal = initVal;
  if (initVal == 0.0) return 0.0; // Trivial case
  for (j=0; j<seqLen-1; j++) {
    curVal *= rateLookup(curseq[j],curseq[j+1]);
  }
  return curVal;
}


/* A conversion chain is a sequence of currencies; 
 * The maximum length of the sequence is defined as MAX_CHAINLEN
 */
const unsigned int MAX_CHAINLEN = 100;
/* Read a chain : terminated by a # */
unsigned int readChain(curSym chain[])
{
  unsigned int chainLen=0;
  printf("\nEnter the sequence of currencies to convert\n");
  while (chainLen < MAX_CHAINLEN) {
  	scanf("%s", chain[chainLen]);
	if (!strcmp(chain[chainLen], "#")) break;
	else chainLen++;
  }
  return chainLen;
}

void repl()
{
 /* Create a chain of symbols of maximum length CHAINLEN */
 curSym chain[MAX_CHAINLEN];
 unsigned int chainLen = 0;

  float initVal;

  while (1)
  {
    chainLen = readChain(chain);
    if (chainLen == 0) break;
    printf("\n Amount of %s to convert:\t", chain[0]);
    scanf("%f",&initVal);
    printf("%f units of %s = %f %s\n",
           initVal, 
	   chain[0],
	   convertChain(chain, chainLen, initVal), 
	   chain[chainLen-1]);
  }

}


int main()
{

  /* Read currency list */
  initCurList();
  

  /* Read c1-c2 rates and store in matrix - assume symmetry */
  initExTab();

  /* Read-eval-print loop */

  repl();
 
}
