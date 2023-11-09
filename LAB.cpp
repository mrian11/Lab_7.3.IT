#include <iostream>
#include <iomanip>
#include <climits>
#include <time.h>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High);
void Input(int** a, const int rowCount, const int colCount);
void Print(int** a, const int rowCount, const int colCount);
int* findColCountWithoutNegatives(int** array, int rowCount, int colCount);
int* calculateColSum(int** array, int rowCount, int colCount, int* colCountWithoutNegatives);
void MinSumAbsDiagonals(int** a, const int rowCount, const int colCount);

int main()
{
    srand((unsigned)time(NULL));
    int Low = -17;
    int High = 15;
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    // Create(a, rowCount, colCount, Low, High);
    Input(a, rowCount, colCount);
    Print(a, rowCount, colCount);

    int* colCountWithoutNegatives = findColCountWithoutNegatives(a, rowCount, colCount);
    int* colSum = calculateColSum(a, rowCount, colCount, colCountWithoutNegatives);

    MinSumAbsDiagonals(a, rowCount, colCount);

   
    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;
    delete[] colCountWithoutNegatives;
    delete[] colSum;
    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

void Input(int** a, const int rowCount, const int colCount)
{
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
        cout << endl;
    }
}

void Print(int** a, const int rowCount, const int colCount)
{
    cout << endl;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

int* findColCountWithoutNegatives(int** array, int rowCount, int colCount)
{
    int* colCountWithoutNegatives = new int[colCount];

    for (int col = 0; col < colCount; ++col)
    {
        bool containsNegatives = false;

        for (int row = 0; row < rowCount; ++row)
        {
            if (array[row][col] < 0)
            {
                containsNegatives = true;
                break;
            }
        }

        if (!containsNegatives)
        {
            colCountWithoutNegatives[col] = 1;
        }
        else
        {
            colCountWithoutNegatives[col] = 0;
        }
    }

    cout << "Columns without negative elements: ";
    for (int col = 0; col < colCount; ++col)
    {
        if (colCountWithoutNegatives[col] == 1)
        {
            cout << col << " ";
        }
    }
    cout << endl;

    return colCountWithoutNegatives;
}

int* calculateColSum(int** array, int rowCount, int colCount, int* colCountWithoutNegatives)
{
    int* colSum = new int[colCount];

    for (int col = 0; col < colCount; ++col)
    {
        if (colCountWithoutNegatives[col] == 1) {
            int sum = 0;
            for (int row = 0; row < rowCount; ++row)
            {
                sum += array[row][col];
            }
            colSum[col] = sum;
            cout << "Sum of column " << col << ": " << sum << endl;
        }
    }

    return colSum;
}

void MinSumAbsDiagonals(int** a, const int rowCount, const int colCount)
{
    int minSum = INT_MAX;

    for (int k = 0; k < rowCount + colCount - 1; k++)
    {
        int currentSum = 0;

        for (int i = max(0, k - colCount + 1); i < min(rowCount, k + 1); i++)
        {
            int j = colCount - 1 - (k - i);
            currentSum += abs(a[i][j]);
        }

        minSum = min(minSum, currentSum);
    }

    cout << "Min sum of absolute values in parallel diagonals: " << minSum << endl;
}
