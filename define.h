#ifndef DEFINE_H
#define DEFINE_H


#define INFTY   10000000000
#define NINFTY -10000000000

#define DISCOUNT    1/100
#define MOVESCOUNT  1
#define CORNERCOUNT 10

enum Type {UNKNOWN, HUMAN, COMPUTER};
enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED};

#endif // DEFINE_H
