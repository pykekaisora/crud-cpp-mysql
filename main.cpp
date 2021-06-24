
/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <sstream>

using namespace std;

// Music Store Manangement System in C++ Design and Developed by CodeWithC.com
void AddNewItemInDatabase();
void ShowAllItems();
void EditItem();
void RemoveItem();

int main(){


    // Variables
    int chooseOneFromMenu = 0;
    char exitSurity;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Music Store Menu" << endl;
    cout << "1. All Items." << endl;
    cout << "2. Add New Item." << endl;
    cout << "3. Edit Item." << endl;
    cout << "4. Remove Item." << endl;
    cout << "5. Exit." << endl;
    cout << "Choose One: ";
    cin >> chooseOneFromMenu;

        switch (chooseOneFromMenu)
    {
    case 1:
        ShowAllItems();
        break;
    case 2:
        AddNewItemInDatabase();
        break;
    case 3:
        EditItem();
        break;
    case 4:
        RemoveItem();
        break;
    case 5:
        ExitProgram:
        cout << "Program terminating. Are you sure? (y/N): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y') {
            return 0;
        }else if (exitSurity == 'n' || exitSurity == 'N') {
            system("cls");
            main();
        }else {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 7. Press Enter To Continue...";
        main();
        break;
    }
    return 0;

}

void ShowAllItems(){


    try
    {
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = get_driver_instance();
	con = driver->connect("tcp://localhost:3306", "username", "password");

	con->setSchema("court");
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * FROM musicinfo_tb");

	char choose;

	cout << "Welcome To Music Store" << endl << endl;
	cout << "Show All Items Menu" << endl << endl;

	if (res->rowsCount() != 0)
	{
		while(res->next()) {

		cout << "ID: " << res->getInt(1) << endl;
		cout << "Category: " << res->getString(2) << endl;
		cout << "Type: " << res->getString(3) << endl;
		cout << "Name: " << res->getString(4) << endl;
		cout << "Artist: " << res->getString(5) << endl;
		cout << "Price: " << res->getString(6) << endl;
		cout << "Quantity: " << res->getString(7) << endl << endl;
		
		}
	} else{
		cout << "No Items Available, Please add items" << endl;
	}

	cout << "Press 'm' to Menu and any other key to Exit: ";
	cin >> choose;

	if (choose == 'm' || choose == 'M')
	{
		main();
	}
	else
	{
		exit(0);
	}

	delete res;
	delete stmt;
	delete con;
	
    }
    catch(sql::SQLException &e)
    {
      cout << "# ERR: " << e.what();
      cout << " (MYSQL error code: " << e.getErrorCode();
      cout << ", SQLState " << e.getSQLState() << " )" << endl;
    }

}

void AddNewItemInDatabase(){

 try
    {
      sql::Driver *driver;
      sql::Connection *con;
      sql::Statement *stmt;
      sql::ResultSet *res;

      cout << "connecting to mysql server....";
      driver = get_driver_instance();
      con = driver->connect("tcp://localhost:3306", "username", "password");  
      cout << "connected" << endl;

      con->setSchema("court");
      stmt = con->createStatement();

      // Variables
      string category = "";
      string type = "";
      string name = "";
      string artist = "";
      float price = 0.0;
      int quantity = 0;
      char choose;

      cout << "Welcome To Music Store\n" << endl;
      cout << "Add New Item Menu\n" << endl;

//       cin.ignore(1, '\n');
      cout << "Enter Category: ";
      getline(cin, category);
      cout << "Enter Type: ";
      getline(cin, type);
      cout << "Enter Name: ";
      getline(cin, name);
      cout << "Enter Artist: ";
      getline(cin, artist);
      cout << "Enter Price: ";
      cin >> price;
      cout << "Enter Quantity: ";
      cin >> quantity;

      stringstream streamPrice, streamQuan;
      string sprice, squan;
      streamPrice << price;
      streamPrice >> sprice;
      streamQuan << quantity;
      streamQuan >> squan;


      string insert_query = "insert into musicinfo_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) values ('"+category+"','"+type+"','"+name+"','"+artist+"','"+sprice+"','"+squan+"')";

      const char* q = insert_query.   c_str(); // c_str converts string to constant char and this is required

      if (name != "")
      {
        stmt->executeUpdate(q);
        }
        else
      {
        cout << "\nName Wajib\n";
      }
        
      cout << "Press 'm' to Menu and any other key to Exit: ";
      cin >> choose;

      if (choose == 'm' || choose == 'M')
      {
      	main();
      } else if (choose == 'a' || choose == 'a')
      {
        AddNewItemInDatabase();
      } else
      {
      	exit(0);
      }
      delete res;
      delete stmt;
      delete con;
    }
    catch(sql::SQLException &e)
    {
      cout << "# ERR: " << e.what();
      cout << " (MYSQL error code: " << e.getErrorCode();
      cout << ", SQLState " << e.getSQLState() << " )" << endl;
    }

}

