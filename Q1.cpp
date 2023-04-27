// Maham_F_22i-2733_Assignment_4
// cash and carry management system
// instructions for example input at the end
#include <iostream>
#include <ctime>
using namespace std;
struct Product{
    string name;
    int quantity;
    double price;
};
class InventoryManagement{
protected:
    Product *products;
    int size;
public:
    InventoryManagement(int s=0);
    ~InventoryManagement();
    Product get_product(int index);
    void set_product(int index, Product p);
    void set_size(int s);
    int get_size();
    void display();
    void productOrdering();
    void productTake();
    void priceManagement();
};
class PointofSale:public InventoryManagement{
protected:
    Product *cart;
    int cartItems;
    int totalCost;
    string *date;
public:
    PointofSale();
    ~PointofSale();
    Product get_cart(int index);
    void set_cart(int index, Product p);
    string get_date(int index);
    void set_date(int index, string d);
    int get_cartItems();
    void set_cartItems(int c);
    void addToCart();
    void applyDiscounts();
    void issueRefund();
    bool isNull();
};
class ReportingSystem:public PointofSale{
public:
    ReportingSystem();
    ~ReportingSystem();
    void salesReport();
    void inventoryReport();
    void profitReport();
};

// Prototypes
void subMenuInventory(InventoryManagement &I1);
void subMenuPointofSale(PointofSale &P1);
void subMenuReportingSystem(ReportingSystem &R1);


// Inventoey Management System Defined
InventoryManagement::InventoryManagement(int s){
    size = s;
    products = new Product[size];
}
InventoryManagement::~InventoryManagement(){
    delete [] products;
}
Product InventoryManagement::get_product(int index){
    return products[index];
}
void InventoryManagement::set_product(int index, Product p){
    products[index] = p;
}
void InventoryManagement::set_size(int s){
    size = s;
    products = new Product[size];
}
int InventoryManagement::get_size(){
    return size;
}
void InventoryManagement::display(){
    cout<<"\nInventory: "<<endl;
    cout<<"Name, Quantity, Price"<<endl;
    for(int i=0; i<size; i++){
        cout<<"product "<<i+1<<": "<<products[i].name<<", "<<products[i].quantity<<", Rs."<<products[i].price<<endl;
    }
}
void InventoryManagement::productOrdering(){
    for(int i=0;i<size;i++){
        if(products[i].quantity<100){
            cout<<"Stock of "<<products[i].name<<" is low.("<<products[i].quantity<<") Ordering 50 more... "<<endl;
            products[i].quantity+=50;
            cout<<"New Quantity: "<<products[i].quantity<<endl;
        }
        else cout<<"\nEverything is in stock"<<endl;
    }
}
void InventoryManagement::productTake(){
    string productName;
    int index = -1;
    int takenQuantity;
    double takenPrice;
    cout << "\nEnter the name of the product you want to update: ";
    cin >> productName;
    for(int i=0; i<size; i++){
        if(products[i].name == productName){
            index = i;
            break;
        }
    }
    // if the product is found, ask for the quantity and price taken and update the inventory
    if(index != -1){
        cout << "Enter the updated quantity of the product: ";
        cin >> takenQuantity;
        products[index].quantity = takenQuantity;
        cout << "Enter the updated price of the product: ";
        cin >> takenPrice;
        products[index].price = takenPrice;
        cout << "Product inventory successfully updated" << endl;
    }
    else cout << "Product not found in inventory." << endl;
}
void InventoryManagement::priceManagement(){
    cout<<"\nWelcome to the price management system!\n";
    cout<<"What action would you like to perform?\n";
    cout<<"1. Update the price of a product\n";
    cout<<"2. Add a promotional discount to items\n";
    int choice=0;
    cin>>choice;
    switch(choice)
    {
         case 1:{
            string productName;
            int index = -1;
            double newPrice;
            cout << "\nEnter the name of the product you want to update: ";
            cin >> productName;
            for(int i=0; i<size; i++){
                if(products[i].name == productName){
                    index = i;
                    break;
                }
            }
            if(index != -1){
                cout << "Enter the new price: ";
                cin >> newPrice;
                products[index].price = newPrice;
                cout << "Product inventory successfully updated" << endl;
            }
            else cout << "Product not found in inventory." << endl;
            break;
        }
        case 2:{
            cout<<"\nWhat discount would you like to apply?\n";
            cout<<"1. Specific % discount\n";
            cout<<"2. Ramadan Discount (50%)\n";
            cout<<"3. Eid Discount (25%)\n";
            cout<<"4. Specific amount discount\n";
            cout<<"5. Rs. 20 discount on all products\n";
            int choice=0;
            cin>>choice;
            if(choice==1){
                double discount;
                cout<<"Enter the discount percentage: ";
                cin>>discount;
                for(int i=0;i<size;i++){
                    products[i].price = products[i].price - (products[i].price * (discount/100));
                }
                cout<<discount<<"% discount applied successfully!"<<endl;
            }
            else if(choice==2){
                for(int i=0;i<size;i++){
                    products[i].price = products[i].price - (products[i].price * (50/100.0));
                }
                cout<<"50% discount applied successfully!"<<endl;
            }
            else if(choice==3){
                for(int i=0;i<size;i++){
                    products[i].price = products[i].price - (products[i].price * (25/100.0));
                }
                cout<<"25% discount applied successfully!"<<endl;
            }
            else if(choice==4){
                double discount;
                cout<<"Enter the discount amount: ";
                cin>>discount;
                for(int i=0;i<size;i++){
                    products[i].price = products[i].price - discount;
                }
                cout<<"Rs."<<discount<<" discount applied successfully!"<<endl;
            }
            else if(choice==5){
                for(int i=0;i<size;i++){
                    products[i].price = products[i].price - 20;
                }
                cout<<"Rs.20 discount applied successfully!"<<endl;
            }
            else cout<<"Invalid choice!"<<endl;
            break;
        }
        default:{
            cout<<"Invalid choice!"<<endl;
            break;
        }
    }
}

