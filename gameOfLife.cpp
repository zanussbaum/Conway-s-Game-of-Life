#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define HEIGHT 45
#define WIDTH 45
#define ITER 1000
struct Shape{
    public:
        int xCoord;
        int yCoord;
        vector<int> figure;
};
struct Block : public Shape{
    public:
        Block(int x, int y);
};
struct Glider : public Shape{
    public:
        Glider(int x, int y);
};

struct Blinker : public Shape{
    public:
        Blinker(int x, int y);
};
struct Acorn : public Shape{
    public:
        Acorn(int x, int y);
};
class GameOfLife{
    public:
        int rows;
        int cols;
        int iter;
        vector<int> gameBoard;


        GameOfLife(Shape pattern);
        void updateGame(vector<int> &gameBoard);
        void printBoard();
        void iterate();
        int numNeighbors(int index);
};
Block::Block(int x,int y){
    xCoord = x;
    yCoord = y;
    figure.assign(HEIGHT*WIDTH,0);


    figure[xCoord*WIDTH + yCoord] = 1;
    figure[xCoord*WIDTH + yCoord + 1] = 1;
    figure[(xCoord+1)*WIDTH + yCoord] = 1;
    figure[(xCoord+1)*WIDTH + yCoord + 1] = 1;
}
Blinker::Blinker(int x, int y){
    xCoord = x;
    yCoord = y;
    figure.assign(HEIGHT*WIDTH,0);

    figure[xCoord*WIDTH + yCoord] = 1;
    figure[(xCoord+1)*WIDTH + yCoord] = 1;
    figure[(xCoord+2)*WIDTH + yCoord] = 1;
}
Glider::Glider(int x, int y){
    xCoord = x;
    yCoord = y;
    figure.assign(HEIGHT*WIDTH,0);

    figure[xCoord*WIDTH + yCoord] = 1;
    figure[(xCoord+1)*WIDTH + yCoord] = 1;
    figure[(xCoord+1)*WIDTH + yCoord-2] = 1;
    figure[(xCoord+2)*WIDTH + yCoord] = 1;
    figure[(xCoord+2)*WIDTH + yCoord-1] = 1;
    
}

Acorn::Acorn(int x, int y){
    xCoord = x;
    yCoord = y;
    figure.assign(HEIGHT*WIDTH,0);

    figure[xCoord*WIDTH + yCoord] = 1;
    figure[(xCoord+1)*WIDTH + yCoord + 2] = 1;
    figure[(xCoord+2)*WIDTH + yCoord + -1] = 1;
    figure[(xCoord+2)*WIDTH + yCoord] = 1;
    figure[(xCoord+2)*WIDTH + yCoord + 3] = 1;
    figure[(xCoord+2)*WIDTH + yCoord + 4] = 1;
    figure[(xCoord+2)*WIDTH + yCoord + 5] = 1;

}

GameOfLife::GameOfLife(Shape shape){
    Shape();
    rows = HEIGHT;
    cols = WIDTH;
    iter = ITER;

    gameBoard.assign(rows*cols, 0);
    gameBoard.swap(shape.figure);
};

int GameOfLife::numNeighbors(int index){
    int numNeighbors = 0;
    int rowIndex = index / cols;
    int colIndex = index % cols;
    int checkRow;
    int checkcols;
    for(int i = rowIndex-1; i<=rowIndex+1; i ++){
        for(int j = colIndex-1; j <= colIndex+1; j++){
            checkRow = (i%rows);
            checkcols = (j%cols);
            if(checkRow < 0){
                checkRow+= rows;
            }
            if(checkcols < 0){
                checkcols += cols;
            }
            if(i == rowIndex && j == colIndex){
                continue;
            }
            if(gameBoard[checkRow * cols + checkcols]){
                numNeighbors++;
            }
        }
    }
    return numNeighbors;
}

void GameOfLife::updateGame(vector<int> &array){
    vector<int> temp (rows*cols);
    int neighbors;
    for(int i = 0; i<rows*cols; i ++){
            neighbors = numNeighbors(i);
            if(array[i] == 1){
                if((neighbors== 2 || neighbors == 3)){
                    temp[i] = 1;
                }
            }
            if(array[i] == 0){
                if(neighbors == 3){
                    temp[i] = 1;
                    }
                }
    }
    array.swap(temp);
    temp.clear();
}

void GameOfLife::printBoard(){
    for(int i = 0; i< rows*cols; i++){
        int colIndex = i % cols;
        if(gameBoard[i]){
            if(colIndex+1 == cols){
                cout << "@";
                cout<<endl;
            }
            else{
                cout << "@ ";
            }
        }
        else{
            if(colIndex+1 == cols){
                cout << "-";
                cout<<endl;
            }
            else{
                cout << "- ";
            }
        }
    }
    
}
void GameOfLife::iterate(){
    for(int i = 0; i < 92; i++){
        system("clear");
        printBoard();
        cout << "Generation: " << i <<endl;
        usleep(200000);
        updateGame(gameBoard);
    }
}

int main(int argc, char ** argv){
    Block block(3, 29);
    Acorn acorn(10,5);
    Blinker blinker(15,15);
    Glider glider(20, 3);
    GameOfLife game = GameOfLife(acorn);
    game.iterate();
    return 0;
}
