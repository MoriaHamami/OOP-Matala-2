#include "Transaction.h"

Transaction::Transaction(Account *s, Account *d, double amount, const char *date)
{
    SetAmount(amount);
    SetDate(date);
    SetSource(s);
    SetDes(d);
}

Transaction::Transaction(const Transaction &other)
{
    // WRONG ? Is this enough?
    Transaction(other.m_source, other.m_destination, other.m_amount, other.m_date);
}

void Transaction::SetSource(Account *src)
{
    m_source=src;
}
void Transaction::SetDes(Account *dst)
{
    m_destination = dst;
}
void Transaction::SetAmount(double amount)
{
    m_amount = amount;
}
void Transaction::SetDate(const char *date)
{
    if (m_date != nullptr) delete[] m_date;
    int size = strlen(date);
    m_date = new char[size + 1];
    strcpy(m_date, date);

    // WRONG ? Should I just do this:
    // strcpy(m_date, date);
}
Account *Transaction::GetSource() const
{
    return m_source;
}
Account *Transaction::GetDes() const
{
    return m_destination;
}
double Transaction::GetAmount() const
{
    return m_amount;
}
char *Transaction::GetDate() const
{
    return m_date;
}