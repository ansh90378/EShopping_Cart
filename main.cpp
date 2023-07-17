#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//Forword Declaration
class Item;
class cart;

class Product
{
    int id;
    string name;
    int price;

public:
    Product()
    {

    }
    Product(int u_id, string name, int price)
    {
        id = u_id;
        this->name = name;
        this->price = price;
    }
    string getDisplayName()
    {
        return name + " : Rs " + to_string(price) + "\n";
    }
    string getShortName()
    {
        return name.substr(0,1);
    }
    friend class Item;
    friend class cart;
};

vector<Product> allProducts = {
    Product(1,"apple",26),
    Product(3,"mango",16),
    Product(2,"guava",36),
    Product(5,"banana",56),
    Product(4,"pineapple",25)
};

class Item
{
    Product product;
    int quentity;

public:
    Item(){}
    //constructor using a Init List
    Item(Product p, int q):product(p), quentity(q){}

    int getItemPrice()
    {
        return quentity * product.price;
    }
    string getItemInfo()
    {
        return '\n' + to_string(quentity) + " x " + product.name + " Rs. " + to_string(quentity * product.price);
    }
    friend class cart;
};

class cart
{
    // Collection
    unordered_map<int,Item> items;

public:
    void addProduct(Product product)
    {
        if(items.count(product.id) == 0)
        {
            Item newItem(product,1);
            items[product.id] = newItem;
        }
        else
        {
            items[product.id].quentity += 1;
        }
    }

    int getTotal()
    {
        int total = 0;
        for(auto itemPair : items)
        {
            auto item = itemPair.second;
            total += item.getItemPrice();
        }
        return total;
    }

    string viewCart()
    {
        if(items.empty())
        {
            return "Cart is empty";
        }

        string itemizedList;
        int cart_total = getTotal();

        for(auto itemPair : items)
        {
            auto item = itemPair.second;
            itemizedList.append(item.getItemInfo());
        }

        return '\n' + itemizedList + '\n' + " Total Amount : Rs. " + to_string(cart_total) + '\n';
    }

    bool isEmpty()
    {
        return items.empty();
    }
};

Product* chooseProduct()
{
    //Display the list products
    string productList;
    cout<<"Available Products"<<endl;

    for(auto Product : allProducts)
    {
        productList.append(Product.getDisplayName());
    }
    cout<<productList<<endl;

    cout<<"------------------"<<endl;
    string choice;
    cin>>choice;

    for(int i=0; i<allProducts.size(); i++)
    {
        if(allProducts[i].getShortName() == choice)
        {
            return &allProducts[i];
        }


    }
    cout<<"Product not found!"<<endl;
    return NULL;
}

bool chechout(cart &cart)
{
    if(cart.isEmpty())
    {
        return false;
    }
    int total = cart.getTotal();
    cout<<"Pay in Cash"<<endl;
    int paid;
    cin>>paid;

    if(paid >= total)
    {
        cout<<"Change "<<paid-total<<endl;
        cout<<"Thank you for shopping!";
        return true;
    }
    else
    {
        cout<<"Not enough cash!";
        return false;
    }
}

int main()
{
    char action;
    cart cart;
    while(true)
    {
        cout<<"Select an action - (a)dd item, (v)iew cart, (c)heckout"<<endl;
        cin>>action;

        if(action == 'a')
        {
            //Todo:: Add to cart
            //View All Product + Choose Product + Add to Cart
            Product * product = chooseProduct();
            if(product != NULL)
            {
                cout<<"Added to the Cart "<<product->getDisplayName()<<endl;
                cart.addProduct(*product);
            }
        }
        else if(action == 'v')
        {
            //View the cart
            cout<<"________________"<<endl;
            cout<<cart.viewCart();
            cout<<"________________"<<endl;
        }
        else
        {
            //Checkout
            cart.viewCart();
            if(chechout(cart))
            {
                break;
            }
        }
    }
    return 0;
}
