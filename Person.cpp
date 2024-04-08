#include "Person.h"
#include <cstring>

// MORIA HAMAMI
// 315464347

Person::Person()
{
    m_id = 0;
    m_name = nullptr;
}

Person::Person(const char *name, int id)
{
    SetId(id);
    SetName(name);
}

Person::Person(const Person &other)
{
    SetId(other.m_id);
    SetName(other.m_name);
}

Person::~Person()
{
    delete m_name;
}

void Person::SetName(const char *newName)
{
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