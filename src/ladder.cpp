#include "ladder.h"
#include <queue>
#include <vector>
#include <iostream>

void error(string word1, string word2, string msg) {
    cerr << msg << ": " << word1 << " -> " << word2 << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int length1 = str1.size();
    int length2 = str2.size();

    if (abs(length1 - length2) > d){return false;}

    int diff = 0;
    if (length1 == length2) {
        for (int i = 0; i < length1; ++i) {
            if (str1[i] != str2[i]) {
                ++diff;
                if(diff > d) {return false;}
            }
        }
        return diff <= d;
    }
    else {
        const string& longer = (length1 > length2) ? str1 : str2;
        const string& shorter = (length1 < length2) ? str1 : str2;
        
        int i = 0, j = 0;
        while(i < longer.size()) {
            if (j < shorter.size() && longer[i] == shorter[j]) {
                ++j;
            } 
            else {
                ++diff;
                if (diff > d) {return false;}
            }
            ++i;
        }
    }
    return diff <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last = ladder.back();
        for(const string& word : word_list) {
            if(is_adjacent(last, word)) {
                if(visited.find(word) == visited.end()) {
                    visited.insert(word);

                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if(word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while(file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    for(const string& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}