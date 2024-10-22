#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;

int** make_arr(int rows) {
    return new int*[rows];
}

void make_cols(int** arr, int rows, int cols, int index) {
    if (index != rows) {
        arr[index] = new int[cols];
        make_cols(arr, rows, cols, index + 1);
    }
}

void fill_arr(int** arr, int rows, int cols, int low, int high, int r=0, int c=0) {
    if (r != rows) {
        if (c != cols) {
            arr[r][c] = low + rand() % (high - low + 1);
            fill_arr(arr, rows, cols, low, high, r, c+1);
        }
        else {
            fill_arr(arr, rows, cols, low, high, r+1);
        }
    }
}

void print_arr(int** arr, int rows, int cols, int r=0, int c=0) {
    if (r != rows) {
        if (c != cols) {
            cout << setw(4) << arr[r][c];
            print_arr(arr, rows, cols, r, c+1);
        }
        else {
            cout << endl;
            print_arr(arr, rows, cols, r+1);
        }
    }
    else {
        cout << endl;
    }
}

void Calc(int** arr, int rows, int cols, int& S, int& amount, int r=0, int c=0) {
    if (r != rows) {
        if (c != cols) {
            if (!(arr[r][c] % 2 != 0 && (r + c) % 7 == 0)) {
                amount++;
                S += arr[r][c];
                arr[r][c] = 0;
            }
            Calc(arr, rows, cols, S, amount, r, c+1);
        }
        else {
            Calc(arr, rows, cols, S, amount, r+1, 0);
        }
    }
}

void Change(int** arr, int rows, int cols, int index=0, int r=0, int c=0) {
    int tmp;
    if (r != rows-1) {
        if (c != rows-r-1) {
            if ((arr[c][0] > arr[c+1][0]) ||
                (arr[c][0] == arr[c+1][0] && arr[c][1] < arr[c+1][1]) ||
                (arr[c][0] == arr[c+1][0] && arr[c][1] == arr[c+1][1] && arr[c][2] < arr[c+1][2])) {
                if (index != cols) {
                    tmp = arr[c][index];
                    arr[c][index] = arr[c+1][index];
                    arr[c+1][index] = tmp;
                    Change(arr, rows, cols, index+1, r, c);
                }
                else {
                    index = 0;
                }
            }
            else {
                Change(arr, rows, cols, index, r, c+1);
            }
        }
        Change(arr, rows, cols, index, r+1, 0);
    }
}

int main()
{
    srand(time(NULL));

    int low = 9, high = 61;
    int rows = 7, cols = 6;
    int S = 0, amount = 0;

    int** a = make_arr(rows);
    make_cols(a, rows, cols, 0);
    fill_arr(a,rows,cols,low,high);
    print_arr(a, rows, cols);

    Change(a, rows, cols);
    print_arr(a, rows, cols);
    Calc(a, rows, cols, S, amount);
    cout << "Amount = " << amount << endl;
    cout << "S = " << S << endl;
    print_arr(a, rows, cols);

    for (int i = 0; i != rows; i++) {
        delete[] a[i];
    }
    delete[] a;
}