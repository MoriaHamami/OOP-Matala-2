#include "Bank.h"

Bank::Bank()
{
    SetTotal(0);
    m_name = nullptr;
    // TODO: MAKE A UNIQUE CODE
    SetCode(0);
    m_account = nullptr;
    m_numbeOfAccounts = 0;
}
Bank::Bank(const char *name, int code)
{
    // CHANGED
    // m_name = nullptr;

    SetTotal(0);
    SetBankName(name);
    SetCode(code);
    m_account = nullptr;
    m_numbeOfAccounts = 0;
}
Bank::~Bank()
{
    for (int i = 0; i < m_numbeOfAccounts; i++)
    {
        delete m_account[i];
    }
    delete[] m_account;
    delete[] m_name;

    // if (m_name != nullptr) {
    //     delete[] m_name;
    //     m_name = nullptr;
    // }

    // CHANGED
    // WRONG ? Did I need to check if it is null first?
    // if (m_account != nullptr)
    // {
    // CHANGED2
    // if (m_name)
    //     delete m_name;
    // for (int i = 0; i < m_numbeOfAccounts; i++)
    // {
    //     delete m_account[i];
    // }
    // delete[] m_account;

    // CHANGED
    // m_numbeOfAccounts = 0;
    // m_account = nullptr;
}

void Bank::SetBankName(const char *name)
{
    // CHANGED
    // if (m_name != nullptr)
    //     delete[] m_name;

    int len = strlen(name);
    m_name = new char[len + 1];
    strcpy(m_name, name);
}
void Bank::SetAccount(Account **account, int numbeOfAccounts)
{
    // CHANGED
    // if (m_account)
    // {
    //     // WRONG ? Deep delete?
    //     delete[] m_account;
    // }
    // m_account = new Account *[numbeOfAccounts];
    // for (int i = 0; i < numbeOfAccounts; i++)
    // {
    //     m_account[i] = account[i];
    // }

    // WRONG ? Was I supposed to delete account if there was one?
    if (m_numbeOfAccounts > 0)
    {
        // Account arr member isn't empty -> CLEAR THE ARRAY
        for (int i = 0; i < m_numbeOfAccounts; i++)
        {
            delete m_account[i];
        }
        delete[] m_account;
    }
    m_account = new Account *[numbeOfAccounts];
    int i;
    for (i = 0; i < numbeOfAccounts; i++)
    {
        m_account[i] = new Account(*account[i]);
    }

    m_numbeOfAccounts = numbeOfAccounts;
    // CHANGED 2
    // m_account = account;
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

    // Account isn't in the bank -> Add the account
    Account **tmp = new Account *[m_numbeOfAccounts + 1];
    for (int i = 0; i < m_numbeOfAccounts; i++)
    {
        tmp[i] = new Account(*m_account[i]);
        delete m_account[i];
    }
    tmp[m_numbeOfAccounts] = new Account(account); // Add the new account to the arr
    delete[] m_account;
    m_account = tmp;
    m_numbeOfAccounts++;
    m_totalBalance += account.GetBalance();

    // CHANGED 2
    // if (m_account == nullptr)
    //     m_account = new Account *[m_numbeOfAccounts];
    // m_account[m_numbeOfAccounts++] = new Account(account);
    // m_totalBalance += account.GetBalance();

    // CHANGED
    // Account **temp = new Account *[m_numbeOfAccounts + 1];
    // for (int i = 0; i < m_numbeOfAccounts; i++)
    // {
    //     temp[i] = m_account[i];
    // }
    // temp[m_numbeOfAccounts] = new Account(account);
    // m_numbeOfAccounts++;
    // if (m_account)
    // {
    //     delete[] m_account;
    // }
    // m_account = temp;

    // m_totalBalance = +account.GetBalance();
}

// void Bank::AddAccount(const Person &per, double amount)
// {
// }
// void Bank::AddPerson(const Person &newPerson, const Account &account, double amount)
// {
// }
// void Bank::DeleteAccount(const Account &account)
// {
// }
// void Bank::DeletePerson(const Person &p)
// {
// }

void Bank::AddAccount(const Person& per, double amount) {
	Account* newA = new Account(per, amount);
	AddAccount(*newA);
	delete newA;
}
void Bank::AddPerson(const Person& newPerson, const Account& account, double amount) {
	int flag = 1;
	AddAccount(account);
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		if (account.GetAccountNumber() == m_account[i]->GetAccountNumber()) {
			// Found the account
			for (int j = 0; j < m_account[i]->GetTotalPersons(); j++) {
				if (newPerson.GetId() == m_account[i]->GetPersons()[j]->GetId())
					flag = 0; // Person in the account
			}
			if (flag) {
				// Person not in the account -> ADD THE PERSON
				m_account[i]->AddPerson(newPerson, amount);
			}
		}
	}
}
void Bank::DeleteAccount(const Account& account) {
	int flag = 0;
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
			flag = 1; // Account exist in the bank -> Delete the account
	}

	if (!flag) return; // Account isn't in the bank -> DO NOTHING

	// Delete the account from the bank
	Account** tmp = new Account * [m_numbeOfAccounts - 1];
	int i, j;
	for (i = 0, j = 0; i < m_numbeOfAccounts; i++) {
		if (m_account[i]->GetAccountNumber() != account.GetAccountNumber()) {
			tmp[j] = new Account(*m_account[i]);
			j++;
		}
	}
	delete[] m_account;
	m_account = tmp;
	tmp = nullptr;
	m_numbeOfAccounts--;
}
void Bank::DeletePerson(const Person& p) {
	int i;
	for (i = 0; i < m_numbeOfAccounts; i++) {
		m_account[i]->DeletePerson(p);
		if (m_account[i]->GetTotalPersons() == 0) {
			DeleteAccount(*m_account[i]);
		}
	}
}

// char*		m_name;
// Account**	m_account;
// int			m_bankCode;
// int			m_numbeOfAccounts;
// double		m_totalBalance;