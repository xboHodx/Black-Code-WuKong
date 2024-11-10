#include <iostream>
#include <random>
using namespace std;

//�����������
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dist(0.0, 1.0);

//���ࣺ��ɫ��
class character {
protected:
	int hp, atk, tkdmg=0;
	bool charge=false;//������
	int pauseturn = 0;
public:
	//���캯��
	character(int h, int a) :hp(h), atk(a) {};
	//����
	virtual void attack(character& wk, double multipower) {
		wk.takedamage(atk * multipower);
	}
	bool isalive() {
		return hp > 0;
	}
	void takedamage(int damage) {
		tkdmg+=damage;
	}
	void truedamage(double multipower) {
		hp -= tkdmg * multipower;
	}

	void addpauseturn(int a) {
		pauseturn += a;
	}
	//�ж��Ƿ���ͣ�غ�
	bool ispauseturn() {
		return pauseturn;;
	}
	//�ж��Ƿ��ܵ��˺�
	int isdamaged() {
		return tkdmg;
	}
	//���麯����״̬���
	virtual void clearState() = 0;
};

//�����ࣺ���
class Wukong : public character {
protected:
	int mp=0,gunshi=0;//����ֵ������ֵ
	int dr = 0;//ʣ�����
	char hl=0;//��«����
	bool isdodge = false;//���غ��Ƿ�������
	double damageReduction = 0;//�˺�����
	bool tttb = false;//���غ��Ƿ�ʹ��ͭͷ����
	bool dss = false;//���غ��Ƿ�ʹ�ö�����
	bool windSand = false;//Debuff:��ɳ
	bool attackback = false;//Debuff:���غϽ�������
	bool tripleTaped = false;//���غϱ�������
public:
	//���캯��
	Wukong(int h,int a,int m) :character(h,a),mp(m) {}
	//ѡ���«
	void choosehl() {
		cout << "��ѡ���«�����屦��«��s��or Ǭ���ʺ�«��q)" << endl;
		cin >> hl;
		if (hl == 's') dr = 10;
		else if (hl == 'q') dr = 6;
		if (hl != 's' && hl != 'q') choosehl();
	}
	//��ͨ����
	void attack(character&target, double multipower) {
		target.takedamage(atk * multipower);
		if (gunshi < 2) gunshi++;
	}
	//��������
	void chargeattack(character&wk ,character &target) {
		if (gunshi != 2) {
			cout << "���Ʋ���3��������ѡ���ж�\n";
			wkturn(wk, target);
		}
		int choice;
		cout << "��ѡ�����1.����2.����3.����4.����\n";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 1:
			cout << "߾�����֣�����������\n";
			attack(target, 1.5);
			gunshi = 0;
			break;
		case 2:
			cout << "߾�����֣�����������\n";
			attack(target, 1);
			damageReduction = 0.5;
			gunshi = 0;
			break;
		case 3:
			cout << "߾�����֣����Ҵ�����\n";
			attack(target, 1);
			isdodge = true;
			gunshi = 0;
			break;
		case 4:
			wkturn(wk, target);
			break;
		default:
			cout << "��������ȷ������\n";
			chargeattack(wk, target);
		}
	}
	//�Ⱦ�
	void drink() {
		cout << "��¶������\n";
		dr--;
		hp += 35;
		if (hl == 'q') {
			atk += 3;
		}
		if (hp > 100) hp = 100;
	}
	//����
	void dodge() {
		cout << "����\n";
		isdodge = true;
	}
	//����
	void magic(character &wk, character &target) {
		cout << "��ѡ����1.ͭͷ����2.������3.����\n";
		int choice;
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 1:
			cout << "Ӳ!"<<endl;
			tttb = true;
			mp -= 20;
			break;
		case 2:
			cout << "����"<<endl;
			dss = true;
			mp -= 20;
			break;
		case 3:
			wkturn(wk, target);
			break;
		default:
			cout << "��������ȷ������\n";
			magic(wk, target);
		}
		return;
	}
	//Debuff:��ɳ
	void windsand() {
		windSand = true;
	}
	bool iswindsand() {
		return windSand;
 	}
	//�Ƿ�ͭͷ����
	bool istttb() {
		return tttb;
	}
	//�Ƿ�����
	bool isdss() {
		return dss;
	}
	//�Ƿ�����
	bool isDodge() {
		return isdodge;
	}
	//Defuff�����غϽ�������
	void attackbacked() {
		attackback = true;
	}
	//��������
	void tripletaped() {
		tripleTaped = true;
	}
	bool istripletap() {
		return tripleTaped;
	}
	//�Ƿ񱻵���
	bool isattackbacked() {
		return attackback;
	}
	//��ջغ�
	void wkturn(character &wk,character &target) {
		cout <<endl<< "��ѡ���ж�1.���� 2.�������� 3.���� 4.���� 5.�Ⱦ�"<<endl;
		int act;
		cin >> act;
		cout << endl;
		switch (act) {
		case 1: 
			cout << "��� �� ���� ʹ�� ��ͨ����"<<endl;
			wk.attack(target, 1);
			break;
		case 2:
			if (gunshi < 2) {
				cout << "���Ʋ��㣬������ѡ��\n";
				wkturn(wk, target);
				return;
			}
			chargeattack(wk, target);
			break;
		case 3:
			dodge();
			break;
		case 4:
			if (mp < 20) {
				cout << "�������㣬������ѡ��\n";
				wkturn(wk, target);
				return;
			}
			magic(wk,target);
			break;
		case 5:
			if(dr>0) drink();
			else {
				cout << "��«�ѿ�\n";
				wkturn(wk, target);
			}
			break;
		default:
			cout << "��������ȷ������\n";
			wkturn(wk, target);
		}
		return;
	}
	//�����˺�
	void truedamage(double multipower) {
		hp -= tkdmg * multipower * (1-damageReduction);
	}
	//���״̬
	void clearState() override {
		isdodge=false;
		damageReduction = false;
		tttb= false;
		dss= false;
		tkdmg = 0;
		attackback = false;
		tripleTaped = false;
	}
	//��ӡ״̬
	void printstate() {
		if (hp <= 0) cout << "���״̬������" << endl;
		else cout << "���״̬��hp��" << hp << ",mp:" << mp << ",����:" << gunshi << ",������"<<dr<<endl;
	}
};

