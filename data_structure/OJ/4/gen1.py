import random

def ranstr(num):

    H = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'

    salt = ''
    for i in range(num):
        salt += random.choice(H)

    return salt

import numpy as np
import time
import random
import sys
import os
testCase = 10

for case in range(1, testCase + 1) :

    point = []
    ans = []
    with open('data.in', 'w') as f:

        oldstdout = sys.stdout
        sys.stdout = f
        try:
            n = 40
            m = 20
            print(f'{n} {m}')

            for i in range(0, n) :
                print(f'{random.sample(range(100000000, 1000000000), 1)[0]} {ranstr(10)}')

        finally:
            sys.stdout = oldstdout

    print("generated")

    start = time.time()
    os.system('T4.exe < data.in > res2.txt')
    end = time.time()
    testTime = (end - start) * 1000

    fin = open('res2.txt', 'r')
    testres = fin.readline()
    fin.close()


    start = time.time()
    os.system('3.exe < data.in > res1.txt')
    end = time.time()
    stdTime = (end - start) * 1000

    fin = open('res1.txt', 'r')
    ansres = fin.readline()
    fin.close()


    if (ansres == testres)  :
        print('TestCase{} Successed ----- std time : {} ----- test time: {}'.format(case, stdTime, testTime))
    else :
        print('TestCase{} Failed'.format(case))
        break