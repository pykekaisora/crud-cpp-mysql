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
