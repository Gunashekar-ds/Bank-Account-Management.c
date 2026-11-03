#ifndef CALCULATOR_H
#define CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CALC_SUCCESS = 0,
    CALC_ERR_DIV_BY_ZERO = 1,
    CALC_ERR_INVALID_OP = 2,
    CALC_ERR_OVERFLOW = 3,
    CALC_ERR_UNDERFLOW = 4,
    CALC_ERR_INVALID_INPUT = 5
} CalcStatus;

/* Core arithmetic operations */
CalcStatus calc_add(double a, double b, double *result);
CalcStatus calc_subtract(double a, double b, double *result);
CalcStatus calc_multiply(double a, double b, double *result);
CalcStatus calc_divide(double a, double b, double *result);
CalcStatus calc_modulo(double a, double b, double *result);
CalcStatus calc_power(double base, double exponent, double *result);

/* Evaluation helper for operators (+, -, *, /, %, ^) */
CalcStatus calc_evaluate(char op, double a, double b, double *result);

/* Convert error code to human-readable string */
const char* calc_error_string(CalcStatus status);

#ifdef __cplusplus
}
#endif

#endif /* CALCULATOR_H */
