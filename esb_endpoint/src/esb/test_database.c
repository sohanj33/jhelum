#include "munit.h"
#include "esb.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmd_parser.h"


/* Test function for Payload.Json Filesize */
static MunitResult
test_select_active_route(const MunitParameter params[], void *fixture)
{
  int x=select_active_route("756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA","6393F82F-4687-433D-AA23-1966330381FE","CreditReport");
  munit_assert_int(x, ==,1);

}
static MunitResult
test_select_transport_config(const MunitParameter params[], void *fixture)
{
  int x=select_transport_config(1);
  munit_assert_int(x, ==,1);

}
static MunitResult
test_select_transform_config(const MunitParameter params[], void *fixture)
{
  int x=select_transform_config(1);
  munit_assert_int(x, ==,1);

}


//Put all unit tests here
MunitTest database_tests[] = {
    {
        "/test_select_active_route",        /* name */
        test_select_active_route,           /* test function */
        NULL,     /* setup function for the test */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */
    },
    {
        "/test_select_transport_config",        /* name */
        test_select_transport_config,           /* test function */
        NULL,     /* setup function for the test */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */

      
    },
    {
        "/test_select_transform_config",        /* name */
        test_select_transform_config,           /* test function */
        NULL,     /* setup function for the test */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */

      
    },

    {
        NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL
    }};


static const MunitSuite suite = {
    "/test_suite_databse",      /* name */
    database_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main(int argc, const char *argv[])
{
    return munit_suite_main(&suite, NULL, argc, argv);
}
