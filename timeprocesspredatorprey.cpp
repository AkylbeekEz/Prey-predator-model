#include <bits/stdc++.h>
#include <cstdio>
#include <stdio.h>
#include <math.h>
#define f first
#define s second
#define pb push_back

#define casualgnuplot "C:\\gnuplot\\bin\\gnuplot -persist"

using namespace std;

const double EPS = 1e-9;

const int N = 1e6 + 10;

double v, k;
double a1, b1, a2, b2;
double vv[N];
double kk[N];
double tt[N];
double T;
double n;

int step;

int main() {
    cin >> v;
    cin >> k;
    cin >> a1 >> b1 >> a2 >> b2;
    cin >> T;
    cin >> n;
    double v0 = v - a2/b2;
    double k0 = k - a1/b1;
    step = 0;
    for (double t = 0.0; t <= T; t += (T / n)) {
        tt[step] = t;
        step++;
    }
    step = 0;
    for (double t = 0.0; t <= T; t += (T / n)) {
        vv[step] = a2/b2 + v0 * cos(sqrt(a1 * a2) * t) - k0 * sqrt(a2) * b1 / (b2 * sqrt(a1)) * sin(sqrt(a1 * a2) * t);
        step++;
    }
    step = 0;
    for (double t = 0.0; t <= T; t += (T / n)) {
        kk[step] = a1/b1 + v0 * sqrt(a1) * b2 / (b1 * sqrt(a2)) * sin(sqrt(a1 * a2) * t) + k0 * cos(sqrt(a1 * a2) * t);
        step++;
    }
    FILE *pipe = _popen(casualgnuplot, "w");
    if (pipe != NULL) {
        const int npoints = n;
        fprintf(pipe, "%s\n", "plot '-' using 1:2 title 'victims' with lines, '-' using 1:2 title 'killers' with lines");

        for (int i = 0; i < npoints + 1; i++) {
            double x = tt[i];
            double y = vv[i];
            fprintf(pipe, "%f\t%f\n", x, y);
        }
        fprintf(pipe, "%s\n", "e");

        for (int i = 0; i < npoints + 1; i++) {
            double x = tt[i];
            double y = kk[i];
            fprintf(pipe, "%f\t%f\n", x, y);
        }
        fprintf(pipe, "%s\n", "e");
        fflush(pipe);
        _pclose(pipe);
    } else {
        cout << "Could not open pipe" << endl;
    }
    return 0;
}
