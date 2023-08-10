#include "Header.h"

#include <vector>
/*
void create_water_company( sql::Connection* con) {
    sql::Statement* stmt;
    stmt = con->createStatement();
    stmt->execute("DROP TABLE IF EXISTS water_company");
    cout << "Finished dropping table (if existed)" << endl;
    stmt->execute("CREATE TABLE water_company (id INT AUTO_INCREMENT PRIMARY KEY, start INT, end INT, price INT);");
    cout << "Finished creating table" << endl;
    delete stmt;
}

void insert_into_water_company(std::vector<std::vector<int>> vec, sql::Connection* con) {
    sql::PreparedStatement* pstmt;
    pstmt = con->prepareStatement("INSERT INTO water_company(start, end, price) VALUES(?, ?, ?);");

    for (std::vector<int> v : vec) {
        pstmt->setInt(1, v[0]);
        pstmt->setInt(2, v[1]);
        pstmt->setInt(3, v[2]);
        pstmt->execute();
        cout << "Row inserted: " << v[0] << " " << v[1] << " " << v[1] << endl;
    }
    delete pstmt;
}
*/
/*
void water_query_price(sql::Connection* con) {
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt;
    pstmt = con->prepareStatement("SELECT SUM(price) as s FROM water_company WHERE start>? AND end<?");
    pstmt->setInt(1, 6);
    pstmt->setInt(2, 25);
    res = pstmt->executeQuery();
    while (res->next()) {
        // You can use either numeric offsets...
        cout << "price = " << res->getInt("s") << endl;
    }

    delete res;
    delete pstmt;
}*/

int main()
{
    sql::Driver* driver;
    sql::Connection* con;


    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    con->setSchema("DataBase1");


    //create_water_company(con);

    //insert_into_water_company(vec, con);
    ///water_query_price(con);
    delete con;
    //system("pause");
    return 0;
}


/*
 std::vector<std::vector<int>> vec;
 vec.push_back({ 5, 20, 5 });
 vec.push_back({ 6, 21, 4 });
 vec.push_back({ 6, 22, 3 });
 vec.push_back({ 7, 23, 2 });
 vec.push_back({ 10, 24, 1 });
 */


/*
    sql::Statement* stmt;
    sql::ResultSet* res;
    stmt = con->createStatement();

    res = stmt->executeQuery("SELECT price FROM water_company WHERE id = 9;");
    while (res->next()) {
        // You can use either numeric offsets...
        cout << "price = " << res->getInt("price")<< endl;
    }

    delete res;
    delete stmt;*/