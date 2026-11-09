
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void Create(int** a, int n, int m, int low, int high, int i = 0, int j = 0)
{
    if (i == n)
        return;

    a[i][j] = low + rand() % (high - low + 1);

    if (j + 1 < m) // переходим до наступного стовпця поки не дійдем до края
        Create(a, n, m, low, high, i, j + 1); // якщо в поточному рядку ще є елементи - збільшуємо j
    else
        Create(a, n, m, low, high, i + 1, 0); // Якщо рядок закінчився - збільшуємо i, а j повертаємо на 0.
}

void Print(int** a, int n, int m, int i = 0, int j = 0) // виведення
{
    if (i == n)
        return;

    cout << setw(5) << a[i][j];

    if (j + 1 < m)
        Print(a, n, m, i, j + 1);
    else
    {
        cout << endl;
        Print(a, n, m, i + 1, 0);
    }
}

void Change(int** a, int j1, int j2, int n, int i = 0) // поміняти два стовпці місцями
{
    if (i == n)
        return;

    int tmp = a[i][j1];
    a[i][j1] = a[i][j2];
    a[i][j2] = tmp;

    Change(a, j1, j2, n, i + 1); // перехід до наступного рядка , перебираємо тільки всі рядки
}

void Sort(int** a, int n, int m, int i = 0, int j = 0) // сортування
{
    if (i == m - 1) // маємо 6 стовпців , для сортування потрібно потрібно 5 проходів
        return;
    
    if (j == m - i - 1) // коли закінчується порівнювняння стовпців в поточному проході , йдемо до наступного
    {
        Sort(a, n, m, i + 1, 0); 
        return;
    }

    if (a[0][j] < a[0][j + 1] || // якщо ліве число менше правого , міняємо стовпці місцями
        (a[0][j] == a[0][j + 1] && a[1][j] < a[1][j + 1]) || // якщо числа першого рядка однакові, порівнюємо другий рядок
        (a[0][j] == a[0][j + 1] && a[1][j] == a[1][j + 1] && a[2][j] > a[2][j + 1])) // Якщо перший і другий рядки однакові, порівнюємо третій
    {
        Change(a, j, j + 1, n);
    }

    Sort(a, n, m, i, j + 1);
}

void Calc(int** a, int n, int m, int& s, int& k, int i = 0, int j = 0)
{
    if (i == n)
        return;

    if (a[i][j] >= 0 && a[i][j] % 3 == 0)
    {
        s += a[i][j];
        k++;
        a[i][j] = 0;
    }

    if (j + 1 < m)
        Calc(a, n, m, s, k, i, j + 1);
    else
        Calc(a, n, m, s, k, i + 1, 0);
}

int main()
{
    srand((unsigned)time(NULL));

    int n = 9, m = 6;
    int low = -21, high = 24;

    int** a = new int* [n];

    for (int i = 0; i < n; i++)
        a[i] = new int[m];

    Create(a, n, m, low, high);

    cout << "Original matrix:" << endl;
    Print(a, n, m);
    cout << endl;

    Sort(a, n, m);

    cout << "Sorted matrix:" << endl;
    Print(a, n, m);
    cout << endl;

    int s = 0, k = 0;
    Calc(a, n, m, s, k);

    cout << "S = " << s << endl;
    cout << "k = " << k << endl;

    cout << "Modified matrix:" << endl;
    Print(a, n, m);

    for (int i = 0; i < n; i++)
        delete[] a[i];

    delete[] a;

    return 0;
}
