#ifndef MAIN_H
#define MAIN_H
#include<iostream>
#include<cmath>
#include<fstream>
#include<string>

using namespace std;
#define MAXSIZE 15

class table
{
public:
    int ID;
    string name;
    int age;
    table* next;
    table(int ID, string name, int age, table* next)
    {
        this->ID = ID;
        this->name = name;
        this->age = age;
        this->next = next;
    }
};

class restaurant
{
public:
    table *recentTable;
    restaurant()
    {
        recentTable = nullptr;
    }
    ~restaurant()
    {
        delete recentTable;
    }
    table* finsert(table *last, int ID, string name, int age)
    {
        if (last != nullptr)
            return last;
        table *temp = new table(ID, "", age, last);

        last = temp;
        last->next = last;
        return last;
    }
    table *insert(table *last, int ID, string name, int age)
    {
        if (last == NULL)
            return finsert(last, ID, name, age);
        table *temp = new table (ID, name, age, last->next);
        last -> next = temp;
        last = temp;
        return last;
    }
};
#endif

//tạo hàng đợi
class queue {
public:
    class Node; 
protected:
    Node* head;
    Node* tail;
    int count;
public:
    queue() {
        this->head = NULL;
        this->tail = NULL;
        this->count = 0;
    }
    void push(string name, int age) {
        Node* p = new Node(name,age,NULL);
        if(count == 0) {
            head = tail = p;
            count = count + 1;
        }
        else {
            tail -> next = p;
            tail = tail->next;
            count = count + 1;
        }
    }
    int size() {
        return count;
    }
    void pop() {
        Node *p = this->head;
        head = p->next;
        count--;
    }
    string front() {
        Node *p = this->head;
        return p->name;
    }
    int age_front() {
        return head->age;
    }
    bool empty() {
        if(count == 0)  return true;
        return false;
    }
    void top(string name, int age) {
        Node* temp = new Node(name,age,NULL);
        if(count == 0) {
            push(name, age);
            return;
        }
        temp->next = head;
        head = temp;
        count++;
        return;
    }
    void removeAt(int index) {
        Node *p = this->head;
        if(index == 0) { 
            head = p->next;
            count--;
            return;
        }
        else if(index == (this->count)-1) {
            while((p->next)->next!=NULL) {
                p = p->next;
            }
            delete p->next;
            p->next = NULL;
            this->tail = p;
            count--;
            return;
        }
        else {
            for(int i=1;i<index;i++) {
                p = p->next;
            }
            Node *t = p->next;
            p->next = p->next->next;
            delete t;
            count--;
            return;
        }
    }
    void remove(string name, int age) {
        Node *p = this->head;
        int i = 0;
        while(p) {
            if(p->name == name && p->age == age) {
                removeAt(i);
                return;
            }
            p = p->next;
            i++;
        }
    }

public:
    class Node {
    private:
        string name;
        int age;
        Node* next;
        friend class queue;
    public:
        Node() {
            name = "";
            age = 0;
            next = NULL;
        }
        Node(Node* next) {
            this->next = next;
        }
        Node(string name, int age, Node* next) {
            this->name = name;
            this->age = age;
            this->next = next;
        }
    };
};
//Hàm REG>>Hoàn thành
void REG(int ID, string name, int age, restaurant* r, queue &customer, queue &qu, int &ID_PT) {
    if(age < 16 || age > 115)    return;
    restaurant *re = r;
    bool empty = false;
    if(ID == -1) {
        while(re->recentTable->ID != 1) {
            re->recentTable = re->recentTable->next;
        }
        for(int i=1;i<=MAXSIZE;i++) {
            if(re->recentTable->name == "") {
                re->recentTable->name = name;
                re->recentTable->age = age;
                ID_PT = re->recentTable->ID;
                customer.top(name,age);
                return;
            }
            re->recentTable = re->recentTable->next;
        }
        if(qu.size() < MAXSIZE) {
            qu.push(name,age);
        }
        return;
    }
    while(re->recentTable->ID != 1) {
        re->recentTable = re->recentTable->next;
    }
    for(int i=1;i<=MAXSIZE;i++) {
        if(re->recentTable->ID == ID) {
            if(re->recentTable->name == "") {
                re->recentTable->name = name;
                re->recentTable->age = age;
                ID_PT = re->recentTable->ID;
                customer.top(name,age);
                return;
            }
            else 
                break;
        }
        re->recentTable = re->recentTable->next;
    }
    for(int i=ID+1;i<=MAXSIZE;i++) {
        if(re->recentTable->name == "") {
            re->recentTable->name = name;
            re->recentTable->age = age;
            ID_PT = re->recentTable->ID;
            customer.top(name,age);
            return;
        }
        re->recentTable = re->recentTable->next;
    }
    if(qu.size() < MAXSIZE) {
        qu.push(name,age);
    }
    return;
}

