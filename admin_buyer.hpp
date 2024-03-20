#include "products_and_store.hpp"
#include<bits/stdc++.h>
using namespace std;

class Administrator{
    Store& store;
    public:
    Administrator(Store& store) : store(store) {}
    bool admin_auth();
    void adminoperations();
    void additems(string&, string& ,int&, double&);
    void deleteitems(string&);
    void displayitems();
};

bool Administrator::admin_auth(){
    a:
    system("CLS");
    string username = "Abhijeet";
    string password = "abhijeet";
    cout << "\n\t\t\t\tEnter Username and Password to continue"<<endl;
    cout<<"\n\t\t\t\tUsername: ";
    string inputUsername;
    cin>>inputUsername;
    cout<<"\t\t\t\tPassword: ";
    string inputPassword;
    
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!inputPassword.empty()) {
                cout << "\b \b";
                inputPassword.pop_back();
            }
        } 
        else {
            cout << '*';
            inputPassword.push_back(ch);
        }
    }
    cout << endl;
    if(inputUsername==username && inputPassword==password){
        cout<<"\n\t\t\t\tWelcome "<<username<<endl;
        cout<<"\t\t\t\tFetching operations..."<<endl;
        sleep(2);
        return true;
    }
    else{
        cout<<"\t\t\t\tIncorrect Username or Password\n";
        cout<<"\t\t\t\t1. Enter again\n\t\t\t\t2. Go back\n";
        cout<<"\t\t\t\tEnter the choice: ";
        int choice;
        cin>>choice;
        if(choice==1){
            goto a;
        }
        else if(choice==2){
            return false;
        }
        else exit(0);
    }
}

void Administrator::adminoperations()
{
    if(!(admin_auth())){
        system("CLS");
        return;
    }
    int choice;
    m:
    system("CLS");
    cout << "\n\t\t\t\tADMINISTRATOR\n";
    cout << "\t\t\t\t1. Add item\n";
    cout << "\t\t\t\t2. Delete item\n";
    cout << "\t\t\t\t3. Display items\n";
    cout << "\t\t\t\t4. Exit\n\n";
    cout << "\t\t\t\tEnter your choice: ";
    cin >> choice;
    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\n\t\t\t\tInvalid input. Please enter an integer." << endl;
        sleep(2);
        goto m;
    }
    switch(choice){
        case 1:{
            s:
            string code;
            string name;
            int quantity;
            double price;
            cout << "\t\t\t\tEnter item code: ";
            cin >> code;
            cout << "\t\t\t\tEnter item name: ";
            cin >> name;
            cout << "\t\t\t\tEnter item quantity: ";
            cin >> quantity;
            cout << "\t\t\t\tEnter item price: ";
            cin >> price;
            additems(code, name, quantity, price);
            cout<<"\n\t\t\t\tDo you want to add more?(y/n)";
            char ch;
            cin>>ch;
            if(ch=='y'|| ch=='Y') goto s;
            
            break;
        }
        case 2:{
            string name;
            cout << "\t\t\t\tEnter the name of the item you want to delete: ";
            cin >> name;
            deleteitems(name);
            break;
        }
        case 3:{
            displayitems();
            char ch;
            cout<<"\n\t\t\t\tPress any key to go back...";
            getch();
            break;
        }
        case 4:{
            exit(0);
        }
        default:{
            cout << "Invalid Entry:D\nEnter again: ";
               
        }
        
    }
    goto m;
    }

void Administrator::additems(string& _c, string& _n, int&_q, double& _p){
    Product newproduct(_c,_n,_q,_p);
    store.products.push_back(newproduct);
    store.saveProductsToFile();
    cout<<"\t\t\t\t\""<<_n<<"\" Added\n";
    
}


