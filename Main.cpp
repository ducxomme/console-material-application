#include "NhanVien.cpp"

string dsChucNang[]={"VAT TU", "NHAN VIEN", "IN HOA DON", "DANH SACH VAT TU XUAT CAO NHAT"};



const int so_item = 5;
const int dong = 11;
const int cot = 40 ;
const int Up = 72;
const int Down = 80;
char thucdon [so_item][50] = {"1. Vat Tu                        ",
			                  "2. Nhan Vien                     ",
			                  "3. In Hoa Don                    ",
			                  "4. Thong Ke Hoa Don              ",
			                  "5. Danh sach vat tu xuat cao nhat"
			                  };




void Normal () {
	SetColor(15);
	SetBGColor(0);
}
void HighLight () {
	SetColor(15);
	SetBGColor(1);
}
int MenuDong(char td [so_item][50]){
	  Normal();
	  system("cls");   int chon =0;
	  int i; 
	  gotoxy(50, 8);
	  SetColor(4);
	  cout << "QUAN LY VAT TU";
	  Normal();
	  for ( i=0; i< so_item ; i++)
	  { gotoxy(cot, dong +i);
	    cout << td[i];
	  }
	  HighLight();
	  gotoxy(cot,dong+chon);
	  cout << td[chon];
	  char kytu;
	  do {
	  kytu = getch();
	  if (kytu==0) kytu = getch();
	  switch (kytu) {
	    case Up :if (chon+1 >1)
	  			  {
	  		              	Normal();
	              	gotoxy(cot,dong+chon);
	              	cout << td[chon];
	              	chon --;
	              	HighLight();
	              	gotoxy(cot,dong+chon);
	              	cout << td[chon];
	  				
	  			  }
	  			  break;
	  	case Down :if (chon+1 <so_item)
	  			  {
	  		        Normal();
	              	gotoxy(cot,dong+chon);
	              	cout << td[chon];
	              	chon ++;
	              	HighLight();
	              	gotoxy(cot,dong+chon);
	              	cout << td[chon];
	  				
	  			  }
	  			  break;
	  	case 13 : return chon+1;
	  }  // end switch
	  } while (1);
}

int Menu (char td [so_item][50]){

  system("cls");   int chon =0;
  int i;
  for ( i=0; i< so_item ; i++)
  { gotoxy(cot, dong +i);
    cout << td[i];
  }
Nhaplai:
  gotoxy (cot, dong + so_item);
  cout << "Ban chon 1 so (1..10) :    ";
  gotoxy (wherex()-4, wherey());
  cin >> chon;
  if (chon <1 || chon >so_item) goto Nhaplai;
  return chon;

}

void LuuFile(TreeNhanVien &root){
	ofstream myFile;
	myFile.open("dsNV.txt");
	
	StackNV sp = NULL;
	TreeNhanVien p = root;
	PTRHoaDon ptrHD;
	PTR_CT_HoaDon ptrCTHD;
	
	while(p != NULL){
		myFile << "+" << endl;
		// Nhan Vien
		myFile << p->nhanVien.maNhanVien << endl;
		myFile << p->nhanVien.ho << endl;
		myFile << p->nhanVien.ten << endl;
		myFile << (int)p->nhanVien.phai << endl;
		
		// Hoa Don
		ptrHD = p->nhanVien.hoaDonFirst;
		while(ptrHD != NULL){
			myFile << "-" << endl;
			myFile << ptrHD->hoaDon.soHoaDon << endl;
			myFile << ptrHD->hoaDon.ngayLapHoaDon.ngay << endl;
			myFile << ptrHD->hoaDon.ngayLapHoaDon.thang << endl;
			myFile << ptrHD->hoaDon.ngayLapHoaDon.nam << endl;
			myFile << ptrHD->hoaDon.loai << endl;
			
			// Chi Tiet Hoa Don
			PTR_CT_HoaDon ptrCTHD = ptrHD->hoaDon.CT_HD_First;
			while(ptrCTHD != NULL){
				myFile << "*" << endl;
				myFile << ptrCTHD->chiTietHD.maVT << endl;
				myFile << ptrCTHD->chiTietHD.soLuong << endl;
				myFile << ptrCTHD->chiTietHD.donGia << endl;
				myFile << ptrCTHD->chiTietHD.vat << endl;
				
				ptrCTHD = ptrCTHD->CT_HD_Next;
			}	
			ptrHD = ptrHD->HD_Next;
		}
			
		if(p->nvRight != NULL)
			push(sp, p->nvRight);
		if(p->nvLeft != NULL)
			p=p->nvLeft;
		else 
			if(sp == NULL)
				break;
			else pop(sp, p);		
	}
	myFile << "=";
	myFile.close();
}

