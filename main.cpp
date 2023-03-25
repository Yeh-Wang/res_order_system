#include <ostream>
#include "header.h"

//data struct
struct menuList;       //�˵��ṹ��
struct beverage;       //��ˮ�ṹ��
struct orderList;      //����б�
class consumerEntity;  //��������
class cashierEntity;   //����Ա��
class cooksEntity;     //��ʦ��
class waiterEntity;    //����Ա��
class resOwner;        //�����ϰ�
class systemAdmin;     //ϵͳ����Ա

//global variable
vector<menuList> list;  //���в�Ʒ����
vector<beverage> bevList; //���о�ˮ����
vector<consumerEntity> allConsumer; //δ���˵���������������
vector<consumerEntity> alreadyConsumer; //�Ѿ����˵�����������
map<int, int> allTable;   //������λ��Ϣ
int tableFee = 2;   //��λ��
vector<orderList> finishedDishes;  //����ɵ����в�Ʒ

//global functions
void init_menu();  //��ʼ���˵�����λ
void show_panel();  //��չʾ���
void adminShow();   //ϵͳ����Ա����
void consumerShow(); //�û�����
void cashierShow();  //����Ա����
void waiterShow();   //����Ա����
void all_notCheckout_orders(); //չʾ����δ���˵������߶�����Ϣ
void all_unfinished_orders();  //չʾδ���˲����в�Ʒδ����������߶�����Ϣ
//void all_notDeliver_orders();  //չʾ�в�Ʒδ���͵������߶�����Ϣ
void viewAllDishes();//�˵�
void viewDishes();  //�鿴���в�Ʒ��Ϣ
void viewBeverage(); //�鿴���о�ˮ��Ϣ

//�˵��ṹ��
typedef struct menuList {
    int dishCode;  //��Ʒ���
    string dishName;  //��Ʒ����
    double dishPrice; //��Ʒ�۸�

    menuList() {
        this->dishCode = 0;
        this->dishName = "";
        this->dishPrice = 0;
    }
} menu;

//��ˮ�ṹ��
struct beverage {
    int bevCode;    //��ˮ���
    string bevName; //����
    double bevPrice;//�۸�
    int bevStock;   //���

    beverage() {
        this->bevCode = 0;
        this->bevName = "";
        this->bevPrice = 0;
        this->bevStock = 0;
    }
};

//�����б�
typedef struct orderList {
    menu dishOrder;  //��Ʒ��Ϣ
    int dishCount = 0;  //��Ʒ����
    string status;   //�Ƿ����   ����  ����
    beverage bevInfo; //��ˮ��Ϣ
    int bevCount;   //��ˮ����
    string deliver; //�Ƿ����  δ����  �ѳ���

    orderList() {
        this->dishCount = 0;
        this->status = "����";
        this->bevCount = 0;
        this->deliver = "δ����";
    }

    void setStatus(const string &statusL) {
        orderList::status.clear();
        orderList::status.assign(statusL);
    }

    void setDeliver(const string &delivers) {
        orderList::deliver.clear();
        orderList::deliver.assign(delivers);
    }
} order;

//��������
class consumerEntity {
private:
    int conCode;   //�û����
    int conTable;  //�û���λ
    int conStatus; //��ʦ��ʶ,�������߲��Ƿ�����  0: No  1: Yes
    int isCheckout; //����Ա��ʶ  ���������Ƿ����
    vector<orderList> conOrder;  //�û�����
    double totalMoney;   //�����ܶ�
    int conRemark;  //����Ա��ʶ���������߲�Ʒ�Ƿ��������  0��No  1: Yes
    int conNumber;  //�ò�����
public:
    consumerEntity() {
        this->conCode = 0;
        this->conTable = 0;
        this->conStatus = 0;
        this->isCheckout = 0;
        this->totalMoney = 0;
        this->conRemark = 0;
        this->conNumber = 0;
    }

