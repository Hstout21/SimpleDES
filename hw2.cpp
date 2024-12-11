
// Hunter Stout, HW2. :D
// 12/10/2024.

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "constants.h"

static bool debug = false;

class Key {
    public:
        vector<bool> k1;
        vector<bool> k2;
};

//Helper Declaration.
vector<char> GetFile(ifstream& stream);
vector<char> GetInput();
string EasyBinaryString(vector<bool> bin);
vector<bool> EasyGetHalf(vector<bool> original, bool isLeft);
vector<bool> EasyCombine(vector<bool> left, vector<bool> right);
vector<bool> PerformPermutation(int operationNumber, vector<bool> before);
vector<bool> CharToBinary(char input);
char BinaryToChar(vector<bool> input);

//Key Gen Declaration.
Key GenerateKey(int originalKey);
vector<bool> DecimalToBinary(int num);
vector<bool> GetLeftShift(vector<bool> before, int amount);

//SDES Declaration.
vector<bool> PlainToCipher(vector<bool> plain, Key key);
vector<bool> CipherToPlain(vector<bool> cipher, Key key);
vector<bool> PerformRound(vector<bool> before, vector<bool> key);
vector<bool> PerformXOR(vector<bool> first, vector<bool> second);
vector<bool> MatrixLookup(vector<bool> coords, bool isS0);
int GetIndex(bool first, bool second);


//Main.

int main(int argc, char* argv[]) {

    Key key = GenerateKey(stoi(string(argv[1]).substr(2, 3), nullptr, 16));

    bool isEncrypt = getpid() % 2 == 0;

    cout << "Hello, it appears you're in " << (isEncrypt ? "en" : "de") << "crypt mode.\n"
    << "Would you like to use an input file (1) or stdin (2) as your input?\nPlease enter 1 or 2: ";
    string choice;
    getline(cin, choice);
    cout << "\n";
    bool isInFile = choice == "1";
    ifstream in;

    if (isInFile) {
        cout << "Please enter the file to input results (ex: input.txt): ";
        getline(cin, choice);
        cout << "\n";
        in.open(choice);
        isInFile = !in.fail();
    }
    
    vector<char> contents = isInFile ? GetFile(in) : GetInput();

    cout << "Would you like to see debug information? (Y or N): ";
    getline(cin, choice);
    cout << "\n";
    debug = choice == "Y";

    cout << "Would you like to print results to a file (1) or stdout (2)?\nPlease enter 1 or 2: ";
    getline(cin, choice);
    cout << "\n";
    bool isToFile = choice == "1";
    ofstream file;

    if (isToFile) {
        cout << "Please enter the file to output results (ex: cipher.txt): ";
        getline(cin, choice);
        cout << "\n";
        file.open(choice);
        isToFile = !file.fail();
    }

    for (size_t i = 0; i < contents.size(); i++) {
        vector<bool> binary = CharToBinary(contents[i]);
        (isToFile ? file : cout) << BinaryToChar(isEncrypt ? PlainToCipher(binary, key) : CipherToPlain(binary, key));
    }

    if (!isToFile) { cout << "\n"; }

    return 0;
}


// Helper Functions.

vector<char> GetFile(ifstream& stream) {
    vector<char> retVal;
    string temp;
    while (getline(stream, temp)) {
        for(size_t i = 0; i < temp.size(); i++) {
            retVal.push_back(temp[i]);
        }
    }
    return retVal;
}

vector<char> GetInput() {
    vector<char> retVal;
    string input;
    cout << "Please enter string: ";
    getline(cin, input);
    cout << "\n";
    for (size_t i = 0; i < input.size(); i++) { retVal.push_back(input[i]); }
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
    size_t start = isLeft ? 0 : original.size()/2;
    size_t size = isLeft ? original.size()/2 : original.size();
    for (size_t i = start; i < size; i++) { retVal.push_back(original[i]); }
    return retVal;
}

vector<bool> EasyCombine(vector<bool> left, vector<bool> right) {
    vector<bool> retVal;
    for (size_t i = 0; i < left.size(); i++) { retVal.push_back(left[i]); }
    for (size_t i = 0; i < right.size(); i++) { retVal.push_back(right[i]); }
    return retVal;
}

vector<bool> PerformPermutation(int operationNumber, vector<bool> before) {
    vector<bool> retVal;
    Permutation newOp(operationNumber);
    for (int i = 0; i < newOp.size; i++) { retVal.push_back(before[newOp.indexes[i]]); }
    if (debug) { cout << "\n" << newOp.title << " Started (" << EasyBinaryString(before) << ")...\n"
        << newOp.title << " Finished (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

vector<bool> CharToBinary(char input) {
    vector<bool> retVal;
    for (int i = 7; i >= 0; --i) { retVal.push_back((input >> i) & 1); }
    return retVal;
}

char BinaryToChar(vector<bool> input) {
    char retVal = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i]) { retVal |= (1 << (7 - i)); }
    }
    return retVal;
}


// Key Gen Functions.

