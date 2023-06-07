#include <iostream>
#include <cstring>
#define max 10
using namespace std;

struct client
{
    long int iPhno;
    char name[20];
};

class hashtable
{

public:
    client ht[max];
    
    hashtable()
    {
        // Constructor
    }

    void insert()
    {
        client c;
        int iPos;
        char cAns;

        do
        {
            cout << "\nEnter Phone Number: ";
            cin >> c.iPhno;
            iPos = hash(c.iPhno);

            if (ht[iPos].iPhno == 0)
            {
                ht[iPos] = c;
            }
            else
            {
                int i = iPos + 1;
                while (i % max != iPos)
                {
                    if (ht[i].iPhno == 0)
                    {
                        ht[i] = c;
                        break;
                    }
                    i = (i + 1) % max;
                }
            }

            cout << "Add More (Y/N): ";
            cin >> cAns;
        } while (cAns == 'y' || cAns == 'Y');
    }

    int hash(long int key)
    {
        return (key % max);
    }

    void display()
    {
        cout << "------------------------------------";
        cout << "\nSrno\tPhone number\n";
        cout << "------------------------------------\n";
        for (int i = 0; i < max; i++)
        {
            cout << i << "\t" << ht[i].iPhno << endl;
        }
        cout << "------------------------------------\n";
    }

    int search(int x)
    {
        int iFlag = 0;
        cout << "Enter Phone number to be searched: ";
        cin >> x;
        for (int i = 0; i < max; i++)
        {
            if (ht[i].iPhno == x)
            {
                cout << "\nPhone Number Found at position " << i;
                iFlag = 1;
            }
        }
        if (iFlag == 0)
            cout << "\nPhone Number Not Found";
        return 0;
    }

    int del(int s)
    {
        int iF = 0;
        cout << "\nEnter phone number to be deleted: ";
        cin >> s;

        for (int i = 0; i < max; i++)
        {
            if (ht[i].iPhno == s)
            {
                ht[i].iPhno = 0;
                cout << "\nPhone number found and deleted";
                iF = 1;
                break; // Added break statement to exit the loop after deleting the number
            }
        }
        if (iF == 0)
            cout << "\nPhone number not found";
        return 0;
    }
};

int main()
{
    int y, s, iCh;
    hashtable h;

    // Initialize the hash table
    for (int i = 0; i < max; i++)
    {
        h.ht[i].iPhno = 0;
    }

    do
    {
        cout << "\n---------------LIST---------------\n";
        cout << "\n1. INSERT\n2. DISPLAY\n3. SEARCH\n4. DELETE\n5. EXIT\n\n";
        cout << "Enter your choice: ";
        cin >> iCh;
        cout << "\n";
        switch (iCh)
        {
            case 1: // insert
                h.insert();
                cout << "\n";
                break;
            case 2: // display
                h.display();
                cout << "\n";
                break;
            case 3: // search
                h.search(y);
                cout << "\n";
                break;
            case 4: // delete
                h.del(s);
                cout << "\n";
                break;
            case 5: // exit
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (iCh != 5);
    return 0;
}
