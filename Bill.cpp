//*******************************************************
//	             INCLUDED HEADER FILES
//*******************************************************

#include <iostream>
#include <fstream>
#include<string>

using namespace std;
int main();
//*******************************************************
//	           STRUCTURE NAME : ITEM
//*******************************************************

int itemID;
struct Item{
	int id;
	string name;
	string size;
	string color;
	int price;
	int number;
};

//*******************************************************
//	          STRUCTURE NAME : BILL
//*******************************************************

int billID;
struct Bill{
    int id;
    string name;
    string address;
    string billerName;
    Item item;
};

//*****************************************************************
//	ITEM FUNCTIONS : MENU , ADD , LIST , SEARCH , MODIFY , DELETE
//*****************************************************************

void itemMenu();
void addItem();
void listItem();
int searchItem();
void modifyItem();
void deleteItem();

//------------------------- ITEM MENU -----------------------------
void itemMenu(){
	
	ifstream fr;
    fr.open("itemID.txt");  //Set item ID
    if (!fr.fail()) {
        fr >> itemID;
    }
    else {
        itemID = 0;
    }
    fr.close();
    
    int choice;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
	while (true) {
		cout << "------------------------------------------------------------------------------\n";
		cout << "\t\t    *  ITEM  *" << endl;                  //             *  ITEM  *
        cout << "\t1.Add\t\t2.List\t\t3.Search" << endl;       //   1.Add       2.List      3.Search
        cout << "\t4.Modify\t5.Delete\t6.Back" << endl;        //   4.Modify    5.Delete    6.Back
    	do {
        	try {  //Exception Choice
        		cout << "Enter choice : ";
				cin >> choice ;
				aux = true;
        		switch (choice) {
        			case 1:
            			addItem();		//Add
            			break;
        			case 2:
            			listItem();		//List
            			break;
        			case 3:
            			searchItem();	//Search
            			break;
        			case 4:
            			modifyItem();	//Modify
            			break;
        			case 5:
            			deleteItem();	//Modify
            			break;
        			case 6:
        				main();			//Back
        				break;
        			default:
        				throw choice;	//Exception
        				itemMenu();		
        				break;
        		}
        	}catch (std::ios_base::failure &fail) {   //Exception: String.
            	aux = false;
            	cout << "Exception: String." << endl; 
				cout << "\tPlease insert an integer number in option." << endl;
            	cin.clear();
            	std::string tmp;
            	getline(cin, tmp);
        	}catch (int e1){						 //Exception: No such option.
				aux = false;			
        		cout << "Exception: \"" << e1 <<  "\"  No such option." << endl;
        		cout << "\tPlease insert a valid option." << endl;
        		cin.clear();
            	std::string tmp;
            	getline(cin, tmp);
    		}
    		
    	} while (aux == false);
    }
    
}

//------------------------- ADD ITEM -----------------------------

void addItem() { 
	//Get item data
    Item item;
    cout << "\t\t    --  Add Item  --" << endl;  
    cout << "\tEnter Name : ";
    cin.get();
    getline(cin, item.name); 
    cout << "\tEnter Size : ";
    getline(cin, item.size); 
    cout << "\tEnter Color : ";
    getline(cin, item.color); 
    
    bool aux = true;
    	cin.exceptions(std::istream::failbit);
        do {	        
        	try {
        		cout << "\tEnter Price : ";
    			cin >> item.price;
				aux = true;
        		if(item.price > 0){
        			itemID++;
					//Write item data to item.txt
    				ofstream fw;
    				fw.open("item.txt", ios::app);     
    				fw << "\n" << itemID;
    				fw << "\n" << item.name ;
    				fw << "\n" << item.size ;
    				fw << "\n" << item.color ;
    				fw << "\n" << item.price ;
    				fw.close();
    				fw.open("itemID.txt");
    				fw << itemID;
    				fw.close();
    				cout << "\tData save to file" << endl;
				}else{
        			throw item.price;  //Exception
				}
        	}catch (std::ios_base::failure &fail) {   // Exception: String
            	aux = false;
            	cout << "Exception: String.\n"; 
				cout << "\tPlease insert an integer number in option." << endl;
            	cin.clear();
            	std::string tmp;
            	getline(cin, tmp);
        	}catch (int e1){			              // Exception: Negative Number
        		aux = false;
        		cout << "Exception: \"" << e1 <<  "\"  is ";
        		if (e1==0){
        			cout << "Exception: \"" << e1 <<  "\"  is zero number." << endl;
				}else{
					cout << "Exception: \"" << e1 <<  "\"  is negative number." << endl;
				}
        		cout << "\tPlease insert a positive integer number." << endl;
        		cin.clear();
            	std::string tmp;
            	getline(cin, tmp);
    		}
    	} while (aux == false);
    
}

