#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "calculator.h"

#define EPSILON 1e-9

static int tests_run = 0;
static int tests_failed = 0;

static void assert_double_equal(double actual, double expected, const char *test_name) {
    tests_run++;
    if (fabs(actual - expected) > EPSILON) {
        printf("FAILED: %s (expected %f, got %f)\n", test_name, expected, actual);
        tests_failed++;
    } else {
        printf("PASSED: %s\n", test_name);
    }
}

static void assert_status(CalcStatus actual, CalcStatus expected, const char *test_name) {
    tests_run++;
    if (actual != expected) {
        printf("FAILED: %s (expected status %d, got %d)\n", test_name, expected, actual);
        tests_failed++;
    } else {
        printf("PASSED: %s\n", test_name);
    }
}

static void test_addition(void) {
    double res;
    CalcStatus status = calc_add(15.5, 4.5, &res);
    assert_status(status, CALC_SUCCESS, "test_addition_status");
    assert_double_equal(res, 20.0, "test_addition_value");

    calc_add(-10.0, -5.0, &res);
    assert_double_equal(res, -15.0, "test_addition_negatives");
}

static void test_subtraction(void) {
    double res;
    CalcStatus status = calc_subtract(10.0, 3.0, &res);
    assert_status(status, CALC_SUCCESS, "test_subtraction_status");
    assert_double_equal(res, 7.0, "test_subtraction_value");

    calc_subtract(5.0, 12.0, &res);
    assert_double_equal(res, -7.0, "test_subtraction_negative_result");
}

static void test_multiplication(void) {
    double res;
    CalcStatus status = calc_multiply(2.5, 4.0, &res);
    assert_status(status, CALC_SUCCESS, "test_multiplication_status");
    assert_double_equal(res, 10.0, "test_multiplication_value");

    calc_multiply(-3.0, 4.0, &res);
    assert_double_equal(res, -12.0, "test_multiplication_negative");
}

static void test_division(void) {
    double res;
    CalcStatus status = calc_divide(20.0, 4.0, &res);
    assert_status(status, CALC_SUCCESS, "test_division_status");
    assert_double_equal(res, 5.0, "test_division_value");

    status = calc_divide(10.0, 0.0, &res);
    assert_status(status, CALC_ERR_DIV_BY_ZERO, "test_division_by_zero");
}

static void test_modulo(void) {
    double res;
    CalcStatus status = calc_modulo(10.0, 3.0, &res);
    assert_status(status, CALC_SUCCESS, "test_modulo_status");
    assert_double_equal(res, 1.0, "test_modulo_value");

    status = calc_modulo(10.0, 0.0, &res);
    assert_status(status, CALC_ERR_DIV_BY_ZERO, "test_modulo_by_zero");
}

static void test_power(void) {
    double res;
    CalcStatus status = calc_power(2.0, 3.0, &res);
    assert_status(status, CALC_SUCCESS, "test_power_status");
    assert_double_equal(res, 8.0, "test_power_value");

    calc_power(5.0, 0.0, &res);
    assert_double_equal(res, 1.0, "test_power_zero_exp");

    status = calc_power(0.0, -1.0, &res);
    assert_status(status, CALC_ERR_DIV_BY_ZERO, "test_power_zero_negative_exp");
}

static void test_evaluate(void) {
    double res;
    CalcStatus status;

    status = calc_evaluate('+', 12.0, 8.0, &res);
    assert_status(status, CALC_SUCCESS, "evaluate_+");
    assert_double_equal(res, 20.0, "evaluate_+_val");

    status = calc_evaluate('-', 12.0, 8.0, &res);
    assert_status(status, CALC_SUCCESS, "evaluate_-");
    assert_double_equal(res, 4.0, "evaluate_-_val");

    status = calc_evaluate('*', 6.0, 7.0, &res);
    assert_status(status, CALC_SUCCESS, "evaluate_*");
    assert_double_equal(res, 42.0, "evaluate_*_val");

    status = calc_evaluate('x', 6.0, 7.0, &res);
    assert_status(status, CALC_SUCCESS, "evaluate_x");
    assert_double_equal(res, 42.0, "evaluate_x_val");

    status = calc_evaluate('/', 100.0, 5.0, &res);
    assert_status(status, CALC_SUCCESS, "evaluate_/");
    assert_double_equal(res, 20.0, "evaluate_/_val");

    status = calc_evaluate('%', 17.0, 5.0, &res);
    assert_status(status, CALC_SUCCESS, "evaluate_%");
    assert_double_equal(res, 2.0, "evaluate_%_val");

    status = calc_evaluate('^', 3.0, 4.0, &res);
    assert_status(status, CALC_SUCCESS, "evaluate_^");
    assert_double_equal(res, 81.0, "evaluate_^_val");

    status = calc_evaluate('?', 3.0, 4.0, &res);
    assert_status(status, CALC_ERR_INVALID_OP, "evaluate_invalid_op");
}

static void test_null_pointers(void) {
    CalcStatus status = calc_add(1.0, 2.0, NULL);
    assert_status(status, CALC_ERR_INVALID_INPUT, "test_null_pointer_add");

    status = calc_divide(1.0, 2.0, NULL);
    assert_status(status, CALC_ERR_INVALID_INPUT, "test_null_pointer_div");
}

int main(void) {
    printf("Starting calculator test suite...\n\n");

    test_addition();
    test_subtraction();
    test_multiplication();
    test_division();
    test_modulo();
    test_power();
    test_evaluate();
    test_null_pointers();

    printf("\nTest Summary: %d executed, %d failed.\n", tests_run, tests_failed);

    return tests_failed == 0 ? 0 : 1;
}