void Administrator::deleteitems(string& nam){

    for(auto iter=store.products.begin(); iter!=store.products.end(); iter++){
        if(iter->name==nam){
            int quant;
            cout<<"\t\t\t\tEnter the quantity of "<<nam<<" to be removed: ";
            cin>>quant;
            if(quant < iter->quantity){
                (iter->quantity) -= quant;
                cout<<"\n\t\t\t\t"<<quant<<" units of "<<nam<<" removed from stock...";
            }
            
            else if(quant > iter->quantity ){
                cout<<"\n\t\t\t\tInvalid operation\nReturning back....";
                sleep(2);
                return;
            }

            else {
                store.products.erase(iter);
                cout<<"\t\t\t\t"<<nam<<" removed from the stock successfully...";

            }
            store.saveProductsToFile();
            sleep(2);
            return;
        }
    }
    cout << "\t\t\t\t"<<"No item named "<<nam<<" in the store";
    sleep(2);

}

void Administrator::displayitems(){
    system("CLS");
    cout<<"\t\t\t\t\t\tAVAILABLE ITEMS"<<endl;
    cout<<"\n\t\t\t---------------------------------------------------------------"<<endl;
    cout<<"\t\t\t"<<setw(15)<<left<<"  Code"<<" "
                  <<setw(20)<<left<<"Name"<<" "
                  <<setw(15)<<left<<"Quantity"<<" "
                  <<setw(8)<<left<<"Price"<<endl;
    cout<<"\t\t\t---------------------------------------------------------------"<<endl;
    for(int i=0; i<store.products.size(); i++){
        cout<<"\t\t\t  "<<setw(15)<<left<<store.products[i].code
                      <<setw(20)<<left<<store.products[i].name<<" "
                  <<setw(15)<<left<<store.products[i].quantity<<" "
                  <<setw(8)<<left<<store.products[i].price<<endl;
    }
    cout<<"\t\t\t---------------------------------------------------------------"<<endl;
}


class Buyer{
    public:
    Store& store;
    vector<Product> cart;
    
    Buyer(Store& store) : store(store) {}
    void buyeroperations();
    bool buyer_auth();
    void additemstocart(string&);
    void deleteitemsfromcart(string&);
    void displaycart();
    void display_menu();
};
void Buyer::display_menu(){
    system("CLS");
    cout<<"\t\t\t\t\t\tAVAILABLE ITEMS"<<endl;
    cout<<"\n\t\t\t---------------------------------------------------------------"<<endl;
    cout<<"\t\t\t"<<setw(15)<<left<<"  Code"<<" "
                  <<setw(20)<<left<<"Name"<<" "
                  <<setw(15)<<left<<"Quantity"<<" "
                  <<setw(8)<<left<<"Price"<<endl;
    cout<<"\t\t\t---------------------------------------------------------------"<<endl;
    for(int i=0; i<store.products.size(); i++){
        cout<<"\t\t\t  "<<setw(15)<<left<<store.products[i].code
                  <<setw(20)<<left<<store.products[i].name<<" "
                  <<setw(15)<<left<<store.products[i].quantity<<" "
                  <<setw(8)<<left<<store.products[i].price<<endl;
    }
    cout<<"\t\t\t---------------------------------------------------------------"<<endl;
}
void Buyer::buyeroperations(){
    label:
    display_menu();
    int choice;
    
    cout<<"\n\t\t\t\tWhat would you like to do?";
    cout<<"\n\t\t\t\t1. Buy something";
    cout<<"\n\t\t\t\t2. Delete items from the Cart";
    cout<<"\n\t\t\t\t3. Display your Cart";
    cout<<"\n\t\t\t\t4. Exit";
    cout<<"\n\n\t\t\t\tEnter your choice: ";
    cin>>choice;
    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\n\t\t\t\tInvalid input. Please enter an integer." << endl;
        sleep(2);
        goto label;
    }

    switch(choice){
        case 1:{
            p:
            string name;
            int quantity;
            cout<<"\n\t\t\t\tEnter the name for the item you wanna buy: ";
            cin>>name;
            additemstocart(name);
            display_menu();
            cout << "\n\t\t\t\tDo you wanna buy anything else?(y/n) ";
                char ch;
                cin>>ch;
                if(ch=='y' || ch=='Y') goto p;
            break;
        }
        case 2:{
            string name;
            cout<<"\n\t\t\t\tEnter the name of the item you wanna remove from cart: ";
            cin>>name;
            deleteitemsfromcart(name);
            break;
        }
        case 3:{
            displaycart();
            break;
        }
        case 4:{
            store.saveProductsToFile();
            exit(0);
            break;
        }
        default:{
            cout<<"Invalid Entry :D\n\nEnter again";
            
        }
    }
    goto label;
    
}

