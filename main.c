#include <stdio.h>
#include <math.h>
#include <locale.h>

// Объявление типа указателя на функцию
typedef double (*TFun)(double);

// Прототипы функций
double Y(double x);
double V(double x);
int calculate(TFun prtf, double *x, int n);

int main()
{
    setlocale(LC_ALL, "RUS");
    int n = 10;
    double x[10];
    int result_Y, result_V;
    printf("Дано:\n");
    puts("Y(x) = 2*sin(πx)*sin(3πx) - 0.5");
    puts("При x < 0: V(x) = 1+2x/1+x^2");
    puts("При 0 ≤ x < 1: V(x) = (sin(x * √(1 + x)))^2");
    puts("При x ≥ 1: V(x) = (sin (x))^2 * e^(0.2 * x)");
    printf("\nВвод %d исходных значений x:\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("Введите значение x: ");
        scanf("%lf", &x[i]);
    }
    printf("\n");
    result_Y = calculate(Y, x, n);
    if (result_Y == 1)
    {
        printf("Функция Y(x) является знакопеременной на заданном интервале\n");
    }
    else
    {
        printf("Функция Y(x) не является знакопеременной на заданном интервале\n");
    }
    result_V = calculate(V, x, n);
    if (result_V == 1)
    {
        printf("Функция V(x) является знакопеременной на заданном интервале\n");
    }
    else
    {
        printf("Функция V(x) не является знакопеременной на заданном интервале\n");
    }

    return 0;
}

// Функция проверки знакопеременности
int calculate(TFun prtf, double *x, int n)
{
    if (n < 2)
    {
        return 0; // Недостаточно точек для анализа
    }
    else
    {
        // Вычисляем первое значение и его знак
        double prev_value = prtf(x[0]);
        int prev_sign = (prev_value > 0) ? 1 : ((prev_value < 0) ? -1 : 0);

        // Проверяем остальные точки
        for (int i = 1; i < n; i++)
        {
            double current_value = prtf(x[i]);
            int current_sign = (current_value > 0) ? 1 : ((current_value < 0) ? -1 : 0);

            // Если функция принимает нулевое значение, считаем это изменением знака
            if (current_sign == 0)
            {
                continue; // пропускаем нулевые значения
            }

            // Если знак изменился по сравнению с предыдущим ненулевым значением
            if (prev_sign != 0 && current_sign != prev_sign)
            {
                return 1; // Функция знакопеременная
            }

            prev_sign = current_sign;
        }

        return 0; // Знак не менялся - функция не знакопеременная
    }
}

//--- Математические функции ---

double Y(double x)
{
    double result = 2 * sin(M_PI * x) * sin(3 * M_PI * x) - 0.5;
    return result;
}

double V(double x)
{
    double result;
    if (x < 0)
    {
        result = (1 + 2 * x) / (1 + x * x);
        return result;
    }
    else if (x < 1)
    {
        result = sin(x) * sin(x) * sqrt(1 + x);
        return result;
    }
    else
    {
        result = sin(x) * sin(x) * exp(0.2 * x);
        return result;
    }
}