
// Hunter Stout, HW2.

#include <iostream>
#include <bitset>
#include <vector>
#include "constants.h"

using namespace std;

class Key {
    public:
        vector<bool> k1;
        vector<bool> k2;
};

//Functions.
vector<char> GetFile();
string EasyBinaryString(vector<bool> bin);
vector<bool> EasyGetHalf(vector<bool> original, bool isLeft);
vector<bool> EasyCombine(vector<bool> left, vector<bool> right);

//Key Gen Functions.
Key GenerateKey(int originalKey);
vector<bool> DecimalToBinary(int num);
vector<bool> GetP10(vector<bool> before);
vector<bool> GetLeftShift(vector<bool> before, int amount);
vector<bool> GetP8(vector<bool> before);

//SDES Functions.

int main(int argc, char* argv[]) {

    Key key = GenerateKey(stoi(string(argv[1]).substr(2, 3), nullptr, 16));
    vector<char> fileContents = GetFile();

    cout << endl << endl << endl;
    for (int i = 0; i < fileContents.size(); i++) {
        cout << fileContents[i];
    }
    cout << endl << endl << endl;
    return 0;
}

#pragma region Helpers

vector<char> GetFile() {
    vector<char> retVal;
    string temp;
    while (getline(cin, temp)) {
        for(int i = 0; i < temp.size(); i++) {
            retVal.push_back(temp[i]);
        }
    }
    return retVal;
}

string EasyBinaryString(vector<bool> bin) {
    string retVal = "";
    for (size_t i = 0; i < bin.size(); i++) {
        if (bin[i]) { retVal += "1"; }
        else { retVal += "0"; }
    }
    return retVal;
}

vector<bool> EasyGetHalf(vector<bool> original, bool isLeft) {
    vector<bool> retVal;
    size_t i = isLeft ? 0 : original.size()/2;
    size_t size = isLeft ? original.size()/2 : original.size();
    for (i; i < size; i++) { retVal.push_back(original[i]); }
    return retVal;
}

vector<bool> EasyCombine(vector<bool> left, vector<bool> right) {
    vector<bool> retVal;
    for (size_t i = 0; i < left.size(); i++) { retVal.push_back(left[i]); }
    for (size_t i = 0; i < right.size(); i++) { retVal.push_back(right[i]); }
    return retVal;
}

#pragma endregion

#pragma region KeyGeneration

Key GenerateKey(int originalKey) {

    Key retVal;

    if (debug) { cout << "Starting Key Generation (" << originalKey << ")...\n"; }

    vector<bool> p10 = GetP10(DecimalToBinary(originalKey));
    vector<bool> left = GetLeftShift(EasyGetHalf(p10, 1), 1);
    vector<bool> right = GetLeftShift(EasyGetHalf(p10, 0), 1);
    retVal.k1 = GetP8(EasyCombine(left, right));
    retVal.k2 = GetP8(EasyCombine(GetLeftShift(left, 2), GetLeftShift(right, 2)));

    if (debug) { cout << "Finished Key Generation (k1:" << EasyBinaryString(retVal.k1) << ", k2:" << EasyBinaryString(retVal.k2) << ")...\n"; }

    return retVal;
}

vector<bool> DecimalToBinary(int num) {
    vector<bool> retVal;
    if (num >= (1 << 10)) { cout << "Error, key is invalid\n"; return retVal; }
    for (int i = 9; i >= 0; --i) { retVal.push_back(num & (1 << i)); }
    if (debug) { cout << "Hex To Binary Started (" << num << ")...\n"
        << "Hex To Binary Finished (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

vector<bool> GetP10(vector<bool> before) {
    vector<bool> retVal;
    for (int i = 0; i < 10; i++) { retVal.push_back(before[p10[i]]); }
    if (debug) { cout << "P10 Started (" << EasyBinaryString(before) << ")...\n"
        << "P10 Finished (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

vector<bool> GetLeftShift(vector<bool> before, int amount) {
    vector<bool> retVal;
    for (int i = amount; i < before.size(); i++) { retVal.push_back(before[i]); }
    for (int i = 0; i < amount; i++) { retVal.push_back(before[i]); }
    if (debug) { cout << "x" << amount << " Left Shift Started (" << EasyBinaryString(before) << ")...\n"
        << "x" << amount << " Left Shift Finished (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

vector<bool> GetP8(vector<bool> before) {
    vector<bool> retVal;
    for (int i = 0; i < 8; i++) { retVal.push_back(before[p8[i]]); }
    if (debug) { cout << "P8 Started (" << EasyBinaryString(before) << ")...\n"
        << "P8 Finished (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

#pragma endregion

#pragma region SDES

#pragma endregion