void Buyer::additemstocart(string& n){
    for (auto& product : store.products) {
            if (product.name == n) {
                int quantity;
                a:
                cout<<"\t\t\t\tEnter the quantity of "<<n<<" : ";
                cin>>quantity;
                if(quantity > product.quantity){
                    cout<<"\t\t\t\tSorry, we don't have the stock of "<<product.name<<
                    " more than "<<product.quantity<<endl;
                    cout<<"\t\t\t\tSo please, enter valid quantity :D"<<endl<<endl;
                    goto a;
                }
                cart.push_back(product);
                auto iter = cart.end()-1;
                iter->quantity = quantity;
                product.quantity -= quantity;
                
                cout << "\n\t\t\t\tItem added to cart: " << n << endl;
                cout << "\t\t\t\tQuantity: "<< quantity <<endl;
                sleep(2);
                return;
            }
    }
    cout<<"\t\t\t\tSorry, This item is currently not available"<<endl;
    sleep(2);

}

void Buyer::deleteitemsfromcart(string& n){
    for (auto it = cart.begin(); it != cart.end(); ++it) {
            if (it->name == n) {
                
                int q;
                cout<<"\t\t\t\tEnter the quantity to remove: ";
                cin>>q;
                if(q < it->quantity) {
                    (it->quantity)-=q;
                }
                else if(q > it->quantity){
                    cout<<"\t\t\t\tInvalid operation\nReturning back!!! "<<endl;
                    sleep(2);
                    return;
                } 
                else cart.erase(it);
                cout << "\n\t\t\t\tItem deleted from cart: " << n << endl;
                cout << "\t\t\t\tQuantity: "<< q <<endl;
                for(auto& product : store.products){
                    if (product.name == n)
                    product.quantity += q; 

                }
                
                sleep(2);
                return;
            }
    }
        cout<<"\n\t\t\t\tSorry, there is no item named \""<<n<<"\" in the cart"<<endl;
}

void Buyer::displaycart(){
    system("CLS");
    cout<<"\n\t\t\t\t\tCART DETAILS";
    cout<<endl;
    cout<<"\n\t\t\t-------------------------------------------------------------------"<<endl;
    cout<<"\t\t\t"<<setw(15)<<left<<"  Code"<<" "
                  <<setw(20)<<left<<"Name"<<" "
                  <<setw(15)<<left<<"Quantity"<<" "
                  <<setw(8)<<left<<"Amount"<<endl;
    cout<<"\t\t\t-------------------------------------------------------------------"<<endl;
    float sum = 0;
    for(int i=0; i<cart.size(); i++){
        int amount = (cart[i].price)*(cart[i].quantity);
        sum += (float)amount;
        cout<<"\t\t\t  "<<setw(15)<<left<<cart[i].code
                      <<setw(20)<<left<<cart[i].name<<" "
                      <<setw(15)<<left<<cart[i].quantity<<" "
                      <<setw(3)<<left<<cart[i].price<<"*"<<cart[i].quantity<<
                      "="<<amount<<endl;
    }
    cout<<"\t\t\t-------------------------------------------------------------------"<<endl;

    cout<<"\t\t\tTotal payable amount: "<<sum<<endl;
    cout<<"\n\n\t\t\t\t\tPress any key to go back...";
    getch();
    
    
}