//------------------------- SHOW ITEM -----------------------------

void listItem(){
	
	Item item;
    ifstream fr;
    fr.open("item.txt");         
    if(!fr){        // No file      
      cout<<"\t!!!!  No Item Information.  !!!!" << endl;  
	  fr.close();      
      itemMenu();  // back to menu
   	}
   	cout << "\t\t    --  List Item  --" << endl;
    cout << "\tID\tName\tSize\tColor\tPrice" << endl;
    while (!fr.eof()) {      
        fr >> item.id;
        if(item.id<=0){   // No item
   			cout<<"\t!!!!  No Item Information.  !!!!" << endl;  
   			fr.close();
    		itemMenu();  // back to menu
		}
        fr.ignore();
        getline(fr, item.name);   
        getline(fr, item.size);
        getline(fr, item.color);
        fr >> item.price;
        // Get item data to print    ID   Name   Size   Color   Price
        cout << "\t" << item.id << "\t" << item.name << "\t" << item.size;
		cout << "\t" << item.color << "\t" << item.price << endl;
		ofstream fw;
		fw.open("itemID.txt");
    	fw << item.id;
    	fw.close();
    }
    fr.close();
    
}

//------------------------- SEARCH ITEM -----------------------------

int searchItem() {
	
    int id;
    Item item;
    cout << "\n\tEnter Item ID want to search : ";
    cin >> id;
    
    ifstream fr;
    fr.open("item.txt");
    if(!fr){          // No file
      cout<<"\t!!!!  This ID does not exist.  !!!!\n";
      fr.close();
      itemMenu();    // back to menu
   	}
    while (!fr.eof()) {
        fr >> item.id;
        fr.ignore();
        getline(fr, item.name);
        getline(fr, item.size);
        getline(fr, item.color);
        fr >> item.price;
        // Get item data to print
        if (item.id == id) { 
        	cout << "\t====  Data Item  ====\n";
        	cout << "\tID : " << item.id << endl;
        	cout << "\tName : " << item.name << endl;
        	cout << "\tSize : " << item.size << endl;
        	cout << "\tColor : " << item.color << endl;
        	cout << "\tPrice : " << item.price << endl;
            return id;
        }
    }
    fr.close();
    // No item
    cout<<"\t!!!!  This ID does not exist.  !!!!\n";
    itemMenu(); // back to menu
}

//------------------------- MODIFY ITEM -----------------------------

void modifyItem(){
	cout << "\t\t   --  Modify Item  --";
    int id = searchItem();
    
    Item newItem;
    // Get New Item Data
    cout << "\n\tEnter Name : ";
    cin.get();
    getline(cin, newItem.name); 
    cout << "\n\tEnter Size : ";
    getline(cin, newItem.size); 
    cout << "\n\tEnter Color : ";
    getline(cin, newItem.color); 
    cout << "\n\tEnter Price : ";
    cin >> newItem.price;
    
    cout << "\n\tYou want to modify record (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y') { 
        Item item;
        ofstream fTemp;
        fTemp.open("temp.txt");
        ifstream fr;
        fr.open("item.txt");
        // Copy Item Data from item.txt to temp.txt
        while (!fr.eof()) {
            fr >> item.id;
            fr.ignore();
            getline(fr, item.name);
            getline(fr, item.size);
            getline(fr, item.color);
            fr >> item.price;
            if(item.id != id){
                fTemp << "\n" << item.id;
                fTemp << "\n" << item.name;
                fTemp << "\n" << item.size;
                fTemp << "\n" << item.color;
                fTemp << "\n" << item.price;
            }else{ // Replace with new item data of id
                fTemp << "\n" << item.id;
                fTemp << "\n" << newItem.name;
                fTemp << "\n" << newItem.size;
                fTemp << "\n" << newItem.color;
                fTemp << "\n" << newItem.price;
            }
        }
        fr.close();
        fTemp.close();
        // Remove and Rename file after copying is complete. 
        remove("item.txt");
        rename("temp.txt", "item.txt");
        cout << "\n\tData modified successfuly" << endl;
    }else{
        cout << "\n\tRecord not modified" << endl;
    }
    
}

