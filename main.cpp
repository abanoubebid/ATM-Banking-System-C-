#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Client.txt";
const string UsersFile = "Users.txt";
const string UsersPermission = "UserPermission.txt";


void ShowMainMenue();
void ShowTransactionsMenue();
void Login();
void ShowManageUsersMenue();
void ShowAllClientsScreen();
void GoBackToMainMenue();
void ShowMainMenueGetAccess(string);
void ShowManageUsersMenueGetAccess(string);




struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;


};

struct sPermission {
    int Permission;
    char Mark = 'n';
    string name;
    bool MarkForDelete = false;
    short One = 0 ,Two = 0 ,Three = 0 ,Four = 0 ,Five = 0 ,Six = 0 , Seven  = 0 ;
};

struct sUser
{
    sPermission P;
    string Name;
    string Passwd;
    int  Permission ;
    bool MarkForDelete = false;
};
void AddNewUsersP(sPermission);

sUser CurrentUser ;

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable

    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}
sUser ConvertLinetoRecordForUsers(string Line, string Seperator = "#//#")
{
    sUser User;
    vector<string> vUserData;

    vUserData = SplitString(Line, Seperator);

    if (vUserData.size() < 3)
        return User; // حماية من الكراش

    User.Name = vUserData[0];
    User.Passwd = vUserData[1];
    User.Permission = stoi(vUserData[2]);

    return User;
}

sPermission ConvertLinetoRecordForUsersP(string Line, string Seperator = "#//#")
{
    sPermission P;
    vector<string> vUserPData;

   vUserPData = SplitString(Line, Seperator);

    if (vUserPData.size() < 8)
        return P; // حماية من الكراش

    P.name = vUserPData[0];
    P.One = stoi(vUserPData[1]);
    P.Two = stoi(vUserPData[2]);
    P.Three = stoi(vUserPData[3]);
    P.Four = stoi(vUserPData[4]);
    P.Five = stoi(vUserPData[5]);
    P.Six = stoi(vUserPData[6]);
    P.Seven = stoi(vUserPData[7]);



    return P;
}



string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

string ConvertRecordToLineP(sPermission P , string Seperator = "#//#")
{

    string stUserPRecord = "";

    stUserPRecord += P.name + Seperator;
    stUserPRecord += to_string(P.One) + Seperator;
    stUserPRecord += to_string(P.Two) + Seperator;
    stUserPRecord += to_string(P.Three) + Seperator;
    stUserPRecord += to_string(P.Four) + Seperator;
    stUserPRecord += to_string(P.Five) + Seperator;
    stUserPRecord += to_string(P.Six) + Seperator ;
    stUserPRecord += to_string(P.Seven) ;



    return stUserPRecord;

}

string ConvertRecordToLineForUser(sUser User, string Seperator = "#//#")
{

    string stUserRecord = "";

    stUserRecord += User.Name + Seperator;
    stUserRecord += User.Passwd + Seperator;
    stUserRecord += to_string(User.Permission);

    return stUserRecord;

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return false;


}

bool UserExistsByName(string Name, string FileName)
{

    vector <sUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {

            User = ConvertLinetoRecordForUsers(Line);
            if (User.Name == Name)
            {
                MyFile.close();
                return true;
            }


            vUsers.push_back(User);
        }

        MyFile.close();

    }

    return false;


}
sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

sPermission ReadNewuSERp(short Number)
{
    sPermission P;
    P.Permission = Number;
    return P;
}
sPermission SetPermission(string name) {
    sPermission P;
    P.name = name;

    P.Permission = 0;

    cout << "\nDo You Want To Give Access To? " << endl;

    cout << "Show Client List? y/n ";
    cin >> P.Mark;
    if (toupper(P.Mark) == 'Y') {
        P.Permission |= 2 ;
        P.One = 2;
    }

    cout << "New Client? y/n ";
    cin >> P.Mark;
    if (toupper(P.Mark) == 'Y') {
        P.Permission |= 4 ;
        P.Two = 4;
    }

    cout << "Delete Client? y/n ";
    cin >> P.Mark;
    if (toupper(P.Mark) == 'Y') {
        P.Permission |= 8 ;
        P.Three = 8;
    }

    cout << "Update Client? y/n ";
    cin >> P.Mark;
    if (toupper(P.Mark) == 'Y') {
        P.Permission |= 16 ;
        P.Four = 16;
    }

    cout << "Find Client? y/n ";
    cin >> P.Mark;
    if (toupper(P.Mark) == 'Y') {
        P.Permission |= 32 ;
        P.Five = 32;
    }

    cout << "Transactions? y/n ";
    cin >> P.Mark;
    if (toupper(P.Mark) == 'Y') {
        P.Permission |= 64 ;
        P.Six = 64;
    }

    cout << "Manage User? y/n ";
    cin >> P.Mark;
    if (toupper(P.Mark) == 'Y') {
        P.Permission |= 128 ;
        P.Seven = 128;
    }
    AddNewUsersP(P);

    return P ;
}


