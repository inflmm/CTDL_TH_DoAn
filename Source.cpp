#include<iostream>
#include<fstream>
#include <vector>
#include<string>

//Làm lại
// 
// Dong dau tien trong file khong can sap xep, ghi thang vao
// NRow: so luong dong doc 1 lan (RAM 4GB: 300,000 dong, RAM 8GB: 2,000,000 dong)

using namespace std;

struct Book
{
    string ID;
    string text;
};
int RowLimit = 250; // 4 GB RAM: 300000, 8 GB RAM: 2000000

int partition(Book*& arr, int low, int high)
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
void quickSort(Book*& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void writeSmallFile(Book*& Lines, int& end, vector<string>& Sorted, int& count)
{
    string name;
    name = "Sorted";
    name = name + to_string(count) + ".csv";
    count++;
    Sorted.push_back(name);

    fstream file(name, ios_base::out);
    if (!file.is_open())
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        int i = 0;
        while (i < end)
        {
            file << Lines[i].text << endl;
            i++;
        }
    }
    file.close();
}

void ReadAndCreateFile(vector<string> Sorted, vector<string> Merge)
{
    //int limit = 1000;

    string line;
    string fileName("Books_rating_test.csv");
    int count = 0;
    
    fstream file(fileName, ios_base::in);
    if (!file.is_open())
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        if (file.tellg() == 0)
        {
            getline(file, line, '\n');
            int length = line.length() + 1;
            file.seekg(length);
        }
        while (!file.eof())
        {
            Book* Lines = new Book[RowLimit];
            int i = 0;
            while (i < RowLimit)
            {
                if (file.eof())
                {
                    break;
                }
                getline(file, line, '\n');
                string s = "";
                int length = line.length();
                for (int j = 0; j < length; j++)
                {
                    if (line[j] == ',')
                    {
                        break;
                    }
                    s += line[j];
                }
                Lines[i].ID = s;
                Lines[i].text = line;
                i++;
            }
            

            quickSort(Lines, 0, i - 1);

            //trong trường hợp file nhỏ mà ram có thể chứa hết các dòng, đến end of file, thì cho sắp xếp rồi xuất thẳng file ra, nhớ delete Lines
            if (file.eof() == true && count == 0) // nghĩa là đã đến cuối file nhưng có ghi file nhỏ nào cả
            {
                //cout << "true" << endl;
                fstream fileResult("Books_rating_Sorted.csv", ios_base::out);
                if (!fileResult.is_open())
                {
                    cout << "Cannot open file." << endl;
                }
                else
                {
                    file.close();
                    file.open(fileName, ios_base::in);
                    //file.seekg(0, file.beg);
                    getline(file, line);
                    fileResult << line;
                    cout << line << endl;
                    cout << Lines[0].text << endl;
                    cout << Lines[1].text << endl;
                    cout << Lines[2].text << endl;
                    int j = 0;
                    while (j < i - 1)
                    {
                        //cout << Lines[j].text << endl;
                        fileResult << Lines[j].text << endl;
                        j++;
                    }
                    cout << "The file has been sorted successfully." << endl;
                }
                fileResult.close();
                file.close();
                delete[] Lines;

                

                return;
            }

            writeSmallFile(Lines, i, Sorted, count);

            delete[] Lines;
        }
        //Khởi tạo Merge file
        for (int i = 0; i < count - 1; i++)
        {
            string name = "Merge";
            name = name + to_string(i) + ".csv";
            fstream mergeFile(name, ios::out);
            mergeFile.close();
        }


    }
    file.close();
}

void MergeFile(vector<string> Sorted, vector<string> Merge)
{

}

void Run()
{
    vector<string> Sorted;
    vector<string> Merge;

    ReadAndCreateFile(Sorted, Merge);
    MergeFile(Sorted, Merge);
}

int main()
{
    Run();

    return 0;
}