// Point of Sale Defined
PointofSale::PointofSale(){
    totalCost=0;
    cartItems=0;
    cart = nullptr;
    date = nullptr;
}
PointofSale::~PointofSale(){
    delete [] cart;
    delete [] date;
}
Product PointofSale::get_cart(int index){
    return cart[index];
}
void PointofSale::set_cart(int index, Product p){
    cart[index] = p;
}
string PointofSale::get_date(int index){
    return date[index];
}
void PointofSale::set_date(int index, string d){
    date[index] = d;
}
int PointofSale::get_cartItems(){
    return cartItems;
}
void PointofSale::set_cartItems(int c){
    cartItems = c;
    cart = new Product[cartItems];
    date = new string[cartItems];
}

void PointofSale::addToCart(){
    // add to cart
    cout<<"How many items would you like to buy?\n";
    cin>>cartItems;
    cart = new Product[cartItems];
    date = new string[cartItems];
    for(int j=0;j<cartItems;j++){
        // saving the date
        time_t now = time(0);
        date[j] = ctime(&now);
         // update inventory
        string productName;
        int index = -1;
        int takenQuantity;
        // dynmaically allocating  memory of cart based on how many items user wants to buy
        cout << "\nEnter the name of the product you want to buy: ";
        cin >> productName;
        for(int i=0; i<size; i++){
            if(products[i].name == productName){
                index = i;
                cart[j].name = products[i].name;
                break;
            }
        }
        // if the product is found, ask for the quantity and price taken and update the inventory
        if(index != -1){
            cout << "Enter the amount of "<<products[index].name<<" you'd like to buy: ";
            cin >> takenQuantity;
            if(takenQuantity<products[index].quantity){
             products[index].quantity -= takenQuantity;
             cart[j].quantity = takenQuantity;
             cart[j].price = products[index].price;
            }
            else
                cout<<"\nNot enough stock. Only "<<products[index].quantity<<" available."<<endl;
        }
        else cout << "Product not found in inventory." << endl;
    }
        // displaying items in cart
        cout<<"\nItems in cart: "<<endl;
        cout<<"Name, Quantity, Price"<<endl;
        for(int i=0; i<cartItems; i++){
            cout<<"product "<<i+1<<": "<<cart[i].name<<", "<<cart[i].quantity<<", Rs."<<cart[i].price<<" each"<<endl;
            totalCost+=cart[i].price*cart[i].quantity;
            cout<<"Date & Time: "<<date[i]<<endl;
        }
        cout<<"Total: Rs."<<totalCost<<endl;
}
void PointofSale::applyDiscounts(){
    if(cart!=NULL){
        // checking cart if eligible for discount
        cout<<"available discounts: "<<endl;
        cout<<"1. 10% discount on items with quantity of 3 or more"<<endl;
        cout<<"2. 5% discount on total cost if total cost exceeds Rs.1000\n"<<endl;

        // when quantity of item in cart is 3 or more, 10% discount is applied
        int totalLocal=0;
        for(int i=0;i<cartItems;i++){
            if(cart[i].quantity>=3){
                cout<<"You are eligible for a 10% discount on "<<cart[i].name<<endl;
                cout<<"Price before discount: Rs."<<cart[i].price<<endl;
                cart[i].price-=cart[i].price*0.1;
                cout<<"Price after discount: Rs."<<cart[i].price<<endl;
                totalLocal+=cart[i].price*cart[i].quantity;
            }
            else {
                totalLocal=totalCost;
                cout<<"you are not eligible for a 10% discount on "<<cart[i].name<<endl;
            }
        }
    // checking if total cost exceeds 1000, if so, 5% discount is applied
    if(totalCost>=1000){
        cout<<"You are eligible for a 5% discount since the total cost exceeds Rs.1000"<<endl;
        totalLocal-=totalLocal*0.05;
    }
    else {
        cout<<"You are not eligible for a 5% discount since the total cost is less than Rs.1000"<<endl;
    }

        if(totalCost!=totalLocal){
            cout<<"Total before discount: Rs."<<totalCost<<endl;
            cout<<"Total after discount: Rs."<<totalLocal<<endl;
        }
        else cout<<"You're not eligible for any discount. ziada cheezain leni thin\n";
    }
    else cout<<"add items to cart first\n";
}
void PointofSale::issueRefund(){
    // issue refund
    cout<<"What item would you like to return?"<<endl;
    string productNameLocal;
    cin>>productNameLocal;
    for(int i=0;i<cartItems;i++){
        if(cart[i].name==productNameLocal){
            cout<<"Enter the quantity of "<<cart[i].name<<" you would like to return: ";
            int quantityLocal;
            cin>>quantityLocal;
            if(quantityLocal<=cart[i].quantity){
                // updating cart
                cart[i].quantity-=quantityLocal;
                // updating inventory
                products[i].quantity+=quantityLocal;
                cout<<"Refund issued for Rs."<<cart[i].price*quantityLocal<<endl;
            }
            
            else
                cout<<"You can only return "<<cart[i].quantity<<" of "<<cart[i].name<<endl;
        }
        // else cout<<"Item not found in cart"<<endl;
    }
}
bool PointofSale::isNull(){
    if(cart!=nullptr&&date!=nullptr)return false;
    return true;
}
// Reporting System Defined
ReportingSystem::ReportingSystem(){
    cartItems=0;
    // no dynamically allocated stuff
    cout<<"reporting system object created\n";
}
ReportingSystem::~ReportingSystem(){
    // no deallocation
}
void ReportingSystem::salesReport(){
    // sales report
       cout<<"Which view would you like to see?\n";
       cout<<"1. Sales by Product\n";
       cout<<"2. Sales by Date\n";
       cout<<"3. Sales by Customer\n";
       int choice;
       cin>>choice;
       switch(choice){
           case 1:{
               // sales by product
               for(int i=0;i<cartItems;i++){
                   cout<<"product: "<<cart[i].name<<endl;
                   cout<<"quantity sold: "<<cart[i].quantity<<endl;
                   cout<<"price sold at: "<<cart[i].price<<endl;
                   cout<<"_____________________"<<endl;
               }
               break;
           }
           case 2:{
               // sales by date
               for(int i=0;i<cartItems;i++){
                   cout<<"Date: "<<date[i]<<endl;
                   cout<<"product: "<<cart[i].name<<endl;
                   cout<<"quantity sold: "<<cart[i].quantity<<endl;
                   cout<<"price sold at: "<<cart[i].price<<endl;
                   cout<<"_____________________"<<endl;
               }
              
               break;
           }
           case 3:{
               // sales by customer
               cout<<"Items customer 1 bought: "<<endl;
               for(int i=0;i<cartItems;i++){
                   cout<<"product: "<<cart[i].name<<endl;
                   cout<<"quantity bought: "<<cart[i].quantity<<endl;
                   cout<<"price bought at: "<<cart[i].price<<endl;
               }
          
           }
               break;
           default:
               cout<<"Invalid choice. Please try again."<<endl;
       }
   }
