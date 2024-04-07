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
Account::Account(Person **persons, int count, double balance) : m_transactionList(nullptr)
{
    // CHANGED
    int id = 0;
    if (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            id += persons[i]->GetId();
        }
    }
    SetAccountNumber(id);

    // CHANGED 2
    // m_persons = nullptr;
    // TODO - Change account number to a unique one
    // SetAccountNumber(balance);

    m_numberOfTransaction = 0;
    SetBalance(balance);
    // WRONG ? Did I need to initialize persons here?
    // m_persons = new Person *[count];
    SetPersons(persons, count);
}

// Might be WRONG putting a null pointer to initialize
Account::Account(const Person &person, double balance) : m_transactionList(nullptr)
{

    // CHANGED
    m_numberOfTransaction = 0;

    // TODO - Change account number to a unique one
    SetAccountNumber(person.GetId());
    SetBalance(balance);
    m_persons = new Person *[1];

    // WRONG ? Send a pointer or value maybe?
    m_persons[0] = new Person(person);
    m_totalPersons = 1;
    // WRONG ? Should I send person to setpersons func?
    // SetPersons([person], 1);
}

// Might be WRONG putting a null pointer to initialize
// CHANGED
// Account::Account(const Account &other) : m_transactionList(nullptr)
Account::Account(const Account &other)
{
    // CHANGED 2
    // m_numberOfTransaction = other.m_numberOfTransaction;
    // m_totalPersons = other.GetTotalPersons();

    // CHANGED
    // m_totalPersons = other.m_totalPersons;
    // SetAccountNumber(other.m_accountNumber);
    // SetBalance(other.m_balance);
    // m_persons = nullptr;

    SetAccountNumber(other.GetAccountNumber());
    SetBalance(other.GetBalance());

    // m_accountNumber = other.m_accountNumber;
    // m_balance = other.m_balance;
    // WRONG? Did I need to do this:
    // Account(other.m_persons, other.m_totalPersons, other.m_balance);
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
    // m_persons = new Person *[m_totalPersons];
    // for (int i = 0; i < m_totalPersons; i++)
    // {
    //     m_persons[i] = new Person(*(other.m_persons[i]));
    // }
}

Account::~Account()
{

    for (int i = 0; i < m_numberOfTransaction; i++)
    {
        delete[] m_transactionList[i]->GetDate();
    }
    // delete[] m_transactionList;
    clearPersons();

    // CHANGED 2
    // clearTransactions();
    // clearPersons();
}

