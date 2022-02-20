#include <iostream>

struct point
{
    char m_name;
    int pos1;
    int pos2;
    point(const char);
    void set_position();
    int checkInputPosition(const char*);
    ~point(){};
};

class TicTacToe
{
public:
    TicTacToe();
    ~TicTacToe();

public:
    void play();

private:
    void show_desk();
    void doStep(point*);
    bool checkGameEnd(point*);
    void playing(point*);
    void winner(point*);
    void reset();
    void draw();
    void result();
private:
    TicTacToe(const TicTacToe&) = delete;
    TicTacToe(TicTacToe&&) = delete;
    
private:
    enum {_m_draw = 9};
    static const int row = 4;
    static const int col = 4;
    static int winX;
    static int winO;
    static int count;
    static std::string m_board[row][col]; 
    point* x;
    point* o;
    bool _m_step;
    bool _m_gameOver;
    char _m_again;
};
