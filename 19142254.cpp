#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
using namespace std;


class Product {//商品情報を管理するクラスの定義
public:
	string number;
	int price;
	void setNumber(const string& newNumber) { number = newNumber; }
	string getNumber() { return number; }
	void setPrice(int newPrice) { price = newPrice; }
	int getPrice() { return price; }
};

int postage(string a, string b, string c, string d, string e, string f) {//個人情報をファイルに出力する関数の定義
	int add;
	ofstream mfile("mail.text");
	mfile << "宛先：" << f << endl;
	mfile << a << " " << b << " 様" << endl;
	mfile << "\nご注文いただき誠に有難うございます。下記ご注文にお間違えないかご確認ください。\n";
	mfile << "郵便番号：〒" << c << endl;
	mfile << "ご住所：" << d << endl;
	mfile << "電話番号：" << e << endl;
	if (d.find("北海道") != std::string::npos || d.find("沖縄県") != std::string::npos) {
		add = 1000;
	}
	else {
		add = 500;
	}
	mfile << "\n送料：" << add << "円" << endl;
	return add;
}

void buylist(string buy, string cart) {//入力された商品情報をファイルに出力する関数の定義
	ofstream outfile(cart, ios_base::app);
	regex rx(R"(,)");
	sregex_token_iterator it(buy.begin(), buy.end(), rx, -1);//反復子（イテレータ）
	sregex_token_iterator end;
	while (it != end) {
		outfile << *it++ << " ";
	}
	outfile << endl;
}

int money(string text, string nu, int pr) {//合計金額を求める関数の定義
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
	cout << "\nお客様情報をご入力ください。" << endl << "姓（漢字）：";
	cin >> lastname;
	cout << "名（漢字）：";
	cin >> firstname;
	cout << "郵便番号（ハイフンと半角数字）：";
	cin >> post;
	cout << "住所：";
	cin >> address;
	cout << "電話番号（ハイフンと半角数字）：";
	cin >> tell;
	cout << "メールアドレス：";
	cin >> mail;
	postage(lastname, firstname, post, address, tell, mail);
	result1 += postage(lastname, firstname, post, address, tell, mail);
	cout << "\n送料：" << result1 << "円\n" << endl;//関数を用いて送料表示


	cout << "\n商品名と個数を入力してEnterキーを押してください。[商品aを2個購入する場合→a,2] (Ctrl+Zで終了)\n";
	string goods;
	ofstream cartfile("mycart.txt");//ファイル作成
	while (cin >> goods) {
		buylist(goods, "mycart.txt");//そのファイルを使って関数利用
	}
	cartfile.close();

	ifstream infile("list.txt");//商品情報ファイル読み込み
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
		result2 += money("mycart.txt", v1[i].getNumber(), v1[i].getPrice());//関数を用いて金額計算
	}
	cout << "\n小計：" << result2 << "円\n" << endl;
	infile.close();

	cout << "\n合計金額：" << result1 + result2 << "円" << endl;

	ofstream mfile("mail.text", ios_base::app);
	mfile << "小計：" << result2 << "円" << endl;
	mfile << "合計金額：" << result1 + result2 << "円" << endl;
	mfile.close();
}
