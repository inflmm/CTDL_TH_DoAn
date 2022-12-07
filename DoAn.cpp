#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include <chrono>
// Dong dau tien trong file khong can sap xep, ghi thang vao
// NRow: so luong dong doc 1 lan (RAM 4GB: 800,000 dong, RAM 8GB: 2,000,000 dong)
using namespace std::chrono;
using namespace std;
struct Book
{
    string ID;
    string line;
};
vector<Book> ListBook;

void readFileOnly(vector<Book>& ListBook, int start, int end)
{
    string fileName("Books_rating.csv");
    ifstream file(fileName, ios_base::in | ios_base::binary);
    string line;
    if (!file.is_open())
    {
        cout << "Error" << endl;
    }
    else
    {
        if (file.tellg() == 0)
        {
            getline(file, line, '\n');
            int length = line.length() + 1;
            file.seekg(length);
        }
        for (int i = start; i < end; i++)
        {
            getline(file, line, '\n');
            Book L;
            string s;
            L.line = line;
            int length = line.length();
            for (int j = 0; j < length; j++)
            {
                if (line[j] == ',')
                {
                    break;
                }
                s += line[j];
            }
            L.ID = s;
            ListBook.push_back(L);
        }
    }
    file.close();
}
void writeFile(vector<Book> LinkedList, int start, int end, char a[], int i)
{
    int count = 0;
    string b = "Books_rating_Sorted.csv";
    string fileName(a[i] + b);
    fstream file(fileName, ios_base::out);
    if (!file.is_open())
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        while (count < end)
        {
            file << LinkedList[start + count].line << endl;
            count++;
        }
    }
    file.close();
}
int partition(vector<Book>& arr, int low, int high)
{
    string pivot = arr[high].ID;
    int left = low;
    int right = high - 1;
    while (true) {
        while (left <= right && arr[left].ID < pivot) left++;
        while (right >= left && arr[right].ID > pivot) right--;
        if (left >= right) break;
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
    swap(arr[left], arr[high]);
    return left;
}

/* Hàm thực hiện giải thuật quick sort */
void quickSort(vector<Book>& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void Run()
{
    char count[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '10'};

    vector<string> lines;
    int start = 0;
    for (int i = 0; i < 10; i++) {
        vector<Book> LinkedList;
        readFileOnly(LinkedList, 0, start);
        quickSort(ListBook, 0, start);
        writeFile(LinkedList, 0, 0, count[i], i);
        vector<Book>().swap (LinkedList);
        start += 300000;
    }
}

int main()
{
    Run();
    return 0;


