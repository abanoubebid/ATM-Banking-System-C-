#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


enum enATMMainMenueOption { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalances = 4 , eLogout = 5 };


const string ClientsFileName = "Client.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

 sClient CurrentUser;


void GoBackToATMMainMenue();
void ShowATMMainMenue();
void Login();



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

    if (vClientData.size() < 5)
        return Client;

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

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

void ShowTotalBalances()
{
    double TotalBalances = 0 ;

    sClient Client  = CurrentUser;

    TotalBalances = Client.AccountBalance;
    cout << "Your Balances is = " << TotalBalances;

}

bool FindClientByAccountNumberAndPinCode(string AccountNumber,string PinCode, vector <sClient>& vClients, sClient& Client) {

    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }

    }
    return false;
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

void SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient& C : vClients)
        {
            if (!C.MarkForDelete)
                MyFile << ConvertRecordToLine(C) << endl;
        }


        MyFile.close();

    }
}



void DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount)
{
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    char Answer = 'n';
    cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                CurrentUser = C; // تحديث الحالي
                break;
            }
        }

        SaveCleintsDataToFile(ClientsFileName, vClients);

        cout << "\n\nDone Successfully. New balance is: " << CurrentUser.AccountBalance;
    }
}


void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client = CurrentUser;

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(Client.AccountNumber, Amount);

}
void ShowMainMenueQuickWithDrawScreen() {

    cout << "[1] 20  \t\t [2] 50  " << endl;
    cout << "[3] 100 \t\t [4] 200 " << endl;
    cout << "[5] 400 \t\t [6] 600 " << endl;
    cout << "[7] 800 \t\t [8] 1000" << endl;
    cout << "[9] Exit" << endl;
    cout << "-----------------------------------\n";

    ShowTotalBalances();

}

int Choose_Number(int Choose_Number) {

    int Amount = 0;

    if      (Choose_Number == 1) Amount = 20;
    else if (Choose_Number == 2) Amount = 50;
    else if (Choose_Number == 3) Amount = 100;
    else if (Choose_Number == 4) Amount = 200;
    else if (Choose_Number == 5) Amount = 400;
    else if (Choose_Number == 6) Amount = 600;
    else if (Choose_Number == 7) Amount = 800;
    else if (Choose_Number == 8) Amount = 1000;

  return Amount;
}
void withdrawAmount(int ChooseNumber) {


    int Amount = 0;

    if (ChooseNumber == 9)
         GoBackToATMMainMenue();

   Amount = Choose_Number(ChooseNumber);

    while (Amount > CurrentUser.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentUser.AccountBalance << endl;
        cout << "Choose What to Withdraw from [1] to [9]? ";
        cin >> ChooseNumber;

        if (ChooseNumber == 9)
            GoBackToATMMainMenue();

        Amount = Choose_Number(ChooseNumber);

    }

    DepositBalanceToClientByAccountNumber(CurrentUser.AccountNumber, Amount * -1 );
}
void ShowQuickWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tQuick Withdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    int  ChooseNumber = 0;

    ShowMainMenueQuickWithDrawScreen();

    do
        {
        if (ChooseNumber >= 10)
            cout << "\nPlease Choose Number from [1] to [9]! ";

        cout << "\nChoose What to Withdraw from [1] to [9]? ";
        cin >> ChooseNumber;

        }while (ChooseNumber >= 10);

    withdrawAmount(ChooseNumber);

}

void ShowNormalWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tNormal Withdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    Client = CurrentUser;


    int Amount = 0;

    do {
        cout << "\nPlease enter amount multiple of 5 's ? ";
        cin >> Amount;
    }while (!(Amount % 5 == 0));


    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }


    DepositBalanceToClientByAccountNumber(Client.AccountNumber, Amount * -1);

}

void ShowTotalBalancesScreen()
{

    cout << "=======================================\n";
    cout << "\t\tCheck Balances Screen" << endl;
    cout << "=======================================\n";

    ShowTotalBalances();

}


void GoBackToATMMainMenue()
{
    cout << "\n\nPress any key to go back to ATM Main Menue...";
    cin.ignore();
    cin.get();
    ShowATMMainMenue();

}



short ReadATMMainMenueOption()
{
    short Choice = 0;
    do {

        if (Choice >= 6)
            cout << "\n\nPlease Choose Number From [1 to 5]! ";

        cout << "\nChoose what do you want to do? [1 to 5]? ";
        cin >> Choice;

        } while (Choice >= 6);


    return Choice;
}



void PerfromATMMainMenueOption(enATMMainMenueOption ATMMainMenueOption)
{
    switch (ATMMainMenueOption)
    {
        case enATMMainMenueOption::eQuickWithdraw:
    {
            system("clear");
            ShowQuickWithDrawScreen();
            GoBackToATMMainMenue();
        break;
    }
        case enATMMainMenueOption::eNormalWithdraw:
    {
        system("clear");
        ShowNormalWithDrawScreen();
        GoBackToATMMainMenue();
        break;
    }

        case enATMMainMenueOption::eDeposit:
    {
            system("clear");
            ShowDepositScreen();
            GoBackToATMMainMenue();
        break;
    }

        case enATMMainMenueOption::eCheckBalances:
    {
            system("clear");
            ShowTotalBalancesScreen();
            GoBackToATMMainMenue();
        break;
    }

        case enATMMainMenueOption::eLogout:
        {

               Login();

        }
    }

}

void ShowATMMainMenue()
{


    system("clear");

    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balances.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    PerfromATMMainMenueOption((enATMMainMenueOption)ReadATMMainMenueOption());
}



bool  LoadUserInfo(string AccountNumber, string PinCode)
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode,vClients, CurrentUser))
        return true;
    else
        return false;

}

void Login()
{
    bool LoginFaild = false;

    string AccountNumber, PinCode;

    do
    {
        system("clear");

        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";


        if (LoginFaild)
            cout << "Invalid AccountNumber/PinCode!\n";

        cout << "Enter Account Number? ";
        getline(cin >> ws, AccountNumber);

        cout << "Enter PinCode? ";
        getline(cin, PinCode);

        LoginFaild = !LoadUserInfo(AccountNumber, PinCode);


    } while (LoginFaild);

    ShowATMMainMenue();
}


int main()

{
    Login();
    cin.ignore();
    cin.get();
    return 0;
}