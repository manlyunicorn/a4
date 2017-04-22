#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "regions.h"

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

  static Boolean rc;
  static int *ia;
  static char *ca1, *ca2, *ca3, *ca4;
  static char *fail;
  static int size = 3023;
  static char *testI[size];

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

void testInit();
void testChoose();
void testChosen();
void testAlloc();
void testSize();
void testFree();
void testDump();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------


int main( int argc, char *argv[] )
{

    printf( "Tests\n\n" );

    testInit();
    testChoose();
    testChosen();
    testAlloc();
    testFree();
    testDump();

    printf( "\nPass.\n" );

    return EXIT_SUCCESS;
}

void testInit()
{
   rc = rinit("hello", 1024);
  assert(rc);
  rc = rinit("hello", 798);
  assert(rc);
  rc rinit("once more", size);
  rc = rinit("", 7292);
  assert(rc);
  rc = rinit("this is a rather annoying test", 0);
  assert(rc);
}

void testChoose()
{
      rc = rchoose("hello");
      assert(rc);
      rc = rchoose("no such thing");
      assert(rc);
      rc = rchoose("once more")
      assert(rc);
      rc = rchoose("this is a rather annoying test");
}

void testChosen()
{
    rc =rchosen("hello");
    rc = rchosen("no such thing");
}

void testAlloc()
{
  ia = ralloc(sizeof(int) * 32);
  printf("Size: %d\n", rsize(ia)); // 128
  ca1 = ralloc(256);
  assert(NULL != ca1);
  ca2 = ralloc(384);
  assert(NULL != ca2);
  fail = ralloc(384); // not enough memory
  assert(NULL == fail);
  assert(rc);
  ca3 = ralloc(384); // now there's enough memory
  assert (NULL != ca3);
  for (i = 0; i<size; i++)
  {
    test[i] = ralloc(1);
    assert(ptrs[i]);
  }
}

void testFree()
{
  rc = rfree(ca1);
  rc = rfree(ia);
  rc = rfree(ia);
}
void testDump()
{
  rdump();
  rdestroy("hello");
  rdestroy("hello");
  rdestroy("no such thing");
}
