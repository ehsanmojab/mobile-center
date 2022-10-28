#include <iostream> // Ehsan Mojab
#include <fstream>  // Term 4001
#include <cstring>  // University of Sistan and Baluchestan
#include <iomanip>
#include <string>
using namespace std;

///////////////////    Structures    //////////////////////
typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    int code;
    char type[30];
    Date sold_date;
    int warranty;
    int service;    
} Mobile;

typedef struct
{
    char text[30] = {'\0'};
    int num = 0;
} Info;
///////////////////////////////////////////////////////////

int numLines = 0, lines = 0;
int Count = -1; // line of specific input code

///////////////////////     FUNCTIONS     ///////////////////////
void getdate(Mobile &);
bool check(int); // this function checks if the mobile is valid or not
int char_to_int(char[]);
void add_moobile();         
void mobile_service();      
int most_service_warranty();
void print(int);
void service_date(); 
void sold_date();     
void most_warranty(); 
void menu_1();
void menu_2();
bool is_numb(char[]);
////////////////////////////////////////////////////////////////

int main()
{
    int a, b;
    Mobile A;
    fstream read("memory.txt", ios::in);
    fstream write("memory.txt", ios::app);
    fstream read1("service_date.txt", ios::in);

    if (!read.is_open() || !write.is_open())
    {
        cerr << "memory textfile did not found!";
        exit(1);
    }

    char unused[200];
    while (read.getline(unused, 200))
        ++numLines;
    // count lines of memory.txt ^
    while (read1.getline(unused, 200))
        ++lines;
    // count lines of service_date.txt ^

    menu_1();

    cin >> a;

    switch (a)
    {
    case 1: // reports
        system("cls");
        menu_2();
        cin >> b;
        system("cls");
        cout << endl;
        switch (b)
        {
        case 1:
            cout << "The model that has had the most repairs :\n";
            mobile_service();
            break;
        case 2:
            cout << "The most serviced mobile :\n";
            print(most_service_warranty());
            break;
        case 3:
            cout << "Number of repairs by month :\n";
            service_date();
            break;
        case 4:
            cout << "Number of solds By month :\n";
            sold_date();
            break;
        case 5:
            cout << "The most lenght of warranty  : (months)\n";
            most_warranty();
            break;
        }
        break;
    case 2:
        add_moobile();
        break;
    case 3:
        cout << "Enter the code to search : ";
        cin >> A.code;
        cout << check(A.code) << endl;
        if (!check(A.code))
            break;
        getdate(A);
        cout << A.sold_date.year << '/' << A.sold_date.month << '/' << A.sold_date.day;
        break;
    case 4:
        for (int i = 0; i < numLines; i++)
            print(i);
        break;
    }
    read.close();
    write.close();
    read1.close();

    cout << endl;
    system("pause");
    return 0;
}

bool check(int code)
{
    int phone_code;
    char check[100] = {'\0'}, CODE[10] = {'\0'};
    fstream read("memory.txt", ios::in);

    for (int i = 0; i < numLines; i++)
    {
        read.getline(check, 100);
        for (int k = 0; check[k] != ' '; k++)
            CODE[k] = check[k];
        phone_code = char_to_int(CODE);
        if (phone_code == code)
        {
            Count = i;
            read.close();
            return true;
        }
    }
    read.close();
    return false;
}

void getdate(Mobile &A)
{
    if (Count == -1)
    {
        cerr << "not valid mobile!";
        return;
    }
    int i;
    fstream read("memory.txt", ios::in);
    char ch[100] = {'\0'}, year[5] = {'\0'}, month[3] = {'\0'}, day[3] = {'\0'}, unused[100];

    for (int k = 0; k < Count; k++)
        read.getline(unused, 100);
    read.getline(ch, 100);
    for (i = 0; ch[i] != ':'; i++);
    i++;
    for (int j = 0; ch[i] != '/'; j++, i++)
        year[j] = ch[i];
    A.sold_date.year = char_to_int(year);
    i++;
    read.ignore();
    for (int j = 0; ch[i] != '/'; j++, i++)
        month[j] = ch[i];
    A.sold_date.month = char_to_int(month);
    i++;
    for (int j = 0; ch[i] != ';'; j++, i++)
        day[j] = ch[i];
    A.sold_date.day = char_to_int(day);
    // cout << A.sold_date.year << A.sold_date.month << A.sold_date.day;
    read.close();
}

int char_to_int(char ch[])
{
    int l = strlen(ch);
    int A = 0, ten, c;
    for (int i = 0; i < l; i++)
    {
        ten = 1;
        for (int j = l - 1; j > i; j--)
            ten *= 10;
        c = (int)ch[i] - 48;
        A += c * ten;
    }
    return A;
}

