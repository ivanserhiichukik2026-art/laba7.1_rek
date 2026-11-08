
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void Create(int** a, int rowCount, int colCount, int Low, int High, int i = 0, int j = 0)
{
    if (i == rowCount)
        return;

    a[i][j] = Low + rand() % (High - Low + 1);

    if (j + 1 < colCount)
        Create(a, rowCount, colCount, Low, High, i, j + 1);
    else
        Create(a, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** a, int rowCount, int colCount, int i = 0, int j = 0)
{
    if (i == rowCount)
    {
        cout << endl;
        return;
    }

    cout << setw(5) << a[i][j];

    if (j + 1 < colCount)
        Print(a, rowCount, colCount, i, j + 1);
    else
    {
        cout << endl;
        Print(a, rowCount, colCount, i + 1, 0);
    }
}

void Change(int** a, int col1, int col2, int rowCount, int i = 0)
{
    if (i == rowCount)
        return;

    int tmp = a[i][col1];
    a[i][col1] = a[i][col2];
    a[i][col2] = tmp;

    Change(a, col1, col2, rowCount, i + 1);
}

void Sort(int** a, int rowCount, int colCount, int i = 0, int j = 0)
{
    if (i == colCount - 1)
        return;

    if (j == colCount - i - 1)
    {
        Sort(a, rowCount, colCount, i + 1, 0);
        return;
    }

    if (a[0][j] < a[0][j + 1] ||
        (a[0][j] == a[0][j + 1] &&
            a[1][j] < a[1][j + 1]) ||
        (a[0][j] == a[0][j + 1] &&
            a[1][j] == a[1][j + 1] &&
            a[2][j] > a[2][j + 1]))
    {
        Change(a, j, j + 1, rowCount);
    }

    Sort(a, rowCount, colCount, i, j + 1);
}

void Calc(int** a, int rowCount, int colCount, int& S, int& k, int i = 0, int j = 0)
{
    if (i == rowCount)
        return;

    if (a[i][j] >= 0 && a[i][j] % 3 == 0)
    {
        S += a[i][j];
        k++;
        a[i][j] = 0;
    }

    if (j + 1 < colCount)
        Calc(a, rowCount, colCount, S, k, i, j + 1);
    else
        Calc(a, rowCount, colCount, S, k, i + 1, 0);
}

int main()
{
    srand((unsigned)time(NULL));

    int rowCount = 9;
    int colCount = 6;
    int Low = -21;
    int High = 24;

    int** P = new int* [rowCount];

    for (int i = 0; i < rowCount; i++)
        P[i] = new int[colCount];

    Create(P, rowCount, colCount, Low, High);

    cout << "Original matrix:";
    Print(P, rowCount, colCount);

    Sort(P, rowCount, colCount);

    cout << "Sorted matrix:";
    Print(P, rowCount, colCount);

    int S = 0;
    int k = 0;

    Calc(P, rowCount, colCount, S, k);

    cout << "S = " << S << endl;
    cout << "k = " << k << endl;

    cout << "Modified matrix:";
    Print(P, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] P[i];

    delete[] P;

    return 0;
}
