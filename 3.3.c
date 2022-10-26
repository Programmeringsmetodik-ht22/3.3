/*******************************************************************************
* 3.3.c: Programkod skriven i C89. Ett dynamiskt fält tilldelas 20 osignerade
*        heltal mellan 5 - 15, vilket skrivs till en fil. Innan programmet
*        avslutas läses filens innehåll in och skrivs ut i terminalen.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* Makrodefinitioner: */
#define SIZE 20 /* Storlek på dynamisk array för lagring av osignerade heltal. */

/*******************************************************************************
* UINT_PTR_NEW: Returnerar dynamiskt allokerat fält med angiven storlek för
*               lagring av osignerade heltal av datatypen size_t.
*******************************************************************************/
#define UINT_PTR_NEW(SIZE) (size_t*)malloc(sizeof(size_t) * SIZE);

/*******************************************************************************
* GET_RANDOM: Returnerar ett heltal mellan angiven min och max.
*******************************************************************************/
#define GET_RANDOM(MIN, MAX) rand() % (MAX + 1 - MIN) + MIN

/*******************************************************************************
* assign: Fyller array med randomiserade heltal mellan angivet min och max.
*******************************************************************************/
static void assign(size_t* data, const size_t size, const size_t min, const size_t max)
{
   size_t* i;
   for (i = data; i < data + size; ++i)
      { *i = GET_RANDOM(min, max); }
   return;
}

/*******************************************************************************
* print: Skriver ut innehåll lagrat i en array via angiven utström. Som
*        default används standardutenheten för utskrift i terminalen.
*******************************************************************************/
static void print(const size_t* data, const size_t size, FILE* ostream)
{
   if (size)
   {
      const size_t* i;
      if (!ostream) ostream = stdout;
      fprintf(ostream, "--------------------------------------------------------------------------\n");
      for (i = data; i < data + size; ++i)
         { fprintf(ostream, "%lu\n", (unsigned long)*i); }
      fprintf(ostream, "--------------------------------------------------------------------------\n\n");
   }
   return;
}

/*******************************************************************************
* file_read: Läser innehåll från angiven filsökväg och skriver ut via angiven
*            utström, där utskrift i terminalen används som default.
*******************************************************************************/
static void file_read(const char* filepath, FILE* ostream)
{
   FILE* istream = fopen(filepath, "r");
   if (!ostream) ostream = stdout;

   if (!istream)
   {
      fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
   }
   else
   {
      char s[100] = { '\0' };
      while (fgets(s, (int)sizeof(s), istream))
         { fprintf(ostream, "%s", s); }
      fclose(istream);
   }
   return;
}

/*******************************************************************************
* main: Fyller dynamiskt allokerat fält med 20 osignerade heltal mellan 5 - 15.
*       Arrayens innehåll skrivs till filen data.txt, vars innehåll sedan
*       läses in och skrivs ut i terminalen.
*******************************************************************************/
int main(void)
{
   FILE* stream = fopen("data.txt", "w");
   size_t* data = UINT_PTR_NEW(SIZE);
   if (!data) return 1;

   assign(data, SIZE, 5, 15);
   print(data, SIZE, stream);
   fclose(stream);
   
   file_read("data.txt", 0);
   return 0;
}