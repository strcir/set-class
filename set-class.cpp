/*
This program contains a class representing a mathematical set with appropriate constructors and functions.
Author: Strahinja Ciric
sciric@mit.edu
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;

typedef int* IntArrayPtr;

class Set
{
public:
    Set();
    Set(int in_members[], int capacity);
    friend Set operator +(const Set& set1, const Set& set2); //set union
    friend Set intersection(const Set& set1, const Set& set2); //set intersection
    friend Set operator -(const Set& set1, const Set& set2); //set difference
    friend void delete_repeats(int a[], int& capacity);
    int get_cardinality();
    IntArrayPtr get_members();
    void input(istream& ins);
    void output(ostream& outs);
private:
    IntArrayPtr members;
    int cardinality;
};

int Set::get_cardinality()
{
    return cardinality;
}

IntArrayPtr Set::get_members()
{
    if (cardinality == 0)
    {
        cout << "Error: Cannot retrieve members from an empty set.\n";
        exit(1);
    }
    return members;
}

void delete_repeats(int a[], int& capacity)
{
    for (int i = 0; i < capacity; i++)
    {
        for (int j = (i + 1); j < capacity; j++)
        {
            if (a[i] == a[j])
            {
                capacity--;
                for (int k = j; k < capacity; k++)
                {
                    a[k] = a[k + 1];
                }
            }
        }
    }
    return;
}

Set::Set()
{
    cardinality = 0; //creates an empty set
}

Set::Set(int in_members[], int capacity)
{
    members = new int[capacity];
    for (int i = 0; i < capacity; i++)
    {
        members[i] = in_members[i];
    }
    delete_repeats(members, capacity); //set elements must be distinct by the Axiom of Extensionality
    cardinality = capacity;
}

Set operator +(const Set& set1, const Set& set2)
{
    Set temp;
    temp.cardinality = set1.cardinality + set2.cardinality;
    if (temp.cardinality != 0)
    {
        temp.members = new int[temp.cardinality];
        if (set1.cardinality != 0)
        {
            for (int i = 0; i < set1.cardinality; i++)
            {
                temp.members[i] = set1.members[i];
            }
        }
        if (set2.cardinality != 0)
        {
            for (int i = set1.cardinality; i < temp.cardinality; i++)
            {
                temp.members[i] = set2.members[i - set1.cardinality];
            }
        }
        delete_repeats(temp.members, temp.cardinality);
    }
    return temp;
}

Set intersection(const Set& set1, const Set& set2)
{
    Set temp;
    if (set1.cardinality == 0 || set2.cardinality == 0)
    {
        temp.cardinality = 0;
    }
    else
    {
        temp.members = new int[set1.cardinality];
        temp.cardinality = 0;
        for (int i = 0; i < set1.cardinality; i++)
        {
            for (int j = 0; j < set2.cardinality; j++)
            {
                if (set1.members[i] == set2.members[j])
                {
                    temp.members[temp.cardinality] = set1.members[i];
                    temp.cardinality++;
                }
            }
        }
        delete_repeats(temp.members, temp.cardinality);
    }
    return temp;
}

Set operator -(const Set& set1, const Set& set2)
{
    Set temp;
    if (set1.cardinality == 0)
    {
        temp.cardinality = 0;
    }
    else
    {
        temp.members = new int[set1.cardinality];
        for (int i = 0; i < set1.cardinality; i++)
        {
            temp.members[i] = set1.members[i];
        }
        temp.cardinality = set1.cardinality;
        if (set2.cardinality != 0)
        {
            for (int i = 0; i < temp.cardinality; i++)
            {
                for (int j = 0; j < set2.cardinality; j++)
                {
                    if (temp.members[i] == set2.members[j])
                    {
                        temp.cardinality--;
                        for (int k = i; k < temp.cardinality; k++)
                        {
                            temp.members[k] = temp.members[k + 1];
                        }
                        i--;
                    }
                }
            }
            delete_repeats(temp.members, temp.cardinality);
        }
    }
    return temp;
}

void Set::output(ostream& outs)
{
    if (cardinality == 0)
    {
        outs << "{Empty Set}";
    }
    else
    {
        outs << "{";
        for (int l = 0; l < (cardinality - 1); l++)
        {
            outs << members[l] << ", ";
        }
        outs << members[cardinality - 1] << "}";
    }
}

void Set::input(istream& ins)
{
    delete [] members;
    cout << "Enter the number of elements of the set:\n";
    ins >> cardinality;
    members = new int[cardinality];
    cout << "Enter the (integer) elements, separated by spaces or carriage returns:\n";
    for (int i = 0; i < cardinality; i++)
    {
        ins >> members[i];
    }
    delete_repeats(members, cardinality);
}

int main()
{
    int p[20] = {4, 3, 5, 3, 18, 7, 18, 4, 2, 2, 6};
    int q[20] = {11, 18, 7, 7, 5, 1, 2};
    Set a(p, 11);
    Set b;
    Set c;
    Set d(q, 7);
    cout << "For Set A: ";
    a.input(cin);
    cout << "\nHere are sets A, B, C, and D:\n\nSet A: ";
    a.output(cout);
    cout << "\nSet B: ";
    b.output(cout);
    cout << "\nSet C: ";
    c.output(cout);
    cout << "\nSet D: ";
    d.output(cout);
    cout << "\n\nA union A = ";
    (a + a).output(cout);
    cout << "\nA union D = ";
    (a + d).output(cout);
    cout << "\nA union B = ";
    (a + b).output(cout);
    cout << "\nB union C = ";
    (b + c).output(cout);
    cout << "\n\nA intersect A = ";
    intersection(a, a).output(cout);
    cout << "\nA intersect D = ";
    intersection(a, d).output(cout);
    cout << "\nA intersect B = ";
    intersection(a, b).output(cout);
    cout << "\nB intersect C = ";
    intersection(b, c).output(cout);
    cout << "\n\nA - A = ";
    (a - a).output(cout);
    cout << "\nA - D = ";
    (a - d).output(cout);
    cout << "\nA - B = ";
    (a - b).output(cout);
    cout << "\nB - C = ";
    (b - c).output(cout);
    char letter;
    cout << "\n\nEnter any letter to end the program.\n";
    cin >> letter;
    return 0;
}
