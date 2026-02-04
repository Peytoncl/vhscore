#ifndef MATHEXT

#define MATHEXT

double dlerp(double a, double b, double t)
{
    return a + t * (b - a);
}

#endif