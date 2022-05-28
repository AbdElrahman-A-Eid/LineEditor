#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

using namespace std;

/*
 Author: AbdElrahman Eid
 Github: AbdElrahman-A-Eid
*/

void gotoxy(int column, int line);
int right(int& currCol, int& newIn);
int left(int& currCol, int& newIn);
void print(char ch, int& currCol,  char* ptr, int arrSize, int& newIn, int& insertMode);
void shiftChR(int& currCol, char* arrPtr, int& newIn);
void shiftChL(int& currCol, char* arrPtr, int& newIn);
void deleteCh(int& col, char* arrPtr, int& newIn);
void guiInit();
void thankMsg ();

int main()
{

    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);

    guiInit();

    int arrSize;
    cin >> arrSize;

    int currCol = 5;
    int newIn = 5;
    int insertMode = 0;

    char* arrPtr;
    arrPtr = new char[arrSize+1];

    gotoxy(1, 8);
    cout << "-> ";

    if (arrPtr != NULL) {

        do {
                gotoxy(currCol, 8);
                char ch;
                ch = getch();

                if((int)ch == -32) {

                    ch = getch();
                    switch ((int)ch) { // Extended Keys
                    case 77: // Right
                        currCol = right(currCol, newIn);
                        break;
                    case 75: // Left
                        currCol = left(currCol, newIn);
                        break;
                    case 71: // Home
                        currCol = 5;
                        gotoxy(currCol, 8);
                        break;
                    case 79: // END
                        currCol = newIn;
                        break;
                    case 83:  // Delete
                        deleteCh(currCol, arrPtr, newIn);
                        break;
                    case 82: // Insert
                        insertMode = !insertMode;
                    }

                } else if ((int)ch == 27) { // Escape Key
                    SetConsoleTextAttribute(console_color, 4);
                    arrPtr[0] = '\0';
                    thankMsg();
                    SetConsoleTextAttribute(console_color, 15);
                    return 0;

                } else if ((int)ch == 13) { // Enter Key
                    SetConsoleTextAttribute(console_color, 4);
                    arrPtr[newIn-5] = '\0';
                    cout << "\n\nYour line is:\n" << "\t\t\"" << arrPtr << "\"" << endl;
                    SetConsoleTextAttribute(console_color, 2);
                    thankMsg();
                    SetConsoleTextAttribute(console_color, 15);
                    return 0;

                } else if ((int)ch == 8) { // Backspace Key

                    deleteCh(currCol, arrPtr, newIn);
                    currCol = left(currCol, newIn);

                } else { // Printable Keys
                    print(ch, currCol, arrPtr, arrSize, newIn, insertMode);
                }

        } while (1);

        delete(arrPtr);
    }

    return 0;
}


void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
 }

 int right(int& currCol, int& newIn)
 {
     if (currCol > newIn) {
        return currCol;
     } else {
        currCol++;
     }
     gotoxy(currCol, 8);
     return currCol;
 }

  int left(int& currCol, int& newIn)
 {
     if (currCol < 6) {
        return 5;
     } else {
        currCol--;
     }
     gotoxy(currCol, 8);
     return currCol;
 }

 void print(char ch, int& currCol, char* arrPtr, int arrSize, int& newIn, int& insertMode)
 {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);

    if (insertMode == 1) {

        SetConsoleTextAttribute(console_color, 9);

        shiftChR(currCol, arrPtr, newIn);
        arrPtr[currCol-5] = ch;
        cout << arrPtr[currCol-5];

        SetConsoleTextAttribute(console_color, 8);
        for (int i = currCol+1; i <= newIn; i++) {
            gotoxy(i, 8);
            cout << arrPtr[i-5];
        }
        if (newIn < arrSize+4) {
           newIn++;
        }

    } else {

        SetConsoleTextAttribute(console_color, 8);

        arrPtr[currCol-5] = ch;
        cout << arrPtr[currCol-5];

    }

    if ((newIn == currCol) && (currCol < arrSize+4)) {

        newIn++;
        currCol++;
        gotoxy(currCol, 8);

    } else if (currCol == arrSize+4) {

        arrPtr[currCol-5] = ch;
        gotoxy(currCol, 8);

    } else {
        currCol++;
        gotoxy(currCol, 8);
    }
 }

 void deleteCh(int& currCol, char* arrPtr, int& newIn)
 {
    shiftChL(currCol, arrPtr, newIn);
    for (int i = currCol; i < newIn; i++) {
        gotoxy(i, 8);
        cout << arrPtr[i-5];
    }
    newIn--;
 }

void shiftChR (int& currCol, char* arrPtr, int& newIn)
{
    int n;
    n = newIn - 1;
    arrPtr[n-4] = ' ';
    while (n >= currCol) {
        arrPtr[n-4] = arrPtr[n-5];
        n--;
    }
}

void shiftChL (int& currCol, char* arrPtr, int& newIn)
{
    int n;
    n = currCol;
    while (n < newIn) {
        arrPtr[n-5] = arrPtr[n-4];
        n++;
    }
}

void guiInit()
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(console_color, 10);

    cout << "**** AbdElrahman's Line Editor ****\n" << endl;

    SetConsoleTextAttribute(console_color, 12);

    cout << "Key Instructions:" << endl;

    SetConsoleTextAttribute(console_color, 23);

    gotoxy(0, 4);
    cout << "Left & Right Arrows: Navigation";
    gotoxy(40, 4);
    cout << "Home: Line Beginning";
    gotoxy(70, 4);
    cout << "End: Last Input";
    gotoxy(100, 4);
    cout << "Esc: Terminate";
    gotoxy(0, 5);
    cout << "Delete/Backspace: Delete on Cursor";
    gotoxy(40, 5);
    cout << "Insert: Toggle Insertion";
    gotoxy(70, 5);
    cout << "Enter: Save & Terminate";

    SetConsoleTextAttribute(console_color, 14);

    cout << "\n\nPlease enter the size of your line (Maximum number of characters): ";
}

void thankMsg ()
{
    cout << "\nThank you for using my Line Editor.\nThe program will exit shortly..." << endl;
    Sleep(1500);
}
