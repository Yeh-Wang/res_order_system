#include <ostream>
#include "header.h"

//菜单结构体
typedef struct menuList {
    int dishCode;  //餐品编号
    string dishName;  //餐品名称
    double dishPrice; //餐品价格

    menuList() {
        this->dishCode = 0;
        this->dishName = "";
        this->dishPrice = 0;
    }
} menu;
//点菜列表
typedef struct orderList {
    menu dishOrder;  //餐品信息
    int dishCount = 0;  //餐品数量
    string status;   //是否完成   待做  已做

    orderList() {
        this->dishCount = 0;
        this->status = "待做";
    }
} order;

//消费者类
class consumerEntity {
private:
    int conCode;   //用户编号
    int conTable;  //用户餐位
//    string conName;
    vector<order> conOrder;  //用户订单
    double totalMoney;   //订单总额
    string conRemark;  //用户备注
    int conNumber;  //用餐人数
public:
    consumerEntity() {
        this->conCode = 0;
        this->conTable = 0;
        this->totalMoney = 0;
        this->conNumber = 0;
    }

    friend ostream &operator<<(ostream &os, const consumerEntity &entity) {
        os<<"\nUser number: "<<entity.conCode<<endl;
        os<<"User table: "<<entity.conTable<<"\t\t Number of diners："<<entity.conNumber<<endl;
        os<<"dish name "<<"\t    amount \n";
        for (auto &j: entity.conOrder) {
            os << j.dishOrder.dishName << "\t\t" << j.dishCount << endl;
        }
        os<<"total money: "<<entity.totalMoney<<endl;
        os<<endl;
        return os;
    }

    int getConCode() const {
        return conCode;
    }

    void setConCode(int conCodes) {
        consumerEntity::conCode = conCodes;
    }

    int getConTable() const {
        return conTable;
    }

    void setConTable(int conTables) {
        consumerEntity::conTable = conTables;
    }

    const vector<order> &getConOrder() const {
        return conOrder;
    }

    void setConOrder(const vector<order> &conOrders) {
        consumerEntity::conOrder = conOrders;
    }

    double getTotalMoney() const {
        return totalMoney;
    }

    void setTotalMoney(double totalMoneys) {
        consumerEntity::totalMoney = totalMoneys;
    }

    const string &getConRemark() const {
        return conRemark;
    }

    void setConRemark(const string &conRemarks) {
        consumerEntity::conRemark = conRemarks;
    }

    int getConNumber() const {
        return conNumber;
    }

    void setConNumber(int conNumbers) {
        consumerEntity::conNumber = conNumbers;
    }
};

//收银员类
class cashierEntity {
private:
    int cashCode;   //收银员编号
    vector<consumerEntity> consumerA;  //顾客编号
public:
    cashierEntity() {
        this->cashCode = 0;
    }

    int getCashCode() const {
        return cashCode;
    }

    void setCashCode(int cashCodes) {
        cashierEntity::cashCode = cashCodes;
    }

    const vector<consumerEntity> &getConsumerA() const {
        return consumerA;
    }

    void setConsumerA(const vector<consumerEntity> &consumerAs) {
        cashierEntity::consumerA = consumerAs;
    }
};

//厨师类
class cooksEntity {
private:
    int cookCode;   //厨师编号
public:
    cooksEntity() {
        this->cookCode = 0;
    }

    int getCookCode() const {
        return cookCode;
    }

    void setCookCode(int cookCodes) {
        cooksEntity::cookCode = cookCodes;
    }
};

//服务员类
class waiterEntity {
private:
    int waiterCode;  //服务员编号
    int conCode;  //目标用户编号
    vector<menu> addDishes;  //加菜列表
    string remarks;  //用户备注
public:
    waiterEntity() {
        this->conCode = 0;
        this->waiterCode = 0;
        this->remarks = "";
    }

    int getWaiterCode() const {
        return waiterCode;
    }

    void setWaiterCode(int waiterCodes) {
        waiterEntity::waiterCode = waiterCodes;
    }

    const vector<menu> &getAddDishes() const {
        return addDishes;
    }

    void setAddDishes(const vector<menu> &addDishesS) {
        waiterEntity::addDishes = addDishesS;
    }

