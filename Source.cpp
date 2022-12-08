#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

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
void writeSmallMergeFile(string output, string input1, string input2)
{
    fstream fileOutput(output, ios_base::out);
    fstream fileInput1(input1, ios_base::in);
    fstream fileInput2(input2, ios_base::in);
    Book book1;
    Book book2;
    string s = "";
    string line = "";
    bool check1 = false;
    bool check2 = false;
    if (!fileOutput.is_open() || !fileInput1.is_open() || !fileInput2.is_open())
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        while (!fileInput1.eof() || !fileInput2.eof())
        {
            if (check1 == false && !fileInput1.eof())
            {
                getline(fileInput1, line, '\n');
                if (line[0] == NULL)
                {
                    continue;
                }
                int length = line.length();
                for (int j = 0; j < length; j++)
                {
                    if (line[j] == ',')
                    {
                        break;
                    }
                    s += line[j];
                }
                book1.ID = s;
                book1.text = line;
                s = "";
                line = "";
                check1 = true;
            }
            else if (check2 == false && !fileInput2.eof())
            {
                getline(fileInput2, line, '\n');
                if (line[0] == NULL)
                {
                    continue;
                }
                int length = line.length();
                for (int j = 0; j < length; j++)
                {
                    if (line[j] == ',')
                    {
                        break;
                    }
                    s += line[j];
                }
                book2.ID = s;
                book2.text = line;
                s = "";
                line = "";
                check2 = true;
            }

            if (fileInput1.eof())
            {
                fileOutput << book2.text;

                while (!fileInput2.eof())
                {
                    getline(fileInput2, line, '\n');
                    if (line[0] == NULL)
                    {
                        continue;
                    }
                    fileOutput << endl << line ;
                    line = "";
                }
            }
            else if (fileInput2.eof())
            {
                fileOutput << book1.text;

                while (!fileInput1.eof())
                {
                    getline(fileInput1, line, '\n');
                    if (line[0] == NULL)
                    {
                        continue;
                    }
                    fileOutput << endl << line ;
                    line = "";
                }
            }

            if (book1.ID < book2.ID)
            {
                fileOutput << book1.text << endl;
                check1 = false;
            }
            else
            {
                fileOutput << book2.text << endl;
                check2 = false;
            }
        }
    }

    fileOutput.close();
    fileInput1.close();
    fileInput2.close();

    //xoa file
    remove(input1.c_str());
    remove(input2.c_str());
}
void ReadAndCreateFile(vector<string>& Sorted, vector<string>& Merge)
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
            if (file.eof() == true && count == 0) // nghĩa là đã đến cuối file nhưng k có ghi file nhỏ nào cả
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
        for (int i = 0; i < count - 1; i++)
        {
            string name = "Merge";
            name = name + to_string(i) + ".csv";
            Merge.push_back(name);
            /*fstream mergeFile(name, ios::out);
            mergeFile.close();*/
        }


    }
    file.close();
}

void MergeFile(vector<string> Sorted, vector<string> Merge)
{
    //int lengthSorted = Sorted.size();
    int lengthMerge = Merge.size();
    //cout << lengthSorted << " " << lengthMerge << endl;
    //cout << Merge[0] << " " << Sorted[0] << " " << Sorted[1] << endl;
    writeSmallMergeFile(Merge[0], Sorted[0], Sorted[1]);
    for (int i = 0; i < lengthMerge - 1; i++)
    {
        //cout << Merge[i + 1] << " " << Sorted[i + 2] << " " << Merge[i] << endl;
        writeSmallMergeFile(Merge[i + 1], Sorted[i + 2], Merge[i]);
    }

    remove("Books_rating_Sorted.csv");
    rename(Merge[lengthMerge - 1].c_str(), "Books_rating_Sorted.csv");
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
