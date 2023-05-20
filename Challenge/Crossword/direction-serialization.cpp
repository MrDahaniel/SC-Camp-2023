#include <stdio.h>
#include <omp.h>

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <tuple>

#define FMT_HEADER_ONLY
#include <fmt/core.h>

using namespace std;

const int M = 4; // Cols
const int N = 4; // Rows

enum Direction {
    EAST = 0,
    SOUTH_EAST = 1,
    SOUTH = 2,
    SOUTH_WEST = 3,
    WEST = 4,
    NORTH_WEST = 5,
    NORTH = 6,
    NORTH_EAST = 7,
};

struct Location {
    int x;
    int y;
    Direction dir;
    int caso;

    Location(int x, int y, Direction dir, int caso = 0) {
        Location::x = x;
        Location::y = y;
        Location::dir = dir; 
        Location::caso = caso; 
    }

    string to_string() {
        return fmt::format("col: {} row: {} dir: {} {}", Location::x, Location::y, Location::dir, Location::caso);
    }
};

struct Word {
    string str;
    vector<Word*> subwords;
    int length;

    vector<Location> instances;

    Word(string Word) {
        Word::str = Word;
        Word::length = Word.length();
        Word::instances = vector<Location>();
    }

    void print_instances() {
        for (auto locations : Word::instances) {
            cout << fmt::format("{} {}", Word::str, locations.to_string());
        }
    }
};

vector<char> set_soup(string letters) {
    if (letters.length() < M * N) {
        invalid_argument("Given string is smaller than matrix size");
    }

    vector<char> soup(M * N);

    for (int col = 0; col < M; col++) {
        for (int row = 0; row < N; row++) {
            soup[col * M + row] = letters[col * M + row];
        }
    }

    return soup;
}

void print_soup(vector<char>* soup) {
    for (int col = 0; col < M; col++) {
        for (int row = 0; row < N; row++) {
            cout << (*soup)[col * M + row] << ' ';
        }
        cout << endl;
    }
}

bool compare_words(const Word& a, const Word& b) {
    // First, sort by length (shortest to longest)
    return b.length < a.length;
}

void print_wordlist(vector<Word>* wordlist) {
    
    cout << endl << "wordlist:" << endl;

    for (auto word : *wordlist) {
        cout << "- " << word.str << endl;
    }
}

void process_wordlist(vector<Word>* wordlist) {

    // for (auto word : (*wordlist)) {
    //     wordlist->push_back(Word(string(word.str.rbegin(), word.str.rend())));
    // }

    sort((*wordlist).begin(), (*wordlist).end(), compare_words);
}

void horizontal_search(vector<char>* soup, vector<Word>* wordlist) {
    // Can pragma here
    for (int i = 0; i < M; i++) {
    // Could do it here but can break things, maybe not 
    for (int k = 0; k < N; k++) {
    for (auto &word : (*wordlist)) {
        if (word.str[0] == (*soup)[i * M + k] || word.str[word.length - 1]  == (*soup)[i * M + k]) {
            if (k - (word.length - 1) >= 0) { // Seg fault Chad avoider
                bool found; 

                // caso 1: la palabra está al revés y se retrocede en el vector
                if (word.str[word.length - 1]  == (*soup)[i * M + k]) {
                    found = true;
                    for (int j = 1; j < word.length; j++) {
                        if (!found) { break; }
                        if (word.str[word.length - 1 - j] != (*soup)[i * M + k - j]) { found = false; }
                    }
                    if (found) {
                        word.instances.push_back(Location(k - (word.length - 1), i, Direction::EAST, 1));
                        break;
                    }
                }
                // caso 2: la palabra está al derecho y se retrocede en el vector
                if (word.str[0] == (*soup)[i * M + k]) {
                    found = true;
                    for (int j = 1; j < word.length; j++) {
                        if (!found) { break; }
                        if (word.str[j] != (*soup)[i * M + k - j]) { found = false; }
                    }
                    if (found) {
                        word.instances.push_back(Location(k, i, Direction::WEST, 2));
                        break;
                    }
                }
            }
            if ((word.length - 1) + k < M) { // Seg fault Chad avoider
                bool found; 
                cout << fmt::format("({}, {}) - {} == {} || {} == {}? {}", i, k, word.str[0], (*soup)[i * M + k], word.str[word.length - 1], (*soup)[i * M + k],word.str[0] == (*soup)[i * M + k] || word.str[word.length - 1]  == (*soup)[i * M + k]) << endl;
                // caso 3: la palabra está al revés y se avanza en el vector
                if (word.str[word.length - 1]  == (*soup)[i * M + k]) {
                    found = true;
                    for (int j = 1; j < word.length; j++) {
                        if (!found) { break; }
                        if (word.str[word.length - 1 - j] != (*soup)[i * M + k + j]) { found = false; }
                        cout << fmt::format("({}, {}) - {} != {}? {} found {}", i, k, word.str[word.length - 1 - j], (*soup)[i * M + k + j], word.str[word.length - 1 - j] != (*soup)[i * M + k + j], found) << endl;
                    }
                    if (found) {
                        k += (word.length - 1);
                        word.instances.push_back(Location(k, i, Direction::WEST, 3));
                        break;
                    }
                }
                // caso 4: la palabra está al derecho y se avanza en el vector
                if (word.str[0]  == (*soup)[i * M + k]) {
                    found = true;
                    for (int j = 1; j < word.length; j++) {
                        if (!found) { break; }
                        if (word.str[j] != (*soup)[i * M + k + j]) { found = false; }
                    }
                    if (found) {
                        word.instances.push_back(Location(k, i, Direction::EAST, 4));
                        k += (word.length - 1);
                        break;
                    }   
                }
            }
        }
    }
    }
    }
}

