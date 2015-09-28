//
//  deque.h
//  Project 1
//  Will perform both stack and queue schemes
//  Created by Howard Mok on 1/18/15.
//  Copyright (c) 2015 Howard Mok. All rights reserved.
//

#ifndef __Project_1__deque__
#define __Project_1__deque__

#include <deque>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>

struct many_words {
    std::string word;
    bool used;
    int change_counter;
    int length_counter;
    std::string previous;
    int position;
    char difference;
};

void implement(std::vector<many_words> dictionary, std::vector<std::string> path, std::deque<std::string> words, std::string start, std::string end, std::string root, int output, int mod, int stack, int index);
//Changes letter at position

int change_mode(std::string current, std::string check, char& letter);

int length_mode(std::string current, std::string check, char& letter);

void word_output(std::vector<many_words> dictionary, std::vector<std::string> path);
//Word output mode

void modification_output(std::vector<many_words> dictionary, std::vector<std::string> path);
//Modification output mode

#endif /* defined(__Project_1__deque__) */
