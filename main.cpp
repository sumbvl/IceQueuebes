#include<iostream>
#include<vector>
#include<stack>
#include<unordered_map>
#include<string>
#include<queue>
#include<cstdlib>
#include<ctime>
using namespace std;

//Structs

struct IceCream
{
    string name;
    int price;
    int stock;
};
struct Customer
{
    string name;
    vector<string> order;
    int patience;
    int tip;
};

//Custom Linked List

struct Node
{
    string  data;
    Node *next;
    Node(string val)
    {
        data = val;
        next = NULL;
    }
};

class LinkedList
{
public:
    Node *head;
    LinkedList()
    {
        head = NULL;
    }
    void insert(string val)
    {
        Node *newNode = new Node(val);

        if (head == NULL)
        {
            head = newNode;
            return;
        }

        Node *ptr = head;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }

        ptr->next = newNode;
    }
    void deleteNode(string val)
    {
        if (head == NULL)
        {
            return;
        }

        if (head->data == val)
        {
            Node *temp = head;
            head       = head->next;
            delete temp;
            return;
        }
        Node *ptr = head;
        while (ptr->next != NULL && ptr->next->data != val)
        {
            ptr = ptr->next;
        }
        if (ptr->next != NULL)
        {
            Node *temp = ptr->next;
            ptr->next  = ptr->next->next;
            delete temp;
        }
    }
    bool empty()
    {
        return head == NULL;
    }
};