void EditItem(){

    try
    {
	    sql::Driver *driver;
	    sql::Connection *con;
	    sql::Statement *stmt;
	    sql::ResultSet *res;

	    sql::PreparedStatement *prep_stmt;

	    driver = get_driver_instance();
	    con = driver->connect("tcp://localhost:3306", "username", "password");
	    con->setSchema("court");
	    stmt = con->createStatement();
	    res = stmt->executeQuery("SELECT * FROM musicinfo_tb");
	    
	    string category = "";
	    string type = "";
	    string name = "";
	    string artist = "";
	    string items[5000];
	    string price = "";
	    string quantity = "";
	    char choose;
	    int itemId;
	    bool HaveException = false;
	    bool NotInDatabase = false;
	    int indexForId = 1;

	    // Store Variables
	    string storeid = "";
	    string storecategory = "";
	    string storetype = "";
	    string storename = "";
	    string storeartist = "";
	    string storeprice = "";
	    string storequantity = "";

	    cout << "Welcome To Music Store\n" << endl;
	    cout << "Edit Item Menu\n" << endl;

	    if (res->rowsCount() != 0) {
			cout << "ID\tCategory\tType\tName\tArtist\tPrice\tQuantity\n" << endl;
		    while (res->next()) {
			cout << res->getInt(1) << "\t" << res->getString(2) << "\t" << res->getString(3) << "\t" << res->getString(4) << "\t" << res->getString(5) << "\t" << res->getString(6) << "\t" << res->getString(7) << endl;

			items[indexForId] = res->getString(1);
			indexForId++;
		    }

	    } else {
		    	cout << "No Items Available, Please Add Items first." << endl;
			cout << "Press any key to continue: ";
			cin.ignore();
			AddNewItemInDatabase();
	    }

	    try {

		cout << endl;
		cout << "Enter Item ID: ";
		cin >> itemId;
		cout << endl;

	    }
	    catch(exception e) {
		cout << "Please Enter a valid NUMBER." << endl;
		HaveException = true;
		goto ExitMenu;
	    }

	    if (HaveException == false) {
		stringstream streamid;
		string strid;
		streamid << itemId;
		streamid >> strid;

		for (int i = 0; i <= indexForId; i++) {
			if (strid != items[i]) {
				NotInDatabase = true;
			} else {
				NotInDatabase = false;
				break;
			}
		}

		if (NotInDatabase == false) {
			string findbyid_query = "select * from musicinfo_tb where m_id = '"+strid+"'";
			const char* qi = findbyid_query.c_str();
			res = stmt->executeQuery(qi);

			while (res->next()) {
				cout << "ID: " << res->getInt(1) << endl;
				cout << "Category: " << res->getString(2) << endl;
				cout << "Type: " << res->getString(3) << endl;
				cout << "Name: " << res->getString(4) << endl;
				cout << "Artist: " << res->getString(5) << endl;
				cout << "Price: " << res->getString(6) << endl;
				cout << "Quantity: " << res->getString(7) << endl << endl;

				storeid = res->getInt(1);
				storecategory = res->getString(2);
				storetype = res->getString(3);
				storename = res->getString(4);
				storeartist = res->getString(5);
				storeprice = res->getString(6);
				storequantity = res->getString(7);
			}

			cout << "Enter Category (xN to not change): ";
			cin >> category;
			if (category == "xN") {
				category = storecategory;
			}
			
			cout << "Enter Type (xN to not change): ";
			cin >> type;
			if (type == "xN") {
				type = storetype;
			}
			
			cout << "Enter Name (xN to not change): ";
			cin >> name;
			if (name == "xN") {
				name = storename;
			}
			
			cout << "Enter Artist (xN to not change): ";
			cin >> artist;
			if (artist == "xN") {
				artist = storeartist;
			}
			
			cout << "Enter Price (xN to not change): ";
			cin >> price;
			if (price == "xN") {
				price = storeprice;
			}
			
			cout << "Enter Quantity (xN to not change): ";
			cin >> quantity;
			if (quantity == "xN") {
				quantity = storequantity;
			}

			string update_query = "update musicinfo_tb set m_category = '"+category+"', m_type = '"+type+"', m_name = '"+name+"', m_artist = '"+artist+"', m_price = '"+price+"', m_quantity = '"+quantity+"' where m_id = '"+strid+"'";
            		const char* qu = update_query.c_str();

			stmt->executeUpdate(qu);
			cout << "Edit Successful\n";
			
		} else {
			cout << "Item Not Found in database." << endl;
		}
		
			
	    }
		ExitMenu:
		cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
		cin >> choose;
		if (choose == 'm' || choose == 'M')
		{
			main();
		}
		else if (choose == 'e' || choose == 'E')
		{
			EditItem();
		}
		else
		{
			exit(0);
		}
	    
    }
    catch(sql::SQLException &e)
    {
      cout << "# ERR: " << e.what();
      cout << " (MYSQL error code: " << e.getErrorCode();
      cout << ", SQLState " << e.getSQLState() << " )" << endl;
    }
    
}

