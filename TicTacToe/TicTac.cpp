#include "TicTac.h"

const int TicTacToe::row ;
const int TicTacToe::col ;
int TicTacToe::winX = 0;
int TicTacToe::winO = 0;
int TicTacToe::count = 0;
std::string TicTacToe::m_board[row][col] = {
        {"       ","   Col 1.","      Col 2.","      Col 3."},
        {" Row 1.|   ","-#-    |    ","-#-    |    ","-#-    |"},
        {" Row 2.|   ","-#-    |    ","-#-    |    ","-#-    |"},
        {" Row 3.|   ","-#-    |    ","-#-    |    ","-#-    |"}
};


point::point(char name) : m_name(name),pos1{},pos2{} {};

int point::checkInputPosition(const char* RowOrCol) {
    int InputValue = 0;
    while (1) {
        std::cout << RowOrCol;
        std::cin >> InputValue;
        if(std::cin.fail() || (InputValue <= 0 || InputValue >= 4)) {
            std::cin.clear();
            std::cin.ignore(32767,'\n');
            continue;
        }
        std::cin.ignore(32767,'\n');
        if(std::cin.gcount() > 1) {
            continue;
        }
        return InputValue;
    }
}

void point::set_position() {
    this->pos1 = checkInputPosition("Row = ");
    this->pos2 = checkInputPosition("Col = ");
}

TicTacToe::TicTacToe() : x(new point('X')),o(new point('O')),_m_gameOver(false),_m_step(true),_m_again('n') {};

TicTacToe::~TicTacToe() {
    delete x;
    delete o;
    x = nullptr;
    o = nullptr;
}

void TicTacToe::show_desk() {
    std::cout << std::endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout <<  m_board[i][j];
        }
        std::cout << std::endl  <<  std::endl;
    }
    std::cout << std::endl;
}

void TicTacToe::result() {
    std::cout << std::endl;
    std::cout << " X | O " << std::endl;
    std::cout << "---|---" << std::endl;
    std::cout << " " << winX << " | " << winO << " " << std::endl << std::endl;
}

void TicTacToe::reset() {
    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            m_board[i][j][0] = '-';
            m_board[i][j][1] = '#';
            m_board[i][j][2] = '-';
        }
    }
    _m_again = 'n';
    _m_gameOver = false;
    _m_step = true;
    count = 0;
}

void TicTacToe::doStep(point * Point) {
    do{
        Point->set_position();
        if(m_board[Point->pos1][Point->pos2][1] == '#'){
            m_board[Point->pos1][Point->pos2][1] = Point->m_name;
            m_board[Point->pos1][Point->pos2][0] = ' ';
            m_board[Point->pos1][Point->pos2][2] = ' ';
            count++;
            _m_step = false;
        } else {
            _m_step = true;
        }
    }while (_m_step);
};

bool TicTacToe::checkGameEnd(point* Point) {
    int j = 1;
    for (int i = 1; i < row; i++)
    {
        j = 1;
        if (m_board[i][j][1] == m_board[i][j+1][1] && m_board[i][j+1][1] == m_board[i][j+2][1] && 
            m_board[i][j + 2][1] == Point->m_name) {
                return true;
        }
        if((m_board[j][i][1] == m_board[j+1][i][1] && m_board[j+1][i][1] == m_board[j+2][i][1] &&
            m_board[j + 2][i][1] == Point->m_name)){
                return true;
        }
        if(m_board[j][j][1] == m_board[j+1][j+1][1] && m_board[j+1][j+1][1] == m_board[j+2][j+2][1] &&
            m_board[j + 2][j + 2 ][1] == Point->m_name){
                return true;
        }
        j = 3;
        if(m_board[j][j-2][1] == m_board[j-1][j-1][1] && m_board[j-1][j-1][1] == m_board[j-2][j][1] &&
            m_board[j-2][j][1] == Point->m_name){
                return true;
        }
    }
    return false;
}

void TicTacToe::winner(point* Point) {
    system("clear");
    show_desk();
    if(Point->m_name == 'X') {
        winX++;
    } else {
        winO++;
    }
    std::cout << std::endl << "\tEnd of the game:" << std::endl;
    std::cout << "*** Player '" << Point->m_name << "' won ***" << std::endl << std::endl;
    result();
    std::cout << "--- Do you want to play again? (Y/N)" << std::endl;
    std::cin >> _m_again;
}

void TicTacToe::draw() {
    system("clear");
    show_desk();
    std::cout << std::endl ;
    std::cout << "\t*** The game ended in a draw ***" <<  std::endl << std::endl;
    std::cout << "--- Do you want to play again? (Y/N)" << std::endl;
    std::cin >> _m_again;
    result();
}

void TicTacToe::playing(point* Point) {
    system("clear");
    show_desk();
    doStep(Point);
}

void TicTacToe::play() {
    do {
        reset();
        do {
            playing(x);
            if(checkGameEnd(x)) {
                winner(x);
                break;
            }else if (count == _m_draw){
                draw();
                break;
            }
            playing(o);
            if(checkGameEnd(o)) {
                winner(o);
                break;
            }else if (count == _m_draw){
                draw();
                break;
            }
        } while (!_m_gameOver);
    }while(_m_again == 'y' || _m_again == 'Y');
}

