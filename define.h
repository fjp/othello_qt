#ifndef DEFINE_H
#define DEFINE_H


#define INFTY   10000000000
#define NINFTY -10000000000

#define DISCOUNT    1/100
#define MOVESCOUNT  1
#define CORNERCOUNT 10

/**
 * @brief The Type enum used for the type of the current and the opponent player.
 */
enum Type {UNKNOWN, HUMAN, COMPUTER};

/**
 * @brief The State enum used for squares on the board inside the Board and the UISquare class.
 */
enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED};

#endif // DEFINE_H
