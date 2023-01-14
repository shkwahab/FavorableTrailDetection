#include <iostream>
#include <vector>
#include <string>
#include <unistd.h> //for linux
// #include<windows.h> //windows

using namespace std;

const int INF = 1e9;

int n, m, source; // n = number of trails, m = number of connections, source = starting trail, d= distance of trails
string u_name, u_password, confirm_password;

vector<string> name;

vector<vector<pair<int, int>>> adj;
int *dist;

bool login()
{
    string name, password;
    cout << " Enter the username:";
    cin >> name;
    cout << "Enter the password:";
    cin >> password;
    if (u_name == name && u_password == password)
    {
        return true;
    }
    else
    {
        cout << "Wrong Creditionals";
        cout << endl;
        return false;
    }
    return false;
}

void takeSignUp()
{
    cout << "Enter your username:";
    cin >> u_name;
    cout << "Enter your password:";
    cin >> u_password;
    cout << "Enter confirm password:";
    cin >> confirm_password;
}
void signup()
{
    takeSignUp();
    int counter = 0;
    if (u_password != confirm_password)
    {
        cout << "Password and Confirm Password doesn't match!\n";
        cout << "Retry" << endl;
        while (true)
        {
            if (counter == 3)
            {
                break;
            }
            if (counter == 1)
            {
                cout << "You have left one chance to type write password otherwise you will have to wait run the program again\n";
            }
            takeSignUp();
            counter++;
        }
    }
    else
    {
        cout << "Registered Successfully" << endl;
    }
}

class FavorableTrailDetection
{
public:
    void inputTrails(vector<string> &name)
    {
        cout << "Enter number of trails: ";
        cin >> n;
        name.resize(n);
        for (int i = 0; i < n; i++)
        {
            cout << "Enter name for trail " << i << ": ";
            cin >> name[i];
        }
    }

    void inputConnections()
    {
        cout << "Enter number of connections: ";
        cin >> m;
        adj.resize(m);
        for (int i = 0; i < m; i++)
        {
            int a, b, w; // a, b are the trails, w is the difficulty level of the connection
            cout << "Enter the trails which you want to connect like(0,1):";
            cin >> a;
            cin >> b;
            cout << "Enter the difficulty level for connection " << i << ":";
            cin >> w;
            adj[a].push_back({b, w});
        }
    }

    void inputDistances(int n)
    {
        dist = new int[n];
        for (int i = 0; i < n; i++)
        {
            cout << "Enter distance for trail " << i << ": ";
            cin >> dist[i];
        }
    }
    void bellman_ford(int n, int m, int source, vector<string> &name)
    {
        dist[source] = 0; // initialize distance to source trail
        cout << "Initial distance: ";
        for (int i = 0; i < n; i++)
            cout << dist[i] << " ";
        cout << endl;
        for (int i = 0; i < n - 1; i++)
        { // repeat V-1 times
            for (int j = 0; j < n; j++)
            { // for each trail
                for (auto u : adj[j])
                { // for each connection
                    int v = u.first, w = u.second;
                    if (dist[j] != INF && dist[j] + w < dist[v])
                    { // relaxation
                        dist[v] = dist[j] + w;
                    }
                }
            }
            cout << "After iteration " << i + 1 << ": ";
            for (int i = 0; i < n; i++)
                cout << dist[i] << " ";
            cout << endl;
        }
        bool negative_cycle = false;
        for (int j = 0; j < n; j++)
        { // check for negative cycles
            for (auto u : adj[j])
            {
                int v = u.first, w = u.second;
                if (dist[j] != INF && dist[j] + w < dist[v])
                {
                    negative_cycle = true;
                    break;
                }
            }
        }
        if (negative_cycle)
        {
            cout << "Graph contains a negative cycle." << endl;
        }
        else
        {
            cout << "Final distance: ";
            for (int i = 0; i < n; i++)
                cout << dist[i] << " ";
            cout << endl;
            for (int i = 0; i < n; i++)
            {
                cout << "Shortest difficulty level from " << name[source] << " to " << name[i] << " is " << dist[i] << endl;
            }
        }
    }
};

int main()
{
    cout << "--------------------------------------------------------------------"
         << endl;
    cout << "\t\t\t"
         << "Favorable Trail Detection\n"
         << "---------------------------------------------------------------------"
         << "\n\n";
    unsigned int microsecond = 1000000; // for linux
    usleep(2 * microsecond);            // sleeps for 3 second //for unix or linux
    //  Sleep(milliseconds); windows
    FavorableTrailDetection project;
    system("clear"); // for linux
    // system("cls")
    while (true)
    {
        cout << "⚠ To Use This Application You mush have to sign in" << endl;
        cout << endl
             << "Press 1 to Sign In" << endl
             << "Press 2 to Sign Up" << endl
             << "Press 3 to Exit" << endl;
        int option;
        cout << "Enter your choice:";
        cin >> option;
        if (option == 3)
        {
            break;
        }
        switch (option)
        {
        case 1:

            if (login() == 1)
            {
                system("clear"); // for linux
                // system("cls"); //for windows
                cout << "\n\t\t\t"
                     << "Welcome to my Favorable Trail Detection made by Farhan Zafar"
                     << "\n\n";
                int ch;
                while (true)
                {
                    cout << "Press 1 to enter the number of trails and their names" << endl;
                    cout << "Press 2 to enter the number of connection of trails and their connections and the difficult levels of the trails" << endl;
                    cout << "Press 3 to enter the distances of the trails" << endl;
                    cout << "Press 4 for to Choose Your Source Trail or Starting Trail" << endl;
                    cout << "Press 5 to show the final distances and shortest difficult level by trail by trails" << endl;
                    cout << "Press 6 to Back" << endl;
                    cout << "\nEnter your choice: ";
                    cin >> ch;
                    if (ch == 6)
                    {
                        break;
                    }
                    switch (ch)
                    {
                    case 1:
                        cout << endl;
                        project.inputTrails(name);
                        cout << endl;
                        break;
                    case 2:
                        cout << endl;
                        project.inputConnections();
                        cout << endl;
                        break;
                    case 3:
                        cout << endl;
                        project.inputDistances(n);
                        cout << endl;
                        break;
                    case 4:
                        cout << endl;
                        cout << "Enter the Source Trail or Starting Trail:";
                        cout << endl;
                        cin >> source;
                        break;
                    case 5:
                        cout << endl;
                        if (n == 0 || m == 0 || source == -1)
                        {
                            cout << endl;
                            cout << "Can't use this functionality without specifying trails or its connection or source trails" << endl;
                        }
                        else
                        {
                            cout << endl;
                            cout << endl;
                            project.bellman_ford(n, m, source, name);
                        }
                        cout << endl;
                        break;
                    default:
                        cout << endl;
                        cout << "Invalid option" << endl;
                        cout << endl;
                        break;
                    }
                }
            }
            break;
        case 2:
            signup();
            break;
        case 3:
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    }

    return 0;
}