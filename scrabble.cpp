#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include <cstdio>
#include "scrabble.h"

using namespace std;

const int MAX_WORD_LENGTH = 512;

/* insert your function definitions here */
int tile_score(char tile) {
    /* Blank character */
    if (tile == ' ' || tile == '?') return 0;

    /* Uppercase or lowercase */
    switch (tile) {                                
        case 'A': case 'E': case 'I': case 'L': case 'N':
        case 'O': case 'R': case 'S': case 'T': case 'U':
            return 1;

        case 'D': case 'G':
            return 2;

        case 'B': case 'C': case 'M': case 'P':
            return 3;

        case 'F': case 'H': case 'V': case 'W': case 'Y':
            return 4;

        case 'K':
            return 5;

        case 'J': case 'X':
            return 8;

        case 'Q': case 'Z':
            return 10;
    }

    return -1;
}


bool can_form_word_from_tiles(char *word, char *tiles, char *played_tiles) {
    int indexWord = 0, indexTile = 0;

    if (form_process(word, tiles, played_tiles, indexWord, indexTile)) return true;
    else return false;
}


bool form_process(const char *word, char *tiles, char *played_tiles, int indexWord, int indexTile) {
    if (indexWord == strlen(word)) return true;

    if (indexTile >= strlen(tiles)) return false;

    if (tiles[indexTile] == word[indexWord] || tiles[indexTile] == '?') {
        memmove(&tiles[indexTile], &tiles[indexTile + 1], strlen(tiles) - indexTile);
        played_tiles[indexWord] = word[indexWord];
        return form_process(word, tiles, played_tiles, ++indexWord, 0);
    } else {
        return form_process(word, tiles, played_tiles, indexWord, ++indexTile);
    }
}


int compute_score(const char *played_tiles, const ScoreModifier score_modifiers[]) {
    int doubleWordCount = 0, tripleWordCount = 0, totalScore = 0, modifierIndex = 0;
    string words = played_tiles;

    for (auto ch : words) {
        switch (score_modifiers[modifierIndex]) {
            // None
            case 0:
                totalScore += tile_score(ch);
                break;

            // DOUBLE_LETTER_SCORE
            case 1:
                totalScore += 2 * tile_score(ch);
                break;

            // TRIPLE_LETTER_SCORE
            case 2:
                totalScore += 3 * tile_score(ch);
                break;

            // DOUBLE_WORD_SCORE
            case 3:
                totalScore += tile_score(ch);
                doubleWordCount += 1;
                break;

            // TRIPLE_WORD_SCORE
            case 4:
                totalScore += tile_score(ch);
                tripleWordCount += 1;
                break;
        }

        modifierIndex += 1;
    }

    if (!doubleWordCount)
        totalScore *= 2;

    if (!tripleWordCount)
        totalScore *= 3;

    if (modifierIndex == 6)
        totalScore += 50;

    return totalScore;
}


int highest_scoring_word_from_tiles(char *tiles, ScoreModifier score_modifier[], char *word) {
    char played_tiles[MAX_WORD_LENGTH], potentialWord[MAX_WORD_LENGTH];
    int score = 0, tempScore = 0;
    ofstream in_file;
    in_file.open("words.txt");

    while (cin.getline(potentialWord, MAX_WORD_LENGTH - 1)) {
        bool success = can_form_word_from_tiles(potentialWord, tiles, played_tiles);

        if (success) {
            tempScore = compute_score(played_tiles, score_modifier);

            if (tempScore > score) {
                score = tempScore;
                strncpy(word, played_tiles, MAX_WORD_LENGTH - 1);
            }
        }
    }

    return score;
}