//�����ࣺС��
class Xiaoyao : public character {
protected:
public:
	Xiaoyao(int h,int a): character(h,a){}
	//С���غ�
	void xyturn(Wukong&wk) {
		if (pauseturn > 0) {
			cout << "�ûغ�С�������ж�" << endl;
			return;
		}
		if (charge) {
			cout << "С�� �� ��� ʹ�� ��������\n" ;
			attack(wk, 2);
			charge = false;
		}
		else {
			double randomNum = dist(gen);
			if (randomNum < 0.5) {
				cout << "С�� �� ��� ʹ�� ��ͨ����\n";
				attack(wk, 1);
			}
			else {
				cout << "С�������³������۵���\n";
				charge = true;
			}
		}
	}
	void printstate() {
		if (hp <= 0) cout << "С��״̬������" << endl;
		else cout << "С��״̬��hp��" << hp<< endl;
	}
	void clearState() override {
		tkdmg = 0;
		if (pauseturn > 0) pauseturn--;
	}
};

//�����ࣺͷĿ
class Toumu : public character {
protected:
public:
	//���캯��
	Toumu(int h, int a) : character(h, a) {}
	//ͷĿ�غ�
	void tmturn(Wukong& wk) {
		if (pauseturn > 0) {
			cout << "�ûغ�ͷĿ�����ж�" << endl;
			return;
		}
		if (charge) {
			cout << "ͷĿ �� ��� ʹ�� ��������"<<endl;
			attack(wk, 2);
			charge = false;
		}
		else {
			double randomNum = dist(gen);
			if (randomNum < 0.4) {
				cout << "ͷĿ �� ��� ʹ�� ��ͨ����\n";
				attack(wk, 1);
			}
			else if(randomNum<0.8){
				cout << "ͷĿ��Ϣ����������ᶨ\n";
				charge = true;
			}
			else {
				//����
				cout << "ͷĿ�����������ںü���\n";
				wk.attackbacked();
			}
		} 
	}
	void printstate() {
		if (hp <= 0) cout << "ͷĿ״̬������" << endl;
		else cout << "ͷĿ״̬��hp��" << hp << endl;
	}
	void clearState() override {
		tkdmg = 0;
		if (pauseturn > 0) pauseturn--;
	}
};

//�����ࣺ����
class Yaowang : public character {
protected:
public:
	Yaowang(int h, int a) : character(h, a) {}
	void tripleTap(Wukong&wk) {
		double randomNum2 = dist(gen);
		wk.tripletaped();
		if (randomNum2 > 0.75) {
			cout << "�����ֽ��ʵʵ�س���մ�������!��մ����ˣ�û����" << endl;
			attack(wk, 3);
		}
		else {
			double randomNum2 = dist(gen);
			if (randomNum2 > 0.67) {
				cout << "�����ֳ�����ʹ����£����������һ�£�ȴ�����Լ����϶��������" << endl;
				attack(wk, 2);
			}
			else {
				double randomNum2 = dist(gen);
				if (randomNum2 > 0.5) {
					cout << "�����ֵ�����ꪳ���շ�������ɨ���£���պ󳷲��㿪���£����һ��ȴ���̵��ڵأ�" << endl;
					attack(wk, 1);
				}
				else {
					cout << "���������¹���û�У������ܻ����������������㣡��"<<endl;
				}
			}
		}
	}
	void ywturn(Wukong& wk) {
		if (pauseturn > 0) {
			cout << "�ûغ����������ж�" << endl;
			return;
		}
		if (charge) {
			cout << "���� �� ��� �ݺݿ���һ��\n";
			attack(wk, 2);
			charge = false;
		}
		else {
			double randomNum = dist(gen);
			if (randomNum < 0.3) {
				cout << "���� �� ��� ʹ�� ��ͨ����\n";
				attack(wk, 1);
			}
			else if (randomNum < 0.6) {
				cout << "������ŭ��һ��������ճ����!\n";
				charge = true;
			}
			else if(randomNum<0.9){
				if (wk.iswindsand()) {
					ywturn(wk);
					return;
				}
				cout << "ֻ���ǻ�ë�������ɳ���������������Ļ�ɳ֮��\n";
				wk.windsand();
			}
			else {
				tripleTap(wk);
			}
		}
	}
	void printstate() {
		if (hp <= 0) cout << "����״̬������" << endl;
		else cout << "����״̬��hp��" << hp << endl;
	}
	void clearState() override {
		tkdmg = 0;
		if (pauseturn > 0) pauseturn--;
	}
};

