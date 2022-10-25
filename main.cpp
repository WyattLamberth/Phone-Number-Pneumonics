//
//  main.cpp
//  Project 1
//
//  Created by Wyatt Lamberth on 2/28/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>
using namespace std;

vector<string> letterCombinations(string digits) {
    static const vector<string> lookup = {" ", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};

    vector<string> result = {""};
    for (int i = digits.length() - 1; i >= 0; --i) {
        const auto& choices = lookup[digits[i] - '0'];
        int m = choices.length();
        int n = result.size();
        result.resize(m * n);
        for (int j = m * n - 1; j >= 0; --j) {
            result[j] = choices[j / n] + result[j % n];
        }
    }
    return result;
}

void check_phone(string input_phone){
    /*
     Note: A phone number must be in the format ###-#### and contain only the digits [2-9] inclusive to be considered valid. The digits 1 and 0 are considered invalid because they are not associated with any letters.
     */
    // check if the number is in a valid format
    //cout << "You entered: " << user_phone << endl;
    
    bool good_format = false;
    while (good_format == false){
        if (input_phone.length() == 8){
            for (int i = 0; i < input_phone.size(); i++){
                if ( isdigit(input_phone[i]) ){
                    if ( (input_phone[i] != '0' && input_phone[i] != '1') && input_phone[3] == '-')
                    {
                        good_format = true;
                    }
                    else{
                        cout << "Invalid phone number" << endl;
                        exit(1);
                    }
                }
            } // end for loop
        }
        else{
            cout << "Invalid phone number" << endl;
            exit(2);
        }
    
    
    if (good_format)
        cout << "Good Format: " << input_phone << endl;
     
    
    }
}

int main() {
    vector<string> three_letter_words;
    vector<string> four_letter_words;
    string filename = "yawl.txt";
    //cout << "Enter the file name:" << endl;
    //cin >> filename;
    
    ifstream fin(filename);
    ofstream fout("output.txt");
    
    // while there is still information in the file, assign the current word to a temp string
    // check the length of the string, if the length is correct, add it to the vector
    // print out to double check
    int COUNT_3 = 0;
    int COUNT_4 = 0;
    string WORD;
    while(!fin.eof()){
        getline(fin, WORD);
        if (WORD.size() == 3){
            three_letter_words.push_back(WORD);
            //cout << three_letter_words.at(COUNT_3) << endl;
            COUNT_3++;
        }
        if (WORD.size() == 4){
            four_letter_words.push_back(WORD);
            //cout << four_letter_words.at(COUNT_4) << endl;
            COUNT_4++;
        }
    }
    
    // take phone number from input
    string user_phone;
    cin >> user_phone;
    // check if the format is valid
    check_phone(user_phone);

    string first = "";
    first =  first + user_phone[0] + user_phone[1] + user_phone[2];
    string second = "";
    second =  second + user_phone[4] + user_phone[5] + user_phone[6] + user_phone[7];
    
    
    vector<string> all_first_combos = letterCombinations(first);
    vector<string> first_set;
    for (int i = 0; i < three_letter_words.size(); i++){
        for (int k = 0; k < all_first_combos.size(); k++){
            if ( all_first_combos.at(k) == three_letter_words.at(i) ){
                first_set.push_back( three_letter_words.at(i) );
            }
        }
    }
    
    vector<string> all_second_combos = letterCombinations(second);
    vector<string> second_set;
    for (int i = 0; i < four_letter_words.size(); i++){
        for (int k = 0; k < all_second_combos.size(); k++){
            if ( all_second_combos.at(k) == four_letter_words.at(i) ){
                second_set.push_back( four_letter_words.at(i) );
            }
        }
    }
    
    vector<string> both;
    
    for (int i = 0; i < first_set.size(); i++){
        for (int k = 0; k < second_set.size(); k++){
            both.push_back(first_set.at(i) + "-" + second_set.at(k));
        }
    }
    
    for (int i = 0; i < both.size(); i++)
        fout << both.at(i) << endl;
  
    return 0;
}
    

/*
 
 Before the advent of smart phones, it was challenging to remember phone numbers. One mnemonic solution was to associate words with the phone number for easy retention. Telephone keypads still show letters on the keypad associated with the numbers.

 In this assignment you will identify the word and word combinations associated with telephone numbers by using the word list contained in the file "yawl.txt". You will extract from this file and store all the three and four-letter words.

 You will then accept, from user input, a phone number as a string. Then you will validate that the phone number is in the correct format and contains valid numbers. If the phone number is not valid, you should display the message "Invalid phone number" and exit.

 Using the phone number, you will determine all the corresponding words and word combinations and write them into a file named "output.txt".

 Note: A phone number must be in the format ###-#### and contain only the digits [2-9] inclusive to be considered valid. The digits 1 and 0 are considered invalid because they are not associated with any letters.
 
 Example Input:
 234-5678
 The output.txt file should contain:
 BEG-LOST
 
 Example Input:
 223-5653
 The output.txt file should contain:
 ACE-JOKE
 ACE-JOLE
 ACE-LOKE
 BAD-JOKE
 BAD-JOLE
 BAD-LOKE
 CAD-JOKE
 CAD-JOLE
 CAD-LOKE
 
 */
