#include <iostream>
#include<fstream>
#include "doublelinklist.cpp"
using namespace std;

class Students {
private:
    string name;
    string lop;
    string phoneNumber;
    float diemTB;

public:
    Students(string name = "", string lop = "", string phoneNumber = "", float diemTB = 0.0) {
        this->name = name;
        this->lop = lop;
        this->phoneNumber = phoneNumber;
        this->diemTB = diemTB;
    }
    void nhap(){
        cout<<"Nhap ten: ";
        cin.ignore();
        getline(cin,name);
        cout<<"\nNhap lop: ";
        cin.ignore();
        getline(cin,lop);
        cout<<"\nNhap so dien thoai: ";
        cin.ignore();
        getline(cin,phoneNumber);
        cout<<"\nNhap diem trung binh: ";
        cin>>diemTB;
    }

    friend ostream& operator<<(ostream& os, const Students& st) {
        os << "Ten: " << st.name << endl;
        os << "Lop: " << st.lop << endl;
        os << "So dien thoai: " << st.phoneNumber << endl;
        os << "Diem trung binh: " << st.diemTB << endl;
        return os;
    }
    float getDiemTB(){
       return diemTB;
    }
    string getName(){
       return name;
    }
    string getLop(){
       return lop;
    }
    string getPhoneNumber(){
       return phoneNumber;
    }
};

string ClassIfication(Students& st){
   if(st.getDiemTB()>=8.0){
      return "Gioi";
   }else if(st.getDiemTB()>=6.5){
     return "Kha";
   }else if(st.getDiemTB()>=5.0){
      return "Trung binh";
   }else{
       return "Yeu";
   }
}

class StudentsManager {
private:
    DoubleLinkList<Students> StudentsList;

public:
    void inputStudents() {
        int numStudents;
        cout << "Nhap so luong hoc sinh : ";
        cin >> numStudents;
        for (int i = 0; i < numStudents; i++) {
            Students st;
            st.nhap(); // Use nhap function to handle getline consistently
            StudentsList.InsertNodeEnd(st);
        }
    }

    void inputStudentsFormFile() {
        string filename;
        cout << "Nhap ten file can tim: ";
        cin.ignore();
        getline(cin, filename);
        ifstream inputFile(filename);
        // is_open kiem tra file da duoc mo hay chua
        if (!inputFile.is_open()) {
            cout << "Khong the mo file!" << endl;
            return;
        }
        // Hàm eof() trả về true khi con trỏ đã trỏ tới cuối file và với false thì ngược lại.
        while (!inputFile.eof()) {
            Students st;
            st.nhap();
            StudentsList.InsertNodeEnd(st);
        }
        inputFile.close();
    }
    void  displayStudentListWithClassification(){
        cout << "\nDanh sach hoc sinh va xep loai:\n";
        Node<Students>* current=StudentsList.getHead();
        while(current!=nullptr){
            cout<<"Name: "<<current->data.getName()<<endl;
            cout<<"Xep loai: "<<ClassIfication(current->data)<<endl;
            current=current->next;
        }
    }
    void displayFullStudentList(){
        cout << "\nDanh sach hoc sinh:\n";
        Node<Students>* current = StudentsList.getHead();
        while (current != nullptr) {
            cout << current->data << endl;  // Sử dụng toán tử nhập xuất đã được định nghĩa trong lớp Students
            current = current->next;
        }
    }
    void searchStudentFromNameAndClass(){
       string inputName,inputClass;
       cout<<"Nhap ten can tim: ";
       cin.ignore();
       getline(cin,inputName);
       cout<<"\nNhap lop can tim: ";
       cin.ignore();
       getline(cin,inputClass);
       Node<Students>* current=StudentsList.getHead();
       bool found=false;
       while(current!=nullptr){
        if(current->data.getName()==inputName && current->data.getLop()==inputClass){
            cout<<"So dien thoai cua hoc sinh "<<inputName<<"lop "<<inputClass<<" la : "<<current->data.getPhoneNumber()<<endl;
            found=true;
            break;
        }
        current=current->next;
       }
       if(!found){
        cout<<"Khong tim thay hoc sinh!"<<endl;
       }
    }
    void addInforStudent(){
        Students st;
        st.nhap();
        StudentsList.InsertNodeEnd(st);
        cout<<"Them hoc sinh moi thanh cong\n";
    }
    void deleteStudent(){
        string inputClass;
        cout<<"Nhap lop can xoa\n";
        cin.ignore();
        getline(cin,inputClass);
        Node<Students>* current=StudentsList.getHead();
        Node<Students>* prev=nullptr;
        while(current!=nullptr){
            if (current->data.getLop() == inputClass){
                Node<Students>* temp=current;
                if(prev!=nullptr){
                    prev->next=current->next;
                    if (current->next!=nullptr){
                        current->next->prev=prev;
                    }
                }else{
                   StudentsList.setHead(current->next);
                   if(current->next!=nullptr){
                       current->next->prev=nullptr;
                   }
                }
                delete temp;
                    cout<<"Da xoa toan bo hoc sinh tu lop : "<<inputClass<<endl;
                    current=(prev!=nullptr)?prev->next:StudentsList .getHead();
            }else{
               prev=current;;
               current=current->next;
            }
        }
    }
    void bubbleSortByDeiemTB(){
        int n=StudentsList.size();
        Node<Students>* current;
        Node<Students>* next;
        bool swapped;
        for (int i=0;i<n-1;i++){
            current=StudentsList.getHead();
            swapped=false;
            for (int j=0;j<n-i-1;j++){
                next=current->next;
                if (current->data.getDiemTB()<next->data.getDiemTB()){
                    if(current->prev!=nullptr){
                            current->prev->next=next;
                    }else{
                        StudentsList.setHead(next);
                    }
                    if(next->next!=nullptr){
                        next->next->prev=current;
                    }
                    current->next = next->next;
                    next->prev = current->prev;
                    next->next = current;
                    current->prev = next;

                    swapped=true;
                }else{
                   current=current->next;
                }
            }
            if(!swapped){
                break;
            }
        }
    }
    void insertStudentInSortedOrder() {
        Students newStudent;
        newStudent.nhap();
        Node<Students> *newNode = StudentsList.makeNode(newStudent);
        Node<Students> *current = StudentsList.getHead();
        Node<Students> *prev = nullptr;
        while (current != nullptr && current->data.getDiemTB() >= newStudent.getDiemTB()) {
            prev = current;
            current = current->next;
        }

        newNode->prev = prev;
        newNode->next = current;

        if (prev != nullptr) {
            prev->next = newNode;
        } else {
            StudentsList.setHead(newNode);
        }

        if (current != nullptr) {
            current->prev = newNode;
        }
    }


