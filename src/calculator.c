#include "calculator.h"
#include <math.h>
#include <float.h>

CalcStatus calc_add(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    *result = a + b;
    if (isinf(*result)) {
        return CALC_ERR_OVERFLOW;
    }
    return CALC_SUCCESS;
}

CalcStatus calc_subtract(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    *result = a - b;
    if (isinf(*result)) {
        return CALC_ERR_OVERFLOW;
    }
    return CALC_SUCCESS;
}

CalcStatus calc_multiply(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    *result = a * b;
    if (isinf(*result)) {
        return CALC_ERR_OVERFLOW;
    }
    return CALC_SUCCESS;
}

CalcStatus calc_divide(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    if (fabs(b) == 0.0) {
        return CALC_ERR_DIV_BY_ZERO;
    }
    *result = a / b;
    if (isinf(*result)) {
        return CALC_ERR_OVERFLOW;
    }
    return CALC_SUCCESS;
}

CalcStatus calc_modulo(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    if (fabs(b) == 0.0) {
        return CALC_ERR_DIV_BY_ZERO;
    }
    *result = fmod(a, b);
    return CALC_SUCCESS;
}

CalcStatus calc_power(double base, double exponent, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    if (base == 0.0 && exponent < 0.0) {
        return CALC_ERR_DIV_BY_ZERO;
    }
    *result = pow(base, exponent);
    if (isnan(*result)) {
        return CALC_ERR_INVALID_INPUT;
    }
    if (isinf(*result)) {
        return CALC_ERR_OVERFLOW;
    }
    return CALC_SUCCESS;
}

CalcStatus calc_evaluate(char op, double a, double b, double *result) {
    switch (op) {
        case '+':
            return calc_add(a, b, result);
        case '-':
            return calc_subtract(a, b, result);
        case '*':
        case 'x':
        case 'X':
            return calc_multiply(a, b, result);
        case '/':
            return calc_divide(a, b, result);
        case '%':
            return calc_modulo(a, b, result);
        case '^':
            return calc_power(a, b, result);
        default:
            return CALC_ERR_INVALID_OP;
    }
}

const char* calc_error_string(CalcStatus status) {
    switch (status) {
        case CALC_SUCCESS:
            return "Success";
        case CALC_ERR_DIV_BY_ZERO:
            return "Error: Division or modulo by zero is undefined.";
        case CALC_ERR_INVALID_OP:
            return "Error: Invalid or unsupported operator.";
        case CALC_ERR_OVERFLOW:
            return "Error: Arithmetic overflow.";
        case CALC_ERR_UNDERFLOW:
            return "Error: Arithmetic underflow.";
        case CALC_ERR_INVALID_INPUT:
            return "Error: Invalid numeric input.";
        default:
            return "Error: Unknown error occurred.";
    }
}
