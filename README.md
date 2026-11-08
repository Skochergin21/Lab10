# Работа 10

## Задание 1. Составьте программу вычисления произведения, разности квадратов и удвоенной суммы значений двух функций

## Задание 2. Составьте программу, которая вычисляет математическую функцию sin(x) тремя различными способами

Вариант 14: ln x = 2((x−1)/(x+1) + (x−1)³/(3(x+1)³) + (x−1)⁵/(5(x+1)⁵) + ...), x > 0.

## Код

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

double fa(double x);
double fb(double x);
double sin_n(double x, int N);
double sin_eps(double x, double eps);
double ln_n(double x, int N);
double ln_eps(double x, double eps);

int main()
{
    double x, y, eps;
    int N, i, vybor;

    setlocale(LC_ALL, "Rus");

    printf("=== Задание 1 ===\n");
    printf("Введите x: ");
    scanf("%lf", &x);
    printf("fa(x)=%lf , fb(x)=%lf\n", fa(x), fb(x));
    printf("произведение %lf, разность квадратов %lf, удвоенная сумма %lf\n",
        fa(x) * fb(x), fa(x) * fa(x) - fb(x) * fb(x), 2 * (fa(x) + fb(x)));

    do
    {
        printf("\nМеню:\n");
        printf("1 - значение fa(x)\n");
        printf("2 - значение fb(x)\n");
        printf("3 - произведение\n");
        printf("4 - разность квадратов\n");
        printf("5 - удвоенная сумма\n");
        printf("6 - ввести другой x\n");
        printf("0 - выход\n");
        printf("Выберите пункт: ");
        vybor = 0;
        scanf("%d", &vybor);

        switch (vybor)
        {
        case 1:
            printf("fa(%g) = %lf\n", x, fa(x));
            break;
        case 2:
            printf("fb(%g) = %lf\n", x, fb(x));
            break;
        case 3:
            printf("произведение = %lf\n", fa(x) * fb(x));
            break;
        case 4:
            printf("разность квадратов = %lf\n", fa(x) * fa(x) - fb(x) * fb(x));
            break;
        case 5:
            printf("удвоенная сумма = %lf\n", 2 * (fa(x) + fb(x)));
            break;
        case 6:
            printf("Введите x: ");
            scanf("%lf", &x);
            break;
        case 0:
            break;
        default:
            printf("Нет такого пункта\n");
        }
    } while (vybor != 0);

    printf("\n=== Задание 2 ===\n");
    printf("Введите x: ");
    scanf("%lf", &x);
    printf("Введите количество членов ряда N: ");
    scanf("%d", &N);
    printf("Введите точность eps: ");
    scanf("%lf", &eps);

    printf("\nsin(x) из библиотеки = %.10f\n", sin(x));
    printf(" N |    sin_n     | отклонение\n");
    for (i = 1; i <= N; i++)
        printf("%2d | %12.8f | %+.4e\n", i, sin_n(x, i), sin_n(x, i) - sin(x));
    printf("sin_eps = %.10f, отклонение %+.4e\n", sin_eps(x, eps), sin_eps(x, eps) - sin(x));

    printf("\nВариант 14: ln x\n");
    printf("Введите x (x > 0): ");
    scanf("%lf", &y);
    if (y <= 0)
        printf("Ошибка! x должен быть больше 0\n");
    else
    {
        printf("\nln(x) из библиотеки = %.10f\n", log(y));
        printf(" N |     ln_n     | отклонение\n");
        for (i = 1; i <= N; i++)
            printf("%2d | %12.8f | %+.4e\n", i, ln_n(y, i), ln_n(y, i) - log(y));
        printf("ln_eps = %.10f, отклонение %+.4e\n", ln_eps(y, eps), ln_eps(y, eps) - log(y));
    }

    return 0;
}

double fa(double x)
{
    double y;
    if (x <= 3)
        y = x * x - 3 * x + 9;
    else
        y = 1 / (x * x * x + 3);
    return y;
}

double fb(double x)
{
    double y;
    y = x * exp(sin(x * x));
    return y;
}

double sin_n(double x, int N)
{
    double chlen = x;
    double summa = 0;
    int k;
    for (k = 1; k <= N; k++)
    {
        summa += chlen;
        chlen = -chlen * x * x / ((2 * k) * (2 * k + 1));
    }
    return summa;
}

double sin_eps(double x, double eps)
{
    double chlen = x;
    double summa = 0;
    int k = 1;
    while (fabs(chlen) >= eps)
    {
        summa += chlen;
        chlen = -chlen * x * x / ((2 * k) * (2 * k + 1));
        k++;
    }
    return summa;
}

