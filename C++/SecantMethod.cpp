#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double f(double x)
{
    return x * x - 9 * x + 20;
}

int main()
{
    double x0{0};      // first initial guess
    double x1{0};      // second initial guess
    double x2{0};      // value of roots
    double epsilon{0}; // degree of accuracy or tolerance
    int max_iter{0};   // max no of iterations
    int iter{0};       // looping variable

    cout << "Enter the first initial guess" << endl;
    cin >> x0;
    cout << "Enter the second initial guess" << endl;
    cin >> x1;
    cout << "Enter the maximum number of iterations" << endl;
    cin >> max_iter;
    cout << "Enter the degree of accuracy or the tolerance" << endl;
    cin >> epsilon;
    cout << fixed;

    // cout << "\nx0\tf(x0)\tx1\tf(x1)\tx2\tf(x2)" << endl;
    // uncomment to display output in tabular format

    // secant method
    for (int iter = 1; iter <= max_iter; iter++)
    {
        x2 = x1 - f(x1) * ((x1 - x0) / (f(x1) - f(x0)));
        // uncomment the code below for taular format output
        //  cout << setprecision(4) << x0 << "\t" << setprecision(4) << f(x0) << "\t" << setprecision(4) << x1 << "\t" << setprecision(4) << f(x1) << "\t" << setprecision(4) << x2 << "\t" << setprecision(4) << f(x2) << "\t" << endl;
        //  different ways of expressing output
        cout << "The value of x" << iter + 1 << " is " << setprecision(4) << x2 << endl; // comment this line to display the above output in tabular format

        if (fabs(x2 - x1) < epsilon)
        {
            break;
        }
        x0 = x1;
        x1 = x2;
    }
    cout << "------------------------------------------------------" << endl;
    cout << "The root of "
         << "x * x - 9 * x + 20"
         << " is = " << x2 << endl;
    return 0;
}