void RemoveItem(){

	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		sql::PreparedStatement *prep_stmt;

		driver = get_driver_instance();
		con = driver->connect("tcp://localhost:3306", "username", "password");
		con->setSchema("court");
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM musicinfo_tb");

		char choose;
		int itemId;
		string items[5000];
		int indexForId = 1;
		bool HaveException = false, NotInDatabase = false;

		cout << "Welcome To Music Store" << endl << endl;
		cout << "Remove Item Menu" << endl << endl;

		if (res->rowsCount() != 0) {
		    cout << "ID\tCategory\tType\tName\tArtist\tPrice\tQuantity\n" << endl;

		    while (res->next()) {
			cout << res->getInt(1) << "\t" << res->getString(2) << "\t" << res->getString(3) << "\t" << res->getString(4) << "\t" << res->getString(5) << "\t" << res->getString(6) << "\t" << res->getString(7) << endl;

			items[indexForId] = res->getString(1);
			indexForId++;
		    }
		    
		} else {
			cout << "No Items Available, Please Add Items first." << endl;
			cout << "Press any key to continue: ";
			cin.ignore();
			AddNewItemInDatabase();
		}

	    try {

		cout << endl;
		cout << "Enter Item ID: ";
		cin >> itemId;
		cout << endl;

	    }
	    catch(exception e) {
		cout << "Please Enter a valid NUMBER." << endl;
		HaveException = true;
		goto ExitMenu;
	    }
		
	    if (HaveException == false) {
		stringstream streamid;
		string strid;
		streamid << itemId;
		streamid >> strid;

		for (int i = 0; i <= indexForId; i++) {
			if (strid != items[i]) {
				NotInDatabase = true;
			} else {
				NotInDatabase = false;
				break;
			}
		}

		if (NotInDatabase == false) {
			string delete_query = "delete from musicinfo_tb where m_id = '"+strid+"'";
			const char* qd = delete_query.c_str();

			stmt->executeUpdate(qd);
			cout << "Delete Successful\n";
			
		} else {
			cout << "Item Not Found in database." << endl;
		}
		
			
	    }
		ExitMenu:
		cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
		cin >> choose;
		if (choose == 'm' || choose == 'M')
		{
			main();
		}
		else if (choose == 'd' || choose == 'D')
		{
			RemoveItem();
		}
		else
		{
			exit(0);
		}
		


	} catch(sql::SQLException &e) {
		cout << "# ERR: " << e.what();
		cout << " (MYSQL error code: " << e.getErrorCode();
		cout << ", SQLState " << e.getSQLState() << " )" << endl;
	}
}