Key GenerateKey(int originalKey) {
    Key retVal;
    if (debug) { cout << "\nStarting Key Generation (" << originalKey << ")...\n"; }
    vector<bool> p10 = PerformPermutation(operationP10, DecimalToBinary(originalKey));
    vector<bool> left = GetLeftShift(EasyGetHalf(p10, 1), 1);
    vector<bool> right = GetLeftShift(EasyGetHalf(p10, 0), 1);
    retVal.k1 = PerformPermutation(operationP8, EasyCombine(left, right));
    retVal.k2 = PerformPermutation(operationP8, EasyCombine(GetLeftShift(left, 2), GetLeftShift(right, 2)));
    if (debug) { cout << "\nFinished Key Generation (k1:" << EasyBinaryString(retVal.k1) << ", k2:" << EasyBinaryString(retVal.k2) << ")...\n"; }
    return retVal;
}

vector<bool> DecimalToBinary(int num) {
    vector<bool> retVal;
    if (num >= (1 << 10)) { cout << "Error, key is invalid\n"; return retVal; }
    for (int i = 9; i >= 0; --i) { retVal.push_back(num & (1 << i)); }
    if (debug) { cout << "\nHex To Binary Started (" << num << ")...\n"
        << "Hex To Binary Finished (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

vector<bool> GetLeftShift(vector<bool> before, int amount) {
    vector<bool> retVal;
    for (size_t i = amount; i < before.size(); i++) { retVal.push_back(before[i]); }
    for (int i = 0; i < amount; i++) { retVal.push_back(before[i]); }
    if (debug) { cout << "\nx" << amount << " Left Shift Started (" << EasyBinaryString(before) << ")...\n"
        << "x" << amount << " Left Shift Finished (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

vector<bool> PlainToCipher(vector<bool> plain, Key key) {
    if (debug) { cout << "\nP->C Started (" << EasyBinaryString(plain) << ")...\n"; }
    vector<bool> round1 = PerformRound(PerformPermutation(operationIP, plain), key.k1);
    vector<bool> round2 = PerformRound(EasyCombine(EasyGetHalf(round1, 1), EasyGetHalf(round1, 0)), key.k2);
    vector<bool> retVal = PerformPermutation(operationIIP, round2);
    if (debug) { cout << "\nP->C Finished (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}


// SDES Functions.

vector<bool> CipherToPlain(vector<bool> cipher, Key key) {
    if (debug) { cout << "\nC->P Started (" << EasyBinaryString(cipher) << ")...\n"; }
    vector<bool> round1 = PerformRound(PerformPermutation(operationIP, cipher), key.k2);
    vector<bool> round2 = PerformRound(EasyCombine(EasyGetHalf(round1, 1), EasyGetHalf(round1, 0)), key.k1);
    vector<bool> retVal = PerformPermutation(operationIIP, round2);
    if (debug) { cout << "\nC->P Finished (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

vector<bool> PerformRound(vector<bool> before, vector<bool> key) {
    if (debug) { cout << "\nStarting Round (" << EasyBinaryString(before) << ", key:" << EasyBinaryString(key) << ")...\n"; }
    vector<bool> left = EasyGetHalf(before, 1);
    vector<bool> right = EasyGetHalf(before, 0);
    vector<bool> firstXor = PerformXOR(PerformPermutation(operationEP, right), key);
    vector<bool> p4 = PerformPermutation(operationP4, EasyCombine(
        MatrixLookup(EasyGetHalf(firstXor, 1), 1),
        MatrixLookup(EasyGetHalf(firstXor, 0), 0))
    );
    vector<bool> retVal = EasyCombine(PerformXOR(p4, left), right);
    if (debug) { cout << "\nFinished Round (" << EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

vector<bool> PerformXOR(vector<bool> first, vector<bool> second) {
    vector<bool> retVal;
    for (size_t i = 0; i < first.size(); i++) { retVal.push_back(first[i] != second[i]); }
    if (debug) { cout << "\nXOR Finished:\n" << EasyBinaryString(first) << "\n" 
        << EasyBinaryString(second) << "\n----\n" << EasyBinaryString(retVal) << " ...\n"; }
    return retVal;
}

vector<bool> MatrixLookup(vector<bool> coords, bool isS0) {
    vector<bool> retVal;
    int row = GetIndex(coords[0], coords[3]);
    int col = GetIndex(coords[1], coords[2]);
    string lookup = isS0 ? s0[row][col] : s1[row][col];
    for (size_t i = 0; i < lookup.length(); i++) { retVal.push_back(lookup[i] == '1'); }
    if (debug) { cout << "\n" << (isS0 ? "S0" : "S1") << " Matrix Lookup Finished (coords:" << EasyBinaryString(coords) 
        << ", row:" << row << ", col:" << col << ", found:"<< EasyBinaryString(retVal) << ")...\n"; }
    return retVal;
}

int GetIndex(bool first, bool second) {
    if (first) { return second ? 3 : 2; }
    return second ? 1 : 0;
}