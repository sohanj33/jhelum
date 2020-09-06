
#include "munit.h"
#include "esb.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmd_parser.h"
/**
 * If the name of a test function is "test_abc" then you should
 * define the setup and teardown functions by the names:
 * test_abc_setup and test_abc_tear_down respectively.
 */

/*gcc test_esb.c munit.c bmd_parser.c database.c esb.c  `mysql_config --cflags --libs` `xml2-config --cflags --libs` -o test_esb
 */
static void *
test_parse_bmd_xml_setup(const MunitParameter params[], void *user_data)
{
    /**
     * Return the data that will be used for test1. Here we
     * are just return a string. It can be a struct or anything.
     * The memory that you allocate here for the test data
     * has to be cleaned up in corresponding tear down function,
     * which in this case is test1_tear_down.
     */
    printf("Hello Tester setup\n");
    DIR *d;
    struct dirent *dir;
    d = opendir("./Test_files");
    char **s;
    s = malloc(100 * sizeof(char *));
    int i = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char *file = strdup(dir->d_name);
            if(file[0]=='.')
              continue;
            char cwd[100];
            getcwd(cwd, sizeof(cwd));
            char path[100];
            sprintf(path, "%s/Test_files/%s", cwd, file);
             
            s[i] = strdup(path);

            free(file);
            i++;
        }
        closedir(d);
    }

    return s;
}

static void
test_parse_bmd_xml_tear_down(void *fixture)
{
    /* Receives the pointer to the data if that that was created in
    test1_setup function. */
    free(fixture);
}

static MunitResult
test_parse_bmd_xml(const MunitParameter params[], void *fixture)
{
    char **str = (char **)fixture;
    /**
     * Perform the checking of logic here as needed.
     * Typically, you will invoke the function under testing
     * here by passing it suitable data from fixture. Then,
     * use assertions to verify the expected results.
     * In this example, we are just checking the value of a
     * string which we were expecting to be available in the
     * fixture itself. This test will fail when you change the
     * string. You will need to recompile and re-run the tests
     * to see the effect of any changes in data in this example.
     */
    printf("\nHello Tester\n");
    int i = 0;
    while (str[i] != NULL)
    {

        BMD *bmd;

        //munit_assert_true(bmd->bmd_envelope->MessageID == NULL);

        bmd = parse_bmd_xml(str[i]);
        munit_assert_true(bmd != NULL);

        //printf("Message ID: Tester %s \n", bmd->bmd_envelope->MessageID);
        free(bmd);
        i++;
    }

    //munit_assert_string_equal(str, "/path/to/bmd.xml");

    // Invoke the ESB function (or any other function to test)
    //int status = process_esb_request(str);

    // Assert the expected results
    // munit_assert_true(status == 0);
    return MUNIT_OK;
}

/* Define the setup and the test for test2 */
static void *
test2_setup(const MunitParameter params[], void *user_data)
{
    return strdup("TEST-2");
}

static void
test2_tear_down(void *fixture)
{
    free(fixture);
}

static MunitResult
test2(const MunitParameter params[], void *fixture)
{
    char *str = (char *)fixture;
    munit_assert_string_equal(str, "TEST-2");
    return MUNIT_OK;
}

/* Put all unit tests here. */
MunitTest esb_tests[] = {
    {
        "/test_bmd_parse_xml",        /* name */
        test_parse_bmd_xml,           /* test function */
        test_parse_bmd_xml_setup,     /* setup function for the test */
        test_parse_bmd_xml_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */
    },
    {
        "/my-test-2",           /* name */
        test2,                  /* test function */
        test2_setup,            /* setup function for the test */
        test2_tear_down,        /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/test_suite_esb",      /* name */
    esb_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main(int argc, const char *argv[])
{
    return munit_suite_main(&suite, NULL, argc, argv);
}
