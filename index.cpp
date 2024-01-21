#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

// Function to add leading zeros if needed
string addLeadingZeros(const string &str, int numZeros) {
    string zeros(numZeros, '0');
    return zeros + str;
}

// Function to make sure strings are equal length
void makeEqualLength(string &str1, string &str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    if (len1 < len2) {
        str1 = addLeadingZeros(str1, len2 - len1);
    } else if (len2 < len1) {
        str2 = addLeadingZeros(str2, len1 - len2);
    }
}

// Function to add two large numbers represented as strings
string addStrings(const string &num1, const string &num2) {
    string result;
    int carry = 0;
    int sum;

    for (int i = num1.size() - 1; i >= 0; i--) {
        sum = (num1[i] - '0') + (num2[i] - '0') + carry;
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }

    if (carry) {
        result.push_back(carry + '0');
    }

    reverse(result.begin(), result.end());
    return result;
}

// Karatsuba algorithm implementation
string karatsubaMultiply(const string &num1, const string &num2) {
    int len = num1.size();
    if (len == 1) {
        int product = (num1[0] - '0') * (num2[0] - '0');
        return to_string(product);
    }

    int halfLen = len / 2;
    string a = num1.substr(0, halfLen);
    string b = num1.substr(halfLen);
    string c = num2.substr(0, halfLen);
    string d = num2.substr(halfLen);

    string ac = karatsubaMultiply(a, c);
    string bd = karatsubaMultiply(b, d);
    string abcd = karatsubaMultiply(addStrings(a, b), addStrings(c, d));

    string acPlusBd = addStrings(ac, bd);
    string middleTerm = addStrings(abcd, "-" + acPlusBd);

    for (int i = 0; i < 2 * (len - halfLen); i++) {
        ac.push_back('0');
    }

    for (int i = 0; i < len - halfLen; i++) {
        middleTerm.push_back('0');
    }

    string result = addStrings(ac, addStrings(middleTerm, bd));
    return result;
}

int main() {
    string num1, num2;
    cout << "Enter first large number: ";
    cin >> num1;
    cout << "Enter second large number: ";
    cin >> num2;

    makeEqualLength(num1, num2);

    string product = karatsubaMultiply(num1, num2);
    cout << "Product: " << product << endl;

    return 0;
}