    const string &getRemarks() const {
        return remarks;
    }

    void setRemarks(const string &remarksS) {
        waiterEntity::remarks = remarksS;
    }
};

void init_menu();  //初始化菜单
void show_panel();  //总展示面板
void consumer_panel(consumerEntity con); //消费者展示面板
void menu_entity(); //菜单录入

vector<menuList> list;  //所有菜品数据
vector<consumerEntity> allConsumer; //所有用户数据

int main() {
    init_menu();
//    menu_entity(list);
    show_panel();
    return 0;
}

void init_menu() {
    menuList dish_1, dish_2, dish_3, dish_4, dish_5, dish_6;
    dish_1.dishCode = 1;
    dish_1.dishName = "炒朝天椒";
    dish_1.dishPrice = 9.9;
    dish_2.dishCode = 2;
    dish_2.dishName = "青椒炒鸡蛋";
    dish_2.dishPrice = 12.5;
    dish_3.dishCode = 3;
    dish_3.dishName = "可乐鸡翅";
    dish_3.dishPrice = 20;
    dish_4.dishCode = 4;
    dish_4.dishName = "泡椒猪肝";
    dish_4.dishPrice = 20;
    dish_5.dishCode = 5;
    dish_5.dishName = "红烧肉";
    dish_5.dishPrice = 25;
    dish_6.dishCode = 6;
    dish_6.dishName = "大闸蟹";
    dish_6.dishPrice = 55;
    list.push_back(dish_1);
    list.push_back(dish_2);
    list.push_back(dish_3);
    list.push_back(dish_4);
    list.push_back(dish_5);
    list.push_back(dish_6);
}

void menu_entity() {
    while (true) {
        int code;
        string name;
        double price;
        cout << "dish code:";
        cin >> code;
        if (code == 0) {
            break;
        }
        cout << "dish Name:";
        cin >> name;
        cout << "dish price:";
        cin >> price;
        menuList newDish;
        newDish.dishCode = code;
        newDish.dishName = name;
        newDish.dishPrice = price;
        list.push_back(newDish);
    }
}

void show_panel() {
    do {
        cout << "1. I'm a consumer.\n";
        cout << "2. I'm a cashier.\n";
        cout << "3. I'm a cook.\n";
        cout << "4. I'm a waiter.\n";
        cout << "5. I'm a boss.\n";
        cout << "6. I'm a administrator.\n";
        int selectNumber = 0;
        cin >> selectNumber;
        if (selectNumber == 1) {
            consumerEntity consumer;
            default_random_engine e;
            uniform_int_distribution<int> u(0, 100);
            e.seed(time(nullptr));
            consumer.setConCode(u(e));
            cout<<"Please enter number of diners:\n";
            int number;
            cin>>number;
            consumer.setConNumber(number);
            consumer_panel(consumer);
        } else if (selectNumber == 2) {
            system("cls");
            cout << "hello";
        } else if (selectNumber == 3) {
            system("cls");
            cout << "hello_1";
        } else if (selectNumber == 4) {
            system("cls");
            cout << "hello_2";
        } else if (selectNumber == 5) {
            system("cls");
            cout << "hello_4";
        } else if (selectNumber == 6) {
            system("cls");
        } else {
            system("exit");
            break;
        }
    } while (true);
};

void consumer_panel(consumerEntity con) {
    cout << " 编号   " << " 菜名   " << "    价格   " << endl;
    for (auto &i: list) {
        cout << i.dishCode << "       " << i.dishName << "     " << i.dishPrice << endl;
    }
    vector<order> new_order;  //用户菜单
    double amount = 0;
    while (true) {
        cout << "Please select the dishes you want to eat:(-1 EXIT)\n";
        int code = 0;
        cin >> code;
        if (code == -1) {
            break;
        }
        cout << "Please enter the quantity you need:\n";
        int count = 0;
        cin >> count;
        order forOrder;
        forOrder.dishOrder = list[code - 1];
        amount = amount + list[code - 1].dishPrice*count;
        forOrder.dishCount = count;
        new_order.push_back(forOrder);
    }
    con.setConOrder(new_order);
    con.setTotalMoney(amount);
    allConsumer.push_back(con);
    cout<<con;
}
