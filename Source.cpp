#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

#include <chrono>
using namespace std::chrono;

using namespace std;

// RowLimit: so luong dong doc 1 lan (RAM 4GB: 300,000 dong, RAM 8GB: 2,000,000 dong)
int RowLimit = 250;

struct Book
{
    string ID;
    string text;
};

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

    fstream file(name, ios_base::out | ios_base::binary);
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
void writeSmallMergeFile(string output, string input1, string input2, bool lastFile)
{
    fstream fileOutput(output, ios_base::out | ios_base::binary);
    fstream fileInput1(input1, ios_base::in | ios_base::binary);
    fstream fileInput2(input2, ios_base::in | ios_base::binary);
    Book book1;
    Book book2;
    string s = "";
    string line = "";
    bool check1 = false;
    bool check2 = false;

    int count1 = 0, count2 = 0;

    if (!fileOutput.is_open() || !fileInput1.is_open() || !fileInput2.is_open())
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        if (lastFile == true)
        {
            fstream f("Books_Rating.csv", ios_base::in);
            string line;
            getline(f, line, '\n');
            cout << "final: true" << endl;
            //cout << line << endl;
            fileOutput << line << endl;
            f.close();
        }
        while (!fileInput1.eof() || !fileInput2.eof())
        {
            if (check1 == false && !fileInput1.eof())
            {
                getline(fileInput1, line, '\n');
                if (line[0] == NULL)
                {
                    //cout << true << endl;
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
                check1 = true;
            }
            else if (check2 == false && !fileInput2.eof())
            {
                getline(fileInput2, line, '\n');
                if (line[0] == NULL)
                {
                    //cout << true << endl;
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
                check2 = true;
            }

            if (fileInput1.eof())
            {
                if(book2.text[0] != NULL)
                {
                    fileOutput << book2.text << endl;
                    //count2++;
                }
                

                while (!fileInput2.eof())
                {
                    getline(fileInput2, line, '\n');
 
                    if (line[0] != NULL)
                    {
                        fileOutput << line << endl;
                        //count2++;
                    }
                    
                }
            }
            else if (fileInput2.eof())
            {
                if (book1.text[0] != NULL)
                {
                    fileOutput << book1.text << endl;
                    //count1++;
                }
                
                while (!fileInput1.eof())
                {
                    getline(fileInput1, line, '\n');
                    if (line[0] != NULL)
                    {
                        fileOutput << line << endl;
                        //count1++;
                    }
                    
                }
            }

            if (book1.ID < book2.ID)
            {
                if (book1.text[0] == NULL)
                {
                    //cout << true << endl;
                }
                else
                {
                    fileOutput << book1.text << endl;
                    //count1++;
                } 
                check1 = false;
            }
            else
            {
                if (book2.text[0] == NULL)
                {
                    //cout << true << endl;
                }
                else
                {
                    fileOutput << book2.text << endl;
                    //count2++;
                }
                check2 = false;
            }
        }
    }

    fileOutput.close();
    fileInput1.close();
    fileInput2.close();

    //cout << "Count1: " << count1 << endl;
    //cout << "Count2: " << count2 << endl;

    //xoa file
    remove(input1.c_str());
    remove(input2.c_str());
}
void ReadAndCreateFile(string fileName, vector<string>& Sorted, vector<string>& Merge)
{
    string line;
    int count = 0;

    fstream file(fileName, ios_base::in | ios_base::binary);
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
            cout << count << endl;
            cout << "Bat dau nap file" << endl;

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

            cout << "Nap file xong" << endl;
            cout << "Bat dau sort" << endl;
            
            quickSort(Lines, 0, i - 1);

            cout << "Sort xong" << endl;

            //trong trường hợp file có số dòng nhỏ hơn RowLimit, đến end of file, sau khi sắp xếp rồi xuất thẳng file ra, nhớ delete Lines
            if (file.eof() == true && count == 0) // nghĩa là đã đến cuối file nhưng chưa ghi file nhỏ nào cả
            {
                //cout << "true" << endl;
                fstream fileResult("Books_rating_Sorted.csv", ios_base::out | ios_base::binary);
                if (!fileResult.is_open())
                {
                    cout << "Cannot open file." << endl;
                }
                else
                {
                    file.close();
                    file.open(fileName, ios_base::in | ios_base::binary);
                    //file.seekg(0, file.beg);
                    getline(file, line, '\n');
                    fileResult << line << endl;
                    int j = 0;
                    while (j <= i)
                    {
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

            cout << "Bat dau ghi file" << endl;

            writeSmallFile(Lines, i, Sorted, count);

            cout << "Ghi file xong" << endl;
            cout << "---------------" << endl << endl;

            delete[] Lines;
        }

        cout << "Da doc het file csv" << endl;

        for (int i = 0; i < count - 1; i++)
        {
            string name = "Merge";
            name = name + to_string(i) + ".csv";
            Merge.push_back(name);
        }
    }
    cout << "Create Sorted file successfully." << endl;
    cout << "---------------" << endl << endl;
    file.close();
}

void MergeFile(vector<string> Sorted, vector<string> Merge)
{

    int lengthMerge = Merge.size();

    if(lengthMerge <= 0) // Co 1 file sorted, so dong file csv < RowLimit
    {
        return;
    }
    else if (lengthMerge == 1) // Chi co tong cong 2 file sorted
    {
        cout << "Merge 0" << endl;
        writeSmallMergeFile(Merge[0], Sorted[0], Sorted[1], true);
    }
    else // Tong cong nhieu hon 2 file sorted
    {
        cout << "Merge 0" << endl;
        writeSmallMergeFile(Merge[0], Sorted[0], Sorted[1], false);
    }
    
    cout << "Merge 0 xong" << endl;
    cout << "---------------" << endl << endl;

    for (int i = 0; i < lengthMerge - 1; i++)
    {
        if (i == lengthMerge - 2)
        {
            cout << "final merge" << endl;
            writeSmallMergeFile(Merge[i + 1], Sorted[i + 2], Merge[i], true);
            cout << "final merge complete" << endl;
            cout << "---------------" << endl << endl;
            cout << "The file has been sorted successfully and saved as Books_rating_Sorted.csv" << endl;
            break;
        }
        
        cout << "Merge " << i + 1 << endl;

        writeSmallMergeFile(Merge[i + 1], Sorted[i + 2], Merge[i], false);

        cout << "Merge " << i + 1<<" xong" << endl;
        cout << "---------------" << endl << endl;
    } 

    remove("Books_rating_Sorted.csv");
    rename(Merge[lengthMerge - 1].c_str(), "Books_rating_Sorted.csv");
    
}

void Run()
{
    RowLimit = 300000; // 4GB: 300,000; 8GB: 2,000,000

    cout << "RowLimit: " << RowLimit << endl << endl;
    vector<string> Sorted;
    vector<string> Merge;
    string fileName("Books_rating.csv"); //"Books_rating.csv" de chay file chinh, "Books_rating_test.csv" de chay thu
    ReadAndCreateFile(fileName, Sorted, Merge);
    MergeFile(Sorted, Merge); // Luu trong "Books_rating_Sorted.csv"
}

void runResultFile()
{
    fstream file("Books_rating_Sorted.csv", ios_base::in);
    fstream result("Result.csv", ios_base::out);
    if (!file.is_open())
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        string line;
        for (int i = 0; i < 1000; i++)
        {
            getline(file, line, '\n');
            result << line << endl;
        }
    }
    file.close();
    result.close();


}

int main()
{
    auto start = high_resolution_clock::now();

    Run();

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    auto duration1 = duration_cast<seconds>(stop - start);

    cout << "Time taken: "
        << duration.count() << " microseconds" << endl;
    cout << "Time taken: "
        << duration1.count() << " seconds" << endl;

    //runResultFile();

    return 0;
}
