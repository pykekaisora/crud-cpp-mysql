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

int main(){

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
			return 0;
			// AddNewItemInDatabase();
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
			cout << "Edit Successful";
			
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
			// RemoveItem();
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