void pauseScreen()
{
    cout<<endl<<"Press Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}
void clearScreen()
{
    system("cls");
}

//ASCII Art

void drawCustomer(string name, int patience)
{
    string bar = "[";
    for (int i=0; i<10; i++)
    {
        if (i < patience)
        {
            bar += "#";
        }
        else
        {
            bar += "-";
        }
    }
    bar += "]";

    string mood;
    if (patience >= 7)
    {
        mood = "^u^";
    }
    else if (patience >= 4)
    {
        mood = "o_o";
    }
    else
    {
        mood = ">_<";
    }
    cout<<"\n";
    cout<<"      .---.\n";
    cout<<"     ( "<<mood<<" )\n";
    cout<<"      `---'\n";
    cout<<"       /|\\\n";
    cout<<"      / | \\\n";
    cout<<"       / \\\n";
    cout<<"      /   \\\n\n";
    cout<<"  >> "<<name<<" <<\n";
    cout<<"  Patience: "<<bar<<" "<<patience<<"/10\n";
}
void drawCone(vector<string>& scoops)
{
    cout<<"\n";
    int total = scoops.size();

    if (total == 0)
    {
        cout<<"       (empty)\n";
        cout<<"        |   |\n";
        cout<<"         \\ /\n";
        cout<<"          V\n";
        return;
    }
    cout<<"      _______\n";
    for (int i=total-1; i>=0; i--)
    {
        cout<<"     (       )  <- "<<scoops[i]<<"\n";
    }
    cout<<"      \\-----/\n";
    cout<<"       \\   /\n";
    cout<<"        \\ /\n";
    cout<<"         V\n";
}

//Main Class

class IceQueuebes
{
public:
    queue<Customer>  customerLine;
    stack<string>  iceCreamTower;
    LinkedList  flavourMenu;
    unordered_map<string,IceCream> catalog;

    int  totalEarnings;
    int  dayNumber;
    int  customersServed;
    int  customersMissed;
    bool gameOver;

    vector<string> customerNames =
    { "Hamza","Noor","Sumbal","Tehreem","Umaima",
      "Hashim","Moiz","Ehtesham","Mohid","Arooj",
      "Iraj","Qudsia","Kainat","Zayera","Maryam" };

    string lastCustomerName = "";

    IceQueuebes()
    {
        totalEarnings   = 0;
        dayNumber       = 1;
        customersServed = 0;
        customersMissed = 0;
        gameOver        = false;

        addFlavour("FrostByte",        200, 20);
        addFlavour("Cocoa Loco",       250, 15);
        addFlavour("Cookie Chaos",     250, 15);
        addFlavour("Berry Blast",      300, 10);
        addFlavour("Espresso Eclipse", 350, 10);
    }

//Catalogue Management

    void addFlavour(string name, int price, int stock)
    {
        IceCream temp;
        temp.name  = name;
        temp.price = price;
        temp.stock = stock;
        catalog[name] = temp;
        flavourMenu.insert(name);
    }

    void removeFlavour()
    {
        displayMenu();
        cout<<"\n  Enter exact flavour name to REMOVE from menu: ";
        cin.ignore(1000, '\n');
        string fname;
        getline(cin, fname);

        if (catalog.find(fname) == catalog.end())
        {
            cout<<"  Flavour not found.\n";
            return;
        }
        catalog.erase(fname);
        flavourMenu.deleteNode(fname);
        cout<<"  Removed "<<fname<<" from the menu.\n";
    }

//Display

    void displayMenu()
    {
        cout<<endl<<" +----------------------------------+\n";
        cout<<      " |        ICE CREAM MENU            |\n";
        cout<<      " +----------------------------------+\n\n";

        int   idx = 1;
        Node *ptr = flavourMenu.head;
        while (ptr != NULL)
        {
            IceCream ic = catalog[ptr->data];
            cout<<"  "<<idx++<<". "<<ic.name
                <<"\n     Rs. "<<ic.price
                <<"  |  Stock: "<<ic.stock<<"\n";
            ptr = ptr->next;
        }
    }

    void displayStats()
    {
        cout<<endl<<" +----------------------------------+\n";
        cout<<      " |  DAY "<<dayNumber
            <<      "  |  Earnings: Rs. "<<totalEarnings<<"\n";
        cout<<      " |  Served: "<<customersServed
            <<      "  |  Missed: "<<customersMissed<<"\n";
        cout<<      " |  Queue size: "<<customerLine.size()<<"\n";
        cout<<      " +----------------------------------+\n";
    }

    void displayTower()
    {
        stack<string>  copy = iceCreamTower;
        vector<string> scoops;
        while (!copy.empty())
        {
            scoops.insert(scoops.begin(), copy.top());
            copy.pop();
        }
        cout<<endl<<"  --- Your Cone So Far ---"<<endl;
        drawCone(scoops);
    }

//Customer Spawning

    void spawnCustomers(int count)
    {
        for (int i=0; i<count; i++)
        {
            Customer c;
            string picked;
            do
            {
                picked = customerNames[rand() % customerNames.size()];
            }
            while (picked == lastCustomerName && customerNames.size() > 1);
            lastCustomerName = picked;
            c.name           = picked;
            c.patience       = rand() % 8 + 3;
            c.tip            = 0;
            int scoops = rand() % 3 + 1;
            vector<string> menuVec;
            Node *ptr = flavourMenu.head;
            while (ptr != NULL)
            {
                menuVec.push_back(ptr->data);
                ptr = ptr->next;
            }

            for (int j=0; j<scoops; j++)
            {
                string pick = menuVec[rand() % menuVec.size()];
                c.order.push_back(pick);
            }
            customerLine.push(c);
        }
    }

//Serving

    void serveNextCustomer()
    {
        if (customerLine.empty())
        {
            cout<<endl<<"  No customers waiting!"<<endl;
            return;
        }
        Customer cust = customerLine.front();
        customerLine.pop();
        cout<<endl<<" ___________________________________"<<endl;
        drawCustomer(cust.name, cust.patience);
        cout<<endl<<"  They want "<<cust.order.size()<<" scoop(s):"<<endl;
        for (int i=0; i<cust.order.size(); i++)
        {
            cout<<"    - "<<cust.order[i]<<endl;
        }
        while (!iceCreamTower.empty())
        {
            iceCreamTower.pop();
        }
        int  orderCost   = 0;
        bool orderFail   = false;
        int  scoopsAdded = 0;
        for (int i=0; i<cust.order.size(); i++)
        {
            string flavour = cust.order[i];
            if (catalog[flavour].stock <= 0)
            {
                cout<<"\n  !! "<<flavour<<" is out of stock! Order failed.\n";
                orderFail = true;
                break;
            }
            cout<<"\n  -> Add scoop: "<<flavour<<" ? (y/n): ";
            char ch;
            cin>>ch;
            if (ch=='y' || ch=='Y')
            {
                catalog[flavour].stock--;
                orderCost += catalog[flavour].price;
                iceCreamTower.push(flavour);
                scoopsAdded++;
                displayTower();
            }
            else
            {
                cout<<"  Skipped scoop. Customer is unhappy!\n";
                cust.patience -= 2;
                if (cust.patience < 0)
                {
                    cust.patience = 0;
                }
            }
        }
        bool orderComplete = (!orderFail && scoopsAdded == cust.order.size());
        if (orderComplete)
        {
            int tip = cust.patience * 10;
            totalEarnings += orderCost + tip;
            customersServed++;

            cout<<"\n  [OK] Order complete!\n";
            cout<<"  Charged : Rs. "<<orderCost<<"\n";
            cout<<"  Tip     : Rs. "<<tip<<"\n";
            cout<<"  Total   : Rs. "<<orderCost+tip<<"\n";
        }
        else
        {
            cout<<"\n  [!!] Order not fulfilled. No charge.\n";
            customersMissed++;
        }
        decreasePatience();
    }

//Patience

    void decreasePatience()
    {
        queue<Customer> updated;
        queue<Customer> temp = customerLine;
        while (!temp.empty())
        {
            Customer c = temp.front();
            temp.pop();
            c.patience--;
            if (c.patience <= 0)
            {
                cout<<"  >:( "<<c.name<<" lost patience and LEFT!\n";
                customersMissed++;
            }
            else
            {
                updated.push(c);
            }
        }
        customerLine = updated;
    }

//Restock

    void restockFlavour()
    {
        displayMenu();
        cout<<"\n  Enter flavour name (case sensitive) to restock (costs Rs. 500): ";
        cin.ignore(1000, '\n');
        string fname;
        getline(cin, fname);
        if (catalog.find(fname) == catalog.end())
        {
            cout<<"  Flavour not found.\n";
            return;
        }
        if (totalEarnings < 500)
        {
            cout<<"  Not enough money!\n";
            return;
        }
        catalog[fname].stock += 10;
        totalEarnings -= 500;
        cout<<"  Restocked "<<fname<<" by 10 units.\n";
    }

//Day Cycle

    void startDay()
    {
        clearScreen();
        cout<<"\n ===================================\n";
        cout<<  "          DAY "<<dayNumber<<" BEGINS!\n";
        cout<<  " ===================================\n";

        int newCustomers = rand() % 5 + 3;
        spawnCustomers(newCustomers);
        cout<<"  "<<newCustomers<<" customers arrived!\n";
        pauseScreen();
    }

    void endDay()
    {
        clearScreen();
        cout<<"\n ===================================\n";
        cout<<  "          END OF DAY "<<dayNumber<<"\n";
        cout<<  " ===================================\n";
        displayStats();
        if (customersMissed==0 && customersServed>0)
        {
            int bonus = 500;
            totalEarnings += bonus;
            cout<<"\n  *** PERFECT DAY BONUS: Rs. "<<bonus<<"! ***\n";
        }
        if (dayNumber >= 5)
        {
            gameOver = true;
            endGame();
            return;
        }
        dayNumber++;
        cout<<"\n  Options before Day "<<dayNumber<<":\n\n";
        cout<<"  [1] Restock a flavour (Rs. 500)\n";
        cout<<"  [2] Remove a flavour from menu\n";
        cout<<"  [3] Skip\n";
        cout<<"  [4] Quit game\n\n";
        cout<<"  Choice: ";
        int ch;
        cin>>ch;
        if (ch==1)
        {
            restockFlavour();
        }
        else if (ch==2)
        {
            removeFlavour();
        }
        else if (ch==4)
        {
            gameOver = true;
            endGame();
        }
    }

//End Game

    void endGame()
    {
        cout<<"\n +----------------------------------+\n";
        cout<<  " |      GAME OVER  -  RESULTS       |\n";
        cout<<  " +----------------------------------+\n\n";
        cout<<  "  Total Earnings  : Rs. "<<totalEarnings<<"\n";
        cout<<  "  Customers Served: "    <<customersServed<<"\n";
        cout<<  "  Customers Missed: "    <<customersMissed<<"\n";

        if (totalEarnings >= 10000)
        {
            cout<<"\n  *** RATING: Ice Cream Legend!  ***\n";
        }
        else if (totalEarnings >= 6000)
        {
            cout<<"\n  **  RATING: Pro Scooper!       **\n";
        }
        else if (totalEarnings >= 3000)
        {
            cout<<"\n  *   RATING: Decent Parlor       *\n";
        }
        else
        {
            cout<<"\n      RATING: Needs Work...\n";
        }
        cout<<"\n  Thanks for playing IceQueuebes!\n\n";
    }

//Game Loop

    void run()
    {
        srand(time(0));

        clearScreen();
        cout<<"\n +-------------------------------------+\n";
        cout<<  " |              IceQueuebes            |\n";
        cout<<  " +-------------------------------------+\n";
        cout<<"\n   ~~ Your go-to Ice Cream Station! ~~\n";
        cout<<"\n\n ___ ";
        cout<<"\n|   |\\    *'      *'          ";
        cout<<"\n|   | |  (  )    (  )          ";
        cout<<"\n|   | |   \\/      \\/         ";
        cout<<"\n| o/| |  \\o/     \\o/          ";
        cout<<"\n|/| | |   |       |       ___ ";
        cout<<"\n|   | |  / \\     / \\     |   |\\";
        cout<<"\n|   | |                  | * | |";
        cout<<"\n| o | |   o       o      |   | |";
        cout<<"\n|/|\\| |  /|\\     /|\\     |___| | ";
        cout<<"\n|   | |  / \\     / \\          \\|  ";
        cout<<"\n|___| |                        ";
        cout<<"\n\\____\\|\n\n                  ";
        displayMenu();
        pauseScreen();

        while (!gameOver)
        {
            startDay();

            while (!customerLine.empty() && !gameOver)
            {
                clearScreen();
                displayStats();
                displayMenu();

                cout<<"\n  ACTIONS:\n\n";
                cout<<"  [1] Serve next customer\n";
                cout<<"  [2] View queue\n";
                cout<<"  [3] Skip customer (they leave angry)\n";
                cout<<"  [4] End day early\n";
                cout<<"  [5] Quit game\n\n";
                cout<<"  Choice: ";
                int choice;
                cin>>choice;
                switch (choice)
                {
                case 1:
                    serveNextCustomer();
                    pauseScreen();
                    break;

                case 2:
                {
                    queue<Customer> temp = customerLine;
                    cout<<"\n  Waiting customers:\n";
                    int pos = 1;
                    while (!temp.empty())
                    {
                        Customer c = temp.front();
                        cout<<"  "<<pos++<<". "<<c.name
                            <<"  (patience: "<<c.patience<<")"
                            <<"  wants: ";
                        for (int i=0; i<c.order.size(); i++)
                        {
                            cout<<c.order[i]<<" | ";
                        }
                        cout<<"\n";
                        temp.pop();
                    }
                    pauseScreen();
                    break;
                }
                case 3:
                    if (!customerLine.empty())
                    {
                        cout<<"  Skipped "<<customerLine.front().name
                            <<". They left furious.\n";
                        customerLine.pop();
                        customersMissed++;
                        decreasePatience();
                    }
                    pauseScreen();
                    break;
                case 4:
                    cout<<"  Ending day early...\n";
                    while (!customerLine.empty())
                    {
                        customersMissed++;
                        customerLine.pop();
                    }
                    break;
                case 5:
                    gameOver = true;
                    endGame();
                    break;
                default:
                    cout<<"  Invalid choice.\n";
                    pauseScreen();
                }
            }
            endDay();
            if (!gameOver)
            {
                pauseScreen();
            }
        }
    }
};

int main()
{
    system("color fc");
    IceQueuebes parlor;
    parlor.run();
    return 0;
}
