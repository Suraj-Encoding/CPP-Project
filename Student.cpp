/*
    # Project Name: << Student Database Management System >>

    # Team Members:
        1. A44 -> Suraj Dalvi
        2. A45 -> Pratiksha Darekar
        3. A48 -> Yogeshwari Desai

    # Info:
        -  Branch: Computer
        -  Div: A
        -  Batch: A3

    # Concepts Used:
         1. OOPS Concepts Including Major Role Of File Handling
         2. Strong knowledge of C++

*/

// ** Source Code **

// # Required Header Files
#include <iostream>
#include <fstream> //  -> Imp for file handling
#include <regex>   //  -> Regular Expression pattern detector
using namespace std;

// # Student Class
class Student
{
private:
    string name, roll_no, course, address, email_id;
    char contact_no[10];

public:
    // Member Functions
    void Menu();
    void Insert();
    void Display();
    void Modify();
    void Search();
    void Delete();
};

//  ** Function Defination **

// ** Email Validation **
bool Emailcheck(string email)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}

// # Database Menu
void Student ::Menu()
{
    // Menu driven program

    int choice;
    char x;
    // system("cls");  // * clear screen
    do
    {
        // Menu
        cout << "\n\t\t\t--------------------------------------" << endl;
        cout << "\t\t\t| STUDENT DATABASE MANAGEMENT SYSTEM |" << endl;
        cout << "\t\t\t--------------------------------------" << endl;
        cout << "\t\t\t 1. Enter New Record" << endl;
        cout << "\t\t\t 2. Display Record" << endl;
        cout << "\t\t\t 3. Modify Record" << endl;
        cout << "\t\t\t 4. Search Record" << endl;
        cout << "\t\t\t 5. Delete Record" << endl;
        cout << "\t\t\t 6. Exit\n"
             << endl;
        cout << "\t\t\t............................" << endl;
        cout << "\t\t\tChoose Options:[1/2/3/4/5/6]" << endl;
        cout << "\t\t\t............................" << endl;
        cout << "\n # Enter Your Choose: ";
        cin >> choice;

        // Switch
        switch (choice)
        {

        case 1:
            do
            {
                Insert();
                cout << "\n\t\t# Add Another Student Record (Y, N) : ";
                cin >> x;
            } while (x == 'y' || x == 'Y');
            break;

        case 2:
            Display();
            break;

        case 3:
            Modify();
            break;

        case 4:
            Search();
            break;

        case 5:
            Delete();
            break;

        case 6:
            cout << "\n\t\t\t# Program Is Exit\n"
                 << endl;
            exit(0);
            break;

        default:
            cout << "\n\n\t\t\t# Invalid Choice! Please Try Again\n"
                 << endl;
            break;
        }
    } while (1);
}

// # Insert Data -> Add Student Data
void Student ::Insert()
{
    // system("cls");
    fstream file;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Add Student Data ---------------------------------------------" << endl;
    cin.ignore();
    cout << "\n\t\t\tEnter Name: ";
    getline(cin, name);
    cout << "\t\t\tEnter Roll No.: ";
    cin >> roll_no;
    cout << "\t\t\tEnter Course: ";
    cin >> course;
email:
    cout << "\t\t\tEnter Email Id (name@gmail.com): ";
    cin >> email_id;
    if (Emailcheck(email_id))
    {
        cout << "\t\t\t# Your Email Id is Valid..." << endl;
    }
    else
    {
        cout << "\t\t\t# Your Email Id is InValid..." << endl;
        goto email;
    }
contact:
    cout << "\t\t\tEnter Contact No. (7447XXXXXX): ";
    cin >> contact_no;
    for (int i = 0; i < 10; i++)
    {
        if (contact_no[i] > 'A' & contact_no[i] < 'z')
        {
            cout << "\t\t\t# Characters are not allowed..." << endl;
            goto contact;
        }
    }
    int len = 0;
    while (contact_no[len] != '\0')
    {
        len++;
    }
    if (len<10 | len> 10)
    {
        cout << "\t\t\t# Please Enter Only 10 Digits..." << endl;
        goto contact;
    }
    if (contact_no[0] == '0')
    {
        cout << "\t\t\t# First digit should not be 0 ..." << endl;
        goto contact;
    }
    cout << "\t\t\tEnter Address: ";
    cin >> address;
    file.open("RecordBook.txt", ios::app | ios::out);
    file << " \t" << name << "\t " << roll_no << "\t " << course << "\t " << email_id << "\t " << contact_no << "\t " << address << "\n";
    file.close();
}

// # Display Record -> Display Student Data
void Student ::Display()
{
    // system("cls");
    fstream file;
    int total = 1;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Student Record Table --------------------------------------------" << endl;
    file.open("RecordBook.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\t# Data Is Not Present...\n"
             << endl;
        file.close();
    }
    else
    {
        int i = 1;
        file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (i == 1)
            {
                cout << endl;
                cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
                cout << left << setw(10) << "SR No";
                cout << left << setw(13) << "Name";
                cout << left << setw(10) << "Roll No";
                cout << left << setw(10) << "Course";
                cout << left << setw(13) << "Contact No";
                cout << left << setw(10) << "Address";
                cout << left << setw(10) << "Email Id";
                cout << endl;
            }
            cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
            cout << left << setw(10) << i;
            cout << left << setw(13) << name;
            cout << left << setw(10) << roll_no;
            cout << left << setw(10) << course;
            cout << left << setw(13) << contact_no;
            cout << left << setw(10) << address;
            cout << left << setw(10) << email_id;
            cout << endl;
            file >> name >> roll_no >> course >> email_id >> contact_no >> address;
            i++;
        }
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    }
    file.close();
}

