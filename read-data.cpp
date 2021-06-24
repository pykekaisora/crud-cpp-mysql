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

using namespace std;

int main(void)
{
cout << endl;
cout << "Running 'SELECT * FROM `musicinfo_tb` AS _message'..." << endl;


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
      res = stmt->executeQuery("SELECT * FROM musicinfo_tb");

      char choose;
      
      cout << "list of data:" << endl;

      // cout << res->rowsCount() << "\n\n";

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
    
cout << endl;

return EXIT_SUCCESS;
}
