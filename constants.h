
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
using namespace std;

const string s0[4][4] = {
    {"01", "00", "11", "10"},
    {"11", "10", "01", "00"},
    {"00", "10", "01", "11"},
    {"11", "01", "11", "10"}
};
const string s1[4][4] = {
    {"00", "01", "10", "11"},
    {"10", "00", "01", "11"},
    {"11", "00", "01", "00"},
    {"10", "01", "00", "11"}
};

const int operationP10 = 1;
const int operationP8 = 2;
const int operationP4 = 3;
const int operationEP = 4;
const int operationIP = 5;
const int operationIIP = 6;

class Permutation {
    public:
        Permutation(int operation) {
           if (operation == operationP10) {
                title = "P10";
                size = 10;
                indexes = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5}; // Actual {3, 5, 2, 7, 4, 10, 1, 9, 8, 6}
           }
           else if (operation == operationP8) {
                title = "P8";
                size = 8;
                indexes = {5, 2, 6, 3, 7, 4, 9, 8}; // Actual {6, 3, 7, 4, 8, 5, 10, 9}
           }
           else if (operation == operationP4) {
                title = "P4";
                size = 4;
                indexes = {1, 3, 2, 0}; // Actual {2, 4, 3, 1}
           }
           else if (operation == operationEP) {
                title = "EP";
                size = 8;
                indexes = {3, 0, 1, 2, 1, 2, 3, 0}; // Actual {4, 1, 2, 3, 2, 3, 4, 1}
           }
           else if (operation == operationIP) {
                title = "IP";
                size = 8;
                indexes = {1, 5, 2, 0, 3, 7, 4, 6}; // Actual {2, 6, 3, 1, 4, 8, 5, 7}
           }
           else if (operation == operationIIP) {
                title = "IP^-1";
                size = 8;
                indexes = {3, 0, 2, 4, 6, 1, 7, 5}; // Actual {4, 1, 3, 5, 7, 2, 8, 6}
           }
        }
        string title;
        int size;
        vector<int> indexes;
};

#endif