#include <iostream>
#include<string>
#include"Vector.cpp"

using namespace std;

class Student {
private:
    string name;
    string id;
    string birthday;
    string gender;
    string className;

public:
    Student(string name = "", string id = "", string birthday = "", string gender = "", string className = "")
        : name(name), id(id), birthday(birthday), gender(gender), className(className) {}

    bool operator<(const Student& other) const {
        return name < other.name;
    }

    bool operator>(const Student& other) const {
        return name > other.name;
    }

    bool operator==(const Student& other) const {
        return id == other.id;
    }

    string getID() const {
        return id;
    }
    string getName(){
        return name;
    }

    void input() {
        cin.ignore();
        cout << "Nhap ten: ";
        getline(cin, name);
        cout << "Nhap ma sinh vien: ";
        getline(cin, id);
        cout << "Nhap ngay sinh: ";
        getline(cin, birthday);
        cout << "Nhap gioi tinh: ";
        getline(cin, gender);
        cout << "Nhap lop hoc: ";
        getline(cin, className);
    }

    void display() const {
        cout << "Ten: " << name << endl;
        cout << "Ma sinh vien: " << id << endl;
        cout << "Ngay sinh: " << birthday << endl;
        cout << "Gioi tinh: " << gender << endl;
        cout << "Lop hoc: " << className << endl;
    }
};


class StudentManager {
private:
    Vector<Student> studentsList;

public:
    void addStudent() {
        char choice;

        do {
            int n;
            cout << "Nhap so luong sinh vien: ";
            cin >> n;

            for (int i = 0; i < n; i++) {
                cout << "Nhap thong tin sinh vien thu " << i + 1 << ":" << endl;
                Student student;
                student.input();
                studentsList.pushBack(student);
            }

            cout << "Ban co muon nhap tiep khong? (c/k): ";
            cin >> choice;

        } while (choice == 'c');
    }

    void deleteStudent() {
        string msv;
        cout << "Nhap ma sinh vien cua sinh vien can xoa: ";
        cin.ignore();
        getline(cin, msv);

        int index = studentsList.binarySearch(Student("", msv));

        if (index != -1) {
            studentsList[index] = studentsList[studentsList.getSize() - 1];
            studentsList.popBack();
            cout << "Da xoa sinh vien co ma sinh vien " << msv << endl;
        } else {
            cout << "Khong tim thay sinh vien co ma sinh vien " << msv << endl;
        }
    }

    void editStudent() {
        string msv;
        cout << "Nhap ma sinh vien cua sinh vien can sua: ";
        cin.ignore();
        getline(cin, msv);

        int index = studentsList.binarySearch(Student("", msv));

        if (index != -1) {
            Student& studentToUpdate = studentsList[index];

            cout << "Nhap thong tin moi cho sinh vien co ma sinh vien " << msv << ":" << endl;
            studentToUpdate.input();

            cout << "Da sua doi thong tin cho sinh vien co ma sinh vien " << msv << endl;
        } else {
            cout << "Khong tim thay sinh vien co ma sinh vien " << msv << endl;
        }
    }
    void sortByName(){
       studentsList.quickSort();
       cout<<"Danh sach da duoc dap sep\n";
    }
    void displayStudents() {
        if (studentsList.getSize() == 0) {
            cout << "Danh sach sinh vien rong." << endl;
        } else {
            cout << "Danh sach sinh vien:\n";
            for (int i = 0; i < studentsList.getSize(); i++) {
                cout << "Sinh vien thu " << i + 1 << ":\n";
                studentsList[i].display();
                cout << endl;
            }
        }
    }
    void searchByName(){
        string nameSearch;
        cout<<"Nhap ten sinh vien can tim: \n";
        cin.ignore();
        getline(cin,nameSearch);
        if(studentsList.getSize()==0){
            cout<<"Danh sach sinh vien rong\n";
        }else{
        Vector<Student> machingStudent;
          for (int i=0;i<studentsList.getSize();i++){
            if(studentsList[i].getName()==nameSearch){
                machingStudent.pushBack(studentsList[i]);
            }
          }
          if(machingStudent.getSize()==0){
            cout<<"Khong tim thay sinh vien co ten: \n"<<nameSearch;
          }else{
             cout<<"Danh sach sinh vien co ten "<<nameSearch<<" la :\n";
             for (int i=0;i<machingStudent.getSize();i++){
                machingStudent[i].display();
             }
          }
        }
    }
};

int main() {
    StudentManager manager;
    int lc;

    do {
        cout << "---------------MENU---------------\n";
        cout << "1. Them sinh vien sau khi nhap danh sach\n";
        cout << "2. Xoa sinh vien theo ma sinh vien\n";
        cout << "3. Sua thong tin sinh vien\n";
        cout<<  "4. Sap xep sinh vien\n";
        cout << "5. Hien thi danh sach sinh vien\n";
        cout<<  "6.Tim kiem sinh vien theo ten\n";
        cout<<  "----------------------------------\n";
        cout << "Nhap lua chon (0 de thoat): ";
        cin >> lc;

        switch (lc) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.deleteStudent();
                break;
            case 3:
                manager.editStudent();
                break;
            case 4:
                manager.sortByName();
                break;
            case 5:
                manager.displayStudents();
                break;
            case 6:
                manager.searchByName();
                break;
        }

    } while (lc != 0);

    return 0;
}