// WRONG ? Did I need to initialize person?
void Account::SetPersons(Person **persons, int count)
{
    // CHANGED
    m_persons = new Person *[count];
    for (int i = 0; i < count; i++)
    {
        m_persons[i] = new Person(*persons[i]);
    }

    // if (m_persons != nullptr)
    // {
    //     // WRONG ? Deep delete?
    //     delete[] m_persons;
    // }
    // // WRONG ? Is it plus 1?
    // // m_persons = new Person*[count + 1];
    // m_persons = new Person *[count];
    // for (int i = 0; i < count; i++)
    // {
    //     m_persons[i] = persons[i];
    //     // WRONG? Should I do:
    //     // m_persons[i] = new Person(persons[i]);
    //     // I think because I didnt recieve const / ref
    //     // for ex const Person &newPerson
    //     // I didnt need to create a new one
    // }
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

    // CHANGED
    // if (m_transactionList)
    // {
    //     // WRONG ? Deep delete?
    //     delete[] m_transactionList;
    // }
    // m_transactionList = new Transaction *[count];
    // for (int i = 0; i < count; i++)
    // {
    //     m_transactionList[i] = new Transaction(*(newTransaction[i]));
    // }
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
    // CHANGED
    // Transaction *newTransaction = new Transaction(this, this, amount, date);
    // AddTransaction(*newTransaction);

    if (m_transactionList == nullptr)
        m_transactionList = new Transaction *[1];
    m_transactionList[m_numberOfTransaction++] = new Transaction(this, this, amount, date);

    // Account *s, Account *d, double amount, const char *date
    m_balance -= amount;
}
void Account::Deposit(double amount, const char *date)
{
    // CHANGED
    // Transaction *newTransaction = new Transaction(this, this, amount, date);
    // AddTransaction(*newTransaction);

    if (m_transactionList == nullptr)
        m_transactionList = new Transaction *[1];
    m_transactionList[m_numberOfTransaction++] = new Transaction(this, this, amount, date);

    m_balance += amount;
}
void Account::AddPerson(const Person &newPerson, double amount)
{

    // WRONG ? Should I update the person?
    for (int i = 0; i < m_totalPersons; i++)
    {
        if (m_persons[i]->GetId() == newPerson.GetId())
        {
            return;
        }
    }
   
   // CHANGED 2
    // if (m_persons == nullptr)
    // {
    //     m_persons = new Person *[1];
    // }
    // m_persons[m_totalPersons++] = new Person(newPerson);
    
    Person** tmp = new Person * [m_totalPersons + 1];
	int i;
	for (i = 0; i < m_totalPersons; i++) {
		tmp[i] = new Person(*m_persons[i]);
	}
	tmp[i] = new Person(newPerson);
	clearPersons();
	m_persons = tmp; 
m_totalPersons++;


    double newBalance = m_balance + amount;
    SetBalance(newBalance);

    int id = 0;
    for (int i = 0; i < m_totalPersons; i++)
    {
        id += m_persons[i]->GetId();
    }
    SetAccountNumber(id);

    // WRONG? I removed this code
    // Update the account number only if a person is being added to the account
    // if (m_accountNumber == m_persons[0]->GetId())
    // {
    //     int newAccountNumber = m_accountNumber;
    //     newAccountNumber = (newAccountNumber + newPerson.GetId()) * (1 + newAccountNumber + newPerson.GetId()) + newPerson.GetId();
    //     newAccountNumber /= 2;
    //     this->SetAccountNumber(newAccountNumber);
    // }

    // CHANGED
    // double newBalance = m_balance + amount;
    // SetBalance(newBalance);

    // Person **temp = new Person *[m_totalPersons + 1];
    // for (int i = 0; i < m_totalPersons; i++)
    // {
    //     temp[i] = m_persons[i];
    // }
    // // temp[m_totalPersons] = newPerson;
    // temp[m_totalPersons] = new Person(newPerson);
    // m_totalPersons++;
    // if (m_persons)
    // {
    //     delete[] m_persons;
    // }
    // m_persons = temp;
}
void Account::DeletePerson(const Person &oldPerson)
{
    if (m_persons == nullptr)
        return;

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
        delete[] m_persons;
        m_persons = nullptr;
        return;
    }
    if (i != m_totalPersons)
    { // Not the last item in the array
        // Move the following items into the position of the indx we removed
        for (; i < m_totalPersons; i++)
        {
            m_persons[i] = m_persons[i + 1];
        }
        // Remove the last item in the list, it was moved by the loop above
        delete m_persons[m_totalPersons];
        // Set the last item to the nullptr
        m_persons[m_totalPersons] = nullptr;
    }

