/*
    Data Structure Homework #1 - Maze Path

    Name: 이정우
    Student ID: 20171676
    Used Algorithm: Stack Functions
    File Name: hw1_miro.cpp
 */
#include <iostream>

using namespace std;

// Global Variables
const int MAZE_ROW = 12;    // 미로의 행
const int MAZE_COLUMN = 15; // 미로의 열

int maze[MAZE_ROW + 2][MAZE_COLUMN + 2] ={
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,2},
        {2,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,2},
        {2,0,0,1,0,0,0,0,1,1,1,1,0,0,1,1,2},
        {2,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,2},
        {2,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,2},
        {2,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,2},
        {2,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,2},
        {2,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,2},
        {2,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,2},
        {2,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,2},
        {2,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,2},
        {2,0,1,0,0,1,1,1,1,1,0,1,1,1,1,0,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};                    // 미로, 0: 통과 가능, 1: 벽, 2: 외벽

int mark[MAZE_ROW + 2][MAZE_COLUMN + 2] = {};   // 탈출로를 기록하기 위한 배열, 0으로 초기화

typedef struct {
        short int vert; short int horiz;
} offsets;  // 방향 정보를 담은 구조체

typedef struct {
        int row; int col; int dir;
} direction;    // 스택에 기록될 좌표 구조체

int top;    // 스택 변수 top
direction stack[MAZE_ROW];    // 스택 선언

void search_maze();

// Main
int main()
{
        search_maze();
        return 0;
}

// Functions of Stack
void create_stack() {
        top = -1;
}

void push(direction dir) {
        stack[++top] = dir;
}

direction pop() {
        return stack[top--];
}

// Function : search_maze
// Description : 미로의 탈출구를 탐색하는 함수
void search_maze() {
        create_stack(); // 탐색한 길을 저장하기 위한 스택 생성

        mark[1][1] = 1; // (1, 1)에서 시작

        direction temp;
        temp.row = 1;
        temp.col = 1;
        temp.dir = 0;
        push(temp); // 스택에 시작 좌표 저장

        int i, j, d; // (i, j): 현재 좌표, d: 현재 방향

        int EXIT_Row = 12;   // 출구의 좌표 행
        int EXIT_Col = 15;   // 출구의 좌표 열

        bool found = false; // 길을 찾았는지에 대한 여부
        bool isFirstProcess = true; // loop가 처음인지 아닌지에 대한 여부 확인

        offsets move[8];    // 이동 방향을 담은 구조체 선언
        move[0].vert = -1; move[0].horiz = 0; //n
        move[1].vert = -1; move[1].horiz = 1; //ne
        move[2].vert = 0; move[2].horiz = 1; //e
        move[3].vert = 1; move[3].horiz = 1; //se
        move[4].vert = 1; move[4].horiz = 0; //s
        move[5].vert = 1; move[5].horiz = -1; //sw
        move[6].vert = 0; move[6].horiz = -1; //w
        move[7].vert = -1; move[7].horiz = -1; //nw

        while (top > -1 && !found) // stack not empty
        {
                if(!isFirstProcess){    // loop에 처음으로 들어온 것이 아닐 경우,
                    mark[i][j] = 0;     // 올바른 경로가 아니었던 곳은 0으로 초기화
                }

                direction popped = pop();
                i = popped.row; j = popped.col;  // (i, j) = stack 의 top 에 있는 좌표 pop.
                d = popped.dir;

                while (d < 8 && !found) // 이동이 계속 가능할 경우
                {
                        isFirstProcess = false; // loop를 한번 벗어났으므로 false
                        int g = i + move[d].vert;
                        int h = j + move[d].horiz; // (g, h): 다음 이동좌표
                        if ((g == EXIT_Row) && (h == EXIT_Col)) { // 출구 도착
                                // 경로 출력(mark), return;
                                found = true;
                                mark[g][h] = 1; // 출구에 마킹
                                for (int k = 0; k < MAZE_ROW + 2; k++) {
                                        for (int m = 0; m < MAZE_COLUMN + 2; m++) {
                                                if(k == 0 || k == MAZE_ROW + 1)
                                                        cout << "*"; // 외벽 표현
                                                else if(m == 0 || m == MAZE_COLUMN + 1)
                                                        cout << "*"; // 외벽 표현

                                                else cout << mark[k][m];
                                        }
                                        cout << endl;
                                }
                                cout << endl << "Finish";
                                return;
                        }
                        if ((!maze[g][h]) && (!mark[g][h])) { // 새로운 위치
                                mark[g][h] = 1;
                                temp.row = i; temp.col = j; temp.dir = d+1; push(temp);  // 이전 위치를 스택에 삽입
                                i = g; j = h; d = 0;// (g, h)로 이동
                        }
                        else d++; // 다음 방향으로 시도
                }
        }
        cout << "No path in Maze" << endl;  // 길을 못찾았을 경우 출력
}
