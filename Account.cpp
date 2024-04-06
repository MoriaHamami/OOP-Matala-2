#include "Account.h"

// Might be WRONG putting a null pointer to initialize
Account::Account() : m_transactionList(nullptr), m_persons(nullptr)
{
    m_numberOfTransaction = 0;
    m_totalPersons = 0;
    m_accountNumber = 0;
    m_balance = 0;
    // WRONG ? Do I need this?
    //    m_persons = new Person*[];
}

Account::Account(Person **persons, int count, double balance)
{
    SetBalance(balance);
    // WRONG ? Did I need to initialize persons here?
    // m_persons = new Person *[count];
    SetPersons(persons, count);
}

Account::Account(const Person &person, double balance)
{
    SetBalance(balance);
    m_persons = new Person *[1];
    // WRONG ? Send a pointer or value maybe?
    m_persons[0] = new Person(person);
    m_totalPersons = 1;
}

Account::Account(const Account &other)
{
    m_numberOfTransaction = other.m_numberOfTransaction;
    m_totalPersons = other.m_totalPersons;
    m_accountNumber = other.m_accountNumber;
    m_balance = other.m_balance;
    
    m_transactionList = new Transaction *[m_numberOfTransaction];
    for (int i = 0; i < m_numberOfTransaction; i++)
    {
        m_transactionList[i] = new Transaction(*(other.m_transactionList[i]));
    }
    
    m_persons = new Person *[m_totalPersons];
    for (int i = 0; i < m_totalPersons; i++)
    {
        m_persons[i] = new Person(*(other.m_persons[i]));
    }
}

Account::~Account()
{
    for (int i = 0; i < m_totalPersons; i++) delete m_persons[i];
    for (int i = 0; i < m_numberOfTransaction; i++) delete m_transactionList[i];
    delete[] m_transactionList;
    delete[] m_persons;
}

// WRONG ? Did I need to initialize person?
void Account::SetPersons(Person **persons, int count)
{
    if(m_persons){
        // TODO Delete persons
    }
   m_persons = new Person*[count + 1];
    for (int i = 0; i < count; i++)
    {
        m_persons[i] = persons[i];
    }
    m_totalPersons = count;
}
void Account::SetAccountNumber(int number)
{
}
void Account::SetBalance(double balance)
{
}
void Account::SetTransactions(Transaction **newTransaction, int count)
{
}
Transaction **Account::GetTransactions()
{
}
int Account::GetNumOfTransactions()
{
}
Person **Account::GetPersons() const
{
}
int Account::GetTotalPersons() const
{
}
int Account::GetAccountNumber() const
{
}
double Account::GetBalance() const
{
}

void Account::Withdraw(double amount, const char *date)
{
}
void Account::Deposit(double amount, const char *date)
{
}
void Account::AddPerson(const Person &newPerson, double amount)
{
}
void Account::DeletePerson(const Person &oldPerson)
{
}
void Account::AddTransaction(const Transaction &newTransaction)
{
}

void Account::clearTransactions()
{
}
void Account::clearPersons()
{
}