    static consumerEntity makeOrder(consumerEntity consumer) {
        viewAllDishes();
        vector<order> new_order;  //�û��˵�
        double amount = 0;
        while (true) {
            order forOrder1;
            cout << "Please select the dishes you want to eat:(-1 EXIT)\n";
            int code = 0;
            cin >> code;
            if (code == -1) {
                break;
            }
            cout << "Please enter the quantity you need:\n";
            int count = 0;
            cin >> count;
            cout << "Please select the beverage:(0 Skip)\n";
            int bevCode;
            cin >> bevCode;
            for (auto k: list) {
                if (k.dishCode == code) {
                    forOrder1.dishOrder = k;
                    forOrder1.dishCount = count;
                }
            }
            if (bevCode != 0) {
                cout << "Please enter the quantity you need:\n";
                int bevCount;
                cin >> bevCount;
                for (auto x: bevList) {
                    if (x.bevCode == bevCode) {
                        forOrder1.bevInfo = x;
                        amount = amount + x.bevPrice * bevCount;
                        x.bevStock = x.bevStock - bevCount;
                        forOrder1.bevCount = bevCount;
                    }
                }
                new_order.push_back(forOrder1);
            } else {
                new_order.push_back(forOrder1);
            }
        }
        consumer.setConOrder(new_order);
        consumer.setTotalMoney(amount);
        return consumer;
    }

    friend ostream &operator<<(ostream &os, consumerEntity &entity) {
        os << "\nUser number: " << entity.conCode << endl;
        os << "User table: " << entity.conTable << "\t\t Number of diners��" << entity.conNumber << endl;
        os << "dish name" << "\t" << "amount \n";
        for (auto &j: entity.conOrder) {
            os << setw(15) << left << j.dishOrder.dishName << setw(15) << j.dishCount << setw(15) << j.status
               << setw(15) << j.deliver << endl;
        }
        os << "beverage name" << "  " << "amount\n";
        for (auto &j: entity.conOrder) {
            if (j.bevCount != 0) {
                os << setw(16) << left << j.bevInfo.bevName << setw(15) << j.bevCount << endl;
            }
        }
        os << "total money: " << entity.totalMoney << endl;
        os << endl;
        return os;
    }

    void outOrder() {
        for (auto &i: conOrder) {
            cout << i.dishOrder.dishCode << ". " << i.dishOrder.dishName << "\t" << i.dishCount << "��\t" << i.status
                 << "\t" << i.deliver
                 << endl;
        }
        cout << endl;
    }

//    int getConCode() {
//        return conCode;
//    }

    void setConCode(int conCodes) {
        consumerEntity::conCode = conCodes;
    }

    int getConStatus() const {
        return conStatus;
    }

    void setConStatus(int conStatusL) {
        consumerEntity::conStatus = conStatusL;
    }

    int getIsCheckout() {
        return isCheckout;
    }

    void setIsCheckout(int isCheckouts) {
        consumerEntity::isCheckout = isCheckouts;
    }

    int getConTable() {
        return conTable;
    }

    void setConTable(int conTables) {
        consumerEntity::conTable = conTables;
    }

    vector<orderList> &getConOrder() {
        return conOrder;
    }

    void setConOrder(vector<order> &conOrders) {
        consumerEntity::conOrder = conOrders;
    }

    double getTotalMoney() {
        return totalMoney;
    }

    void setTotalMoney(double totalMoneys) {
        consumerEntity::totalMoney = totalMoneys;
    }

    int getConRemark() {
        return conRemark;
    }

    void setConRemark(int conRemarks) {
        consumerEntity::conRemark = conRemarks;
    }

    int getConNumber() {
        return conNumber;
    }

    void setConNumber(int conNumbers) {
        consumerEntity::conNumber = conNumbers;
    }
};

//����Ա��
class cashierEntity {
private:
    int cashCode;   //����Ա���
public:
    cashierEntity() {
        this->cashCode = 0;
    }

