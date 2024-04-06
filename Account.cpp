#include "Account.h"

// Might be WRONG putting a null pointer to initialize
Account::Account() : m_transactionList(nullptr), m_persons(nullptr)
{
    SetBalance(0);
    // m_balance = 0;
    // TODO - Change account number to a unique one
    SetAccountNumber(0);
    // m_accountNumber = 0;
    m_numberOfTransaction = 0;
    m_totalPersons = 0;

    // WRONG ? Do I need this?
    // m_persons = new Person*[0];
    // m_transactionList = new Transaction*[0];
}

// Might be WRONG putting a null pointer to initialize
Account::Account(Person **persons, int count, double balance): m_transactionList(nullptr)
{
    // TODO - Change account number to a unique one
    SetAccountNumber(balance);
    m_numberOfTransaction = 0;
    SetBalance(balance);
    // WRONG ? Did I need to initialize persons here?
    // m_persons = new Person *[count];
    SetPersons(persons, count);
}

// Might be WRONG putting a null pointer to initialize
Account::Account(const Person &person, double balance): m_transactionList(nullptr)
{
    // TODO - Change account number to a unique one
    SetAccountNumber(balance);
    SetBalance(balance);
    m_persons = new Person *[1];

    // WRONG ? Send a pointer or value maybe?
    m_persons[0] = new Person(person);
    m_totalPersons = 1;
    // WRONG ? Should I send person to setpersons func?
    // SetPersons([person], 1);
}

// Might be WRONG putting a null pointer to initialize
Account::Account(const Account &other): m_transactionList(nullptr)
{
    m_numberOfTransaction = other.m_numberOfTransaction;
    m_totalPersons = other.m_totalPersons;
    SetAccountNumber(other.m_accountNumber);
    // m_accountNumber = other.m_accountNumber;
    SetBalance(other.m_balance);
    // m_balance = other.m_balance;
    // WRONG? Did I need to do this:
    // Account(other.m_persons, other.m_totalPersons, other.m_balance);

    SetTransactions(other.m_transactionList, other.m_numberOfTransaction);

    SetPersons(other.m_persons, other.m_totalPersons);
    // m_persons = new Person *[m_totalPersons];
    // for (int i = 0; i < m_totalPersons; i++)
    // {
    //     m_persons[i] = new Person(*(other.m_persons[i]));
    // }
}

Account::~Account()
{
    clearTransactions();
    clearPersons();
}

// WRONG ? Did I need to initialize person?
void Account::SetPersons(Person **persons, int count)
{
    if (m_persons)
    {
        // WRONG ? Deep delete?
        delete[] m_persons;
    }
    // WRONG ? Is it plus 1?
    // m_persons = new Person*[count + 1];
    m_persons = new Person *[count];
    for (int i = 0; i < count; i++)
    {
        m_persons[i] = persons[i];
        // WRONG? Should I do:
        // m_persons[i] = new Person(persons[i]);
        // I think because I didnt recieve const / ref 
        // for ex const Person &newPerson
        // I didnt need to create a new one
    }
    m_totalPersons = count;
}
void Account::SetAccountNumber(int number)
{
    m_accountNumber = number;
}
void Account::SetBalance(double balance)
{
    m_balance = balance;
}
void Account::SetTransactions(Transaction **newTransaction, int count)
{
    if (m_transactionList)
    {
        // WRONG ? Deep delete?
        delete[] m_transactionList;
    }
    m_transactionList = new Transaction *[count];
    for (int i = 0; i < count; i++)
    {
        m_transactionList[i] = new Transaction(*(newTransaction[i]));
    }
    m_numberOfTransaction = count;
}
Transaction **Account::GetTransactions()
{
    return m_transactionList;
}
int Account::GetNumOfTransactions()
{
    return m_numberOfTransaction;
}
Person **Account::GetPersons() const
{
    return m_persons;
}
int Account::GetTotalPersons() const
{
    return m_totalPersons;
}
int Account::GetAccountNumber() const
{
    return m_accountNumber;
}
double Account::GetBalance() const
{
    return m_balance;
}

void Account::Withdraw(double amount, const char *date)
{
    // Account *s, Account *d, double amount, const char *date
    Transaction *newTransaction = new Transaction(this, this, amount, date);
    m_balance =-amount;
    AddTransaction(*newTransaction);
}
void Account::Deposit(double amount, const char *date)
{
    Transaction *newTransaction = new Transaction(this, this, amount, date);
    m_balance =+amount;
    AddTransaction(*newTransaction);
}
void Account::AddPerson(const Person &newPerson, double amount)
{
    double newBalance = m_balance + amount;
    SetBalance(newBalance);

    Person** temp = new Person * [m_totalPersons + 1];
	for (int i = 0; i < m_totalPersons; i++)
	{
		temp[i] = m_persons[i];
	}
	// temp[m_totalPersons] = newPerson;
	temp[m_totalPersons] = new Person(newPerson);
	m_totalPersons++;
	if (m_persons)
	{
		delete[] m_persons;
	}
	m_persons = temp;
}
void Account::DeletePerson(const Person &oldPerson)
{
      for (int i = 0; i < m_totalPersons; i++) {
        if (m_persons[i]->GetId() == oldPerson.GetId()) {
            // WRONG? Will I delete the pointer I need one row after?
            m_persons[i] = m_persons[m_totalPersons-1];
            delete m_persons[m_totalPersons-1];
           
            // delete survivors[i];
            // for (int j = i; j < remainingSurvivors - 1; j++) {
            //     survivors[j] = survivors[j + 1];
            // }
           
            m_totalPersons--;
            break;
        }
    }
}
void Account::AddTransaction(const Transaction &newTransaction)
{
    Transaction** temp = new Transaction * [m_numberOfTransaction + 1];

	for (int i = 0; i < m_numberOfTransaction; i++)
	{
		temp[i] = m_transactionList[i];
	}
	temp[m_numberOfTransaction] = new Transaction(newTransaction);
	m_numberOfTransaction++;
	if (m_transactionList) delete[] m_transactionList;
	
	m_transactionList = temp;
}

void Account::clearTransactions()
{
    for (int i = 0; i < m_numberOfTransaction; i++)
        delete m_transactionList[i];
    delete[] m_transactionList;
    m_numberOfTransaction = 0;
}
void Account::clearPersons()
{
    for (int i = 0; i < m_totalPersons; i++)
        delete m_persons[i];
    delete[] m_persons;
    m_persons = 0;
}