#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

double extractNumeric(const string& str);

int main() { // All of main is provided.
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric(input);

        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4)
                 << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }
    return 0;
}

double extractNumeric(const string& str){
    // First we'll just iterate to see if invalid characters are in the string.
    string valid_chars = "0123456789+-.";
    int signCount = 0;
    int pointCount = 0;
    for (int i = 0; i < str.length(); i++){ // Compare valid chars against each char in string.
        bool isValid = false;
        if (str[i] == valid_chars[10] || str[i] == valid_chars[11]) {
                signCount++;
            }
        else if (str[i] == valid_chars[12]){
            pointCount++;
        }
        for (int j = 0; j < valid_chars.length(); j++){
            if (str[i] == valid_chars[j]) {
                isValid = true;
            }
        }
        if (isValid){
            continue;
        }
        else {
            return -999999.99;
        }
    }

    // So what we should now have at this point is a string with only the valid characters
    // Now it's just a matter of ensuring proper formatting.

    // Part 1: Checking the sign.
    // While iterating above, we keep track of how many times a sign is used.
    if (signCount > 1){ // There can only ever be one or no sign so if there's more...
        return -999999.99;
    }
    else if (signCount == 1){ // If there is one sign it has to be up front.
        if (str[0] != valid_chars[10]){ // If the front isn't a plus sign
            if (str[0] != valid_chars[11]){ // If the front isn't a minus sign
                return -999999.99;
            }
        }
    }

    // Part 2: Checking the decimal point.
    // Strictly speaking, there should only be one or no decimal point, ever.
    if (pointCount > 1){
        return -999999.99;
    }
    // Unlike sign, we don't really care where the decimal point is so we're done.

    // Part 3: Assembling the number.
    // We now have a properly formatted and valid input string at this point.
    // All that's left is turning it into a number. We start by reading the sign.
    bool isPositive = true;
    string str1 = str; // We then get a new string variable to edit the original.
    if (str[0] == valid_chars[10]){
        str1 = str.substr(1, (str.length() - 1)); // We cut out the sign.
    }
    else if (str[0] == valid_chars[11]){
        isPositive = false;
        str1 = str.substr(1, (str.length() - 1)); // We cut out the sign.
    }

    // Now that the sign is known and disposed of, we build the number with some cool maths.
    double num = 0;
    double digit;
    bool decimPlaced = false;
    int decimPos = 0;
    for (int i = 0; i < str1.length(); i++){ // We brute force the digits here...yikes
        if (str1[i] == valid_chars[0]){
            digit = 0;
        }
        else if (str1[i] == valid_chars[1]){
            digit = 1;
        }
        else if (str1[i] == valid_chars[2]){
            digit = 2;
        }
        else if (str1[i] == valid_chars[3]){
            digit = 3;
        }
        else if (str1[i] == valid_chars[4]){
            digit = 4;
        }
        else if (str1[i] == valid_chars[5]){
            digit = 5;
        }
        else if (str1[i] == valid_chars[6]){
            digit = 6;
        }
        else if (str1[i] == valid_chars[7]){
            digit = 7;
        }
        else if (str1[i] == valid_chars[8]){
            digit = 8;
        }
        else if (str1[i] == valid_chars[9]){
            digit = 9;
        }
        else if (str1[i] == valid_chars[12]){
            decimPlaced = true;
            decimPos++;
            continue;
        }
        // ...After grabbing the digit, we slot it into the number.
        if (decimPlaced){
            int div_scale = 1;
            for (int j = 0; j < decimPos; j++){
                div_scale *= 10;
            }
            num = num + (digit/div_scale);
            decimPos++;
        }
        else{
            num = (num*10) + digit; // (I feel smart for this, but dumb for the digit thing above)
        }
    }
    // Once we have the number built, we convert it to the proper sign.
    if (isPositive){
        return num;
    }
    else {
        return num * -1;
    }
}