void ReportingSystem::inventoryReport(){
    // inventory report
        cout<<"Inventory Report"<<endl;
        cout<<"Product No.\tName\tQuantity Left\tPrice"<<endl;
        for(int i=0;i<size;i++){
            cout<<i+1<<"\t\t\t"<<products[i].name<<"\t\t"<<products[i].quantity<<"\t\t\tRs."<<products[i].price<<endl;
        }
}
void ReportingSystem::profitReport(){
    // profit report
       cout<<"Profit Report"<<endl;
       // each product gives 5% profit
       double totalProfit=0;
       for(int i=0;i<size;i++){
           cout<<"Profit from "<<products[i].name<<": Rs."<<products[i].price*0.05<<endl;
           totalProfit+=products[i].price*0.05;
       }
       cout<<"Total Profit: Rs."<<totalProfit<<endl;
}

int main(){
    // product initialization
    Product p[50] = {
        {"Milk", 10, 100.0}, {"Eggs", 20, 200.0}, {"Bread", 30, 300.0}, {"Donuts", 40, 400.0}, {"Cake", 50, 500.0},
        {"Apples", 10, 100.0}, {"Potatoes", 20, 200.0}, {"Cookies", 30, 300.0}, {"IceCream", 40, 400.0}, {"Yogurt", 50, 500.0},
        {"Chicken", 10, 100.0}, {"Cucumbers", 20, 200.0}, {"Tomatoes", 30, 300.0}, {"Grapes", 40, 400.0}, {"Cheese", 50, 500.0},
        {"Bananas", 10, 100.0}, {"Carrots", 20, 200.0}, {"Lettuce", 30, 300.0}, {"Pineapple", 40, 400.0}, {"Salmon", 50, 500.0},
         {"Oranges", 10, 100.0}, {"Onions", 20, 200.0}, {"Peppers", 30, 300.0}, {"Watermelon", 40, 400.0}, {"Steak", 50, 500.0},
         {"Grapfruit", 10, 100.0}, {"Sweet Potatoes", 20, 200.0}, {"Broccoli", 30, 300.0}, {"Strawberries", 40, 400.0}, {"Shrimp", 50, 500.0},
        {"Pears", 10, 100.0}, {"Garlic", 20, 200.0}, {"Mushrooms", 30, 300.0}, {"Blueberries", 40, 400.0}, {"Crab", 50, 500.0},
        {"Peaches", 10, 100.0}, {"Corn", 20, 200.0}, {"Spinach", 30, 300.0}, {"Raspberries", 40, 400.0}, {"Lobster", 50, 500.0},
        {"Plums", 10, 100.0}, {"Green Beans", 20, 200.0}, {"Cauliflower", 30, 300.0}, {"Blackberries", 40, 400.0}, {"Scallops", 50, 500.0},
         {"Cherries", 10, 100.0}, {"Peas", 20, 200.0}, {"Asparagus", 30, 300.0}, {"Cantaloupe", 40, 400.0}, {"Crab Legs", 50, 500.0},
    };
    // inventory + product w 50 products
    InventoryManagement I1(50);
    PointofSale P1;
    P1.set_size(I1.get_size());
    ReportingSystem R1;
    R1.set_size(I1.get_size());
   
    // assigning products to inventory, point of sale
    for(int i=0; i<I1.get_size(); i++){
        I1.set_product(i,p[i]);
        P1.set_product(i,p[i]);
        R1.set_product(i,p[i]);
    }
   
    // whoMST are you
    int choice=0;
    while(choice!=-1){
    cout<<"Which Module would you like to access?\n";
    cout<<"1. Inventory Manager\n";
    cout<<"2. Point of Sale\n";
    cout<<"3. Report Generator\n";
    cout<<"Enter -1 to exit\n";
    // when -1 is presssed on any menu, items in other objects are automatically updated
        cin>>choice;
        switch(choice){
            case 1:{
                subMenuInventory(I1);
                // aggregation
                for(int i=0;i<50;i++){
                // assigning updated product values incase discount applied
                    P1.set_product(i,I1.get_product(i));
                    R1.set_product(i,I1.get_product(i));
                }
                break;
            }
            case 2:{
                subMenuPointofSale(P1);
                // preparing reporting system object
                R1.set_cartItems(P1.get_cartItems());
              //  R1.set_size(P1.get_size());
                if(P1.isNull()==false){
                    // updating reporting system object
                    for(int i=0;i<P1.get_cartItems();i++){
                        // assignment to the other object
                        R1.set_cart(i,P1.get_cart(i));
                        R1.set_date(i,P1.get_date(i));
                        
                    }
                    
                }
                else cout<<"nothing is in  your cart\n";
                
                break;
            }
            case 3:{
                subMenuReportingSystem(R1);
                break;
            }
            case -1:
                cout<<"\nExiting Progam...\n\n";
                break;
            default:
                cout<<"Invalid choice!\n";
        }
    }
    return 0;
}
void subMenuInventory(InventoryManagement &I1){
   // menu
    int choice=0;
    while(choice!=-1){
    cout<<"\nWelcome to the Inventory Management System!\n";
    cout<<"\nWhat action would you like to perform?\n"<<endl;
    cout<<"1. Product Ordering\n";
    cout<<"2. Product Take\n";
    cout<<"3. Price Management\n";
    cout<<"4. Display Products\n";
    cout<<"Enter -1 to exit\n"<<endl;
    cin>>choice;
        switch(choice){
            case 1:
                I1.productOrdering();
                break;
            case 2:
                I1.productTake();
                break;
            case 3:
                I1.priceManagement();
                break;
            case 4:
                I1.display();
            case -1:
                cout<<"\nExiting Inventory Menu...\n\n";
                break;
            default:
                cout<<"\nInvalid choice\n"<<endl;
        }
    }
}
void subMenuPointofSale(PointofSale &P1){
    // menu
    int choice=0;
    while(choice!=-1){
        cout<<"\nWelcome to the Point of Sale Management System!\n";
        cout<<"\nWhat action would you like to perform?\n"<<endl;
        cout<<"1. Add to cart\n";
        cout<<"2. Apply Discounts\n";
        cout<<"3. Issue refund\n";
        cout<<"4. Display Products\n";
        cout<<"Enter -1 to exit\n"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                P1.addToCart();
                break;
            case 2:
                P1.applyDiscounts();
                break;
            case 3:
                P1.issueRefund();
                break;
            case 4:
                P1.display();
                break;
            case -1:
                cout<<"\nExiting Point of Sale Menu...\n\n";
                break;
            default:
                cout<<"\nInvalid choice\n"<<endl;
        }
    }
}
void subMenuReportingSystem(ReportingSystem &R1){
    int choice=0;
    while(choice!=-1){
    cout<<"what action would you like to perform?"<<endl;
    cout<<"1. Sales Report"<<endl;
    cout<<"2. Inventory Report"<<endl;
    cout<<"3. Profit Report"<<endl;
    cout<<"4. Display Products"<<endl;
    cout<<"Enter -1 to exit"<<endl;
    cin>>choice;
    switch(choice){
        case 1:
            R1.salesReport();
            break;
        case 2:
            R1.inventoryReport();
            break;
        case 3:
            R1.profitReport();
            break;
        case 4:
            R1.display();
            break;
        case -1:
            cout<<"\nExiting Reporting System Menu...\n\n";
            break;
        default:
            cout<<"\nInvalid choice\n"<<endl;
    }
}
}

// EXAMPLE INPUT

// 1 (invetory management)
// 1 (product ordering)
// 2 (product take)
// Peas
// 20 (quantity update)
// 300.0 (price update)
// 3 (price management)
// 1 (update price)
// Cake
// 500
// 4 (display)
// -1 (exit inventory management)

// 2 (point of sale)
// 1 (add to cart)
// 2 (amount of items to buy)
// Bread
// 4
// Eggs
// 12
// 2 (apply discount)
// 3 (issue refund)
// Eggs
// 3
// 4 (display)
// -1 (exit point of sale)

// 3 (report generator)
// 1 (sales report)
// 1 (sales by product)
// 1 (sales report)
// 2 (sales by date)
// 1 (sales report)
// 3 (sales by customer)
// 2 (inventory report)
// 3 (profit report)
// 4 (display products)
// -1 (exit report generator)

// -1 exit program