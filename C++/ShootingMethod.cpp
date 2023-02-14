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
    cout << fixed;

    double epsilon{0};
    // int max_iter{0};
    cout << "Enter your first random guess for u2" << endl;
    cin >> G1;
    U2[0] = G1;

    RK4(U1, U2, &a, &b);
    c1 = U1[4] - 1;

    cout << "Enter another random guess for u2" << endl; // G2 should not be equal to G1 because c2 would then be equal to c1
    cin >> G2;
    U2[0] = G2;

    RK4(U1, U2, &a, &b);
    c2 = U1[4] - 1;

    if (c1 == 0 and c2 == 0)
    {
        cout << U1[1] << ", " << U1[2] << ", " << U1[3] << " are the solutions of the equation";
    }
    else
    {
        if (G2 == G1)
        {
            cout << "Wrong input" << endl;
        }
        else
        {

            cout << "-------------------------------------------------------------" << endl;

            cout << setprecision(2) << U1[1] << ", " << U1[2] << ", " << U1[3] << " is not the solution of the equation" << endl;
            cout << "We will now calculate U2[0] using the secant method" << endl;
            cout << "----------------------------------------------------" << endl;

            cout << "Enter the degree of accuracy or the tolerance" << endl;
            cin >> epsilon;
            /*cout << "Enter the maximum number of iterations " << endl;
            cin >> max_iter;*/

            while (fabs(G3 - G2) > epsilon)
            {
                G3 = G2 - c2 * ((G2 - G1) / (c2 - c1));
                U2[0] = G3;
                RK4(U1, U2, &a, &b);
                c3 = U1[4] - 1;
                if (c3 == 0)
                {

                    break;
                }
                G2 = G3;
                c2 = c3;
                G1 = G2;
            }
            cout << "The values of U1 are" << endl;
            cout << "-------------------------------------------------------------" << endl;

            for (int i = 0; i < my_sizeof(U1) / my_sizeof(U1[0]); i++)
            {
                cout << setprecision(2) << U1[i] << "\t";
            }
            cout << " \n";
            cout << "-------------------------------------------------------------" << endl;
            cout << "The values of U2 are" << endl;
            cout << "-------------------------------------------------------------" << endl;
            for (int j = 0; j < my_sizeof(U2) / my_sizeof(U2[0]); j++)
            {
                cout << setprecision(2) << U2[j] << "\t";
            }
            cout << "\n";
            cout << "-------------------------------------------------------------" << endl;
            cout << U1[1] << ", " << U1[2] << ", " << U1[3] << " are the solutions of the equation";
        }
    }
}
