#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <numeric>
#include <climits>
#include <iomanip>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <fstream>
using namespace std;

set<string> maNhanVien; //phục vụ cho hàm check mã nhân viên có trùng hay không

//hàm check
bool checkLuong(string luong);
bool checkNgayCong(string ngayCong);
bool checkSDT(string sdt);
bool checkEmail(string email);
bool checkMaNV(string ma);
bool checkTen(string ten);
bool checkNgaySinh(string ns);
void chuanHoaNgaySinh(string& ns);
void chuanHoaTen(string& ten);

struct nhanVien {
	string ma, ten, ns, email, diaChi, sdt;
	string ngayCong, luong;
	long long thucLinh;
	
	//@Overide
	friend istream& operator >> (istream& in, nhanVien& x) {
		// nhap ma nhan vien kem check ma co hop le hay khong
		cout << "Ma nhan vien : ";
		getline(in, x.ma);
		while (maNhanVien.count(x.ma) || !checkMaNV(x.ma) ||  stoll(x.ma) < 0) {
			cout << "Ma nhan vien khong hop le, vui long nhap lai : ";
			getline(in, x.ma);
			if (!maNhanVien.count(x.ma) && checkMaNV(x.ma) && stoll(x.ma) > 0) {
				maNhanVien.insert(x.ma);
				break;
			}
		}
		maNhanVien.insert(x.ma);


		//nhap ten nhan vien va check ten co hop le hay khong
		cout << "Ten nhan vien : ";
		getline(in, x.ten);
		while (!checkTen(x.ten)) {
			cout << "Ten khong hop le, vui long nhap lai ten : ";
			getline(in, x.ten);
			if (checkTen(x.ten)) {
				break;
			}
		}
		chuanHoaTen(x.ten);

		//nhap ngay sinh va check co hop le hay khong
		cout << "Ngay sinh (dinh dang xx/xx/xxxx) : ";
		getline(in, x.ns);
		while (!checkNgaySinh(x.ns)) {
			cout << "Ngay sinh khong hop le, vui long nhap lai : ";
			getline(in, x.ns);
			if (checkNgaySinh(x.ns)) {
				chuanHoaNgaySinh(x.ns);
				break;
			}
		}

		//nhap email va check email hop le hay khong (co dau @ hay khong ?)
		cout << "Email : ";
		getline(in, x.email);
		while (!checkEmail(x.email)) {
			cout << "Email khong hop le, vui long nhap lai : ";
			getline(in, x.email);
			if (checkEmail(x.email)) {
				break;
			}
		}

		//Nhap dia chi
		cout << "Dia chi : ";
		getline(in, x.diaChi);

		//Nhap sdt va check sdt hop le hay khong (có chữ ở trỏng hay ko)
		cout << "So dien thoai : ";
		getline(in, x.sdt);
		while (!checkSDT(x.sdt)) {
			cout << "So dien thoai khong hop le, vui long nhap lai : ";
			getline(in, x.sdt);
			if (checkSDT(x.sdt)) break;
		}

		//nhap ngay cong
		cout << "Ngay cong : ";
		getline(in, x.ngayCong);
		while (!checkNgayCong(x.ngayCong)) {
			cout << "Ngay cong khong hop le, vui long nhap lai : ";
			getline(in, x.ngayCong);
			if (checkNgayCong(x.ngayCong)) break;
		}

		//nhap luong (Lương có thể âm ?)
		cout << "Luong : ";
		getline(in, x.luong);
		while (!checkLuong(x.luong)) {
			cout << "Luong khong hop le, vui long nhap lai : ";
			getline(in, x.luong);
		}

		//Tinh thuc linh
		int ngayCongInt = stoi(x.ngayCong);
		long long luongLong = stoll(x.luong);
		x.thucLinh = ngayCongInt * luongLong;


		return in;
	}
	friend ostream& operator << (ostream& out, nhanVien x) {
		out << "Ma : " << x.ma << "\nTen : " << x.ten << "\nNgay Sinh : " << x.ns <<
			"\nEmail : " << x.email << "\nDia Chi : " << x.diaChi << "\nSDT : " << x.sdt <<
			"\nNgay Cong : " << x.ngayCong << "\nLuong : " << x.luong << "\nThuc Linh : " << x.thucLinh << endl;
		return out;
	}
	string getMa() {
		return ma;
	}
	string getTen() {
		return ten;
	}
	long long getThucLinh() {
		return thucLinh;
	}
};

