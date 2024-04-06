#include "Person.h"
#include <cstring>

Person::Person()
{
    m_id = 0;
    m_name = nullptr;
}

Person::Person(const char *name, int id)
{
    m_name = nullptr;
    SetId(id);
    SetName(name);
}

Person::Person(const Person &other)
{
    m_name = nullptr;
    // WRONG!!! LESSON - You cannot do the following:
    // Person(other.m_name, other.m_id);
    // This causes the person to 
    // get deleted at the end of the scope
    // and calls the destructor.
    // Instead do this:
    SetId(other.m_id);
    SetName(other.m_name);
    // WRONG? Should I do this:
    // SetId(other.m_id);
    // SetName(other.m_name);
}

Person::~Person()
{
    if (m_name != nullptr)
        delete[] m_name;
}

void Person::SetName(const char *newName)
{
    if (m_name != nullptr)
        delete[] m_name;
    int size = strlen(newName);
    m_name = new char[size + 1];
    strcpy(m_name, newName);
}

void Person::SetId(int newId)
{
    m_id = newId;
}

char *Person::GetName() const
{
    return m_name;
}

int Person::GetId() const
{
    return m_id;
}