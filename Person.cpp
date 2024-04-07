#include "Person.h"
#include <cstring>

Person::Person()
{
    m_id = 0;
    m_name = nullptr;
}

Person::Person(const char *name, int id)
{
    // CHANGED
    // m_name = nullptr;
    SetId(id);
    SetName(name);
}

Person::Person(const Person &other)
{
    // CHANGED
    // m_name = nullptr;

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
    // CHANGED
    // if (m_name != nullptr) {
    //     delete[] m_name;
    //     // WRONG? I think this is needed because
    //     // After deleteing person, it goes to bank and tries to delete person 
    //     // but its garbage so it cant
    //     m_name=nullptr;
    // }
    // CHANGED 2
    // if(m_name){
    //     delete m_name;
    // }
    delete m_name;
}

void Person::SetName(const char *newName)
{
    // CHANGED
    // if (m_name != nullptr)
    //     delete[] m_name;
    
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