    void saveFile() {
        string fileName;
        cout << "\nNhap file can luu tru: ";
        cin.ignore();
        getline(cin, fileName);
        ofstream outputFile(fileName);
        if (!outputFile.is_open()) {
            cout << "\nKhong the mo file!";
            return;
        }
        Node<Students> *current = StudentsList.getHead();
        while (current != nullptr) {
            outputFile << current->data << endl;
            current = current->next;
        }
        outputFile.close();
        cout << "\nLuu tru file thanh cong";
    }
};



int main() {
    StudentsManager manager;


    while(1){
        cout<<"---------------MENU---------------\n";
        cout<<"1.Nhap danh sach hoc sinh tu ban phim\n";
        cout<<"2.Lay danh sach sinh vien tu file\n";
        cout<<"3.In danh sach hoc sinh va xep loai\n";
        cout<<"4.in danh sach thong tin sinh vien day du\n";
        cout<<"5.Tim hoc sinh qua ten va lop\n";
        cout<<"6.Them hoc sinh moi\n";
        cout<<"7.Xoa sinh vien theo lop\n";
        cout<<"8.Sap xep sinh vien\n";
        cout<<"9.Chen hoc sinh\n";
        cout<<"10.Save file\n";
        cout<<"11.Exit\n";
        cout << "----------------------------------\n";
        int lc;
        cout<<"Nhap lua chon :";
        cin>>lc;
        if (lc==1){
           manager.inputStudents();
        }
        else if (lc==2){
            manager.inputStudentsFormFile();
        }else if(lc==3){
             manager.displayStudentListWithClassification();
        }else if(lc==4){
            manager.displayFullStudentList();
        }else if (lc==5){
            manager.searchStudentFromNameAndClass();
        }else if(lc==6){
            manager.addInforStudent();
        }else if(lc==7){
            manager.deleteStudent();
        }else if(lc==8){
            manager.bubbleSortByDeiemTB();
        }else if(lc==9){
            manager.insertStudentInSortedOrder();
        }else if(lc==10){
            manager.saveFile();
        }else if(lc==11){
           break;
        }
    }

    return 0;
}
