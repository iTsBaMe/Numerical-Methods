#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstdio>
#define my_sizeof(type) ((char *)(&type + 1) - (char *)(&type))
using namespace std;

double K1_f1, K2_f1, K3_f1, K4_f1, K_f1;
double K1_f2, K2_f2, K3_f2, K4_f2, K_f2;
double K1_f3, K2_f3, K3_f3, K4_f3, K_f3;
double eta[71] = {0};
double Y1[71] = {0};
double Y2[71] = {0};
double Y3[71] = {};
double G1{0}, G2{0}, G3{0};

double a{0}, b{0}, c{0};
double c1{0}, c2{0}, c3{0};

double f1(double y2)
{
    return y2;
}

double f2(double y3)
{
    return y3;
}

double f3(double y1, double y3)
{
    return (-y1 * y3) / 2;
}

void RK4(double Y1[5], double Y2[5], double Y[5], double *a, double *b, double *c)
{
    for (int i = 1; i < 71; i++)
    {
        K1_f1 = 0.1 * (f1(Y2[i - 1]));
        K2_f1 = 0.1 * (f1(Y2[i - 1] + K1_f1 / 2));
        K3_f1 = 0.1 * (f1(Y2[i - 1] + K2_f1 / 2));
        K4_f1 = 0.1 * (f1(Y2[i - 1] + K3_f1));

        K1_f2 = 0.1 * (f2(Y3[i - 1]));
        K2_f2 = 0.1 * (f2(Y3[i - 1] + K1_f2 / 2));
        K3_f2 = 0.1 * (f2(Y3[i - 1] + K2_f2 / 2));
        K4_f2 = 0.1 * (f2(Y3[i - 1] + K3_f2));

        K1_f3 = 0.1 * (f3(Y1[i - 1], Y3[i - 1]));
        K2_f3 = 0.1 * (f3(Y1[i - 1] + K1_f3 / 2, Y3[i - 1] + K1_f3 / 2));
        K3_f3 = 0.1 * (f3(Y1[i - 1] + K2_f3 / 2, Y3[i - 1] + K2_f3 / 2));
        K4_f3 = 0.1 * (f3(Y1[i - 1] + K3_f3, Y3[i - 1] + K3_f3));

        K_f1 = (K1_f1 + 2 * K2_f1 + 2 * K3_f1 + K4_f1) / 6;
        K_f2 = (K1_f2 + 2 * K2_f2 + 2 * K3_f2 + K4_f2) / 6;
        K_f3 = (K1_f3 + 2 * K2_f3 + 2 * K3_f3 + K4_f3) / 6;

        Y1[i] = Y1[i - 1] + K_f1;
        Y2[i] = Y2[i - 1] + K_f2;
        Y3[i] = Y3[i - 1] + K_f3;

        *a = Y1[i];
        *b = Y2[i];
        *c = Y3[i];
    }
}

int main()
{
    int i = 1;
    int itr = 1;

    double Ea;
    cout << fixed;

    double epsilon{0};
    while (i < 71)
    {
        eta[i] = eta[i - 1] + 0.1;

        i++;
    }

    cout << "Enter your first random guess for u3" << endl;
    cin >> G1;

    Y3[0] = G1;
    RK4(Y1, Y2, Y3, &a, &b, &c);
    c1 = fabs(Y2[69] - 1);

    cout << "Enter another random guess for u3" << endl; // Should not be the same as G1
    cin >> G2;
    if (G2 == G1)
    {
        cout << "Wrong input" << endl;
        exit(0);
    }
    Y3[0] = G2;
    RK4(Y1, Y2, Y3, &a, &b, &c);
    c2 = fabs(Y2[69] - 1);

    if (c1 == 0 and c2 == 0)
    {
        cout << " Roots found" << endl;
    }
    else
    {
        cout << "No roots found for the entered guess values: " << endl;
    }

    cout << "-------------------------------------------------------------" << endl;

    cout << "We will now calculate the solutions(y2) using the secant method" << endl;
    cout << "-------------------------------------------------------------" << endl;

    cout << "Enter the degree of accuracy or the tolerance" << endl;
    cin >> epsilon;

    while (1)
    {

        G3 = G2 - c2 * ((G2 - G1) / (c2 - c1));
        Y3[0] = G3;
        RK4(Y1, Y2, Y3, &a, &b, &c);
        c3 = Y2[69] - 1;
        Ea = fabs((G3 - G2) / G3);

        G1 = G2;
        G2 = G3;
        c1 = c2;
        c2 = c3;
        itr++;
        if (Ea <= epsilon)
        {
            break;
        }
    }

    cout << "The desired solutions are: " << endl;
    cout << "------------------------------------------" << endl;
    cout << "Y2\teta" << endl;
    for (int i = 0; i < 71; i++)
    {

        cout << setprecision(4) << Y2[i] << "\t" << setprecision(1) << eta[i] << endl;
    }
    // cout << "The correct guess value is: " << setprecision(4) << Y3[0];
    /*for (int i = 0; i < 71; i++)
    {

        cout << setprecision(4) << Y2[i] << endl;
    }

    for (int i = 0; i < 71; i++)
    {

        cout << setprecision(4) << eta[i] << endl;
    }*/
}