void add_moobile()
{
    Mobile phone;
    char ch[80] = {'\000'};
    phone.warranty = 0, phone.service = 0;
    fstream write("memory.txt", ios::app);

    while (true)
    {
        cout << "enter code of the mobile : ";
        cin >> ch;
        if (!is_numb(ch))
        {
            cout << "Enter number!\n";
            continue;
        }
        if (strlen(ch) > 7)
        {
            cout << "code length should'nt be more than 7 charachters!\n";
            continue;
        }
        phone.code = char_to_int(ch);
        break;
    }

    while (true)
    {
        ch[80] = {'\000'};
        cout << "Enter type of phone : ";
        cin >> ch;
        if (strlen(ch) > 28)
        {
            cout << "lenght of type should be less than 28!\n";
            continue;
        }
        for (int f = 0; f < 29; f++)
            phone.type[f] = ch[f];
        break;
    }
    while (true)
    {
        ch[80] = {'\000'};
        cout << "Enter year : ";
        cin >> ch;
        if (!is_numb(ch))
        {
            cout << "Enter number!\n";
            continue;
        }
        if (strlen(ch) > 4)
        {
            cout << "enter valid year!\n";
            continue;
        }
        phone.sold_date.year = char_to_int(ch);
        if (phone.sold_date.year > 1400 || phone.sold_date.year < 1370)
        {
            cout << "Enter year among 1400-1370\n";
            continue;
        }
        break;
    }
    while (true)
    {
        ch[80] = {'\000'};
        cout << "Enter month : ";
        cin >> ch;
        if (!is_numb(ch))
        {
            cout << "Enter number!\n";
            continue;
        }
        if (strlen(ch) > 2)
        {
            cout << "enter valid month!\n";
            continue;
        }
        phone.sold_date.month = char_to_int(ch);
        if (phone.sold_date.month > 12 || phone.sold_date.month < 1)
        {
            cout << "Enter month among 1-12!\n";
            continue;
        }
        break;
    }
    while (true)
    {
        ch[80] = {'\000'};
        cout << "Enter day: ";
        cin >> ch;
        if (!is_numb(ch))
        {
            cout << "Enter number!\n";
            continue;
        }
        if (strlen(ch) > 2)
        {
            cout << "enter valid day!\n";
            continue;
        }
        phone.sold_date.day = char_to_int(ch);
        if (phone.sold_date.day > 31 || phone.sold_date.day < 1)
        {
            cout << "Enter day among 1-31!\n";
            continue;
        }
        break;
    }

    while (true)
    {
        ch[80] = {'\000'};
        cout << "Enter lenght of warranty in months : ";
        cin >> ch;
        if (!is_numb(ch))
        {
            cout << "Enter number!\n";
            continue;
        }
        if (strlen(ch) > 4)
        {
            cout << "enter valid warranty in month!\n";
            continue;
        }
        phone.warranty = char_to_int(ch);
        if (phone.warranty < 0)
        {
            cout << "Enter valid number!\n";
            continue;
        }
        break;
    }
    while (true)
    {
        ch[80] = {'\000'};
        cout << "Enter number of services : ";
        cin >> ch;
        if (!is_numb(ch))
        {
            cout << "Enter number!\n";
            continue;
        }
        if (strlen(ch) > 4)
        {
            cout << "enter valid number!\n";
            continue;
        }
        phone.service = char_to_int(ch);
        if (phone.service < 0)
        {
            cout << "enter valid number!\n";
            continue;
        }
        break;
    }
    
    write << endl << phone.code << " " << phone.type << " :" << phone.sold_date.year << '/' << phone.sold_date.month 
    << '/' << phone.sold_date.day << ';' << ' ' << phone.warranty << " -" << phone.service << '-';

    cout << "information has been saved!";
    write.close();
}