double ln_n(double x, int N)
{
    double q = (x - 1) / (x + 1);
    double stepen = q;
    double summa = 0;
    int n;
    for (n = 0; n < N; n++)
    {
        summa += stepen / (2 * n + 1);
        stepen = stepen * q * q;
    }
    return 2 * summa;
}

double ln_eps(double x, double eps)
{
    double q = (x - 1) / (x + 1);
    double stepen = q;
    double summa = 0;
    double chlen = q;
    int n = 0;
    while (fabs(2 * chlen) >= eps)
    {
        summa += chlen;
        n++;
        stepen = stepen * q * q;
        chlen = stepen / (2 * n + 1);
    }
    return 2 * summa;
}
```

## Результат

```
=== Задание 1 ===
Введите x: 2
fa(x)=7,000000 , fb(x)=0,938328
произведение 6,568299, разность квадратов 48,119540, удвоенная сумма 15,876657

Меню:
1 - значение fa(x)
2 - значение fb(x)
3 - произведение
4 - разность квадратов
5 - удвоенная сумма
6 - ввести другой x
0 - выход
Выберите пункт: 1
fa(2) = 7,000000

Меню:
1 - значение fa(x)
2 - значение fb(x)
3 - произведение
4 - разность квадратов
5 - удвоенная сумма
6 - ввести другой x
0 - выход
Выберите пункт: 2
fb(2) = 0,938328

Меню:
1 - значение fa(x)
2 - значение fb(x)
3 - произведение
4 - разность квадратов
5 - удвоенная сумма
6 - ввести другой x
0 - выход
Выберите пункт: 3
произведение = 6,568299

Меню:
1 - значение fa(x)
2 - значение fb(x)
3 - произведение
4 - разность квадратов
5 - удвоенная сумма
6 - ввести другой x
0 - выход
Выберите пункт: 4
разность квадратов = 48,119540

Меню:
1 - значение fa(x)
2 - значение fb(x)
3 - произведение
4 - разность квадратов
5 - удвоенная сумма
6 - ввести другой x
0 - выход
Выберите пункт: 5
удвоенная сумма = 15,876657

Меню:
1 - значение fa(x)
2 - значение fb(x)
3 - произведение
4 - разность квадратов
5 - удвоенная сумма
6 - ввести другой x
0 - выход
Выберите пункт: 6
Введите x: 4

Меню:
1 - значение fa(x)
2 - значение fb(x)
3 - произведение
4 - разность квадратов
5 - удвоенная сумма
6 - ввести другой x
0 - выход
Выберите пункт: 1
fa(4) = 0,014925

Меню:
1 - значение fa(x)
2 - значение fb(x)
3 - произведение
4 - разность квадратов
5 - удвоенная сумма
6 - ввести другой x
0 - выход
Выберите пункт: 0

=== Задание 2 ===
Введите x: 0,785398
Введите количество членов ряда N: 10
Введите точность eps: 0,000001

sin(x) из библиотеки = 0,7071066656
 N |    sin_n     | отклонение
 1 |   0,78539800 | +7,8291e-02
 2 |   0,70465254 | -2,4541e-03
 3 |   0,70714293 | +3,6265e-05
 4 |   0,70710635 | -3,1161e-07
 5 |   0,70710667 | +1,7503e-09
 6 |   0,70710667 | -6,9281e-12
 7 |   0,70710667 | +2,0317e-14
 8 |   0,70710667 | -1,1102e-16
 9 |   0,70710667 | -1,1102e-16
10 |   0,70710667 | -1,1102e-16
sin_eps = 0,7071063540, отклонение -3,1161e-07

Вариант 14: ln x
Введите x (x > 0): 2

ln(x) из библиотеки = 0,6931471806
 N |     ln_n     | отклонение
 1 |   0,66666667 | -2,6481e-02
 2 |   0,69135802 | -1,7892e-03
 3 |   0,69300412 | -1,4307e-04
 4 |   0,69313476 | -1,2423e-05
 5 |   0,69314605 | -1,1332e-06
 6 |   0,69314707 | -1,0680e-07
 7 |   0,69314717 | -1,0304e-08
 8 |   0,69314718 | -1,0117e-09
 9 |   0,69314718 | -1,0070e-10
10 |   0,69314718 | -1,0134e-11
ln_eps = 0,6931470738, отклонение -1,0680e-07
```

## Выполнил

Кочергин Савелий бИД-261
