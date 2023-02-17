#include <iostream>
#include <iomanip>
#include <math.h>
#define my_sizeof(type) ((char *)(&type + 1) - (char *)(&type))

using namespace std;

double K1_one, K2_one, K3_one, K4_one, K_one;
double K1_two, K2_two, K3_two, K4_two, K_two;
double x[5] = {0, 0.25, 0.5, 0.75, 1};
double U1[5] = {0.5};
double U2[5] = {};
double G1{0}, G2{0}, G3{0};

double a{0}, b{0};
double c1{0}, c2{0}, c3{0};

double f1(double u2)
{
    return u2;
}

double f2(double u1, double u2)
{
    return 2 * u1 * u2;
}

void RK4(double U1[5], double U2[5], double *a, double *b)
{
    for (int i = 1; i < 5; i++)
    {
        K1_one = 0.25 * (f1(U2[i - 1]));
        K1_two = 0.25 * (f2(U1[i - 1], U2[i - 1]));
        K2_one = 0.25 * (f1(U2[i - 1] + K1_one / 2));
        K2_two = 0.25 * (f2(U1[i - 1] + K1_two / 2, U2[i - 1] + K1_two / 2));
        K3_one = 0.25 * (f1(U2[i - 1] + K2_one / 2));
        K3_two = 0.25 * (f2(U1[i - 1] + K2_two / 2, U2[i - 1] + K2_two / 2));
        K4_one = 0.25 * (f1(U2[i - 1] + K3_one));
        K4_two = 0.25 * (f2(U1[i - 1] + K3_two, U2[i - 1] + K3_two));
        K_one = (K1_one + 2 * K2_one + 2 * K3_one + K4_one) / 6;
        K_two = (K1_two + 2 * K2_two + 2 * K3_two + K4_two) / 6;
        U1[i] = U1[i - 1] + K_one;
        U2[i] = U2[i - 1] + K_two;
        *a = U1[i];
        U2[i] = U2[i - 1] + K_two;
        *b = U2[i];
    }
}

int main()

{
    int i = 1;
    int itr = 1;

    double Ea;
    cout << fixed;

    double epsilon{0};
    while (i < 5)
    {
        x[i] = x[i - 1] + 0.25;

        i++;
    }

    cout << "Enter your first random guess for u2" << endl;
    cin >> G1;
    U2[0] = G1;

    RK4(U1, U2, &a, &b);
    c1 = U1[4] - 1;

    cout << "Enter another random guess for u2" << endl; // G2 should not be equal to G1 because c2 would then be equal to c1
    cin >> G2;
    if (G2 == G1)
    {
        cout << "Wrong input" << endl;
        exit(0);
    }
    U2[0] = G2;

    RK4(U1, U2, &a, &b);
    c2 = U1[4] - 1;

    if (c1 == 0 and c2 == 0)
    {
        cout << " Solutions found" << endl;
    }
    else
    {
        cout << "No solutions for entered guess value" << endl;
    }

    cout << "-------------------------------------------------------------" << endl;

    cout << "We will now calculate U2[0] using the secant method" << endl;
    cout << "----------------------------------------------------" << endl;

    cout << "Enter the degree of accuracy or the tolerance" << endl;
    cin >> epsilon;

    while (1)
    {
        G3 = G2 - c2 * ((G2 - G1) / (c2 - c1));
        U2[0] = G3;
        RK4(U1, U2, &a, &b);
        c3 = U2[4] - 1;
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
    cout << "U1\tx" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << setprecision(2) << U1[i] << "\t" << setprecision(2) << x[i] << endl; // setting precision to 1 does make U1[4] = 1
    }
}