void REGM(string name, int age, int NUM, restaurant *r, int &ID_PT) {
    restaurant *re = r;
    int id_merge = -1;
    int table_empty = 0;
    for(int i=1;i<=MAXSIZE;i++) {
        if(re->recentTable->name == "") {
            table_empty++;
        } 
        else {
            table_empty = 0;
        }
        if(table_empty == NUM) {
            int id_new = 0;
            if(re->recentTable->ID < NUM) {
                id_new = MAXSIZE - NUM + re->recentTable->ID;
            }
            else {
                id_new = re->recentTable->ID - NUM + 1;
            }
            if(id_merge < id_new) {
                id_merge = id_new;
            }  
            table_empty--;  
        }
        re->recentTable = re->recentTable->next;
    }
    if(id_merge == -1)  return;
    for(int i=1;i<=MAXSIZE;i++) {
        if(re->recentTable->ID == id_merge) {
            break;
        }
        re->recentTable = re->recentTable->next;
    }
    re->recentTable->name = name;
    re->recentTable->age = age;
    re->recentTable = re->recentTable->next;    
    for(int i=1;i<=NUM-1;i++) {
        re->recentTable->ID = 0;
        re->recentTable = re->recentTable->next;     
    }
    ID_PT = id_merge;
    return;
}

void CLE(int ID, restaurant* r, queue &customer, queue &qu) { //chưa xong
    restaurant *re = r;
    if(ID <= 0 || ID > MAXSIZE) return;
    //duyệt đến vị trí id
    bool checkid = false;//check xem có id cần xoá ko
    for(int i=1;i<=MAXSIZE;i++) {
        if(re->recentTable->ID == ID) {
            checkid = true;
            break;
        }
        re->recentTable = re->recentTable->next;
    }
    if(checkid == false)    return;
    //Single Table
    if(re->recentTable->ID + 1 == re->recentTable->next->ID || (re->recentTable->ID == MAXSIZE && re->recentTable->next->ID == 1)) {
        if(re->recentTable->name == "") return; //vị trí ID ko có người
        string name = re->recentTable->name;
        int age = re->recentTable->age;
        customer.remove(name,age);
        if(!qu.empty()) {
            re->recentTable->name = qu.front();
            re->recentTable->age = qu.age_front();
            qu.pop();
        }
        else {
            re->recentTable->name = "";
            re->recentTable->age = 0;
        }
    } 
    //Merge Table 
    else {
        int id = ID + 1;
        if(id > MAXSIZE)    id = 1;
        if(!qu.empty()) {   //Nếu hàng đợi có người thì cho nó vào ngồi ăn
            re->recentTable->name = qu.front();
            re->recentTable->age = qu.age_front();
            qu.pop();
        }
        else {
            re->recentTable->name = "";//đưa tên và tuổi của khách hàng tại vị trí ID về 0
            re->recentTable->age = 0;
        }
        //re1 -> ID = 7
        re->recentTable = re->recentTable->next;
        while(id != re->recentTable->ID) {
            re->recentTable->ID = id;
            if(!qu.empty()) {
                re->recentTable->name = qu.front();
                re->recentTable->age = qu.age_front();
                qu.pop();
            }
            else {
                re->recentTable->name = "";
                re->recentTable->age = 0;
            }
            re->recentTable = re->recentTable->next;
            id++;
            if(id > MAXSIZE) {
                id = 1;
            }
        }
        return;
    }
}

void PS(int NUM, queue customer, queue qu) {
    int total_cus = customer.size();
    
    //tính tổng khách hàng trong nhà hàng
    if(total_cus == 0)  {
        cout<<"Empty\n";
        return;
    }
    else if(NUM <= total_cus && NUM != -1) {
        int i=1;
        while(i<=NUM) {
            cout<<customer.front()<<"\n";
            customer.pop();
            i++;
        }
    }
    else if(NUM > total_cus && NUM <= 2*MAXSIZE) {
        while(!customer.empty()) {
            cout<<customer.front()<<"\n";
            customer.pop();
        }
        int i = 1;
        int n = NUM - total_cus;
        while(i<=n && !qu.empty()) {
            cout<<qu.front()<<"\n";
            qu.pop();
            i++;
        }
    }
    else if(NUM == -1) {
        while(!customer.empty()) {
            cout<<customer.front()<<"\n";
            customer.pop();
        }
        while(!qu.empty()) {
            cout<<qu.front()<<"\n";
            qu.pop();
        }
    }
}

