#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <cstdio>
#include "deque.h"
#include <getopt.h>
using namespace std;

int main(int argc, char** argv) {
    freopen("dictionary.txt", "r", stdin); //COMMENT THIS OUT BEFORE YOU SUBMIT ON CAEN
    char test;
    int num_words;
    bool bflag = false;
    bool eflag = false;
    bool hflag = false;
    int sflag = 0;
    int qflag = 0;
    int oflag = 0;
    int mflag = 0;
    int index_dictionary = 0;
    string start, word, end, option;
    bool start_word_present = true;
    bool end_word_present = true;
    
    deque<string> words;
    vector<many_words> dictionary;
    vector<string> path;
    ostringstream wordz;
    
    cout.sync_with_stdio(false);
    cin >> num_words;
    getline(cin, word);
    while (getline(cin, word)){
        many_words wordes;
        wordes.word = word;
        dictionary.push_back(wordes);
    }
    for (size_t i = 0; i < dictionary.size(); i++){
        dictionary[i].used = false;
        dictionary[i].change_counter = 0;
        dictionary[i].length_counter = 0;
    }
    
    struct option longOpts[] = {
        { "stack", no_argument, NULL, 's' },
        { "queue", no_argument, NULL, 'q' },
        { "change", no_argument, NULL, 'c' },
        { "length", no_argument, NULL, 'l' },
        { "output", required_argument, NULL, 'o' },
        { "begin", required_argument, NULL, 'b' },
        { "end", required_argument, NULL, 'e' },
        { "help", no_argument, NULL, 'h' },
    };
    opterr = false;
    
    int opt = 0, index = 0;
    while ((opt = getopt_long(argc, argv, "sqclo:b:e:h", longOpts, &index)) != -1) {
        switch (opt) {
            case 's':
                sflag += 1;
                break;
            case 'q':
                qflag += 2;
                break;
            case 'c':
                mflag += 1;
                break;
            case 'l':
                mflag += 2;
                break;
            case 'o':
                option.assign(optarg);
                if (option == "M"){
                    oflag = 1;
                }
                else if (option == "W"){
                    oflag = 2;
                }
                break;
            case 'b':
                bflag = true;
                start.assign(optarg);
                break;
            case 'e':
                eflag = true;
                end.assign(optarg);
                break;
            case 'h':
                hflag = true;
                wordz << "You want help?  This program accepts:\n";
                wordz << "  -s, --stack       Use a stack\n";
                wordz << "  -q, --queue       Use a queue\n";
                wordz << "  -c, --change      Change one letter\n";
                wordz << "  -l, --length      Modify length by insert/delete\n";
                wordz << "  -o, --output(W|M) Word or modification format, default word\n";
                wordz << "  -b, --begin<word> Word you start with\n";
                wordz << "  -e, --end<word>   Word you end with\n";
                wordz << "  -h, --help        This help page\n";
                exit(0);
            default:
                wordz << "I didn't recognize one of your flags!\n";
        }
    }
    
    if (oflag == 0){
        option = "W";
        oflag = 2;
    }
    
    if (sflag > 1 || qflag > 2){
        cerr << "MORE THAN ONE STACK/QUEUE COMMAND\n";
        exit(1);
    }
    
    if (sflag + qflag > 2){
        cerr << "CHOSE STACK AND QUEUE\n";
        exit(1);
    }
    
    if (sflag + qflag == 0){
        cerr << "NO STACK/QUEUE COMMAND\n";
        exit(1);
    }
    
    if (mflag == 0){
        cerr << "NO CHANGE/LENGTH COMMAND\n";
        exit(1);
    }
    
    if (option != "W" && option != "M"){
        cerr << "INVALID OUTPUT COMMAND\n";
        exit(1);
    }
    
    for (size_t i = 0; i < dictionary.size(); i++){
        if (start != dictionary[i].word){
            start_word_present = false;
        }
        else{
            start_word_present = true;
            break;
        }
    }
    
    for (size_t i = 0; i < dictionary.size(); i++){
        if (end != dictionary[i].word){
            end_word_present = false;
        }
        else{
            end_word_present = true;
            break;
        }
    }
    
    if (!start_word_present || !end_word_present){
        cerr << "WORD DOESN'T EXIST IN DICTIONARY\n";
        exit(1);
    }
    
    if (start == "\0" || end == "\0"){
        cerr << "WORD NOT SPECIFIED\n";
        exit(1);
    }
    
    if (mflag == 1 && (end.length() - start.length() != 0)){
        cerr << "IMPOSSIBLE TO DO THIS\n";
        exit(1);
    }
    
    if (sflag == 1 && (mflag == 1||mflag == 3)){
        implement(dictionary, path, words, start, end, start, oflag, mflag, sflag, index_dictionary);
    }
    else if (qflag == 2 && (mflag == 1||mflag == 3)){
        implement(dictionary, path, words, start, end, start, oflag, mflag, qflag, index_dictionary);
    }
    else if (sflag == 1 && (mflag == 2||mflag == 3)){
        implement(dictionary, path, words, start, end, start, oflag, mflag, sflag, index_dictionary);
    }
    else if (qflag == 2 && (mflag == 2||mflag == 3)){
        implement(dictionary, path, words, start, end, start, oflag, mflag, qflag, index_dictionary);
    }
    return 0;
}
