#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class SinhVien{
private:
    string ten;
    int tuoi;
    int msv;
    double gpa;
public:
	SinhVien(string t = " ", int age = 0, int m = 0, double g = 0.0)
	: ten(t), tuoi(age), msv(m), gpa(g) {}
	string getten() const {	return ten;	}
	int gettuoi() const { return tuoi; }
	int getmsv() const { return msv; }
	double getgpa() const {	return gpa;	}
	string &setten(){ return ten; }
	int &settuoi(){	return tuoi; }
	double &setgpa(){ return gpa; }
    friend istream& operator>>(istream& in, SinhVien& sv);
    friend ostream& operator<<(ostream& out, const SinhVien& sv);
    bool operator<(const SinhVien& a) const {
        return gpa < a.gpa;
    }
};

istream& operator>>(istream& in, SinhVien& sv){
    in.ignore();
    cout << "Nhap ten : "; getline(in, sv.ten);
    cout << "Nhap tuoi : "; in >> sv.tuoi;
    cout << "Nhap msv : "; in >> sv.msv;
    cout << "Nhap gpa : "; in >> sv.gpa;
    return in;
}

ostream& operator<<(ostream& out, const SinhVien& sv){
    out << left << setw(30) << sv.ten
    	<< setw(15) << sv.tuoi
    	<< setw(15) << sv.msv
    	<< setw(15) << sv.gpa << endl;
    return out;
}

class Qlsv{
private:
    list<SinhVien> l;
public:
    void nhaptufile(const string& filename);
    void ghifile(const string& filename);
    void them();
    void xoa();
    void sua();
    void sapxeptheogpa();
    void timkiemten();
    void maxgpa();
	void xuatds();
};

void Qlsv::nhaptufile(const string& filename){
	ifstream doc(filename);
	if(!doc){
		cout << "Khong mo duoc file!" << endl;
		return;
	}
	string ten;
	int tuoi, msv;
	double gpa;
	while(getline(doc, ten)){
		doc >> tuoi >> msv >> gpa;
		SinhVien sv(ten, tuoi, msv, gpa);
		l.push_back(sv);
		doc.ignore();
	}
	doc.close();
}

void Qlsv::ghifile(const string& filename){
	ofstream ghi(filename);
	if(!ghi){
		cout << "Khong mo duoc file!" << endl;
		return ;
	}
	for(const auto &x : l){
		ghi << endl << "Ten : " << x.getten() 
			<< endl << "Tuoi : " << x.gettuoi()
			<< endl << "Ma : " << x.getmsv()
			<< endl << "GPA : " << x.getgpa() << endl;
	}
	cout << "Da ghi !" << endl;
	ghi.close();
}

void Qlsv::them(){
    SinhVien sv;
    cout << "Nhap thong tin sinh vien muon them : \n";
    cin >> sv;
    l.push_back(sv);
    cout << "Da them !\n";
}

void Qlsv::xoa(){
    if(l.empty()){
        cout << "Danh sach rong !" << endl;
        return ;
  	}
    int pos;
    cout << "Nhap vi tri can xoa : "; cin >> pos;
    if(pos > l.size() || pos < 1){
        cout << "Vi tri vua nhap khong hop le !" << endl;
    }else{
        auto it = l.begin();
        advance(it, --pos);
        l.erase(it);
        cout << "Da xoa !\n";
    }
}

void Qlsv::sua(){
	if(l.empty()){
		cout << "Danh sach rong !" << endl;
		return ;
	}
	int m ; cout << "Nhap ma cua sinh vien can sua : "; cin >> m;
	auto it = find_if(l.begin(), l.end(), [m](const SinhVien &sv){
		return sv.getmsv() == m;
	});
	if(it != l.end()){
		cout << "Sinh vien can sua la : " << *it;
		cin.ignore();
		string ten;
		int tuoi, msv;
		double gpa;
		cout << "Nhap ten moi : " ; getline(cin, ten);
		cout << "Nhap tuoi moi : " ; cin >> tuoi ;
		cout << "Nhap GPA moi : " ; cin >> gpa;
		it->setten() = ten;
		it->settuoi() = tuoi;
		it->setgpa() = gpa;
	}else{
		cout << "Khong tim thay ma vua nhap !" << endl;
	}
}

void Qlsv::sapxeptheogpa(){
    l.sort();
    cout << "Da sap xep !\n";
}

void Qlsv::timkiemten(){
    if(l.empty()){
        cout << "Danh sach rong !" << endl;
        return ;
    }
    string s;
    cin.ignore();
    cout << "Nhap ten sinh vien can tim: ";
    getline(cin, s);
    auto it = find_if(l.begin(), l.end(), [s](const SinhVien &sv){
    	return sv.getten() == s;
	});
	if(it != l.end()){
		cout << "Tim thay !\n";
		cout << "Thong tin sinh vien vua tim :\n";
		cout << *it;
	}else{
		cout << "Khong tim thay\n";
	}
}

void Qlsv::maxgpa(){
	if(l.empty()){
		cout << "Danh sach rong !" << endl;
		return ;
	}
    auto it = max_element(l.begin(), l.end());
    double s = it->getgpa();
    for(auto x : l){
    	if(x.getgpa() == s){
    		cout << x ;
		}
	}
}

void Qlsv::xuatds(){
    if(l.empty()){
        cout << "Danh sach rong !" << endl;
        return ;
    }
    cout << left << setw(30) << "Ten"
    	 << setw(15) << "Tuoi"
    	 << setw(15) << "MSV"
    	 << setw(15) << "GPA" << endl;
    	 
	cout << string(65, '-') << endl;
    for(const auto& x : l){
    	cout << x;
    }
}

class APP{
	private:
	    Qlsv q;
	public:
	    void menu();
};

void APP::menu(){
    int luachon;
    do{
        cout << "\t\t~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~\n" << endl;
        cout << "1. Nhap danh sach sinh vien tu file nhapds" << endl;
        cout << "2. Ghi danh sach sinh vien vao file ghids" << endl;
        cout << "3. Them sinh vien vao cuoi danh sach" << endl;
        cout << "4. Xoa sinh vien tai vi tri chi dinh" << endl;
        cout << "5. Sua thong tin sinh vien theo msv" << endl;
        cout << "6. Sap xep danh sach theo GPA tang dan" << endl;
        cout << "7. Tim kiem sinh vien theo ten" << endl;
        cout << "8. Tim sinh vien co GPA cao nhat" << endl;
        cout << "9. Xuat danh sach sinh vien" << endl;
        cout << "0. Thoat" << endl;
        cout << "\t\t-------------------------------\n" << endl;
        cin >> luachon;

        switch(luachon){
            case 1: q.nhaptufile("nhapds.txt"); cout << endl; break;
            case 2: q.ghifile("ghids.txt"); cout << endl; break;
            case 3: q.them(); cout << endl; break;
            case 4: q.xoa(); cout << endl; break;
            case 5: q.sua(); cout << endl; break;
            case 6: q.sapxeptheogpa(); cout << endl; break;
            case 7: q.timkiemten(); cout << endl; break;
            case 8: q.maxgpa(); cout << endl; break;
            case 9: q.xuatds(); cout << endl; break;
            case 0: cout << "Thoat chuong trinh" << endl; break;
            default: cout << "Lua chon khong hop le ! Vui long nhap lai : \n" << endl; break;
        }
    }while(luachon != 0);
}

int main(){
    APP app;
    app.menu();
    return 0;
}
