#include "Account.h"

// MORIA HAMAMI
// 315464347

Account::Account() : m_transactionList(nullptr), m_persons(nullptr)
{
    m_numberOfTransaction = 0;
    m_totalPersons = 0;
    SetBalance(0);
    SetAccountNumber(0);
}

Account::Account(Person **persons, int count, double balance) : m_transactionList(nullptr)
{
    m_numberOfTransaction = 0;
    SetBalance(balance);
    SetPersons(persons, count);

    // Create a unique account number
    int id = 0;
    if (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            id += persons[i]->GetId();
        }
    }
    SetAccountNumber(id);
}

Account::Account(const Person &person, double balance) : m_transactionList(nullptr)
{
    m_numberOfTransaction = 0;
    SetAccountNumber(person.GetId());
    SetBalance(balance);

    m_persons = new Person *[1];
    m_persons[0] = new Person(person);
    m_totalPersons = 1;
}

Account::Account(const Account &other)
{
    SetAccountNumber(other.GetAccountNumber());
    SetBalance(other.GetBalance());

    if (other.m_transactionList)
    {
        SetTransactions(other.m_transactionList, other.m_numberOfTransaction);
    }
    else
    {
        m_transactionList = nullptr;
        m_numberOfTransaction = 0;
    }

    if (other.m_persons)
    {
        SetPersons(other.m_persons, other.m_totalPersons);
    }
    else
    {
        m_persons = nullptr;
        m_totalPersons = 0;
    }
}

Account::~Account()
{
    for (int i = 0; i < m_numberOfTransaction; i++)
    {
        delete[] m_transactionList[i]->GetDate();
    }
    clearPersons();
}

void Account::SetPersons(Person **persons, int count)
{
    m_persons = new Person *[count];
    for (int i = 0; i < count; i++)
    {
        m_persons[i] = new Person(*persons[i]);
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
    m_transactionList = new Transaction *[count];
    for (int i = 0; i < count; i++)
    {
        m_transactionList[i] = new Transaction(*newTransaction[i]);
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
    if (m_transactionList == nullptr)
        m_transactionList = new Transaction *[1];
    m_transactionList[m_numberOfTransaction++] = new Transaction(this, this, amount, date);
    m_balance -= amount;
}

void Account::Deposit(double amount, const char *date)
{
    if (m_transactionList == nullptr)
        m_transactionList = new Transaction *[1];
    m_transactionList[m_numberOfTransaction++] = new Transaction(this, this, amount, date);
    m_balance += amount;
}

void Account::AddPerson(const Person &newPerson, double amount)
{
    // Check if person already exists
    for (int i = 0; i < m_totalPersons; i++)
    {
        if (m_persons[i]->GetId() == newPerson.GetId())
            return;
    }

    Person **tmp = new Person *[m_totalPersons + 1];
    int i;
    for (i = 0; i < m_totalPersons; i++)
    {
        tmp[i] = new Person(*m_persons[i]);
    }
    tmp[i] = new Person(newPerson);
    clearPersons();
    m_persons = tmp;
    m_totalPersons++;

    double newBalance = m_balance + amount;
    SetBalance(newBalance);

    // Update unique account number
    int id = 0;
    for (int i = 0; i < m_totalPersons; i++)
    {
        id += m_persons[i]->GetId();
    }
    SetAccountNumber(id);
}

void Account::DeletePerson(const Person &oldPerson)
{
    if (m_persons == nullptr)
        return;

    // Check if person does'nt exist
    bool exists = false;
    int i = 0;
    for (; i < m_totalPersons; i++)
    {
        if (m_persons[i]->GetId() == oldPerson.GetId())
        {
            exists = true;
            break;
        }
    }
    if (!exists)
        return;

    delete m_persons[i];
    if (--m_totalPersons == 0)
    {
        // If this was the last person in account, delete persons array
        delete[] m_persons;
        m_persons = nullptr;
        return;
    }
    if (i != m_totalPersons)
    {
        // If this was not the last item in the array
        // Move following persons into the position of the index we removed
        for (; i < m_totalPersons; i++)
        {
            m_persons[i] = m_persons[i + 1];
        }
        // Remove the last person in the list
        delete m_persons[m_totalPersons];
        // Set the last item to the nullptr
        m_persons[m_totalPersons] = nullptr;
    }
}

void Account::AddTransaction(const Transaction &newTransaction)
{

    // Add the new transaction
    int i;
    Transaction **tmp = new Transaction *[newTransaction.GetSource()->GetNumOfTransactions() + 1];
    for (i = 0; i < newTransaction.GetSource()->GetNumOfTransactions(); i++)
    {
        tmp[i] = new Transaction(*newTransaction.GetSource()->GetTransactions()[i]);
    }
    tmp[i] = new Transaction(newTransaction); 
    newTransaction.GetSource()->clearTransactions();
    newTransaction.GetSource()->SetTransactions(tmp, newTransaction.GetSource()->GetNumOfTransactions() + 1);


        // Delete tmp list, and update relevant data member
    for (i = 0; i < m_numberOfTransaction; i++)
    {
        m_transactionList[i] = new Transaction(*tmp[i]);
        delete tmp[i]; 
    }
    delete[] tmp;

    // If s and d are different, add transaction to the destination account
    if (newTransaction.GetDes() != newTransaction.GetSource())
    {
        tmp = new Transaction *[newTransaction.GetDes()->GetNumOfTransactions() + 1];
        for (i = 0; i < newTransaction.GetDes()->GetNumOfTransactions(); i++)
        {
            tmp[i] = new Transaction(*newTransaction.GetDes()->GetTransactions()[i]);
        }
        tmp[i] = new Transaction(newTransaction); // add the new transaction
        newTransaction.GetDes()->clearTransactions();
        newTransaction.GetDes()->SetTransactions(tmp, newTransaction.GetDes()->GetNumOfTransactions() + 1);
        for (i = 0; i < m_numberOfTransaction; i++)
        {
            m_transactionList[i] = new Transaction(*tmp[i]);
            delete tmp[i]; 
        }
        delete[] tmp;
    }
    newTransaction.GetSource()->SetBalance(newTransaction.GetSource()->GetBalance() - newTransaction.GetAmount());
    newTransaction.GetDes()->SetBalance(newTransaction.GetDes()->GetBalance() + newTransaction.GetAmount());
}

void Account::clearTransactions()
{
    for (int i = 0; i < m_numberOfTransaction; i++)
    {
        delete[] m_transactionList[i]->GetDate();
    }
    delete[] m_transactionList;
}

void Account::clearPersons()
{
    if (m_totalPersons > 0)
    {
        for (int i = 0; i < m_totalPersons; i++)
        {
            delete m_persons[i];
        }
        delete[] m_persons;
    }
}