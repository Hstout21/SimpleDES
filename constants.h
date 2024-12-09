
#ifndef CONSTANTS_H
#define CONSTANTS_H

const bool debug = true;

const int s0[4][4] = {
    {01, 00, 11, 10},
    {11, 10, 01, 00},
    {00, 10, 01, 11},
    {11, 01, 11, 10}
};
const int s1[4][4] = {
    {00, 01, 10, 11},
    {10, 00, 01, 11},
    {11, 00, 01, 00},
    {10, 01, 00, 11}
};

          // Actual {3, 5, 2, 7, 4, 10, 1, 9, 8, 6}
const int p10[10] = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5};

        // Actual {6, 3, 7, 4, 8, 5, 10, 9};
const int p8[8] = {5, 2, 6, 3, 7, 4, 9, 8};

        // Actual {2, 4, 3, 1};
const int p4[4] = {1, 3, 2, 0};

        // Actual {4, 1, 2, 3, 2, 3, 4, 1}
const int ep[8] = {3, 0, 1, 2, 1, 2, 3, 0};

        // Actual {2, 6, 3, 1, 4, 8, 5, 7}
const int ip[8] = {1, 5, 2, 0, 3, 7, 4, 6};

               // Actual {4, 1, 3, 5, 7, 2, 8, 6}
const int inverseIp[8] = {3, 0, 2, 4, 6, 1, 7, 5};

#endif