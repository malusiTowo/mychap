/*
** EPITECH PROJECT, 2018
** TESTS
** File description:
** TESTS
*/

#include "test.h"
#include "../includes/chap.h"
#include "../includes/global.h"

TestSuite(PARSING,
.description = "---- Parsing Tests -----\n");

Test(PARSING, correct_args)
{
    cmd_args args;
    char *av[] = {"-t", "localhost", "-p", "4142", "-P", "password"};
    parse_cmd_args(7, av, &args);
    cr_str_expect(args.port, "4142", "The port should be equal to 4142 and not %s", args.port);
    cr_str_expect(args.ip, "localhost", "The ip should be equal to localhost and not %s", args.ip);
    cr_str_expect(args.password, "password", "The password should be equal to password and not %s", args.password);
}

Test(PARSING, structure_filled_correctly)
{
    cmd_args args;
    char *av[] = {"-t", "localhost", "-p", "4142", "-P", "password"};
    parse_cmd_args(7, av, &args);
    cr_expect_not_null(args.port, "The port should be equal to 4142");
    cr_expect_not_null(args.ip, "The IP should be equal to localhost");
    cr_expect_not_null(args.password, "The password should be equal to password");
}