void PQ(int NUM, queue qu) {
    if(qu.empty())
        cout<<"Empty\n";
    else if(NUM <= qu.size() && NUM > 0) {
        int i=1;
        while(i<=NUM) {
            cout<<qu.front()<<"\n";
            qu.pop();
            i++;
        }
    }
    else if(NUM == -1 || (NUM > qu.size() && NUM <= MAXSIZE)) {
        while(!qu.empty()) {
            cout<<qu.front()<<"\n";
            qu.pop();
        }
    }
}
void printSQ(queue qu) {
    while(!qu.empty()) {
        cout<<qu.front()<<"\n";
        qu.pop();
    }
}
void SQ(int NUM, queue qu) {    
    if(qu.empty())  {
        cout<<"Empty\n";
        return;
    }
    if(qu.size() == 1) {
        cout<<qu.front()<<"\n";
        return;
    } 
    if(NUM < 1 || NUM > MAXSIZE) {
        printSQ(qu);
        return;
    }
    queue q = qu;
    int n = qu.size();
    int i=1;
    queue qu_ans;
    if(NUM > qu.size()) {
        NUM = qu.size();
    }
    for(int i=1;i<=NUM;i++) {
        int max = 0;
        string name;
        while(!q.empty()) {
            if(max < q.age_front()) {
                max = q.age_front();
                name = q.front();
            }
            q.pop();
        }
        string name1 = qu.front();
        int age1 = qu.age_front();
        qu.pop();
        
        while(!qu.empty()) {
            if(qu.age_front() == max && qu.front() == name) {
                q.push(name1,age1);
                qu.pop();
                
            }
            else {
                q.push(qu.front(),qu.age_front());
                qu.pop();
            }
        }
        qu = q;
        qu_ans.push(name,max);
    }
    while(!qu.empty()) {
        qu_ans.push(qu.front(),qu.age_front());
        qu.pop();
    }
    qu = qu_ans;
    printSQ(qu);
}

void PT(int ID, restaurant* r) { 
    restaurant* re = r;
    for(int i=1;i<=MAXSIZE;i++) {
        if(re->recentTable->ID == ID)
            break;
        re->recentTable = re->recentTable->next;
    }
    for(int i=1;i<=MAXSIZE;i++) {
        if(re->recentTable->name != "") {
            cout<<re->recentTable->ID<<"-"<<re->recentTable->name<<"\n";
        }
        re->recentTable = re->recentTable->next;
    }
}

//Note Cập nhật ID_PT cho REG, REGM, CLE
//Làm lại hàm REGM
void simulate(string filename, restaurant* r) {
    ifstream filein;
	filein.open(filename, ios_base::in);
    string str = "";
    queue customer; //LL để lưu tên của khách hàng vào nhà hàng và được vào bàn
    queue qu; //LL lưu tên khách hàng vào nhà hàng nhưng không được vào bàn
    int ID_PT = 0;
    int Merge_Table = 0;
    while(!filein.eof()) {
        filein>>str;
        // Xử lí hàm REG
        if(str == "REG") {
            char check;
            filein>>check;
            if((check < '0' || check > '9') && check != ' ') {
                string name = "";
                getline(filein,name,' ');
                name = check + name;
                string Age;
                getline(filein,Age);
                int age = stoi(Age);                
                REG(-1,name,age,r,customer,qu,ID_PT);
            }
            else {
                string Id;
                getline(filein,Id,' ');
                Id = check + Id;
                int id = stoi(Id);
                string name;
                getline(filein,name,' ');
                string Age;
                getline(filein,Age);
                int age = stoi(Age);                
                REG(id,name,age,r,customer,qu,ID_PT);
            }        
        }
        //Xử lí hàm REGM
        else if(str == "REGM") {
            Merge_Table++;
            string name;
            getline(filein,name,' ');
            getline(filein,name,' ');
            string Age;
            getline(filein,Age,' ');
            int age = stoi(Age);
            string Num;
            getline(filein,Num);
            int NUM = stoi(Num);
            if(Merge_Table == 1) {            
                REGM(name,age,NUM,r,ID_PT);
            }
        }
        //Xử lí hàm CLE
        else if(str == "CLE") {
            string Id;
            getline(filein,Id);
            int id = stoi(Id);
            ID_PT = id;
            CLE(id,r,customer,qu);
        }
        //Xử lí hàm PS
        else if(str == "PS") {
            string NUM = "";
            getline(filein,NUM);
            if(NUM == "") {
                PS(-1,customer,qu);
            }
            else {
                int num = stoi(NUM);
                PS(num,customer,qu);
            }
        }
        else if(str == "PQ") {
            string NUM = "";
            getline(filein,NUM);
            if(NUM == "") {
                PQ(-1,qu);
            }
            else {
                int num = stoi(NUM);
                PQ(num,qu);
            }
        }
        else if(str == "SQ") {
            string NUM = "";
            
            getline(filein,NUM);
            int num = stoi(NUM);
            SQ(4,qu);
        }
        else if(str == "PT") {
            string ch;
            getline(filein,ch);
            PT(ID_PT,r);
        }
    }
    PT(ID_PT,r);
}

int main(int argc, char* argv[]) {

    restaurant* r = new restaurant();
    string fileName = "test.txt";

    //initialize table with ID, name and age
    for (int i = 1; i <= MAXSIZE; i++)
    {
        r->recentTable = r->insert(r->recentTable,i,"",0);
    }

    simulate(fileName,r);
    //restaurant* re = r;
    
    delete r;

    return 0;
}