//------------------------- DELETE ITEM -----------------------------

void deleteItem(){
	
	cout << "\t\t\tDelete Item";
    int id = searchItem();
    cout << "\n\tYou want to delete record (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        Item item;
        ofstream fTemp;
        fTemp.open("temp.txt");
        ifstream fr;
        fr.open("item.txt");
        // Copy item data from item.txt to temp.txt
        while (!fr.eof()) {
            fr >> item.id;
            fr.ignore();
            getline(fr, item.name);
            getline(fr, item.size);
            getline(fr, item.color);
            fr >> item.price;
            //Copy without current id (delete)
            if (item.id != id) { 
                fTemp << "\n" << item.id;
                fTemp << "\n" << item.name;
                fTemp << "\n" << item.size;
                fTemp << "\n" << item.color;
                fTemp << "\n" << item.price;
            }
        }
        fr.close();
        fTemp.close();
        // Remove and Rename file after copying is complete.
        remove("item.txt");
        rename("temp.txt", "item.txt");
        cout << "\n\tData deleted successfuly\n";
        
    }else{
        cout << "\n\tRecord not deleted\n";
    }
    
}

//*****************************************************************
//	BILL FUNCTIONS : MENU , ADD , LIST , SEARCH , MODIFY , DELETE
//*****************************************************************

void billMenu();
void addBill();
void listBill();
int searchBill();
void modifyBill();
void deleteBill();

//*****************************************************************
//	       ADD ITEM TO BILL AND SHOW ITEM IN BILL FUNCTIONS 
//*****************************************************************

void add_Item_to_Bill(int id);
void show_Item_in_Bill(int id);

//------------------- ADD ITEM TO BILL -----------------------------

void add_Item_to_Bill(int id){
	
	cout << "\n\t* Please enter the required number of items. *" << endl;
	cout << "\t* If you don't want it, Enter the number zero. *" << endl;
	
	Bill bill;
	Item item;
    ifstream fr;
    fr.open("item.txt");
    if(!fr){    // No file
      cout<<"\t!!!!  No Item Information.  !!!!" << endl;
      cout<<"Please add an item to the item mode." << endl;
      fr.close();
      main();   //back to main menu
   	}
   	cout << "\t\t    --  Item List  --" << endl;
    while (!fr.eof()) {
    	//Get item data
        fr >> item.id;
        if(item.id<=0){    // No item
   			cout<<"\t!!!!  No Item Information.  !!!!" << endl;
    		cout<<"\tPlease add an item to the item mode." << endl;
    		fr.close();
      		main();		   //back to main menu
		}
        fr.ignore();
        getline(fr, item.name);
        getline(fr, item.size);
        getline(fr, item.color);
        fr >> item.price;
        cout << "\t\tID: " << item.id << "\t\tName: " << item.name << endl;
        cout << "\t\tSize: " << item.size << "\tColor: " << item.color << endl;
        cout << "\t\tPrice: " << item.price << endl;
        
    	bool aux = true;
    	cin.exceptions(std::istream::failbit);
        do {	        
        	try {
        		cout << "\tEnter number of " << item.name << ": ";
        		cin >> bill.item.number;
				aux = true;
        		if(bill.item.number > 0){
        			//Write ItemInBill.txt (Bill ID , Item ID ,Number of Item)
					ofstream fw;
    				fw.open("ItemInBill.txt", ios::app);
    				fw << "\n" << id;
    				fw << "\n" << item.id ;
    				fw << "\n" << bill.item.number ;
    				fw.close();
    				cout << item.name << " was added to your bill." << endl;
    			}else if(bill.item.number == 0){
    				cout << item.name << " is not added to the bill." << endl;
				}else{
        			throw bill.item.number;  //Exception
				}
        	}catch (std::ios_base::failure &fail) {   // Exception: String
            	aux = false;
            	cout << "Exception: String.\n"; 
				cout << "\tPlease insert an integer number in option." << endl;
            	cin.clear();
            	std::string tmp;
            	getline(cin, tmp);
        	}catch (int e1){			              // Exception: Negative Number
        		aux = false;
        		cout << "Exception: \"" << e1 <<  "\"  is negative number." << endl;
        		cout << "\tPlease insert a positive integer number." << endl;
        		cin.clear();
            	std::string tmp;
            	getline(cin, tmp);
    		}
    	} while (aux == false);
    }
    fr.close();
}