//�ж��׶�
void judge(Wukong& wk, character& enemy) {
	int multipower2=1;
	//
	if (wk.istripletap()) {

	}
	//ͷĿ����
	if (wk.isattackbacked() && enemy.isdamaged()) {
		cout << "��չ������ɷ����Է��������ˣ�\n";
		wk.takedamage(enemy.isdamaged());
		wk.truedamage(1);
		return;
	}
	//��ɳ
	if (wk.iswindsand()) {

	    double windSandRandomNum = dist(gen);
		if (windSandRandomNum > 0.5) {
			multipower2 = 0;
			cout << "��ձ���ɳ�����ۣ�"<<endl;
		}
		else multipower2 = 1;
	}
	//����
	if (wk.istttb()) {
		if (wk.isdamaged() && !wk.istripletap()) {
			cout << "Duang~" << endl;
			enemy.addpauseturn(2);
		}
		else {
			wk.truedamage(1);
			cout << "���÷�����" << endl;
		}
		return;
	}
	if (wk.isdss()) {
		enemy.addpauseturn(3);
		return;
	}
	//��ͣ�غ�
	if (enemy.ispauseturn() ){
		enemy.truedamage(multipower2);
		return;
	}
	//����
	if (wk.isDodge()) {
		double randomNum = dist(gen);
		if (randomNum < 0.8) {
			cout << "����ɹ�" << endl;
			enemy.truedamage(multipower2);
		}
		else {
			cout << "����ʧ��" << endl;
			wk.truedamage(1);
			enemy.truedamage(multipower2);
		}
		return;
	}
	wk.truedamage(1);
	enemy.truedamage(multipower2);
	return;
}

//��һ��
void Stage1(Wukong&wk) {
	cout << "�������һ��С��\n";
	Xiaoyao xy(100,10);
	while (xy.isalive() && wk.isalive()) {
		wk.wkturn(wk,xy);
		xy.xyturn(wk);
		judge(wk,xy);
		wk.printstate();
		xy.printstate();
		wk.clearState();
		xy.clearState();
	}
	return;
}

//�ڶ���
void Stage2(Wukong&wk) {
	cout << "�������һͷĿ��������˵�����Ϳ���\n";
	Toumu tm(200,15);
	while (tm.isalive() && wk.isalive()) {
		wk.wkturn(wk,tm);
		tm.tmturn(wk);
		judge(wk,tm);
		wk.printstate();
		tm.printstate();
		wk.clearState();
		tm.clearState();
	}
	return;
}

//������
void Stage3(Wukong&wk) {
	cout << "��ռ�����һֱ��������ꪵĻ����ǣ�������ԥ������ȥ\n";
	Yaowang yw(300,20);
	while(yw.isalive() && wk.isalive()) {
		wk.wkturn(wk,yw);
		yw.ywturn(wk);
		judge(wk,yw);
		wk.printstate();
		yw.printstate();
		wk.clearState();
		yw.clearState();
	}
	return;
}

void youwin() {
	cout << endl << "��    ʤ" << endl<<endl;
}

//������
int main() {
	Wukong wk(100,20,100);
	wk.choosehl();
	cout << "��Ϸ��ʼ" << endl << endl<<"~�Ʒ���~�˰���~���ǹ��⸻�ĵ�~" << endl<<endl;

	Stage1(wk);
	if (!wk.isalive()) {
		cout << "YOU DEAD\n";
		return 0;
	}
	youwin();

	Stage2(wk);
	if (!wk.isalive()) {
		cout << "YOU DEAD\n";
		return 0;
	}
	youwin();

	Stage3(wk);
	if (!wk.isalive()) {
		cout << "YOU DEAD\n";
		return 0;
	}
	youwin();

	cout << "��ͨ�ر��½�";
	return 0;
}