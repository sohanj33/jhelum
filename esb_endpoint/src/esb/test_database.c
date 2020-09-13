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




/* Run the the test suite */
// int main(int argc, const char *argv[])
// {
//     return munit_suite_main(&suite, NULL, argc, argv);
// }