sPermission ReadPerimssionNotFullAcess(string name,sPermission ePermission , char L ) {

    if (toupper(L) == 'Y' ) {
        ePermission.Permission =  -1 ;
    }
    else {

       ePermission =  SetPermission(name);
    }
    return ePermission;


}

int ReadPerimssion(string name,char L) {

    sPermission ePermission;
    ePermission = ReadPerimssionNotFullAcess(name,ePermission , L );

    return ePermission.Permission;

}

sUser ReadNewUser()
{
    sUser User;
    char L = 'n';
    cout << "Enter Name? ";
    getline(cin >> ws, User.Name);

    while (UserExistsByName(User.Name, UsersFile))
    {
        cout << "\nUser with [" << User.Name << "] already exists, Enter another User? ";
        getline(cin >> ws, User.Name);
    }

    cout << "Enter Password? ";
    cin >> User.Passwd;

    cout << "Do You Want To Give Full Access? ";
    cin >> L ;

    User.Permission = ReadPerimssion(User.Name,L);

    return User;

}
vector <sUser> LoadUsersDataFromFile(string FileName)
{

    vector <sUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sUser  User;

        while (getline(MyFile, Line))
        {

            if (Line.empty())
                continue;

            User = ConvertLinetoRecordForUsers(Line);

            vUsers.push_back(User);
        }

        MyFile.close();

    }

    return vUsers;

}

vector <sPermission> LoadUsersPDataFromFile(string FileName)
{

    vector <sPermission> vPs;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sPermission P;

        while (getline(MyFile, Line))
        {

            if (Line.empty())
                continue;

            P = ConvertLinetoRecordForUsersP(Line);

            vPs.push_back(P);
        }

        MyFile.close();

    }

    return vPs;

}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintUserRecordLine(sUser User)
{

    cout << "| " << setw(15) << left << User.Name;
    cout << "| " << setw(10) << left << User.Passwd;
    cout << "| " << setw(40) << left << User.Permission;

}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowAllClientsScreen()
{


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowAllUsersScreen()
{


    vector <sUser> vUsers = LoadUsersDataFromFile(UsersFile);

    cout << "\n\t\t\tUsers List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________";
    cout << "____________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permission";
    cout << "\n_______________________________________";
    cout << "____________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else

        for (sUser User : vUsers)
        {

            PrintUserRecordLine(User);
            cout << endl;
        }

    cout << "\n_______________________________________";
    cout << "____________________________________\n" << endl;

}

void ShowTotalBalances()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}

void PrintUserCard(sUser User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nName: " << User.Name;
    cout << "\nPassword: " << User.Passwd;
    cout << "\nPermission: " << User.Permission;
    cout << "\n-----------------------------------\n";

}
bool FindUserByNameAndPasswd(string Name , string Passwd, vector <sUser> vUsers, sUser& User)
{

    for (sUser U : vUsers)
    {

        if (U.Name == Name && U.Passwd == Passwd )
        {
            User = U;
            return true;
        }

    }
    return false;

}

bool FindUserByNamePOne(string Name , short Number, vector <sPermission> vPs)
{

    for (sPermission p : vPs)
    {

        if (p.name == Name && p.One == Number )
        {
            return true;
        }

    }
    return false;
}

int FindUserPermission(string Name , string Passwd, vector <sUser> vUsers)
{

    for (sUser U : vUsers)
    {
        if (U.Name == Name && U.Passwd == Passwd )
        {
            return U.Permission ;
        }
    }
}
int GetPerimission(string Name , string Passwd) {

    vector <sUser> vUsers = LoadUsersDataFromFile(UsersFile);
    return FindUserPermission(Name ,Passwd, vUsers);
}
bool SuccessfulAuthentication(string Name , string Passwd) {

    vector <sUser> vUsers = LoadUsersDataFromFile(UsersFile);
    if (FindUserByNameAndPasswd(Name ,Passwd,vUsers , CurrentUser))
        return true;
    else
        return false;
}
bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

