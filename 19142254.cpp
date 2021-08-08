#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
using namespace std;


class Product {//���i�����Ǘ�����N���X�̒�`
public:
	string number;
	int price;
	void setNumber(const string& newNumber) { number = newNumber; }
	string getNumber() { return number; }
	void setPrice(int newPrice) { price = newPrice; }
	int getPrice() { return price; }
};

int postage(string a, string b, string c, string d, string e, string f) {//�l�����t�@�C���ɏo�͂���֐��̒�`
	int add;
	ofstream mfile("mail.text");
	mfile << "����F" << f << endl;
	mfile << a << " " << b << " �l" << endl;
	mfile << "\n�����������������ɗL��������܂��B���L�������ɂ��ԈႦ�Ȃ������m�F���������B\n";
	mfile << "�X�֔ԍ��F��" << c << endl;
	mfile << "���Z���F" << d << endl;
	mfile << "�d�b�ԍ��F" << e << endl;
	if (d.find("�k�C��") != std::string::npos || d.find("���ꌧ") != std::string::npos) {
		add = 1000;
	}
	else {
		add = 500;
	}
	mfile << "\n�����F" << add << "�~" << endl;
	return add;
}

void buylist(string buy, string cart) {//���͂��ꂽ���i�����t�@�C���ɏo�͂���֐��̒�`
	ofstream outfile(cart, ios_base::app);
	regex rx(R"(,)");
	sregex_token_iterator it(buy.begin(), buy.end(), rx, -1);//�����q�i�C�e���[�^�j
	sregex_token_iterator end;
	while (it != end) {
		outfile << *it++ << " ";
	}
	outfile << endl;
}

int money(string text, string nu, int pr) {//���v���z�����߂�֐��̒�`
	ifstream infile(text);
	string label;
	int quantity;
	int total = 0;
	while (infile >> label >> quantity) {
		if(label == nu){
			total += pr * quantity;
		}
		else {
			total += 0;
		}
	}
	return total;
}


int main() {

	int result1 = 0;
	string lastname, firstname, post, address, tell, mail;
	cout << "\n���q�l���������͂��������B" << endl << "���i�����j�F";
	cin >> lastname;
	cout << "���i�����j�F";
	cin >> firstname;
	cout << "�X�֔ԍ��i�n�C�t���Ɣ��p�����j�F";
	cin >> post;
	cout << "�Z���F";
	cin >> address;
	cout << "�d�b�ԍ��i�n�C�t���Ɣ��p�����j�F";
	cin >> tell;
	cout << "���[���A�h���X�F";
	cin >> mail;
	postage(lastname, firstname, post, address, tell, mail);
	result1 += postage(lastname, firstname, post, address, tell, mail);
	cout << "\n�����F" << result1 << "�~\n" << endl;//�֐���p���đ����\��


	cout << "\n���i���ƌ�����͂���Enter�L�[�������Ă��������B[���ia��2�w������ꍇ��a,2] (Ctrl+Z�ŏI��)\n";
	string goods;
	ofstream cartfile("mycart.txt");//�t�@�C���쐬
	while (cin >> goods) {
		buylist(goods, "mycart.txt");//���̃t�@�C�����g���Ċ֐����p
	}
	cartfile.close();

	ifstream infile("list.txt");//���i���t�@�C���ǂݍ���
	string Number;
	int Price;
	vector <Product> v1;
	size_t s = v1.size();
	int i = 0;
	int result2 = 0;
	while (infile >> Number >> Price) {
		v1.emplace_back();
		v1[i].setNumber(Number);
		v1[i].setPrice(Price);
		result2 += money("mycart.txt", v1[i].getNumber(), v1[i].getPrice());//�֐���p���ċ��z�v�Z
	}
	cout << "\n���v�F" << result2 << "�~\n" << endl;
	infile.close();

	cout << "\n���v���z�F" << result1 + result2 << "�~" << endl;

	ofstream mfile("mail.text", ios_base::app);
	mfile << "���v�F" << result2 << "�~" << endl;
	mfile << "���v���z�F" << result1 + result2 << "�~" << endl;
	mfile.close();
}
