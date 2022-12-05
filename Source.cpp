#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include <chrono>
// Dong dau tien trong file khong can sap xep, ghi thang vao
// NRow: so luong dong doc 1 lan (RAM 4GB: 800,000 dong, RAM 8GB: 2,000,000 dong)
using namespace std::chrono;
using namespace std;
struct Book {
    string BookId;
    string title;
    string price;
    string userId;
    string profileName;
    string reviewHelpful;
    string reviewScore;
    string reviewTime;
    string reviewSummary;
    string reviewText;
};

struct List
{
    string ID;
    string line;
};
vector<List> LinkedList;
vector<Book> Listbook;
void WriteElementOfBook(Book& book, string x, int count)
{
    switch (count)
    {
    case(0):
    {
        book.BookId = x;
        break;
    }
    case(1):
    {
        book.title = x;
        break;
    }
    case(2):
    {
        book.price = x;
        break;
    }
    case(3):
    {
        book.userId = x;
        break;
    }
    case(4):
    {
        book.profileName = x;
        break;
    }
    case(5):
    {
        book.reviewHelpful = x;
        break;
    }
    case(6):
    {
        book.reviewScore = x;
        break;
    }
    case(7):
    {
        book.reviewTime = x;
        break;
    }
    case(8):
    {
        book.reviewSummary = x;
        break;
    }
    default:
        book.reviewText = x;
        break;
    }
}
void readFileOnly(vector<List>& LinkedList, int start, int end)
{
    //string fileName("test.txt");
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
            List L;
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
            LinkedList.push_back(L);
        }
        /*for (int i = 0; i < end-1; i++)
        {
            cout << LinkedList[i].ID << "####" << LinkedList[i].line << endl;
        }*/
        
    }
    
    file.close();
}
void writeFile(vector<List> LinkedList, int start, int end)
{
    int count = 0;
    string fileName("Books_rating_Sorted.csv");
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
void Run()
{
    vector<List> LinkedList;
    vector<string> lines;
    int Nrow = 10;
    readFileOnly(LinkedList, 0, 100000);
   // writeFile(LinkedList, 0, 10);
}
void printBook(Book book)
{
    cout << " IDBook:  " << book.BookId << endl;
    cout << " title:  " << book.title << endl;
    cout << " price:  " << book.price << endl;
    cout << " user_id:  " << book.userId << endl;
    cout << " profileName:  " << book.profileName << endl;
    cout << " reviewHelpful:  " << book.reviewHelpful << endl;
    cout << " reviewScore:  " << book.reviewScore << endl;
    cout << " reviewTime:  " << book.reviewTime << endl;
    cout << " reviewSummary:  " << book.reviewSummary << endl;
    cout << " reviewText:  " << book.reviewText << endl;
}
void printListBook(vector<Book> Listbook)
{
    for (int i = 0; i < Listbook.size(); i++)
    {
        printBook(Listbook[i]);
        cout << endl;
    }
}
void ReadFile(vector<Book>& Listbook, int NRow)
{
    string filename("Book2.csv");
    // Khai báo vector để lưu các dòng đọc được
    vector<string> lines;
    string line;

    //Mở file bằng ifstream
    ifstream input_file(filename, ios_base::in | ios_base::binary);
    //Kiểm tra file đã mở thành công chưa
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << filename << "'" << endl;
        return;
    }

    //Đọc từng dòng trong
    while (getline(input_file, line, '\n')) {
        lines.push_back(line);//Lưu từng dòng như một phần tử vào vector lines.

    }
    //Xuất từng dòng từ lines và in ra màn hình
    int length = lines.size();
    for (int i = 0; i < length; i++)
    {
        //cout << lines[i] << endl;
        Book book;
        string x;
        int count = 0;
        int lengthLine = lines[i].length();
        //de nhan biet bat dau mot chuoi co dau phay hay khong
        bool flag = false;
        for (int j = 0; j < lengthLine; j++)
        {
            if (j == lengthLine - 2)
            {
                WriteElementOfBook(book, x, count);
                x = "";
                break;
            }
            else if (lines[i][j] == ',' && flag == false)
            {
                WriteElementOfBook(book, x, count);
                count++;
                x = "";
            }
            else if (lines[i][j] == '"' && flag == false)
            {
                flag = true;
            }
            else if (lines[i][j] == '"' && flag == true)
            {

                if (lines[i][j + 1] == '"')
                {
                    x += '"';
                    j++;
                }
                else if (lines[i][j + 1] == ',')
                {
                    WriteElementOfBook(book, x, count);
                    count++;
                    x = "";
                    flag = false;
                }
                else
                {
                    x += lines[i][j];
                }
            }
            else
            {
                x += lines[i][j];
            }
        }
        Listbook.push_back(book);
    }
    //printListBook(Listbook);
    //Đóng file
    input_file.close();
}

int main()
{
    //Run();
    //readFileOnly();
    //ReadFile();
    return 0;
}