bool FindUserByName(string Name, vector <sUser> vUsers, sUser& User)
{

    for (sUser u : vUsers)
    {

        if (u.Name == Name)
        {
            User= u;
            return true;
        }

    }
    return false;

}

bool FindUserPByName(string Name, vector <sPermission> vPs)
{

    for (sPermission p : vPs)
    {

        if (p.name == Name)
        {
            return true;
        }

    }
    return false;

}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}
sUser ChangeUserRecord(string Name)
{
    sUser User;
    char L;

   User.Name = Name;

    cout << "Enter Password? ";
    cin >> User.Passwd;

    cout << "Do You Want To Give Full Access? ";
    cin >> L ;

    User.Permission = ReadPerimssion(User.Name,L);

    return User;

}




bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

bool MarkUserForDeleteByName(string Name, vector <sUser>& vUsers)
{

    for (sUser& U : vUsers)
    {
        if (U.Name == Name)
        {
            U.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

bool MarkUserPForDeleteByName(string Name, vector <sPermission>& vPs)
{

    for (sPermission& p : vPs)
    {
        if (p.name == Name)
        {
            p.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }
        }

        MyFile.close();

    }

    return vClients;

}

vector <sUser> SaveUsersDataToFile(string FileName, vector <sUser> vUsers)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sUser U : vUsers)
        {

            if (U.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLineForUser(U);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vUsers;

}

vector <sPermission> SaveUsersPDataToFile(string FileName, vector <sPermission> vPs)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sPermission p : vPs)
        {

            if (!p.MarkForDelete)
            {
                //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLineP(p);
                MyFile << DataLine << endl;

            }
        }
        MyFile.close();
    }

    return vPs;

}
void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewUsersP(sPermission P)
{
    AddDataLineToFile(UsersPermission, ConvertRecordToLineP(P));
}

void AddNewUser()
{
    sUser User;
    User = ReadNewUser();
    AddDataLineToFile(UsersFile, ConvertRecordToLineForUser(User));

}


void AddNewClients()
{
    char AddMore = 'Y';
    do
    {

        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

void AddNewUserP(sPermission P)
{
    AddDataLineToFile(UsersPermission, ConvertRecordToLineP(P));
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {

        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

bool DeleteUserByName(string Name, vector <sUser>& vUsers)
{

    sUser User;
    char Answer = 'n';

    if (Name == "admin") {
        cout << "You Can't Delete Admin! " << endl;
        return false;
    }

    if (FindUserByName(Name, vUsers, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByName(Name, vUsers);
            SaveUsersDataToFile(UsersFile, vUsers);

            //Refresh Clients
            vUsers = LoadUsersDataFromFile(UsersFile);

            cout << "\n\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Name (" << Name << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}


void DeleteUserP(string Name)
{
    vector <sPermission> vPs = LoadUsersPDataFromFile(UsersPermission);

    if (FindUserPByName(Name,vPs)) {
        MarkUserPForDeleteByName(Name, vPs);
        SaveUsersPDataToFile(UsersPermission, vPs);
        vPs = LoadUsersPDataFromFile(UsersPermission);
    }


}

bool UpdateUserByName(string Name, vector <sUser>& vUsers)
{

    sUser User;
    char Answer = 'n';

    if (Name == "admin") {
        cout << "This is Admin You Can't Update This User" << endl;
        return false;
    }

    if (FindUserByName(Name, vUsers, User))
    {

        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sUser& C : vUsers)
            {
                if (C.Name == Name)
                {
                    DeleteUserP(Name);
                    C = ChangeUserRecord(Name);
                    break;
                }

            }

            SaveUsersDataToFile(UsersFile, vUsers);
            cout << "\n\nUser Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << Name << ") is Not Found!";
        return false;
    }

}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{


    char Answer = 'n';


    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }


        return false;
    }

}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

string ReadUserName()
{
    string Name = "";

    cout << "\nPlease enter Name? ";
    cin >> Name;
    return Name;

}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients );

}
void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUsers = LoadUsersDataFromFile(UsersFile);
    string Name = ReadUserName();
    DeleteUserByName(Name, vUsers);

}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUsers = LoadUsersDataFromFile(UsersFile);
    string Name = ReadUserName();
    UpdateUserByName(Name, vUsers);

}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();

}


    //AddNewUserP();



void ShowAddNewUsersScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Users Screen";
    cout << "\n-----------------------------------\n";

    AddNewUser();

}


void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUsers = LoadUsersDataFromFile(UsersFile);
    sUser User;
    string Name = ReadUserName();
    if (FindUserByName(Name, vUsers, User))
        PrintUserCard(User);
    else
        cout << "\nUser with Name [" << Name << "] is not found!";

}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";

}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }


    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();

}

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };

enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
                          eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
                          eManageUsers = 7 , eLogout = 8 };

enum enManageUsersOptions { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
                           eUpdateUser = 4, eFindUser   = 5 , eShowMainMenuE = 6};
void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    cin.ignore();
    cin.get();
    ShowMainMenue();

}
void GoBackToManageUserMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    cin.ignore();
    cin.get();
    ShowManageUsersMenue();
}


void GoBackToMainMenueP(string name)
{
    cout << "\n\nPress any key to go back to Main Menue...";
    cin.ignore();
    cin.get();
    ShowMainMenueGetAccess(name);
}
void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    cin.ignore();
    cin.get();
    ShowTransactionsMenue();

}
short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
    system("clear");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
    system("clear");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
    system("clear");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {

        ShowMainMenue();

    }
    }

}


void PerfromTranactionsMenueOptionGetAccess(enTransactionsMenueOptions TransactionMenueOption , string name)
{
    switch (TransactionMenueOption)
    {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("clear");
            ShowDepositScreen();
            GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            system("clear");
            ShowWithDrawScreen();
            GoBackToTransactionsMenue();
            break;
        }


        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            system("clear");
            ShowTotalBalancesScreen();
            GoBackToTransactionsMenue();
            break;
        }


        case enTransactionsMenueOptions::eShowMainMenue:
        {

            ShowMainMenueGetAccess(name);
(name);

        }
    }

}

void ShowTransactionsMenue()
{
    system("clear");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}
void ShowTransactionsMenueGetAccess(string name)
{
    system("clear");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOptionGetAccess((enTransactionsMenueOptions)ReadTransactionsMenueOption(),name);
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
short ReadManageUserOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
    system("clear");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
    system("clear");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
    system("clear");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
    system("clear");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
    system("clear");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
    system("clear");
        ShowTransactionsMenue();
        break;

    case enMainMenueOptions::eManageUsers:
        system("clear");
        ShowManageUsersMenue();
        break;
    case enMainMenueOptions::eLogout:
            Login();
        break;
    }

}

bool FindUserByNamePTwo(string Name , short Number, vector <sPermission> vPs)
{

    for (sPermission p : vPs)
    {

        if (p.name == Name && p.Two == Number )
        {
            return true;
        }

    }
    return false;
}

bool FindUserByNamePThree(string Name , short Number, vector <sPermission> vPs)
{

    for (sPermission p : vPs)
    {

        if (p.name == Name && p.Three == Number )
        {
            return true;
        }

    }
    return false;
}
bool FindUserByNamePFour(string Name , short Number, vector <sPermission> vPs)
{

    for (sPermission p : vPs)
    {

        if (p.name == Name && p.Four == Number )
        {
            return true;
        }

    }
    return false;
}
bool FindUserByNamePFive(string Name , short Number, vector <sPermission> vPs)
{

    for (sPermission p : vPs)
    {

        if (p.name == Name && p.Five == Number )
        {
            return true;
        }

    }
    return false;
}
bool FindUserByNamePSix(string Name , short Number, vector <sPermission> vPs)
{

    for (sPermission p : vPs)
    {

        if (p.name == Name && p.Six == Number )
        {
            return true;
        }

    }
    return false;
}
bool FindUserByNamePSeven(string Name , short Number, vector <sPermission> vPs)
{

    for (sPermission p : vPs)
    {

        if (p.name == Name && p.Seven == Number )
        {
            return true;
        }
    }
    return false;
}