    /**
     * ͨ�����Ž��н���
     * @param tableCode  ����
     */
    static void checkoutByTable(int tableCode) {
        for (auto &i: allConsumer) {
            if (i.getConTable() == tableCode && i.getIsCheckout() == 0) {
                if (i.getIsCheckout() == 1) {
                    cout << "don't checkout again!\n";
                    break;
                }
                for (auto &j: i.getConOrder()) {
                    if (j.deliver == "�ѳ���") {
                        i.setTotalMoney(i.getTotalMoney() + j.dishOrder.dishPrice * j.dishCount);
                    }
                }
                if (i.getTotalMoney() < 500) {
                    i.setTotalMoney(i.getTotalMoney() + tableFee * i.getConNumber());
                    alreadyConsumer.push_back(i);
                } else {
                    alreadyConsumer.push_back(i);
                }
                allTable[i.getConTable()] = 0;
                i.setIsCheckout(1);
                cout << i;
            }
        }
    }

    /**
     * ͳ�ƽ��������
     */
    static double countEarning() {
        double count = 0;
        for (auto i: alreadyConsumer) {
            count = count + i.getTotalMoney();
        }
        return count;
    }

    int getCashCode() {
        return cashCode;
    }

    void setCashCode(int cashCodes) {
        cashierEntity::cashCode = cashCodes;
    }
};

//��ʦ��
class cooksEntity {
private:
    int cookCode;   //��ʦ���
public:
    cooksEntity() {
        this->cookCode = 0;
    }

    static void viewOrders() {
        all_unfinished_orders();
        cout << "Please select the seat number to complete the meal:(-1 EXIT)\n";
        int tableNumber;
        cin >> tableNumber;
        cout << endl;
        for (auto &i: allConsumer) {
            if (i.getConTable() == tableNumber) {
                i.outOrder();
                doDishes(i);
                int j = 0;
                for (j = 0; j < i.getConOrder().size(); j++) {
                    if (i.getConOrder()[j].status == "����") {
                        break;
                    }
                }
                if (j == i.getConOrder().size()) {
                    i.setConStatus(1);
                }
            }
        }
    }

    static void doDishes(consumerEntity &consumer) {
        while (true) {
            cout << "Please enter the serial number of the finished dish:(-1 EXIT)\n";
            int now_code;
            cin >> now_code;
            if (now_code != -1) {
                for (auto &i: consumer.getConOrder()) {
                    if (i.dishOrder.dishCode == now_code) {
                        i.setStatus("����");
                        finishedDishes.push_back(i);
                    }
                }
            } else {
                break;
            }
        }
    }

    static void viewAllFinishedDishes() {
        for (auto &i: finishedDishes) {
            cout << i.dishOrder.dishName << "\t" << i.dishCount << endl;
        }
    }

    static void viewAllUnfinishedDishes() {
        for (auto &i: allConsumer) {
            for (const auto &j: i.getConOrder()) {
                if (j.status == "����") {
                    cout << j.dishOrder.dishName << "\t" << j.dishCount << endl;
                }
            }
        }
    }

    int getCookCode() {
        return cookCode;
    }

    void setCookCode(int cookCodes) {
        cooksEntity::cookCode = cookCodes;
    }
};

//����Ա��
class waiterEntity {
private:
    int waiterCode;  //����Ա���
    int conCode;  //Ŀ���û����
    vector<menu> addDishes;  //�Ӳ��б�
    string remarks;  //�û���ע
public:
    waiterEntity() {
        this->conCode = 0;
        this->waiterCode = 0;
        this->remarks = "";
    }