//----------------------- SHOW ITEM IN BILL ---------------------------

void show_Item_in_Bill(int id){
	
	cout << "\t_______________________________________________________________" << endl;
	cout << "\t\t\t\t*  Item List  *" << endl;
    cout << "\tID\tName\tSize\tColor\t(Price x Number)\tResult" << endl;
    
    int total = 0;
	Bill bill;
	Item item;
	ifstream frItem,frList;
	frList.open("ItemInBill.txt");
    while (!frList.eof()) {
        frList >> bill.id;
        frList >> bill.item.id;
        frList >> bill.item.number;
        if (bill.id == id) {   
        	frItem.open("item.txt");
        	while (!frItem.eof()) {
        		//Get item data
        		frItem >> item.id;
        		frItem.ignore();
        		getline(frItem, item.name);
        		getline(frItem, item.size);
        		getline(frItem, item.color);
        		frItem >> item.price;
        		//Item of Bill
        		if (item.id == bill.item.id) {
        			//  >>  ID   Name   Size   Color   (Price x Number)   Result  <<
        			cout << "\t" << item.id << "\t" << item.name << "\t" << item.size << "\t";
					cout << item.color << "\t     " << item.price << " x " << bill.item.number;
					cout << "\t=\t" << item.price*bill.item.number << " BTH." << endl;
					total+=item.price*bill.item.number;
        		}
    		}
        	frItem.close();
        }
    }
    cout << "\tTotal _________________________________________________ " << total << " BTH."<< endl;
    frList.close();
}

//------------------------- BILL MENU -----------------------------

void billMenu(){
	
	ifstream fr;
    fr.open("billID.txt");
    if (!fr.fail()) {	//Set Bill ID
        fr >> billID;
    } else {
        billID = 0;
    }
    fr.close();
    
    int choice;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
	while (true) {
		cout << "------------------------------------------------------------------------------\n";
		cout << "\t\t    *  BILL  *\n";                     //        *  BILL  *
        cout << "\t1.Add\t\t2.List\t\t3.Search\n";          //  1.Add     2.List     3.Search
        cout << "\t4.Modify\t5.Delete\t6.Back\n";           //  4.Modify  5.Delete   6.Back
		do {
        	try {
        		cout << "Enter choice : ";
				cin >> choice ;
				aux = true;
        		switch (choice) {
        			case 1:
            			addBill();		//Add
            			break;
        			case 2:
            			listBill();		//List
            			break;
        			case 3:
            			searchBill();	//Search
            			break;
        			case 4:
            			modifyBill();	//Modify
            			break;
        			case 5:
            			deleteBill();	//Delete
            			break;
        			case 6:
        				main();			//Back
        				break;
        			default:
        				throw choice;	//Exception
        				itemMenu();
        				break;
        		}
        	}catch (std::ios_base::failure &fail) {		//Exception: String
            	aux = false;
            	cout << "Exception: String.\n"; 
				cout << "\tPlease insert an integer number in option." << endl;
            	cin.clear();
            	std::string tmp;
            	getline(cin, tmp);
        	}catch (int e1){							//Exception: No such option
				aux = false;
        		cout << "Exception: \"" << e1 <<  "\"  No such option.\n";
        		cout << "\tPlease insert a valid option." << endl;
        		cin.clear();
            	std::string tmp;
            	getline(cin, tmp);
    		}
    	} while (aux == false);
    }
}

//------------------------- ADD BILL -----------------------------