void ListClients(string Name) {

    vector <sPermission> vPs = LoadUsersPDataFromFile(UsersPermission);
    bool SL = FindUserByNamePOne(Name , 2 , vPs);
    if (SL) {
        ShowAllClientsScreen();
    }
    else {
        cout << "-----------------------------------------\n";
        cout << "Access Denied," << endl;
        cout << "You Don't Have Perimission To Do This," << endl;
        cout << "Please Concat Your Admin." << endl;
        cout << "-----------------------------------------\n";
    }
}

void AddNewClientAccess(string Name ) {
    vector <sPermission> vPs = LoadUsersPDataFromFile(UsersPermission);
    if (FindUserByNamePTwo(Name , 4 , vPs)) {
        ShowAddNewClientsScreen();
    }
    else {
        cout << "-----------------------------------------\n";
        cout << "Access Denied," << endl;
        cout << "You Don't Have Perimission To Do This," << endl;
        cout << "Please Concat Your Admin." << endl;
        cout << "-----------------------------------------\n";
    }
}

void DeleteClient(string Name) {

    vector <sPermission> vPs = LoadUsersPDataFromFile(UsersPermission);
    if (FindUserByNamePThree(Name , 8 , vPs)) {
        ShowDeleteClientScreen();
    }
    else {
        cout << "-----------------------------------------\n";
        cout << "Access Denied," << endl;
        cout << "You Don't Have Perimission To Do This," << endl;
        cout << "Please Concat Your Admin." << endl;
        cout << "-----------------------------------------\n";
    }
}
void UpdateClient(string Name ) {
    vector <sPermission> vPs = LoadUsersPDataFromFile(UsersPermission);
    if (FindUserByNamePFour(Name , 16 , vPs)) {
        ShowUpdateClientScreen();
    }
    else {
        cout << "-----------------------------------------\n";
        cout << "Access Denied," << endl;
        cout << "You Don't Have Perimission To Do This," << endl;
        cout << "Please Concat Your Admin." << endl;
        cout << "-----------------------------------------\n";
    }
}


