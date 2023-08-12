#include "Header.h"

#include <vector>

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


void insert_into_water_company(sql::Connection* con) {
    std::string mystr;
    std::stringstream ss;
    std::cout << "How many rows? \n";
    std::getline(std::cin, mystr);
    int i; int j = 1;
    std::stringstream(mystr) >> i;
    if (i < 1) {
        std::cout << "incorrect amount";  return;
    }
    std::cout << "Input order info: 'Start' 'End' 'Price' \n";
    sql::PreparedStatement* pstmt;
    pstmt = con->prepareStatement("INSERT INTO water_company(start, end, price) VALUES(?, ?, ?);");
    while (i > 0) {
        std::cout << j << ": ";
        ss << " ";
        std::getline(std::cin, mystr);
        ss << mystr;
        i--; j++;
    }
    while (!ss.eof()) {
        int val1, val2, val3 = 0;
        ss >> val1; ss >> val2; ss >> val3;
        pstmt->setInt(1, val1);
        pstmt->setInt(2, val2);
        pstmt->setInt(3, val3);
        pstmt->execute();
    }
    std::cout <<"\n Success! \n";
    delete pstmt;
}


std::string water_query_price(sql::Connection* con, std::stringstream& ss) {
    sql::PreparedStatement* pstmt1;
    sql::PreparedStatement* pstmt2;
    pstmt1 = con->prepareStatement("SELECT SUM(price) as s FROM water_company WHERE start>=? AND start <= ?;");
    pstmt2 = con->prepareStatement("SELECT SUM(end - start) as s from water_company WHERE end >= ? and end <= ?;");

    std::stringstream result;
    while (!ss.eof()) {
        sql::ResultSet* res;
        int val1, val2, type = 0;
        ss >> val1; ss >> val2; ss >> type;
        if (type == 0) {
            std::cout << "Finished";
            break;
        }
        switch (type) {
        case 1:
            pstmt1->setInt(1, val1);
            pstmt1->setInt(2, val2);
            res = pstmt1->executeQuery();
            break;
        case 2:
            pstmt2->setInt(1, val1);
            pstmt2->setInt(2, val2);
            res = pstmt2->executeQuery();
            break;
        default:
            std::cout << "Wrong type";
            delete pstmt1;
            delete pstmt2;
            return "";
        }
        while (res->next()) {
            cout << "price = " << res->getInt("s") << endl;
            result << res->getInt("s") << " ";
        }
        delete res;
    }
    
    delete pstmt1;
    delete pstmt2;

    return result.str();

    
}

void initial_query(sql::Connection* con) {
    std::string mystr;
    std::stringstream ss;
    std::cout << "How many queries? \n";
    
    //std::cin >> i;
    std::getline(std::cin, mystr);
    int i = stoi(mystr);
    int j = 1;
    //std::stringstream(mystr) >> i;
    std::cout << "Input query: 'Start' 'End' 'Type of query: 1 or 2' \n";
    while (i > 0) {
        std::string s;
        std::cout << j << ": ";
        ss << " ";
        //std::cin >> s;
        std::getline(std::cin, s);
        ss << s;
        i--; j++;
    }
    std::cout << std::endl << water_query_price(con, ss);
}

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

    std::cout << "Input data (1), Output data (2) or Create database (3)? Type a number: ";
    int choice; string str;
    std::getline(std::cin, str);
    choice = stoi(str);
    switch (choice) {
    case 1:
        insert_into_water_company(con);
        break;
    case 2:
        initial_query(con);
        break;
    case 3:
        create_water_company(con);
        break;
    default:
        std::cout << "wrong number";
        break;
    }
    
    delete con;

    //system("pause");
    return 0;
}