void addBill() {
	ifstream fr;
	fr.open("item.txt");
    if(!fr){	// No item for create bill
   		cout<<"\t!!!!  No Item Information.  !!!!" << endl;
    	cout<<"\tPlease add an item to the item mode before add bill data." << endl;
    	fr.close();
      	main();		//Back to main menu
	}
    fr.close();
	//Create New Bill
	cout << "\t\t\t--  Add Bill  --" << endl;
    Bill bill;
    cout << "\n\tEnter Customer Name : ";
    cin.get();
    getline(cin, bill.name); 
    cout << "\tEnter Customer Address : ";
    getline(cin, bill.address); 
    cout << "\tEnter Biller Name : ";
    getline(cin, bill.billerName); 
    billID++;
    //Write Bill data to bill.txt
    ofstream fw;
    fw.open("bill.txt", ios::app);
    fw << "\n" << billID;
    fw << "\n" << bill.name ;
    fw << "\n" << bill.address ;
    fw << "\n" << bill.billerName ;
    fw.close();
    fw.open("billID.txt");
    fw << billID;
    fw.close();
    add_Item_to_Bill(billID);	//Add Item to Bill
    cout << "\tRecord the bill successfully.\n";
    
}

//------------------------- SHOW BILL -----------------------------

void listBill() {
	
    Bill bill;
    ifstream fr;
    fr.open("bill.txt");
    if(!fr){		//No file
    	cout <<"\t!!!!  No Bill Information.  !!!!" << endl;
    	fr.close();
    	billMenu();	//Back to menu
   	}
   	cout << "\t\t\t--  List Bill  --\n";
    cout << "\tID\tName\t\tAddress\tBiller Name" << endl;
    //Get bill data
    while (!fr.eof()) {
        fr >> bill.id;
        if(bill.id<=0){	//No bill data
   			cout<<"\t!!!!  No Bill Information.  !!!!" << endl;
   			fr.close();
    		billMenu();	//Back to menu
		}
        fr.ignore();
        getline(fr, bill.name);
        getline(fr, bill.address);
        getline(fr, bill.billerName);
        //Print List Bill Data >>  ID   Name   Address    Biller Name  <<
        cout << "\t" << bill.id << "\t" << bill.name << "\t\t" << bill.address << "\t" << bill.billerName << endl;
    }
    fr.close();
    
}

//------------------------- SEARCH BILL -----------------------------

int searchBill() {
	
	int id;
    cout << "\n\tEnter Bill ID want to search : ";
    cin >> id;
    Bill bill;
    ifstream fr;
    fr.open("bill.txt");
    if(!fr){		 // No file
      cout<<"\t!!!!  This ID does not exist.  !!!!" << endl;
      fr.close();
      billMenu();	//Back to menu
   	}
   	// Get Bill Data of ID
    while (!fr.eof()) {
        fr >> bill.id;
        fr.ignore();
        getline(fr, bill.name);
        getline(fr, bill.address);
        getline(fr, bill.billerName);
        if (bill.id == id) {
            cout << "\t\t\t\t====  Bill Data  ====" << endl;
        	cout << "\tID: " << bill.id << "\t\t\tBiller Name: " << bill.billerName << endl;
        	cout << "\tCustomer Name: " << bill.name << "\tCustomer Address: " << bill.address << endl;
        	fr.close();
        	show_Item_in_Bill(id);	//Show Item in Bill of ID
            return id;
        }
    }
    fr.close();
    //No Bill
    cout << "\t!!!! This ID does not exist. !!!!" << endl;	
    billMenu();
    
}

//------------------------- MODIFY BILL -----------------------------