void mobile_service() 
{
    Info serv[100];
    serv[100].num = {0};
    serv[100].text[100] = {'\0'};
    fstream read("memory.txt", ios::in);
    char ch[150] = {'\0'}, name[30] = {'\0'}, cd[4] = {'\0'};
    int n, i, j;

    for (i = 0; i < numLines; i++)
    {
        cd[0] = '\0', cd[1] = '\0', cd[2] = '\0', cd[3] = '\0';
        read.getline(ch, 150);
        for (j = 0; ch[j] != ' '; j++) ; // pass the code
        j++;
        for (int k = 0; ch[j] != ' '; k++, j++) // get the mobile name
            serv[i].text[k] = ch[j];
        for (int k = 0; ch[j] != '-'; k++, j++);// pass date and warranty
        j++;
        for (int k = 0; ch[j] != '-'; k++, j++)
            cd[k] = ch[j]; // get number of services
        serv[i].num = char_to_int(cd);
        // cout << serv[i].text << "\t" << serv[i].num << endl;
    }
    char most[30];
    int most_service;
    for (int f = 0; f < numLines; f++)
    {
        if (serv[f].text[0] == '*')
            continue;
        for (int g = f + 1; g < numLines; g++)
        {
            if (serv[g].text[0] == '*')
                continue;
            if (strcmp(serv[f].text, serv[g].text) == 0)
            {
                serv[f].num += serv[g].num;
                serv[g].text[0] = {'*'}; // delete line
                serv[g].num = 0;
            }
        }
    }

    strcpy(most, serv[0].text);
    most_service = serv[0].num;

    for (int h = 0; h < numLines; h++)
    {
        if (serv[h].text[0] == '*')
            continue;
        if (most_service < serv[h].num)
        {
            strcpy(most, serv[h].text);
            most_service = serv[h].num;
        }
    }

    cout << setw(10) << most << setw(4) << most_service;
    read.close();
}

int most_service_warranty()
{
    fstream read("memory.txt", ios::in);
    int max = 0, j, index;
    char m[4] = {'\0'}, ch[200] = {'\0'};

    for (int i = 0; i < numLines; i++)
    {
        m[0] = '\0', m[1] = '\0', m[2] = '\0', m[3] = '\0';
        read.getline(ch, 200);
        for (j = 0; ch[j] != '-'; j++) ;
        j += 1;
        for (int k = 0; ch[j] != '-'; k++, j++)
            m[k] = ch[j];
        if (max < char_to_int(m)) // check for max
        {
            max = char_to_int(m);
            index = i;
        }

        read.ignore();
    }
    read.close();
    return index; 
}

void print(int m)
{
    Mobile A;
    int j, code;
    fstream read("memory.txt", ios::in);
    char ch[200] = {'\0'}, cd[15] = {'\0'}, name[30] = {'\0'};

    for (int i = 0; i <= m; i++) // go to the specific line
        read.getline(ch, 200);

    for (int g = 0; ch[g] != ' '; g++) // get the code
        cd[g] = ch[g];
    code = char_to_int(cd);
    A.code = code;

    for (j = 0; ch[j] != ' '; j++)
        cout << ch[j];
    for (int k = 0; ch[j] != ':'; k++, j++) // get the phone type
        name[k] = ch[j];
    cout << setw(10) << name;
    check(code);
    getdate(A);
    cout << setw(7) << A.sold_date.year << '/' << A.sold_date.month << '/' << A.sold_date.day;

    for (; ch[j] != ';'; j++) ; // pass the Date
    j += 2;
    cout << setw(14) << "\"";
    for (; ch[j] != ' '; j++)
        cout << ch[j];
    cout << "\" months warranty\t";

    for (; ch[j] != '-'; j++);
    j++;
    cout << "---number of services in time of warranty : ";
    for (int s = 0; ch[j] != '-'; s++, j++)
        cout << ch[j];

    cout << "\n___________________________________________________________________________________________________________________\n";
    read.close();
}

void service_date()
{
    int A[12] = {0}, i, month, k, f;
    fstream read("service_date.txt", ios::in);
    char ch[200] = {'\000'}, cd[3] = {'\000'};

    for (k = 0; k < lines; k++)
    {
        char ch[200] = {'\000'};
        read.getline(ch, 200);

        int i = 0;
        bool copy = 0;
        int copy_index = 0;
        while (ch[i] != '\000')
        {
            if (copy)
            {
                if (ch[i] == '/')
                {
                    copy = 0;
                    copy_index = 0;
                    A[char_to_int(cd) - 1]++;
                    cd[0] = '\000', cd[1] = '\000', cd[2] = '\000';
                }
                else
                {
                    cd[copy_index] = ch[i];
                    copy_index++;
                }
            }
            else if (ch[i] == '/')
                copy = 1;

            i++;
        }
    }
    string str[12] = {"Farvardin", "Ordibehesht", "Khordad", "Tir", "Mordad", "Shahrivar", "Mehr", "Aban", "Azar", "Dey", "Bahman", "Esfand"};

    for (int r = 0; r < 12; r++)
        cout << setw(12) << str[r] << " : " << A[r] << endl;
    read.close();
}