// IF THIS DOES PROBLEMS TRY THIS FROM # 2
	// // Person in the bank - delete him
	// Person** tmp = new Person * [m_totalPersons - 1];
	// int i, j;
	// for (i = 0, j = 0; i < m_totalPersons; i++) {
	// 	if (oldPerson.GetId() != m_persons[i]->GetId()) {
	// 		// Copy person to tmp arr if this isn't the person we want to delete
	// 		tmp[j] = new Person(*m_persons[i]);
	// 		j++;
	// 	}
	// }
	// clearPersons();
	// m_totalPersons--;
	// m_persons = tmp;

    // CHANGED
    //    for (int i=0; i < m_totalPersons; i++)
    // {
    //     if (m_persons[i]->GetId() == oldPerson.GetId())
    //     {
    //         // WRONG? Will I delete the pointer I need one row after?
    //         m_persons[i] = m_persons[m_totalPersons - 1];
    //         delete m_persons[m_totalPersons - 1];

    //         // delete survivors[i];
    //         // for (int j = i; j < remainingSurvivors - 1; j++) {
    //         //     survivors[j] = survivors[j + 1];
    //         // }

    //         m_totalPersons--;
    //         break;
    //     }
    // }
}
void Account::AddTransaction(const Transaction &newTransaction)
{

    	int i;
	Transaction** tmp = new Transaction * [newTransaction.GetSource()->GetNumOfTransactions() + 1];
	for (i = 0; i < newTransaction.GetSource()->GetNumOfTransactions(); i++) {
		tmp[i] = new Transaction(*newTransaction.GetSource()->GetTransactions()[i]);
	}
	tmp[i] = new Transaction(newTransaction); // add the new transaction
	newTransaction.GetSource()->clearTransactions();
	newTransaction.GetSource()->SetTransactions(tmp, newTransaction.GetSource()->GetNumOfTransactions() + 1);
	for (i = 0; i < m_numberOfTransaction; i++) {
		m_transactionList[i] = new Transaction(*tmp[i]);
		delete tmp[i]; // delete tmp list
	}
	delete[] tmp;

	// If source and destination are different add -> Add the transaction to the destination account
	if (newTransaction.GetDes() != newTransaction.GetSource()) {
		tmp = new Transaction * [newTransaction.GetDes()->GetNumOfTransactions() + 1];
		for (i = 0; i < newTransaction.GetDes()->GetNumOfTransactions(); i++) {
			tmp[i] = new Transaction(*newTransaction.GetDes()->GetTransactions()[i]);
		}
		tmp[i] = new Transaction(newTransaction); // add the new transaction
		newTransaction.GetDes()->clearTransactions();
		newTransaction.GetDes()->SetTransactions(tmp, newTransaction.GetDes()->GetNumOfTransactions() + 1);
		for (i = 0; i < m_numberOfTransaction; i++) {
			m_transactionList[i] = new Transaction(*tmp[i]);
			delete tmp[i]; // delete tmp list
		}
		delete[] tmp;
	}
	newTransaction.GetSource()->SetBalance(newTransaction.GetSource()->GetBalance() - newTransaction.GetAmount());
	newTransaction.GetDes()->SetBalance(newTransaction.GetDes()->GetBalance() + newTransaction.GetAmount());

// CHANGED 2
    // // Update money for withdrawl or deposit
    // if (newTransaction.GetSource()->GetAccountNumber() == newTransaction.GetDes()->GetAccountNumber())
    // {
    //     if (newTransaction.GetAmount() > 0)
    //     {
    //         newTransaction.GetSource()->Withdraw(newTransaction.GetAmount(), newTransaction.GetDate());
    //     }
    //     else
    //     {
    //         newTransaction.GetSource()->Deposit(newTransaction.GetAmount(), newTransaction.GetDate());
    //     }
    //     return;
    // }
    // // Update money in d & s accounts
    // Account *source = newTransaction.GetSource();
    // Account *dest = newTransaction.GetDes();
    // source->SetBalance(source->GetBalance() - newTransaction.GetAmount());
    // dest->SetBalance(dest->GetBalance() + newTransaction.GetAmount());
    // // Update transactions
    // source->m_transactionList[source->m_numberOfTransaction++] = new Transaction(newTransaction);
    // dest->m_transactionList[dest->m_numberOfTransaction++] = new Transaction(newTransaction);

    // CHANGED
    // Transaction **temp = new Transaction *[m_numberOfTransaction + 1];

    // for (int i = 0; i < m_numberOfTransaction; i++)
    // {
    //     temp[i] = m_transactionList[i];
    // }
    // temp[m_numberOfTransaction] = new Transaction(newTransaction);
    // m_numberOfTransaction++;
    // if (m_transactionList)
    //     delete[] m_transactionList;

    // m_transactionList = temp;
}

void Account::clearTransactions()
{
    for (int i = 0; i < m_numberOfTransaction; i++)
    {
        delete[] m_transactionList[i]->GetDate();
    }
    delete[] m_transactionList;

    // CHANGED 2
    // if (m_transactionList != nullptr)
    // {
    //     // WRONG ? Is the if needed?
    //     for (int i = 0; i < m_numberOfTransaction; i++)
    //         delete m_transactionList[i];
    //     delete[] m_transactionList;
    //     m_numberOfTransaction = 0;
    //     // WRONG ? Is this needed? never saw it like this before
    //     m_transactionList = nullptr;
    // }
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

    // CHANGED 2
    // // WRONG ? Is the if needed?
    // if (m_persons != nullptr)
    // {
    //     for (int i = 0; i < m_totalPersons; i++)
    //         delete m_persons[i];
    //         // cout<< m_persons;
    //     delete[] m_persons;
    //     m_totalPersons = 0;
    //     // WRONG ? Is this needed? never saw it like this before
    //     m_persons = nullptr;
    // }
}