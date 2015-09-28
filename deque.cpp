#include "deque.h"
using namespace std;

void implement(vector<many_words> dictionary, vector<string> path, deque<string> words, string start, string end, string root, int output, int mod, int stack, int index){
    string current;
    ostringstream wordz;
    wordz << "No solution.\n";
    current = start;
    words.push_front(start);
    int valid = -1;
    char difference = '\0';
    while (1){
        if (!words.empty()){
            if (stack == 1){
                current = words.front();
                words.pop_front();
            }
            else{
                current = words.front();
                words.pop_front();
            }
        }
        for (int i = 0; i < dictionary.size(); i++){//LOOP THROUGH DICTIONARY
            if (dictionary[i].word == current && dictionary[i].used == false){
                dictionary[i].used = true;
            }
            if (dictionary[i].used == false){
                signed int lengthDiff = static_cast<int>(current.length()) - static_cast<int>(dictionary[i].word.length());
                if (lengthDiff != 0 && (mod == 2 || mod == 3)){
                    valid = length_mode(current, dictionary[i].word, difference);
                }
                else if (lengthDiff == 0 && (mod == 1 || mod == 3)){
                    valid = change_mode(current, dictionary[i].word, difference);
                }
                if (valid != -1){
                    dictionary[i].position = valid;
                    dictionary[i].difference = difference;
                    dictionary[i].previous = current;
                    dictionary[i].used = true;
                    if (dictionary[i].word == end){
                        current = dictionary[i].word;
                        while (current != root){
                            for (int i = 0; i < dictionary.size(); i++){
                                if (current == dictionary[i].word){
                                    path.push_back(current);
                                    if (current == root){
                                        break;
                                    }
                                    current = dictionary[i].previous;
                                    i = -1;
                                }
                            }
                        }
                        if (output == 1){
                            modification_output(dictionary, path);
                            return;
                        }
                        else if (output == 2){
                            word_output(dictionary, path);
                            return;
                        }
                    }
                    if (stack == 1){
                        words.push_front(dictionary[i].word);
                    }
                    else{
                        words.push_back(dictionary[i].word);
                    }
                }
            }
        }
        if (words.empty()){
            cout << wordz.str();
            exit(0);
        }
    }
}

int length_mode(string current, string check, char& letter){
    int counter = 0;
    signed int lengthDiff = static_cast<int>(current.length()) - static_cast<int>(check.length());
    if(lengthDiff == 1){
        for(int n = 0; n < current.length(); n++){//LOOP THROUGH LETTERS IN CURRENT
            if (current[n] != check[n]){
                counter++;
                string temp = current;
                int m = check.length();
                int q = n;
                letter = '0';
                while (m > 0){
                    temp[n] = temp[n+1];
                    n++;
                    m--;
                }
                temp = temp.substr(0, temp.size() - 1);
                if (temp == check && counter == 1){
                    return q;
                }
            }
        }
        if (counter == 0){
            return check[check.length()-1];
        }
        return -1;
    }
    else if(lengthDiff == -1){
        for (int n = 0; n < current.length(); n++){//LOOP THROUGH LETTERS IN CURRENT
            if (current[n] != check[n]){
                counter++;
                string temp = check;
                int m = current.length();
                int q = n;
                letter = check[n];
                while (m > 0){
                    temp[n] = temp[n+1];
                    n++;
                    m--;
                }
                temp = temp.substr(0, temp.size() - 1);
                if (temp == current && counter == 1){
                    return q;
                }
            }
        }
        if (counter == 0){
            letter = check[check.size() - 1];
            return check.length() - 1;
        }
        return -1;
    }
    return -1;
}

int change_mode(string current, string check, char& letter){
    int counter = 0;
    int q = -1;
    for (int n = 0; n < current.length(); n++){//LOOP THROUGH LETTERS IN CURRENT
        if (current[n] != check[n]){//SEES IF LETTER IS DIFFERENT
            letter = check[n];
            counter++;
            q = n;
        }
    }
    if (counter == 1){
        return q;
    }
    return -1;
}

void word_output(vector<many_words> dictionary, vector<string> path){
    ostringstream wordz;
    wordz << "Words in morph: " << path.size() << '\n';
    cout << wordz.str();
    for (int i = path.size() - 1; i >= 0; i--){
        cout << path[i] << '\n';
    }
    exit(0);
}

void modification_output(vector<many_words> dictionary, vector<string> path){
    ostringstream wordz;
    wordz << "Words in morph: " << path.size() << '\n' << path[path.size()-1] << '\n';
    cout << wordz.str();
    for (int i = path.size() - 1; i >= 0; i--){
        for (int l = 0; l < dictionary.size(); l++){
            if (path[i] == dictionary[l].word){
                if (path[i].length() - dictionary[l].previous.length() == 0){
                    cout << "c," << dictionary[l].position << "," << dictionary[l].difference << '\n';
                }
                else if (path[i].length() - dictionary[l].previous.length() == -1){
                    cout << "d," << dictionary[l].position << '\n';
                }
                else if (path[i].length() - dictionary[l].previous.length() == 1){
                    cout << "i," << dictionary[l].position << "," << dictionary[l].difference << '\n';
                }
            }
        }
    }
    exit(0);
}
