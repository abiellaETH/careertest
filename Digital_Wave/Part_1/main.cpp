#include <fstream>
#include <iostream>
#include <set>
#include <cstring>
#include <string>

#include "custom_hash.h"

using namespace std;

int main()
{
    set<string> words;
    ifstream inputFile("..\\two_cities-charles_dickens.txt");
    auto myHash = custom_hash::createTable(1024);


    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    string str;
    while (inputFile >> str) {
        words.insert(str);
        str = "";
    }

    // Close the file
    inputFile.close();

    int someValue = 0;
    for (const auto& word : words) {
        cout<<word<<endl;
        custom_hash::insert(myHash, word.c_str(), someValue);
        someValue = someValue + 1 % 42;
    }

    //cout << custom_hash::get_first(myHash) << endl;

    return 0;
}