struct node {
	nhanVien data;
	node* next;
};

node* makeNode(nhanVien x) {
	node* newNode = new node;
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}

void themNhanVien(node*& head, nhanVien x) {
	node* newNode = makeNode(x);
	if (head == NULL) {
		head = newNode;
		return;
	}
	node* tmp = head;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = newNode;
}
void xoaDau(node*& head) {
	node* xoa = head;
	head = head->next;
	delete xoa;
}
void xoaNhanVien(node*& head, string ma) {
	if (!maNhanVien.count(ma)) {
		cout << "Khong phat vien ma nhan vien\n";
		return;
	}
	if (head == NULL) {
		cout << "Danh sach rong, khong the xoa\n";
		return;
	}
	int cnt = 0;
	node* tmp = head;
	node* nodeMa = head;
	while (nodeMa->data.getMa() != ma) {
		nodeMa = nodeMa->next;
		cnt++;
	}
	if (cnt == 0) {
		xoaDau(head);
		maNhanVien.erase(ma);
		return;
	}
	for (int i = 0; i < cnt - 1; i++) {
		tmp = tmp->next;
	}
	node* xoa = tmp->next;
	tmp->next = nodeMa->next;
	maNhanVien.erase(ma);
	delete xoa;
}
void print(node* head) {
	while (head != NULL) {
		cout << head->data;
		head = head->next;
		cout << endl;
	}
}

void getMaNhanVien(node* head, string ten) {
	while (head->data.getTen() != ten) {
		head = head->next;
	}
	cout << head->data;
}
int main()
{
	node* quanliNV = NULL;
	while (true) {
		cout << "-----QUAN LI NHAN VIEN-----\n";
		cout << "1. Nhap danh sach nhan vien\n";
		cout << "2. Doc danh sach nhan vien tu file\n";
		cout << "3. Tim thong tin nhan vien theo ma nhan vien\n";
		cout << "4. Tim thong tin nhan vien theo ten\n";
		cout << "5. Tim nhan vien thuc linh thap nhat\n";
		cout << "6. Sap xep danh sach nhan vien giam dan theo thuc linh\n";
		cout << "7. Xoa 1 nhan vien theo ma ra khoi danh sach\n";
		cout << "8. Them 1 nhan vien theo ma vao danh sach\n";
		cout << "9. Sua thong tin 1 nhan vien theo ma\n\n";
		cout << "Lua chon : ";


		int choice;
		cin >> choice;
		cout << endl;
		cin.ignore();

		if (choice == 1) {
			fstream xuatFile("DSNV.txt", ios::out);
			cout << "Nhap so luong nhan vien : ";
			int soLuong; cin >> soLuong;
			cin.ignore();
			cout << endl;
			vector<nhanVien> danhSachNhanVien;
			for (int i = 0; i < soLuong; i++) {
				nhanVien x;
				cin >> x;
				cout << endl;
				danhSachNhanVien.push_back(x);
				themNhanVien(quanliNV, x);
			}
			for (nhanVien x : danhSachNhanVien) {
				xuatFile << x << endl;
				cout << x << endl;
			}
			xuatFile.close();
		}
		else if (choice == 2) {
			fstream nhapFile("DSNV.txt", ios::in);
			vector<string> docFile;
			string line;
			while (getline(nhapFile, line)) {
				if (!line.empty()) {
					docFile.push_back(line);
				}
			}
			vector<nhanVien> danhSachNV;
			for (int i = 0; i < docFile.size() - 8; i += 9) {
				nhanVien nv;
				nv.ma = docFile[i].substr(5);
				if (maNhanVien.count(nv.ma) || !checkMaNV(nv.ma) || stoll(nv.ma) < 0) {
					if (maNhanVien.count(nv.ma)) {
						cout << "Ma nhan vien : " + nv.ma + " da co trong danh sach\n\n";
					}
					else cout << "Ma nhan vien : " + nv.ma + " khong hop le\n\n";
				}
				else {
					maNhanVien.insert(nv.ma);
					nv.ten = docFile[i + 1].substr(6);
					nv.ns = docFile[i + 2].substr(12);
					nv.email = docFile[i + 3].substr(8);
					nv.diaChi = docFile[i + 4].substr(10);
					nv.sdt = docFile[i + 5].substr(6);
					nv.ngayCong = docFile[i + 6].substr(12);
					nv.luong = docFile[i + 7].substr(8);
					nv.thucLinh = stoi(docFile[i + 8].substr(12));
					danhSachNV.push_back(nv);
				}
			}
			for (nhanVien x : danhSachNV) {
				themNhanVien(quanliNV,x);
			}
			print(quanliNV);
		}
		else if (choice == 4) {
			string tenNV;
			cout << "Nhap ten nhan vien : ";
			getline(cin, tenNV);
			chuanHoaTen(tenNV);
			getMaNhanVien(quanliNV, tenNV);
		}
		else if (choice == 5) {

		}
		else if (choice == 7) {
			string mnv; 
			cout << "Nhap ma nhan vien muon xoa : ";
			cin >> mnv;
			xoaNhanVien(quanliNV,mnv);
			cout << "\nDanh sach nhan vien sau khi xoa : \n";
			print(quanliNV);
		}
	}
}


