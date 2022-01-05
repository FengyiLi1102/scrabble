enum ScoreModifier { NONE, DOUBLE_LETTER_SCORE, TRIPLE_LETTER_SCORE, DOUBLE_WORD_SCORE, TRIPLE_WORD_SCORE };

/* insert your function prototypes here */

int tile_score(char tile);

bool can_form_word_from_tiles(char *word, char *tiles, char *played_tiles);

bool form_process(char *word, char *tiles, char *played_tiles, int indexWord, int indexTile);

int compute_score(const char *played_tiles, const ScoreModifier score_modifiers[]);

int highest_scoring_word_from_tiles(char *tiles, ScoreModifier score_modifier[], char *word);