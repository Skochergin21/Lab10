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
