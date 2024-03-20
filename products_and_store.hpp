#include<bits/stdc++.h>
using namespace std;

class Product {
public:
    string code;
    string name;
    int quantity;
    double price;

    Product(string& c , string& n, int q, double& p){
        code=c;
        name=n;
        quantity=q;
        price = p;
    }
};

class Store{
    public:
    vector<Product> products;

    Store(){
        loadProductsFromFile();

    }

    void loadProductsFromFile(){
        ifstream file("products.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                string code;
                string name;
                int quantity;
                double price;
                istringstream iss(line);
                if (iss >> code >> name >> quantity >> price) {
                    Product product(code, name, quantity, price);
                    products.push_back(product);
                }
            }
            file.close();
            cout << "Products loaded from file: products.txt" << endl;
        } 
        else {
            cout << "Error opening file: products.txt" << endl;
        }
    }

    void saveProductsToFile(){
        sort_the_store();
        ofstream file("products.txt");
        if (file.is_open()) {
            for (const auto& product : products) {
              file << product.code << " " << product.name << " " << product.quantity
              <<" "<< product.price << endl;
            }
            file.close();
            cout << "\n\t\t\t\tData Updation!!!" << endl;
        } else {
            cout << "Error opening file: products.txt" << endl;
        }
    }

    void sort_the_store(){
        int n = products.size();
        
        for(int i=0; i<n-1; i++){
            bool swapped = false;
            for(int j=0; j<n-i-1; j++){

                if((products[j].code) > (products[j+1].code)){
                    Product temp_ = products[j];
                    products[j] = products[j+1];
                    products[j+1] = temp_;
                    swapped = true;
                }
            }
            if(!swapped) break;
            
        }
    }
    
};

