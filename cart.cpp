#include <iostream>
#include <string>
#include <vector>

using namespace std;

//item structure
struct Item {
    string name;
    int price;
    int quantity;
};

//function declarations
void displayCart(const vector<Item>& cart);
void checkout(vector<Item>& cart);
void addItem(vector<Item>& cart, const vector<Item>& catalog);
void clearCart(vector<Item>& cart);
void removeItem(vector<Item>& cart);

int main() {
    bool closeCart = false;
    int decision;
    //The user's cart
    vector<Item> cart = {};
    //The product cataog the user can pick from
    vector<Item> catalog = {
        {"HP legion", 1000, 1},
        {"Rolex", 2000, 1},
        {"Iphone 17 air", 3000, 1},
        {"Men chain set", 150, 1},
        {"Burkin Bag", 10000, 1},
        {"Durag", 50, 1},
        {"Oraimo 20000MaH powerbank", 70, 1},
        {"LED light strip", 15, 1}
    };

    while(closeCart != true) {
        displayCart(cart);
        cout << "\nwhat would you like to carry out in your cart??" << endl;
        cout << "1. Checkout \n2. clear cart \n3. add item to cart \n4. remove an item from cart \n5. exit cart" << endl;
        cin >> decision;
        if(decision < 1 || decision > 5) {
            cout << "invalid option" << endl;
        }
        else {
            switch (decision)
            {
            case 1:
                checkout(cart);
                break;
            case 2:
                clearCart(cart);
                break;
            case 3:
                addItem(cart, catalog);
                break;
            case 4:
                removeItem(cart);
                break;
            case 5:
                cout << "cart exited" << endl;
                closeCart = true;
                break;
            default:
                break;
            }
        }

    }

    return 0;
};

//Function definitions

void displayCart (const vector<Item>& cart) {
    cout << "========= Cart =========" << endl;
    if (cart.size() != 0){

            //loop and render the cart if anything is in the cart
            for (int i = 0; i < cart.size(); i++)
            {
                cout << "\n" << i+1 << ". " << cart[i].name << " - " << cart[i].quantity << " pcs" << " - $" << cart[i].price * cart[i].quantity ;
                
            }         
        } else {
            cout << "\ncart is empty" << endl;
        }
    cout << "\n=========================" << endl;
};

void checkout (vector<Item>& cart) {
    int decision;
    cout << "Proceed to checkout ??\n1. yes\n2. no" << endl;
    cin >> decision;
    if (decision == 1)
    {
        if (cart.size() != 0)
        {
            int totalPrice;
            totalPrice = 0;
            for (int i = 0; i < cart.size(); i++)
            {
                totalPrice += cart[i].price * cart[i].quantity;
            }
            cout << "Pay $" << totalPrice << " ?\n1. yes\n2. no" << endl;
            cin >> decision;
            if (decision == 1)
            {
                cout << "$" << totalPrice << " paid successfully" << endl;
                cart.clear();
                totalPrice = 0;
            }
            else if (decision == 2)
            {
                return;
            }
            else
            {
                cout << "invalid operation" << endl;
                return;
            }
        }
        else
        {
            cout << "cart is empty" << endl;
        }
    }
    else if (decision == 2)
    {
        return;
    }
    else
    {
        cout << "invalid operation" << endl;
    }
};

void clearCart (vector<Item>& cart) {
    if (cart.size() != 0)
    {
        int decision;
        cout << "By proceeding, you will remove all items from your cart. Proceed?\n1. yes\n2. no" << endl;
        cin >> decision;
        if (decision == 1)
        {
            cout << "You have successfully cleared your cart" << endl;
            cart.clear();
        }
        else if (decision == 2)
        {
            return;
        }
        else
        {
            cout << "invalid option" << endl;
            return;
        }
    }
    else
    {
        cout << "cart is empty" << endl;
    };
};

void addItem (vector<Item>& cart, const vector<Item>& catalog) {
    bool doneAdding = false;
    int decision;
    while (doneAdding != true)
    {
        cout << "======= Catalog ======" << endl;
        for (int i = 0; i < catalog.size(); i++)
        {
            cout << i + 1 << ". " << catalog[i].name << " - $" << catalog[i].price << "\n";
        }
        cout << "======================\n";
        cin >> decision;
        if (decision >= 1 && decision <= (int)catalog.size())
        {
            bool inCart = false;
            for (int i; i < cart.size(); i++)
            {
                if (cart[i].name == catalog[decision - 1].name)
                {
                    cart[i].quantity++;
                    inCart = true;
                    break;
                }
            }
            if (!inCart)
            {
                cart.push_back(catalog[decision - 1]);
            }
            cout << "Is that all??\n1. No, add more\n2. yes" << endl;
            cin >> decision;
            if (decision == 1)
            {
                continue;
            }
            else if (decision == 2)
            {
                doneAdding = true;
                break;
            }
            else
            {
                cout << "invalid option" << endl;
                break;
            }
        }
        else
        {
            cout << "No such item" << endl;
            break;
        }
    }
};

void removeItem (vector<Item>& cart) {
    int decision;
    if (cart.size() != 0)
    {
        cout << "What item would you like to remove from the cart?" << endl;
        for (int i = 0; i < cart.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ". " << cart[i].name << " - " << cart[i].quantity << " pcs" << " - $" << cart[i].price * cart[i].quantity;
        }
        cin >> decision;
        if (decision >= 1 && decision <= cart.size())
        {
            cout << cart[decision - 1].name << " has been removed from your cart" << endl;
            cart.erase(cart.begin() + decision - 1);
        }
        else
        {
            cout << "invalid option" << endl;
        }
    }
    else
    {
        cout << "cart is empty" << endl;
    }
};