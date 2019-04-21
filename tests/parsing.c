/*
** EPITECH PROJECT, 2018
** TESTS
** File description:
** TESTS
*/

#include "test.h"
#include "chap.h"
#include "global.h"

TestSuite(PARSING, .description = "---- Parsing Tests -----");

Test(PARSING, correct_args)
{
    cmd_args args;
    args.ip = NULL;
    args.password = NULL;
    args.port = NULL;
    char *av[] = {"-t", "localhost", "-p", "4142", "-P", "password"};
    parse_cmd_args(7, av, &args);
    cr_expect_str_eq(args.port, "4142", "The port should be equal to 4142 and not %s", args.port);
    cr_expect_str_eq(args.ip, "localhost", "The ip should be equal to localhost and not %s", args.ip);
    cr_expect_str_eq(args.password, "password", "The password should be equal to password and not %s", args.password);
}

Test(PARSING, structure_filled_correctly)
{
    cmd_args args;
    args.ip = NULL;
    args.password = NULL;
    args.port = NULL;
    char *av[] = {"-t", "127.0.0.1", "-p", "4142", "-P", "password"};
    parse_cmd_args(7, av, &args);
    cr_expect_not_null(args.port, "The port should be equal to 4142 but was %s", args.port);
    cr_expect_not_null(args.ip, "The IP should be equal to 127.0.0.1 but was %s", args.ip);
    cr_expect_not_null(args.password, "The password should be equal to password but was %s", args.password);
}

Test(PARSING, invalid_args)
{
    cmd_args args;
    args.ip = NULL;
    args.password = NULL;
    args.port = NULL;
    char *av[] = {"-t", "ok", "-p", "nope", "-P", "password"};
    parse_cmd_args(7, av, &args);
    cr_expect_null(args.port, "The port should be null");
    cr_expect_null(args.ip, "The IP should be null");
    cr_expect_null(args.password, "The password should be null");
}

Test(PARSING, check_numeric)
{
    char *str = "localhost";
    cr_expect(check_ip(str), "This should be true; localhost is valid IP");
    str = "127.0.0.1";
    cr_expect(check_ip(str), "This should be true; 127.0.0.1 is valid IP");
    str = "invalid";
    cr_expect(!check_ip(str), "This should be false; invalid IP");
    str = "9000";
    cr_expect(check_port(str), "This should be true; valid port");
}