    static void deliverServe(int tableCode) {
        for (auto &i: allConsumer) {
            if (i.getConTable() == tableCode) {
                while (true) {
                    cout << i;
                    cout << "1. deliver dishes.\n2. add dishes.\n-1. EXIT.\n";
                    int code;
                    cin >> code;
                    if (code == 1) {
                        i.outOrder();
                        while (true) {
                            cout << "Please enter the serial number of the dish you want to serve:(-1 EXIT)\n";
                            int now_code;
                            cin >> now_code;
                            if (now_code != -1) {
                                for (auto &j: i.getConOrder()) {
                                    if (j.dishOrder.dishCode == now_code) {
                                        j.setDeliver("�ѳ���");
                                    }
                                }
                            } else {
                                break;
                            }
                        }
                        int j = 0;
                        for (j = 0; j < i.getConOrder().size(); j++) {
                            if (i.getConOrder()[j].deliver == "δ����") {
                                break;
                            }
                        }
                        if (j == i.getConOrder().size()) {
                            i.setConRemark(1);
                        }
                    } else if (code == 2) {
                        viewAllDishes();
                        double amount = 0;
                        while (true) {
                            order forOrder1;
                            cout << "Please select the dishes you want to add:(-1 EXIT)\n";
                            int code1 = 0;
                            cin >> code1;
                            if (code1 == -1) {
                                break;
                            }
                            cout << "Please enter the quantity you need:\n";
                            int count = 0;
                            cin >> count;
                            cout << "Please select the beverage:(0 Skip)\n";
                            int bevCode;
                            cin >> bevCode;
                            for (auto k: list) {
                                if (k.dishCode == code1) {
                                    forOrder1.dishOrder = k;
                                    forOrder1.dishCount = count;
                                }
                            }
                            if (bevCode != 0) {
                                cout << "Please enter the quantity you need:\n";
                                int bevCount;
                                cin >> bevCount;
                                for (auto x: bevList) {
                                    if (x.bevCode == bevCode) {
                                        forOrder1.bevInfo = x;
                                        amount = amount + x.bevPrice * bevCount;
                                        x.bevStock = x.bevStock - bevCount;
                                        forOrder1.bevCount = bevCount;
                                    }
                                }
                                i.getConOrder().push_back(forOrder1);
                                i.setTotalMoney(i.getTotalMoney() + amount);
                            } else {
                                i.getConOrder().push_back(forOrder1);
                            }
                            i.setConStatus(0);
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }

    int getWaiterCode() {
        return waiterCode;
    }

    void setWaiterCode(int waiterCodes) {
        waiterEntity::waiterCode = waiterCodes;
    }

    vector<menu> &getAddDishes() {
        return addDishes;
    }

    void setAddDishes(vector<menu> &addDishesS) {
        waiterEntity::addDishes = addDishesS;
    }

    string &getRemarks() {
        return remarks;
    }

    void setRemarks(string &remarksS) {
        waiterEntity::remarks = remarksS;
    }
};

//�����ϰ�
class resOwner {
private:
    int bossCode;
public:
    static void bossShow(){
        while(true){
            cout<<"1. view menu info.\n2. View income, expenses.\n3. View all consumer orders today.\n-1. EXIT.\n";
            int flag;
            cin>>flag;
            if(flag==1){
                viewAllDishes();
            }else if(flag==2){
                cout << "total consumers:" << alreadyConsumer.size() << "\ntoday's total revenue:"
                     << cashierEntity::countEarning() << endl;
            }else if(flag==3){
                cout<<"���ھͲ͵������߶�����\n";
                all_notCheckout_orders();
                cout<<"�Ѿ����˵������߶�����\n";
                for(auto i :alreadyConsumer){
                    cout<<i;
                }
            } else{
                break;
            }
        }
    }
};

//ϵͳ����Ա
class systemAdmin {
private:
    int adminCode;
public:
    systemAdmin() {
        this->adminCode = 0;
    }

    /**
     * ��Ʒ¼��
     */
    static void menu_entry() {
        while (true) {
            int code;
            string name;
            double price;
            cout << "dish code:(-1 EXIT)";
            cin >> code;
            if (code == -1) {
                break;
            }
            cout << "dish name:";
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

    /**
     * ��ˮ¼��
     */
    static void beverage_entry() {
        while (true) {
            int code;
            string name;
            double price;
            int stock;
            cout << "beverage code:(-1 EXIT)";
            cin >> code;
            if (code == -1) {
                break;
            }
            cout << "beverage name:";
            cin >> name;
            cout << "beverage price:";
            cin >> price;
            cout << "beverage stock:";
            cin >> stock;
            beverage newBev;
            newBev.bevCode = code;
            newBev.bevName = name;
            newBev.bevPrice = price;
            newBev.bevStock = stock;
            bevList.push_back(newBev);
        }
    }

    /**
     * ��λ��Ϣ¼��
     */
    static void table_info_entry() {
        for (auto pos = allTable.begin(); pos != allTable.end();) {
            cout << pos->first << " ";
            pos++;
        }
        cout << endl;
        while (true) {
            cout << "1. delete table.\n2. add table.\n-1. EXIT.\n";
            int flag;
            cin >> flag;
            if (flag == 1) {
                cout << "enter the table number you want to delete:\n";
                int deleteCode;
                cin >> deleteCode;
                auto iter = allTable.find(deleteCode);
                allTable.erase(iter);
                cout << "delete successfully.\n";
            } else if (flag == 2) {
                cout << "enter the table you want to add:\n";
                int addCode;
                cin >> addCode;
                allTable.insert(map<int, int>::value_type(addCode, 0));
                cout << "add successfully.\n";
            } else {
                break;
            }
        }
    }
};

int main() {
    init_menu();
    show_panel();
    return 0;
}

void init_menu() {
    menuList dish_1, dish_2, dish_3, dish_4, dish_5, dish_6;
    dish_1.dishCode = 1;
    dish_1.dishName = "�����콷";
    dish_1.dishPrice = 9.9;
    dish_2.dishCode = 2;
    dish_2.dishName = "�ཷ������";
    dish_2.dishPrice = 12.5;
    dish_3.dishCode = 3;
    dish_3.dishName = "���ּ���";
    dish_3.dishPrice = 20;
    dish_4.dishCode = 4;
    dish_4.dishName = "�ݽ����";
    dish_4.dishPrice = 20;
    dish_5.dishCode = 5;
    dish_5.dishName = "������";
    dish_5.dishPrice = 25;
    dish_6.dishCode = 6;
    dish_6.dishName = "��բз";
    dish_6.dishPrice = 55;
    list.push_back(dish_1);
    list.push_back(dish_2);
    list.push_back(dish_3);
    list.push_back(dish_4);
    list.push_back(dish_5);
    list.push_back(dish_6);

    beverage bev1, bev2, bev3, bev4, bev5;
    bev1.bevCode = 1;
    bev1.bevName = "����";
    bev1.bevPrice = 3;
    bev1.bevStock = 100;
    bev2.bevCode = 2;
    bev2.bevName = "ѩ��";
    bev2.bevPrice = 3;
    bev2.bevStock = 200;
    bev3.bevCode = 3;
    bev3.bevName = "С�ɾ�";
    bev3.bevPrice = 18;
    bev3.bevStock = 50;
    bev4.bevCode = 4;
    bev4.bevName = "Ҭ��";
    bev4.bevPrice = 8;
    bev4.bevStock = 80;
    bev5.bevCode = 5;
    bev5.bevName = "�Ӷ౦";
    bev5.bevPrice = 5;
    bev5.bevStock = 300;
    bevList.push_back(bev1);
    bevList.push_back(bev2);
    bevList.push_back(bev3);
    bevList.push_back(bev4);
    bevList.push_back(bev5);

    allTable.insert(map<int, int>::value_type(1, 0));
    allTable.insert(map<int, int>::value_type(2, 0));
    allTable.insert(map<int, int>::value_type(3, 0));
    allTable.insert(map<int, int>::value_type(4, 0));
    allTable.insert(map<int, int>::value_type(5, 0));
    allTable.insert(map<int, int>::value_type(6, 0));
    allTable.insert(map<int, int>::value_type(7, 0));
    allTable.insert(map<int, int>::value_type(8, 0));
    allTable.insert(map<int, int>::value_type(9, 0));
    allTable.insert(map<int, int>::value_type(10, 0));
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
            consumerShow();
        } else if (selectNumber == 2) {
            cashierShow();
        } else if (selectNumber == 3) {
            while (true) {
                cout << "1. go for the dishes.\n2. Check out the dishes made today.\n-1. Exit.\n";
                int code;
                cin >> code;
                if (code == -1) {
                    break;
                }
                if (code == 1) {
                    cooksEntity::viewOrders();
                } else if (code == 2) {
                    cooksEntity::viewAllFinishedDishes();
                }
            }
        } else if (selectNumber == 4) {
            waiterShow();
        } else if (selectNumber == 5) {
            resOwner::bossShow();
        } else if (selectNumber == 6) {
            adminShow();
        } else {
            system("exit");
            break;
        }
    } while (true);
};

void adminShow() {
    while (true) {
        cout << "1. Menu information actions.\n2. Modification of table information\n3. View all dishes\n-1. EXIT\n";
        int select;
        cin >> select;
        if (select == 1) {
            cout << "===================�˵�======================\n";
            viewAllDishes();
            cout << "============================================\n";
            while (true) {
                cout << endl;
                cout
                        << "1. menu entry.\n2. beverage entry.\n3. delete dishes.\n4. delete beverage.\n5. update dish.\n6. update beverage\n-1. EXIT.\n";
                int flag_2;
                cin >> flag_2;
                if (flag_2 == 1) {
                    cout << endl;
                    systemAdmin::menu_entry();
                    cout << endl;
                } else if (flag_2 == 2) {
                    cout << endl;
                    systemAdmin::beverage_entry();
                    cout << endl;
                } else if (flag_2 == 3) {
                    cout << endl;
                    viewDishes();
                    cout << "Please enter the serial number you want to delete:";
                    int deleteDish;
                    cin >> deleteDish;
                    for (int i = 0; i < list.size(); i++) {
                        if (list[i].dishCode == deleteDish) {
                            auto it = list.begin() + i;
                            list.erase(it);
                            cout << "delete successfully.\n";
                            break;
                        }
                    }
                    cout << endl;
                } else if (flag_2 == 4) {
                    cout << endl;
                    viewBeverage();
                    cout << "Please enter the serial number you want to delete:";
                    int deleteBev;
                    cin >> deleteBev;
                    for (int i = 0; i < bevList.size(); i++) {
                        if (bevList[i].bevCode == deleteBev) {
                            auto it = bevList.begin() + i;
                            bevList.erase(it);
                            cout << "delete successfully.\n";
                            break;
                        }
                    }
                    cout << endl;
                } else if (flag_2 == 5) {

                } else if (flag_2 == 6) {
                    cout << endl;
                    viewBeverage();
                    cout << "Please input the serial number:";
                    int bevCode;
                    cin >> bevCode;
                    for (auto &i: bevList) {
                        if (i.bevCode == bevCode) {
                            cout << i.bevCode << "\t" << i.bevName << "\t" << i.bevPrice << "\t" << i.bevStock << endl;
                            cout << "beverage name:";
                            string name;
                            cin >> name;
                            cout << "beverage price:";
                            double price;
                            cin >> price;
                            cout << "beverage stock:";
                            int stock;
                            cin >> stock;
                            i.bevName = name;
                            i.bevPrice = price;
                            i.bevStock = stock;
                            cout << i.bevCode << "\t" << i.bevName << "\t" << i.bevPrice << "\t" << i.bevStock << endl;
                            cout << "update successfully.\n";
                            break;
                        }
                    }
                    cout << endl;
                } else {
                    break;
                }
            }
        } else if (select == 2) {
            cout << endl;
            systemAdmin::table_info_entry();
            cout << endl;
        } else if (select == 3) {
            cout << endl;
            viewAllDishes();
            cout << endl;
        } else {
            break;
        }
    }
}

void consumerShow() {
    while (true) {
        cout << endl;
        cout << "1. Order food.\n2. view my order.\n-1. EXIT\n";
        int flag;
        cin >> flag;
        if (flag == 1) {
            consumerEntity consumer;
            default_random_engine e;
            uniform_int_distribution<int> u(0, 1000);
            e.seed(time(nullptr));
            consumer.setConCode(u(e));
            int look = allTable.size();
            int j;
            for (j = 0; j < look; j++) {
                auto pos = allTable.find(j + 1);
                if (pos->second == 0) {
                    break;
                }
            }
            if (j == look) {
                cout << "There is no seat now!\n";
                continue;
            }
            for (int i = 0; i < look; i++) {
                auto pos = allTable.find(i + 1);
                if (pos->second == 0) {
                    cout << pos->first << " ";
                }
            }
            cout << "\nPlease select the seat you would like to eat:\n";
            int tableNumber;   //��������λ��
            cin >> tableNumber;
            consumer.setConTable(tableNumber);
            allTable[tableNumber] = 1;
            cout << "Please enter number of diners:\n";
            int number;   //����������
            cin >> number;
            consumer.setConNumber(number);
            consumer = consumerEntity::makeOrder(consumer);   //���
            allConsumer.push_back(consumer);
            cout << endl;
        } else if (flag == 2) {
            cout << endl;
            cout << "please enter the table number:";
            int table;
            cin >> table;
            for (auto &i: allConsumer) {
                if (i.getConTable() == table && i.getIsCheckout() == 0) {
                    cout << i;
                }
            }
            cout << endl;
        } else {
            break;
        }
    }
}

void cashierShow() {
    while (true) {
        cout << endl;
        cout << "\n1. checkout order.\n2. See today's total revenue.\n3. Statistics on today's dishes.\n-1. EXIT\n";
        int flag;
        cin >> flag;
        if (flag == 1) {
            cout << endl;
            cout << "\nPlease enter the table number you want to checkout:";
            int tableCode;
            cin >> tableCode;
            cashierEntity::checkoutByTable(tableCode);
            cout << endl;
        } else if (flag == 2) {
            cout << endl;
            cout << "total consumers:" << alreadyConsumer.size() << "\ntoday's total revenue:"
                 << cashierEntity::countEarning() << endl;
            cout << endl;
        } else if (flag == 3) {
            cout << endl;
            cout << "Finished:\n";
            cooksEntity::viewAllFinishedDishes();
            cout << endl;
            cout << "Unfinished:\n";
            cooksEntity::viewAllUnfinishedDishes();
            cout << endl;
        } else {
            break;
        }
    }
}

void waiterShow() {
    while (true) {
        cout << endl;
        cout << "\n1. view all orders.\n2. Deliver food or add dishes.\n-1. EXIT\n";
        int flag_1;
        cin >> flag_1;
        if (flag_1 == 1) {
            cout << endl;
            all_notCheckout_orders();
            cout << endl;
        } else if (flag_1 == 2) {
            cout << endl;
            cout << "\nPlease enter the table number you want to serve:";
            int tableNumber;
            cin >> tableNumber;
            waiterEntity::deliverServe(tableNumber);
            cout << endl;
        } else {
            break;
        }
    }
}

void all_notCheckout_orders() {
    for (auto i: allConsumer) {
        if (i.getIsCheckout() == 0) {
            cout << i;
        }
    }
}

void all_unfinished_orders() {
    for (auto i: allConsumer) {
        if (i.getConStatus() == 0 && i.getIsCheckout() == 0) {
            cout << i;
        }
    }
}

void all_notDeliver_orders() {
    for (auto i: allConsumer) {
        if (i.getConRemark() == 0) {
            cout << i;
        }
    }
}

void viewAllDishes() {
    viewDishes();
    viewBeverage();
}

void viewDishes() {
    cout << setiosflags(ios_base::left) << setw(14) << "���"
         << setiosflags(ios_base::left) << setw(14) << "����"
         << setiosflags(ios_base::left) << setw(14) << "�۸�" << endl;
    for (auto &i: list) {
        cout << setiosflags(ios_base::left) << setw(14) << i.dishCode
             << setiosflags(ios_base::left) << setw(14) << i.dishName
             << setiosflags(ios_base::left) << setw(14) << i.dishPrice << endl;
    }
}

void viewBeverage() {
    cout << setiosflags(ios_base::left) << setw(14) << "���"
         << setiosflags(ios_base::left) << setw(14) << "��ˮ����"
         << setiosflags(ios_base::left) << setw(14) << "�۸�"
         << setiosflags(ios_base::left) << setw(14) << "���" << endl;
    for (auto &i: bevList) {
        cout << setiosflags(ios_base::left) << setw(14) << i.bevCode
             << setiosflags(ios_base::left) << setw(14) << i.bevName
             << setiosflags(ios_base::left) << setw(14) << i.bevPrice
             << setiosflags(ios_base::left) << setw(14) << i.bevStock << endl;
    }
}