void modifyBill() {
	
    int id = searchBill();
    Bill newBill;
    //Get New Bill Data
    cout << "\t\t   --  Modify Bill  --";
    cout << "\n\tEnter Customer Name : ";
    cin.get();
    getline(cin, newBill.name);
    cout << "\n\tEnter Customer Address : ";
    getline(cin, newBill.address);
    cout << "\n\tEnter Biller Name : ";
    getline(cin, newBill.billerName); 
    cout << "\n\tYou want to modify record (y/n) : ";
    char choice;
    cin >> choice;
    
    if (choice == 'y') {
		// Copy Bill Data from bill.txt to temp.txt	
        Bill bill;
        ofstream fTemp;
        fTemp.open("temp.txt");
        ifstream fr;
        fr.open("bill.txt");
        while (!fr.eof()) {
            fr >> bill.id;
            fr.ignore();
            getline(fr, bill.name);
            getline(fr, bill.address);
            getline(fr, bill.billerName);
            if (bill.id != id) {
                fTemp << "\n" << bill.id;
                fTemp << "\n" << bill.name;
                fTemp << "\n" << bill.address;
                fTemp << "\n" << bill.billerName;
            } else {	// Replace with New Bill Data of ID
                fTemp << "\n"<< bill.id;
                fTemp << "\n" << newBill.name;
                fTemp << "\n" << newBill.address;
                fTemp << "\n" << newBill.billerName;
            }
        }
        fr.close();
        fTemp.close();
        // Remove and Rename file after copying is complete.
        remove("bill.txt");
        rename("temp.txt", "bill.txt");
        cout << "\n\tData modified successfuly." << endl;
    }
    else {
        cout << "\n\tRecord not modified." << endl;
    }
    
}

//------------------------- DELETE BILL -----------------------------

void deleteBill() {
	
    int id = searchBill();
    cout << "\t\t\tDelete Bill";
    cout << "\n\tYou want to delete record (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
    	// Copy Bill Data from bill.txt to temp.txt  
        Bill bill;
        ofstream fTemp;
        fTemp.open("temp.txt");
        ifstream fr;
        fr.open("bill.txt");
        while (!fr.eof()) {
            fr >> bill.id;
            fr.ignore();
            getline(fr, bill.name);
            getline(fr, bill.address);
            getline(fr, bill.billerName);
            //Copy without current id (delete)
            if (bill.id != id) {
                fTemp << "\n" << bill.id;
                fTemp << "\n" << bill.name;
                fTemp << "\n" << bill.address;
                fTemp << "\n" << bill.billerName;
            }
        }
        fr.close();
        fTemp.close();
        // Remove and Rename file after copying is complete.
        remove("bill.txt");
        rename("temp.txt", "bill.txt");

		ofstream fTemp1;
        fTemp1.open("temp1.txt");
        ifstream frb;
        frb.open("ItemInBill.txt");
        // Copy Item in Bill Data from ItemInBill.txt to temp1.txt  
        while (!frb.eof()) {
            frb >> bill.id;
            frb >> bill.item.id;
            frb >> bill.item.number;
            //Copy without current id (delete)
            if (bill.id != id) {
                fTemp1 << "\n" << bill.id;
                fTemp1 << "\n" << bill.item.id;
                fTemp1 << "\n" << bill.item.number;
            }
        }
        frb.close();
        fTemp1.close();
        // Remove and Rename file after copying is complete.
        remove("ItemInBill.txt");
        rename("temp1.txt", "ItemInBill.txt");
    
        cout << "\n\tData deleted successfuly." << endl;
        
    }
    else {
        cout << "\n\tRecord not deleted." << endl;
    }
    
}

//------------------------- MAIN -----------------------------
//                     BILL SYSTEM
//            1.BILL     2.ITEM      3.EXIT

int main(){
	
	cout << "*****************************************************\n";
	cout << "\t\t=================\n";
	cout << "\t\t|| BILL SYSTEM ||\n";
	cout << "\t\t=================\n";
	cout << "\t1.BILL\t\t2.ITEM\t\t3.EXIT" << endl;
	
	int choice;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {
        	cout << "Enter choice : ";
			cin >> choice ;
			aux = true;
        	if(choice==1){        	// BILL
        		billMenu();
			}else if(choice==2){  	// ITEM
				itemMenu();
			}else if(choice==3){  	// EXIT
				cout << "End Program.\n";
			}else{     
            	throw choice;		//Exception
			}
        }catch (std::ios_base::failure &fail) {	// Exception: String
            aux = false;
            cout << "Exception: String.\n"; 
			cout << "\tPlease insert an integer number in option." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }catch (int e1){						// Exception: No option
        	aux = false;
        	cout << "Exception: \"" << e1 <<  "\"  No such option.\n";
        	cout << "\tPlease insert a valid option." << endl;
        	cin.clear();
            std::string tmp;
            getline(cin, tmp);
    	}
    } while (aux == false);
	return 0;
	
}