// # Modify Record ->  Modify Student Data
void Student ::Modify()
{
    // system("cls");
    fstream file, file1;
    string rollno;
    int found = 0;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Modify Student Record ------------------------------------------" << endl;
    file.open("RecordBook.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\t# Data Not Found...\n"
             << endl;
        file.close();
    }
    else
    {
        cout << "\nEnter Roll No. of student which you want to Modify: ";
        cin >> rollno;
        file1.open("NewRecord.txt", ios::app | ios::out);
        file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (rollno != roll_no)
                file1 << "\t" << name << " \t" << roll_no << "\t " << course << " \t" << email_id << " \t" << contact_no << "\t " << address << "\n";
            else
            {
                cin.ignore();
                cout << "\n\t\t\tEnter Name: ";
                getline(cin, name);
                cout << "\t\t\tEnter Roll No: ";
                cin >> roll_no;
                cout << "\t\t\tEnter Course: ";
                cin >> course;
            email:
                cout << "\t\t\tEnter Email Id (name@gmail.com): ";
                cin >> email_id;
                if (Emailcheck(email_id))
                {
                    cout << "\t\t\t# Your Email Id is Valid..." << endl;
                }
                else
                {
                    cout << "\t\t\t# Your Email Id is InValid..." << endl;
                    goto email;
                }
            contact:
                cout << "\t\t\tEnter Contact No (7447257170): ";
                cin >> contact_no;
                for (int i = 0; i < 10; i++)
                {
                    if (contact_no[i] > 'A' | contact_no[i] < 'z')
                    {
                        cout << "\t\t\t# Characters are not allowed..." << endl;
                        goto contact;
                    }
                }
                int len = 0;
                while (contact_no[len] != '\0')
                {
                    len++;
                }
                if (len<10 | len> 10)
                {
                    cout << "\t\t\t# Please Enter Only 10 Digits..." << endl;
                    goto contact;
                }
                if (contact_no[0] == '0')
                {
                    cout << "\t\t\t# First digit should not be 0 ..." << endl;
                    goto contact;
                }
                cout << "\t\t\tEnter Address: ";
                cin >> address;
                file1 << " " << name << " " << roll_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
                found++;
            }
            file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        }
        if (found == 0)
        {
            cout << "\n\n\t\t\t# Student Roll No. Not Found...\n";
        }
        file1.close();
        file.close();
        remove("RecordBook.txt");
        rename("NewRecord.txt", "RecordBook.txt");
    }
}

// # Search Record -> Search Student Data
void Student ::Search()
{
    // system("cls");
    fstream file;
    int found = 0;
    file.open("RecordBook.txt", ios::in);
    if (!file)
    {
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Search Student Record --------------------------------------------" << endl;
        cout << "\n\t\t\t# Student Data Not Found...\n"
             << endl;
    }
    else
    {
        string rollno;
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Search Student Record --------------------------------------------" << endl;
        cout << "\nEnter Roll No. of Student which you want to search: ";
        cin >> rollno;
        file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (rollno == roll_no)
            {

                cout << endl;
                cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
                cout << left << setw(10) << "SR No";
                cout << left << setw(13) << "Name";
                cout << left << setw(10) << "Roll No";
                cout << left << setw(10) << "Course";
                cout << left << setw(13) << "Contact No";
                cout << left << setw(10) << "Address";
                cout << left << setw(10) << "Email Id";
                cout << endl;
                cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
                cout << left << setw(10) << roll_no;
                cout << left << setw(13) << name;
                cout << left << setw(10) << roll_no;
                cout << left << setw(10) << course;
                cout << left << setw(13) << contact_no;
                cout << left << setw(10) << address;
                cout << left << setw(10) << email_id;
                cout << endl;
                file >> name >> roll_no >> course >> email_id >> contact_no >> address;
                cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
                found++;
            }
            file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        }
        if (found == 0)
        {
            cout << "\n\t\t\t# Student Roll No Not Found...\n"
                 << endl;
        }

        file.close();
    }
}

// # Delete Record -> Delete Student Data
void Student ::Delete()
{
    // system("cls");
    fstream file, file1;
    int found = 0;
    string roll;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Delete Student Record ------------------------------------------" << endl;
    file.open("RecordBook.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\t# Data Not Found...\n"
             << endl;
        file.close();
    }
    else
    {
        cout << "\nEnter Roll No. of Student whose data you want delete: ";
        cin >> roll;
        file1.open("NewRecord.txt", ios::app | ios::out);
        file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (roll != roll_no)
            {
                file1 << "\t" << name << "\t" << roll_no << " \t" << course << " \t" << email_id << "\t " << contact_no << " \t" << address << "\n";
            }
            else
            {
                found++;
                cout << "\n\t\t\t# Successfully Delete Data...\n"
                     << endl;
            }
            file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        }
        if (found == 0)
        {
            cout << "\n\t\t\t# Student Roll No. Not Found...\n"
                 << endl;
            ;
        }
        file1.close();
        file.close();
        remove("RecordBook.txt");
        rename("NewRecord.txt", "RecordBook.txt");
    }
}

// Main Function
int main()
{
    Student stud;
    stud.Menu();
    return 0;
}

// ********** Done *********