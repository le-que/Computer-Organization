// DO NOT MODIFY
#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "test_utils.h"

void print_usage(char *progname)
{
    fprintf(stderr, "usage: %s [testcase [logfile]]\n", progname);
}

int main(int argc, char **argv)
{
    char *testcase = NULL;
    char *logfile = NULL;

    if (argc - 1 > 2)
    {
        print_usage(argv[0]);
        return 1;
    }
    else
    {
        if (argc - 1 >= 1)
        {
            testcase = argv[1];
        }
        if (argc - 1 >= 2)
        {
            logfile = argv[2];
        }
    }

    // Suite
    Suite *hw7Suite = hw7_suite();
    Suite *myStringSuite = my_string_suite();

    // Select test if specified
    if (testcase && !(suite_tcase(hw7Suite, testcase) || suite_tcase(myStringSuite, testcase)))
    {
        print_usage(argv[0]);
        fprintf(stderr, "\n%s: error: `%s' is not a test case\n", argv[0], testcase);
        return 2;
    }

    // Suite Runner -- Setup testing environment
    SRunner *sr = srunner_create(hw7Suite);
    srunner_add_suite(sr, myStringSuite);

    if (logfile)
    {
        srunner_set_log(sr, logfile);
    }

    // Run Tests in Suite -- Execute Tests
    srunner_run(sr, NULL, testcase, CK_NORMAL);

    // Free Suite Runner - frees everything
    srunner_free(sr);

    return 0;
}