void sold_date()
{
    Mobile A;
    int Month[12] = {0};
    string str[12] = {"Farvardin", "Ordibehesht", "Khordad", "Tir", "Mordad", "Shahrivar", "Mehr", "Aban", "Azar", "Dey", "Bahman", "Esfand"};

    for (int i = 0; i < numLines; i++)
    {
        A.sold_date.day = 0, A.sold_date.month = 0, A.sold_date.year = 0;
        Count = i;
        getdate(A);
        // cout << A.sold_date.year << '/' << A.sold_date.month << '/' << A.sold_date.day << endl;
        Month[A.sold_date.month - 1]++;
    }
    for (int j = 0; j < 12; j++)
        cout << setw(15) << str[j] << " : " << setw(2) << Month[j] << '\n';
}

void most_warranty()
{
    Info warranty[100];
    warranty[100].num = {0};
    warranty[100].text[30] = {'\0'};
    fstream read("memory.txt", ios::in);
    char ch[200] = {'\0'}, num[4] = {'\0'}, most[30] = {'\0'};
    int i, j, k, most_warranty = -1;

    for (i = 0; i < numLines; i++)
    {
        read.getline(ch, 200);

        for (j = 0; ch[j] != ' '; j++);
        j++;
        for (k = 0; ch[j] != ' '; k++, j++) // get the mobile name
            warranty[i].text[k] = ch[j];
        for (; ch[j] != ';'; j++);
        j += 2;

        for (k = 0; ch[j] != ' '; k++, j++)
            num[k] = ch[j];
        warranty[i].num = char_to_int(num);
    }

    for (i = 0; i < numLines; i++)
    {
        if (warranty[i].text[0] == '*')
            continue;
        for (j = i + 1; j < numLines; j++)
        {
            if (warranty[i].text[0] == '*')
                continue;
            if (strcmp(warranty[i].text, warranty[j].text) == 0)
            {
                warranty[i].num += warranty[j].num;
                warranty[j].text[0] == '*';
                warranty[j].num = 0;
            }
        }
    }

    most_warranty = warranty[0].num;
    strcpy(most, warranty[0].text);

    for (i = 0; i < numLines; i++)
    {
        if (warranty[i].text[0] == '*')
            continue;
        if (warranty[i].num > most_warranty)
        {
            most_warranty = warranty[i].num;
            strcpy(most, warranty[i].text);
        }
    }
    cout << setw(30) << most << setw(5) << most_warranty;
    read.close();
}

void menu_1()
{
    char ch = '/';

    for (int i = 0; i < 109; i++)
        cout << ch;
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << ch;
        for (int j = 0; j < 26; j++)
            cout << ' ';
        cout << ch;
        for (int j = 0; j < 26; j++)
            cout << ' ';
        cout << ch;
        for (int j = 0; j < 26; j++)
            cout << ' ';
        cout << ch;
        for (int j = 0; j < 26; j++)
            cout << ' ';
        cout << ch << endl;
        if (i == 1)
        {
            cout << ch << "        1. reports        " << ch << "    2. add new mobile     " << ch << "       3. search          " << ch << " 4.print all informations /\n";
            i++;
        }
    }
    for (int i = 0; i < 109; i++)
        cout << ch;
    cout << endl;
}

void menu_2()
{
    char c = '|';
    cout << "- reports : \\/\n";
    for (int i = 0; i < 3; i++)
        cout << "--------------";
    cout << endl;
    cout << "\t+ 1. most services (model)\n";
    for (int i = 0; i < 5; i++)
        cout << "\t" << c << endl;
    cout << "\t+ 2. the most serviced mobile\n";
    for (int i = 0; i < 5; i++)
        cout << "\t" << c << endl;
    cout << "\t+ 3. report of services -12months\n";
    for (int i = 0; i < 5; i++)
        cout << "\t" << c << endl;
    cout << "\t+ 4. report of solds -12months\n";
    for (int i = 0; i < 5; i++)
        cout << "\t" << c << endl;
    ;
    cout << "\t+ 5. most warranty\n";
}

bool is_numb(char ch[])
{
    for (int i = 0; ch[i] != '\0' && i < strlen(ch); i++)
        if (ch[i] > 57 || ch[i] < 48)
            return false;
    return true;
}
// memmory.txt 
/*
1400231 samsung :1400/10/15; 20 -21-
1400562 apple :1400/2/12; 0 -3-
1400213 mi :1400/9/23; 13 -0-
1400111 samsung :1400/10/9; 0 -39-
1400222 apple :1400/5/2; 25 -3-
8752335 samsung :1400/10/10; 24 -79-
1538652 mi :1400/9/9; 44 -111-
5477237 mi :1400/7/30; 12 -0-
1400699 samsung :1400/12/2; 12 -2-
1401241 mi :1400/1/31; 29 -0-
141124 samsung :1400/12/1; 5 -1-
*/