void vertical_search(vector<char>* soup, vector<Word>* wordlist) {
    // Can pragma here
    for (int i = 0; i < M; i++) {
    // Could do it here but can break things, maybe not 
    for (int k = 0; k < N; k++) {
    for (auto &word : (*wordlist)) {
        if (word.str[0] == (*soup)[i + k * N] || word.str[word.length - 1]  == (*soup)[i + k * N]) {
            if (k - (word.length - 1) >= 0) { // Seg fault Chad avoider
                bool found; 

                // caso 1: la palabra está al revés y se retrocede en el vector
                if (word.str[word.length - 1]  == (*soup)[i + k * N]) {
                    found = true;
                    for (int j = 1; j < word.length; j++) {
                        if (!found) { break; }
                        if (word.str[word.length - 1 - j] != (*soup)[i + (k - j) * N]) { found = false; }
                    }
                    if (found) {
                        word.instances.push_back(Location(i, k - (word.length - 1), Direction::SOUTH, 1));
                        break;
                    }
                }
                // caso 2: la palabra está al derecho y se retrocede en el vector
                if (word.str[0] == (*soup)[i + k * N]) {
                    found = true;
                    for (int j = 1; j < word.length; j++) {
                        if (!found) { break; }
                        if (word.str[j] != (*soup)[i + (k - j) * N]) { found = false; }
                    }
                    if (found) {
                        word.instances.push_back(Location(i, k, Direction::NORTH, 2));
                        break;
                    }
                }
            }
            if ((word.length - 1) + k < N) { // Seg fault Chad avoider
                bool found; 

                // caso 3: la palabra está al revés y se avanza en el vector
                if (word.str[word.length - 1]  == (*soup)[i + k * N]) {
                    found = true;
                    for (int j = 1; j < word.length; j++) {
                        if (!found) { break; }
                        if (word.str[word.length - 1 - j] != (*soup)[i + (k + j) * N]) { found = false; }
                    }
                    if (found) {
                        k += (word.length - 1);
                        word.instances.push_back(Location(i, k, Direction::NORTH, 3));
                        break;
                    }
                }
                // caso 4: la palabra está al derecho y se avanza en el vector
                if (word.str[0] == (*soup)[i + k * N]) {
                    found = true;
                    for (int j = 1; j < word.length; j++) {
                        if (!found) { break; }
                        if (word.str[j] != (*soup)[i + (k + j) * N]) { found = false; }
                    }
                    if (found) {
                        word.instances.push_back(Location(i, k, Direction::SOUTH, 4));
                        k += (word.length - 1);
                        break;
                    }
                }
            }
        }
    }
    }
    }
}

void positive_diagonal_search(vector<char>* soup, vector<Word>* wordlist) {
    for (int diag = 0; diag < M + N - 1; diag++) {
    for (int i = 0; i < diag + 1; i++) {
        int k = diag - i;
        if (!(k < N && i < M)) { continue; }
        for (auto &word : (*wordlist)) {
            if (word.length + k > N && word.length + i > M) { continue; }
            if (word.str[word.length - 1] == (*soup)[i + k * M]) {
                bool found = true;
                for (int j = 1; j < word.length; j++) {
                    if (word.str[word.length - j - 1] != (*soup)[(i - j) + (k + j) * M]) { found = false; };
                }

                if (found) { 
                    word.instances.push_back(Location(i, k, Direction::SOUTH_WEST)); 
                    // Update checked indexes
                    i += word.length - 1;
                    continue;
                }
            }

            if (word.str[0] == (*soup)[i + k * M]) {
                // cout << fmt::format("{} {} - {}", i, k, (*soup)[(i) + (k) * M]) << endl;
                // cout << fmt::format("{} - {}", word.str[0], (*soup)[i + k * M]);
                // cout << endl;
                bool found = true;
                for (int j = 1; j < word.length; j++) {
                    // cout << fmt::format("{} - {}", word.str[j], (*soup)[(i + j) + (k - j) * M]);
                    if (word.str[j] != (*soup)[(i + j) + (k - j) * M]) { /* cout << " !"; */ found = false; };
                    // cout << endl;
                }

                if (found) { 
                    cout << "Found!" << endl;
                    word.instances.push_back(Location(i, k, Direction::NORTH_EAST)); 
                    i += word.length - 1;
                }
            }
        }
    }
    }

}

void negative_diagonal_search(vector<char>* soup, vector<Word>* wordlist) {
};

void final_report(vector<Word>* wordlist) {
    for (auto word : (*wordlist)) {
        for (auto inst : word.instances) {
            cout << fmt::format("{} {}", word.str, inst.to_string()) << endl;
        }
    }
}

int main(int argc, char** argv) {
    // define the matrix 
    vector<char> soup = set_soup("123151155051145...........acor......cr.a......o.b.......r..o..t.....ccl.a....a.a..c..tacotaco.......kaco............");
    vector<Word> wordlist {
        Word("123"), 
        // Word("3715"), 
        // Word("1231"), 
        // Word("04"), 
        // Word("3"), 
        // Word("5173"), 
        Word("51"), 
        // Word("47"), 
        // Word("03"), 
        // Word("25"), 
    };

    cout << Word("814").length << endl;

    print_soup(&soup);

    process_wordlist(&wordlist);

    print_wordlist(&wordlist);

    horizontal_search(&soup, &wordlist);

    vertical_search(&soup, &wordlist);

    // positive_diagonal_search(&soup, &wordlist);

    // negative_diagonal_search(&soup, &wordlist);

    final_report(&wordlist);

    return 0;
}


/* 
...........acor......cr.a......o.b.......r..o..t.....ccl.a....a.a..c..tacotaco.........kaco..........

*/