bool checkLuong(string luong) {
	for (int i = 0; i < luong.length(); i++) {
		if (!isdigit(luong[i])) {
			return false;
		}
	}
	return true;
}
bool checkNgayCong(string ngayCong) {
	for (int i = 0; i < ngayCong.length(); i++) {
		if (!isdigit(ngayCong[i])) {
			return false;
		}
	}
	int intNgayCong = stoi(ngayCong);
	if (intNgayCong < 0) return false;
	return true;
}
bool checkSDT(string sdt) {
	for (int i = 0; i < sdt.length(); i++) {
		if (!isdigit(sdt[i])) {
			return false;
		}
	}
	return true;
}
bool checkEmail(string email) {
	if (!isalnum(email[0])) return false;
	int cntDot = 0;
	int cntA = 0;
	for (int i = 0; i < email.length(); i++) {
		if (email[i] == '.') cntDot++;
		if (email[i] == '@') cntA++;
	}
	if (cntA != 1) return false;
	if (cntDot == 0) return false;
	return true;
}
bool checkMaNV(string ma) {
	for (int i = 0; i < ma.length(); i++) {
		if (!isdigit(ma[i])) {
			return false;
		}
	}
	return true;
}
bool checkTen(string ten) {
	for (int i = 0; i < ten.length(); i++) {
		if (!isalpha(ten[i]) && ten[i] != ' ') {
			return false;
		}
	}
	return true;
}
bool checkNgaySinh(string ns) {
	if (!isdigit(ns[0])) return false;
	chuanHoaNgaySinh(ns);
	stringstream ss(ns);
	string nam, thang, ngay;
	getline(ss, ngay, '/');
	getline(ss, thang, '/');
	getline(ss, nam, '/');
	if (nam.length() > 4 || thang.length() > 2 || ngay.length() > 2) return false;
	for (int i = 0; i < ns.length(); i++) {
		if (ns[i] == '/') continue;
		else {
			if (!isdigit(ns[i])) {
				return false;
			}
		}
	}
	int intNam = stoi(nam);
	int intThang = stoi(thang);
	int intNgay = stoi(ngay);
	if (intNam > 2025 || intThang > 12 || intNgay > 31) return false;
	return true;
}
void chuanHoaNgaySinh(string& ns) {
	for (int i = 0; i < ns.size(); i++) {
		if (ns[i] == '.' || ns[i] == '-') {
			ns[i] = '/';
		}
	}
	if (ns[1] == '/') {
		ns = "0" + ns;
	}
	if (ns[4] == '/') {
		ns.insert(3, "0");
	}
}
void chuanHoaTen(string& ten) {
	stringstream ss(ten);
	string res = "";
	string tmp;
	while (ss >> tmp) {
		res += toupper(tmp[0]);
		for (int i = 1; i < tmp.length(); i++) {
			res += tolower(tmp[i]);
		}
		res += " ";
	}
	res.pop_back();
	ten = res;
}
