#include "Bank.h"

// MORIA HAMAMI
// 315464347

Bank::Bank()
{
    m_name = nullptr;
    m_account = nullptr;
    m_numbeOfAccounts = 0;
    SetTotal(0);
    SetCode(0);
}

Bank::Bank(const char *name, int code)
{
    m_account = nullptr;
    m_numbeOfAccounts = 0;
    SetTotal(0);
    SetBankName(name);
    SetCode(code);
}

Bank::~Bank()
{
    for (int i = 0; i < m_numbeOfAccounts; i++)
    {
        delete m_account[i];
    }
    delete[] m_account;
    delete[] m_name;
}

void Bank::SetBankName(const char *name)
{
    int len = strlen(name);
    m_name = new char[len + 1];
    strcpy(m_name, name);
}

void Bank::SetAccount(Account **account, int numbeOfAccounts)
{
    if (m_numbeOfAccounts > 0)
    {
        // Delete existing account
        for (int i = 0; i < m_numbeOfAccounts; i++)
        {
            delete m_account[i];
        }
        delete[] m_account;
    }
    // Allocate and set new account
    m_account = new Account *[numbeOfAccounts];
    for (int i = 0; i < numbeOfAccounts; i++)
    {
        m_account[i] = new Account(*account[i]);
    }

    m_numbeOfAccounts = numbeOfAccounts;
}

void Bank::SetTotal(double total)
{
    m_totalBalance = total;
}

void Bank::SetCode(int code)
{
    m_bankCode = code;
}

const char *Bank::GetBankName() const
{
    return m_name;
}

Account **Bank::GetAccounts() const
{
    return m_account;
}

int Bank::GetNumberOfAccounts() const
{
    return m_numbeOfAccounts;
}

double Bank::GetTotal() const
{
    return m_totalBalance;
}

int Bank::GetCode() const
{
    return m_bankCode;
}

void Bank::AddAccount(const Account &account)
{
    // Check if the account already exists
    bool exists = false;
    for (int i = 0; i < m_numbeOfAccounts; i++)
    {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
        {
            exists = true;
            break;
        }
    }
    if (exists)
        return;

    // Allocate a larger space, and add old + new account
    Account **tmp = new Account *[m_numbeOfAccounts + 1];
    for (int i = 0; i < m_numbeOfAccounts; i++)
    {
        tmp[i] = new Account(*m_account[i]);
        delete m_account[i];
    }
    tmp[m_numbeOfAccounts] = new Account(account); 
    delete[] m_account;
    m_account = tmp;

    m_numbeOfAccounts++;
    m_totalBalance += account.GetBalance();
}


void Bank::AddAccount(const Person &per, double amount)
{
    Account *newA = new Account(per, amount);
    AddAccount(*newA);
    delete newA;
}

void Bank::AddPerson(const Person &newPerson, const Account &account, double amount)
{
    bool exists = false;
    AddAccount(account);
    for (int i = 0; i < m_numbeOfAccounts; i++)
    {
        // Look for the account
        if (account.GetAccountNumber() == m_account[i]->GetAccountNumber())
        {
            for (int j = 0; j < m_account[i]->GetTotalPersons(); j++)
            {
                if (newPerson.GetId() == m_account[i]->GetPersons()[j]->GetId())
                    // Person in the account
                    exists = true;
            }
            // Person not in the account
            if (!exists)
            {
                m_account[i]->AddPerson(newPerson, amount);
            }
        }
    }
}

void Bank::DeleteAccount(const Account &account)
{
    bool exists = false;
    for (int i = 0; i < m_numbeOfAccounts; i++)
    {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
            // Account is in the bank 
            exists = true; 
    }

        // Account isn't in the bank 
    if (!exists)
        return; 

    // Delete account 
    Account **tmp = new Account *[m_numbeOfAccounts - 1];
    int i, j;
    for (i = 0, j = 0; i < m_numbeOfAccounts; i++)
    {
        if (m_account[i]->GetAccountNumber() != account.GetAccountNumber())
        {
            tmp[j] = new Account(*m_account[i]);
            j++;
        }
    }
    delete[] m_account;
    m_account = tmp;
    tmp = nullptr;
    m_numbeOfAccounts--;
}

void Bank::DeletePerson(const Person &p)
{
    int i;
    for (i = 0; i < m_numbeOfAccounts; i++)
    {
        m_account[i]->DeletePerson(p);
        if (m_account[i]->GetTotalPersons() == 0)
        {
            DeleteAccount(*m_account[i]);
        }
    }
}