void FindClient(string Name) {
    vector <sPermission> vPs = LoadUsersPDataFromFile(UsersPermission);
    if (FindUserByNamePFive(Name , 32 , vPs)) {
        ShowFindClientScreen();
    }
    else {
        cout << "-----------------------------------------\n";
        cout << "Access Denied," << endl;
        cout << "You Don't Have Perimission To Do This," << endl;
        cout << "Please Concat Your Admin." << endl;
        cout << "-----------------------------------------\n";
    }
}
void TransactionsMenue(string Name ) {
    vector <sPermission> vPs = LoadUsersPDataFromFile(UsersPermission);
    if (FindUserByNamePSix(Name , 64 , vPs)) {
        ShowTransactionsMenueGetAccess(Name);
    }
    else {
        cout << "-----------------------------------------\n";
        cout << "Access Denied," << endl;
        cout << "You Don't Have Perimission To Do This," << endl;
        cout << "Please Concat Your Admin." << endl;
        cout << "-----------------------------------------\n";
        GoBackToMainMenueP(Name);
    }
}
void ManageUsers(string Name) {
    vector <sPermission> vPs = LoadUsersPDataFromFile(UsersPermission);
    if (FindUserByNamePSeven(Name , 128 , vPs)){
        ShowManageUsersMenueGetAccess(Name);
    }
    else {
        cout << "-----------------------------------------\n";
        cout << "Access Denied," << endl;
        cout << "You Don't Have Perimission To Do This," << endl;
        cout << "Please Concat Your Admin." << endl;
        cout << "-----------------------------------------\n";
        GoBackToMainMenueP(Name);

    }
}
void GetAccess(enMainMenueOptions MainMenueOption,string name)
{
    switch (MainMenueOption)
    {
        case enMainMenueOptions::eListClients:
        {
            system("clear");
            ListClients(name);
            GoBackToMainMenueP(name);
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("clear");
            AddNewClientAccess(name);
            GoBackToMainMenueP(name);
            break;
        case enMainMenueOptions::eDeleteClient:
            system("clear");
            DeleteClient(name);
            GoBackToMainMenueP(name);
            break;

        case enMainMenueOptions::eUpdateClient:
            system("clear");
            UpdateClient(name);
            GoBackToMainMenueP(name);
            break;

        case enMainMenueOptions::eFindClient:
            system("clear");
            FindClient(name);
            GoBackToMainMenueP(name);
            break;
        case enMainMenueOptions::eShowTransactionsMenue:
            system("clear");
            TransactionsMenue(name);
            break;
        case enMainMenueOptions::eManageUsers:
            system("clear");
            ManageUsers(name);

            break;
        case enMainMenueOptions::eLogout:
            Login();
            break;
    }

}


void PerfromManageUserOption(enManageUsersOptions ManageUsersOptions)
{
    switch (ManageUsersOptions)
    {
        case enManageUsersOptions::eListUsers:
        {
            system("clear");
            ShowAllUsersScreen();
            GoBackToManageUserMenue();
            break;
        }
        case enManageUsersOptions::eAddNewUser:
            system("clear");
            ShowAddNewUsersScreen();
            GoBackToManageUserMenue();
            break;

        case enManageUsersOptions::eDeleteUser:
            system("clear");
            ShowDeleteUserScreen();
            GoBackToManageUserMenue();
            break;

        case enManageUsersOptions::eUpdateUser:
            system("clear");
            ShowUpdateUserScreen();
            GoBackToManageUserMenue();
            break;

        case enManageUsersOptions::eFindUser:
            system("clear");
            ShowFindUserScreen();
            GoBackToManageUserMenue();
            break;
        case enManageUsersOptions::eShowMainMenuE:
            system("clear");
            ShowMainMenue();
            break;
    }

}

void PerfromManageUserOptionGetAccess(enManageUsersOptions ManageUsersOptions,string name)
{
    switch (ManageUsersOptions)
    {
        case enManageUsersOptions::eListUsers:
        {
            system("clear");
            ShowAllUsersScreen();
            GoBackToManageUserMenue();
            break;
        }
        case enManageUsersOptions::eAddNewUser:
            system("clear");
            ShowAddNewUsersScreen();
            GoBackToManageUserMenue();
            break;

        case enManageUsersOptions::eDeleteUser:
            system("clear");
            ShowDeleteUserScreen();
            GoBackToManageUserMenue();
            break;

        case enManageUsersOptions::eUpdateUser:
            system("clear");
            ShowUpdateUserScreen();
            GoBackToManageUserMenue();
            break;

        case enManageUsersOptions::eFindUser:
            system("clear");
            ShowFindUserScreen();
            GoBackToManageUserMenue();
            break;
        case enManageUsersOptions::eShowMainMenuE:
            system("clear");
            ShowMainMenue();
            break;
    }

}
void ShowManageUsersMenue()
{
    system("clear");
    cout << "======================================\n";
    cout << "\tManage Users Screen\n";
    cout << "======================================\n";
    cout << "\t[1] Show User List.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User Info.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue Screen.\n";
    cout << "===========================================\n";
    PerfromManageUserOption((enManageUsersOptions)ReadManageUserOption());
}

void ShowManageUsersMenueGetAccess(string name)
{
    system("clear");
    cout << "======================================\n";
    cout << "\tManage Users Screen\n";
    cout << "======================================\n";
    cout << "\t[1] Show User List.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User Info.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue Screen.\n";
    cout << "===========================================\n";
    PerfromManageUserOptionGetAccess((enManageUsersOptions)ReadManageUserOption(),name);
}
void ShowMainMenue()
{
    system("clear");
    cout << "======================================\n";
    cout << "\tMain Menue Screen\n";
    cout << "======================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

void ShowMainMenueGetAccess(string name)
{
    system("clear");
    cout << "======================================\n";
    cout << "\tMain Menue Screen\n";
    cout << "======================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";

    GetAccess((enMainMenueOptions)ReadMainMenueOption(),name);
}

void MenueScreen(string Name , string Passwd) {
    if (GetPerimission(Name ,Passwd) == -1) {
        ShowMainMenue();
    }
    else {
        ShowMainMenueGetAccess(Name);
    }
}
void Login() {

    bool FiledLogin = false;
    string Name ,  Passwd;

    do
    {
        system("clear");

        cout << "-----------------------------" << endl;
        cout << "\tLogin Screen" << endl;
        cout << "-----------------------------" << endl;

        if(FiledLogin)
            cout << "Login Filed Try Again." << endl;

        cout << "Enter Name? ";
        cin >> Name ;
        cout << "Enter Password? ";
        cin >> Passwd;

        FiledLogin = !SuccessfulAuthentication(Name , Passwd);
    }while (FiledLogin);

    MenueScreen( Name ,Passwd) ;
}
int main()

{
    Login();
    cin.ignore();
    cin.get();
    return 0;
}