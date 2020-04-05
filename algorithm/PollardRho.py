#!/usr/bin/env python
import gmpy2

def pollard_rho(n):
    x_fixed = 2
    cycle_size = 2
    x = 2
    factor = 1
    while factor == 1:
        count = 1
        while count <= cycle_size and factor <= 1:
            x = (x ** 2 + 1) % n
            factor = gmpy2.gcd(x - x_fixed, n)
            count += 1
        cycle_size *= 2
        x_fixed = x
    return factor

if __name__ == '__main__':
    n = 10403
    res = pollard_rho(n)
    print res

