#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

static void print_usage(const char *prog_name) {
    printf("Usage:\n");
    printf("  Interactive mode:\n");
    printf("    %s\n", prog_name);
    printf("  Command line mode:\n");
    printf("    %s <number1> <operator> <number2>\n", prog_name);
    printf("  Operators supported: + , - , * (or x), / , %% , ^\n");
    printf("  Example:\n");
    printf("    %s 10 + 25\n", prog_name);
    printf("    %s 2 ^ 8\n", prog_name);
}

static void print_menu(void) {
    printf("\n========================================\n");
    printf("           Simple Calculator            \n");
    printf("========================================\n");
    printf(" 1. Addition (+)\n");
    printf(" 2. Subtraction (-)\n");
    printf(" 3. Multiplication (*)\n");
    printf(" 4. Division (/)\n");
    printf(" 5. Modulo (%%)\n");
    printf(" 6. Power (^)\n");
    printf(" 7. Exit\n");
    printf("----------------------------------------\n");
    printf("Enter choice (1-7): ");
}

static void run_interactive(void) {
    int choice;
    double a, b, result;
    char op;
    CalcStatus status;

    printf("Welcome to Simple Calculator!\n");

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            /* Clear invalid input */
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid selection. Please enter a number between 1 and 7.\n");
            continue;
        }

        if (choice == 7) {
            printf("Exiting Simple Calculator. Goodbye!\n");
            break;
        }

        switch (choice) {
            case 1: op = '+'; break;
            case 2: op = '-'; break;
            case 3: op = '*'; break;
            case 4: op = '/'; break;
            case 5: op = '%'; break;
            case 6: op = '^'; break;
            default:
                printf("Invalid selection. Please enter a number between 1 and 7.\n");
                continue;
        }

        printf("Enter first number: ");
        if (scanf("%lf", &a) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid number entered.\n");
            continue;
        }

        printf("Enter second number: ");
        if (scanf("%lf", &b) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid number entered.\n");
            continue;
        }

        status = calc_evaluate(op, a, b, &result);
        if (status == CALC_SUCCESS) {
            printf("\n>>> Result: %g %c %g = %g\n", a, op, b, result);
        } else {
            printf("\n>>> %s\n", calc_error_string(status));
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        run_interactive();
        return 0;
    }

    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_usage(argv[0]);
        return 0;
    }

    if (argc == 4) {
        char *endptr1, *endptr2;
        double a = strtod(argv[1], &endptr1);
        double b = strtod(argv[3], &endptr2);
        char op;
        double result;
        CalcStatus status;

        if (*endptr1 != '\0' || argv[1] == endptr1) {
            fprintf(stderr, "Error: Invalid first number '%s'\n", argv[1]);
            return 1;
        }

        if (strlen(argv[2]) != 1) {
            fprintf(stderr, "Error: Invalid operator '%s'. Expected single character: +, -, *, /, %%, ^\n", argv[2]);
            return 1;
        }
        op = argv[2][0];

        if (*endptr2 != '\0' || argv[3] == endptr2) {
            fprintf(stderr, "Error: Invalid second number '%s'\n", argv[3]);
            return 1;
        }

        status = calc_evaluate(op, a, b, &result);
        if (status != CALC_SUCCESS) {
            fprintf(stderr, "%s\n", calc_error_string(status));
            return 1;
        }

        printf("%g\n", result);
        return 0;
    }

    fprintf(stderr, "Error: Invalid arguments.\n\n");
    print_usage(argv[0]);
    return 1;
}