void DocFile(TreeNhanVien &root){
	ifstream myFile;
	myFile.open("dsNV.txt");
	if(!myFile){
		cout << "Khong the mo file";
		return;
	}
	
	string s;
	NhanVien nv;
	HoaDon hd;
	ChiTiet_HD ctHD;
	int phai;
	
	getline(myFile, s);
	if(s == "=")
		return;
		
	while(!myFile.eof()){
NHANVIEN:	
		getline(myFile, nv.maNhanVien);
		getline(myFile, nv.ho);
		getline(myFile, nv.ten);
		getline(myFile, s);
		stringstream(s) >> phai;
		nv.phai = (phai == 1) ? 1 : 0;		
		nv.hoaDonFirst = NULL;
			
		getline(myFile, s);
		if(s == "="){
			Insert_Node(root, nv);
			return;
		}
		else if(s == "+")
			goto NHANVIEN;	
			
HOADON:
		getline(myFile, hd.soHoaDon);
		getline(myFile, s);
		stringstream(s) >> hd.ngayLapHoaDon.ngay;
		getline(myFile, s);
		stringstream(s) >> hd.ngayLapHoaDon.thang;
		getline(myFile, s);
		stringstream(s) >> hd.ngayLapHoaDon.nam;
		getline(myFile, s);
		hd.loai = s[0];
		hd.CT_HD_First = NULL;
		
		insertNodeHoaDon(nv.hoaDonFirst, hd);
		getline(myFile, s);
		if(s == "="){
			Insert_Node(root, nv);
			return;
		}
		else if(s == "-")
			goto HOADON;
		else if(s == "+"){
			Insert_Node(root, nv);
			goto NHANVIEN;
		}
			

CTHOADON:
		getline(myFile, ctHD.maVT);
		getline(myFile, s);
		stringstream(s) >> ctHD.soLuong;
		getline(myFile, s);
		stringstream(s) >> ctHD.donGia;
		getline(myFile, s);
		stringstream(s) >> ctHD.vat;
		
		insertCTHoaDonLast(hd.CT_HD_First, ctHD);
		getline(myFile, s);
		if(s == "*"){
			goto CTHOADON;
		}
		else if(s == "+"){
			insertNodeHoaDon(nv.hoaDonFirst, hd);
			Insert_Node(root, nv);
			goto NHANVIEN;
		}
		else if (s == "-"){
			insertNodeHoaDon(nv.hoaDonFirst, hd);
			goto HOADON;
		}
		else if(s == "="){
			insertNodeHoaDon(nv.hoaDonFirst, hd);
			Insert_Node(root, nv);
			return;			
		}
			
	}
	myFile.close();
}

int main(){
//	// Chi tiet HD
//	PTR_CT_HoaDon ctHoaDonFirst1 = new Node_ChiTiet_HD;
//	ctHoaDonFirst1 = NULL;
//	
//	// Chi Tiet HD1
//	ChiTiet_HD cthd1;
//	cthd1.maVT = "VT2";
//	cthd1.soLuong = 100;
//	cthd1.donGia = 200000;
//	cthd1.vat = 3;
//	insertCTHoaDonLast(ctHoaDonFirst1, cthd1);
//	
//	// Chi tiet HD2
//	ChiTiet_HD cthd2;
//	cthd2.maVT = "VT1";
//	cthd2.soLuong = 500;
//	cthd2.donGia = 200;
//	cthd2.vat = 6;
//	insertCTHoaDonLast(ctHoaDonFirst1, cthd2);
//	
//	// Hoa Don
//	PTRHoaDon hoaDonFirst1 = new NodeHoaDon;
//	hoaDonFirst1 = NULL;
//	
//	Date d;
//	HamTraVeCurrentTime(d);
//		
//	HoaDon hd1;
//	hd1.soHoaDon = "HD1";
//	hd1.loai = 'N';
//	hd1.ngayLapHoaDon = d;
//	hd1.CT_HD_First = ctHoaDonFirst1;
//	insertNodeHoaDon(hoaDonFirst1, hd1);	
//	
//	// Nhan Vien
//	TreeNhanVien treeNV = new NodeNhanVien;
//	treeNV = NULL;
//	
//	// NV1
//	NhanVien nv1;
//	nv1.maNhanVien = "NV1";
//	nv1.ho = "Nguyen";
//	nv1.ten = "Duc";
//	nv1.phai = 1;
//	nv1.hoaDonFirst = hoaDonFirst1;
//	Insert_Node(treeNV, nv1);
//	
//	
//	// Chi tiet HD cua NV2
//	PTR_CT_HoaDon ctHoaDonFirst2 = new Node_ChiTiet_HD;
//	ctHoaDonFirst2 = NULL;
//	
//	// Chi Tiet HD1
//	ChiTiet_HD cthd3;
//	cthd3.maVT = "VT2";
//	cthd3.soLuong = 100;
//	cthd3.donGia = 200000;
//	cthd3.vat = 3;
//	insertCTHoaDonLast(ctHoaDonFirst2, cthd3);	
//	
//	PTRHoaDon hoaDonFirst2 = new NodeHoaDon;
//	hoaDonFirst2 = NULL;
//	
//	HoaDon hd5;
//	hd5.soHoaDon = "HD5";
//	hd5.loai = 'N';
//	hd5.ngayLapHoaDon = d;
//	hd5.CT_HD_First = ctHoaDonFirst2;
//	insertNodeHoaDon(hoaDonFirst2, hd5);
//	//NV2
//	NhanVien nv2;
//	nv2.maNhanVien = "NV7";
//	nv2.ho = "Tran";
//	nv2.ten = "Khang";
//	nv2.phai = 1;
//	nv2.hoaDonFirst = hoaDonFirst2;
//	
//	
//	Insert_Node(treeNV, nv2);
	
	//LuuFile(treeNV);
	
	TreeNhanVien root;
	root = NULL;
	
	DocFile(root);
	testInorder(root);
	return 0;
}


