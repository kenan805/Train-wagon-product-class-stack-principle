#include<iostream>
#include<assert.h>
#define MAX 5

using namespace std;

template<typename T>
class Stack {
private:
	T items[MAX];
	int top;
public:
	Stack() {
		top = -1;
	}

	bool push(T item) {
		if (top >= (MAX - 1)) {
			cout << "Stack overflow!";
			return false;
		}
		else {
			++top;
			items[top] = item;
			return true;
		}
	}
	T peek() {
		if (top < 0) {
			cout << "Stack is Empty!" << endl;

		}
		else {
			return items[top];
		}
	}
	T pop() {
		if (top < 0) {
			cout << "Stack is underflow!" << endl;
			return *(new T);
		}
		else {
			return items[top--];
		}
	}
	bool isEmpty() const { return top < 0; }
	bool isFull() const { return top == (MAX - 1); }

};



class Product {
	int _id;
	string _name;
	double _price;
	double _discount;
	string _company;
public:
	Product() :_id(), _name(), _price(), _discount(), _company() {}
	Product(const int id, const string& name, const double price, const double discount, const string& company)
	{
		SetId(id);
		SetName(name);
		SetPrice(price);
		SetDiscount(discount);
		SetCompany(company);
	}

	Product(const Product& other)
	{
		SetId(other.GetId());
		SetName(other.GetName());
		SetPrice(other.GetPrice());
		SetDiscount(other.GetDiscount());
		SetCompany(other.GetCompany());
	}
	Product& operator=(const Product& other)
	{
		SetId(other.GetId());
		SetName(other.GetName());
		SetPrice(other.GetPrice());
		SetDiscount(other.GetDiscount());
		SetCompany(other.GetCompany());

		return *this;
	}

	int GetId()const { return _id; }
	string GetName()const { return _name; }
	double GetPrice()const { return _price; }
	double GetDiscount()const { return _discount; }
	string GetCompany()const { return _company; }

	void SetId(const int id) {
		assert(id >= 0 && "Id < 0");

		_id = id;
	}
	void SetName(const string& name) {
		if (name.empty()) return;
		_name = name;
	}
	void SetPrice(const double price) {
		assert(price >= 0 && "Price < 0");

		_price = price;
	}
	void SetDiscount(const double discount) {
		assert(discount >= 0 && "Discount < 0");

		_discount = discount;
	}
	void SetCompany(const string& company) {
		if (company.empty()) return;
		_company = company;
	}

	void ShowProduct() {
		cout << "Id: " << GetId() << endl;
		cout << "Name: " << GetName() << endl;
		cout << "Price: " << GetPrice() << " AZN" << endl;
		cout << "Discount: " << GetDiscount() << " %" << endl;
		cout << "Company: " << GetCompany() << endl;
	}

};


class Wagon {
	string _no;
	double _speed;
	string _country;
	Stack<Product> _products;
public:
	Wagon() :_no(), _speed(), _country(), _products() {}
	Wagon(const string& no, const double speed, const string& country, Stack<Product> products)
	{
		SetNo(no);
		SetSpeed(speed);
		SetCountry(country);
		SetStackProducts(products);

	}

	Wagon(const Wagon& other)
	{
		SetNo(other.GetNo());
		SetSpeed(other.GetSpeed());
		SetCountry(other.GetCountry());
		SetStackProducts(other.GetStackProducts());
	}
	Wagon& operator=(const Wagon& other)
	{
		SetNo(other.GetNo());
		SetSpeed(other.GetSpeed());
		SetCountry(other.GetCountry());
		SetStackProducts(other.GetStackProducts());

		return *this;
	}

	string GetNo()const { return _no; }
	double GetSpeed()const { return _speed; }
	string GetCountry()const { return _country; }
	Stack<Product> GetStackProducts()const { return _products; }


	void SetNo(const string& no) {
		if (no.empty()) return;
		_no = no;
	}
	void SetSpeed(const double speed) {
		assert(speed >= 0 && "Speed < 0");
		_speed = speed;
	}
	void SetCountry(const string& country) {
		if (country.empty()) return;
		_country = country;
	}
	void SetStackProducts(Stack<Product> products) {
		_products = products;
	}

	void print_only_product() {
		while (!_products.isEmpty())
		{
			_products.pop().ShowProduct();
		}
	}

	void showProduct() {
		Stack<Product> temp = _products;
		cout << "\n----------- Wagon " << GetNo() << " -----------" << endl;
		cout << "Speed: " << GetSpeed() << " km/h" << endl;
		cout << "Country: " << GetCountry() << endl << endl;
		while (!temp.isEmpty())
		{
			temp.pop().ShowProduct();
		}
	}

	friend ostream& operator<<(ostream& out, const Wagon& wagon);
};

ostream& operator<<(ostream& out, const Wagon& wagon) {
	Stack<Product> temp = wagon._products;
	cout << "\n----------- Wagon " << wagon.GetNo() << " -----------" << endl;
	cout << "Speed: " << wagon.GetSpeed() << " km/h" << endl;
	cout << "Country: " << wagon.GetCountry() << endl << endl;
	while (!temp.isEmpty())
	{
		temp.pop().ShowProduct();
	}
	return out;
}



template<typename T>
class Node {
public:
	T data;
	Node* next;
	Node* prev;

	Node(const T& data) {
		this->data = data;
	}
};

template<typename T>
class DoubleLinkedList {
private:
	Node<T>* head;
	Node<T>* tail;
	friend class Train;
public:
	DoubleLinkedList() :head(), tail() {}

	void forwardTravers()const {
		auto temp = head;
		while (temp != nullptr)
		{
			temp->data.showProduct();
			temp = temp->next;
		}
		cout << endl;
	}

	void backwardTravers()const {
		auto temp = tail;
		while (temp != nullptr) {
			temp->data.showProduct();
			temp = temp->prev;
		}cout << endl;

	}

	void addBegin(const T& data) {
		auto newTrain = new Node<T>(data);

		if (head == NULL) {
			head = newTrain;
			tail = newTrain;
			return;
		}

		newTrain->next = head;
		head->prev = newTrain;
		head = newTrain;
	}

	void addEnd(const T& data) {
		auto newTrain = new Node<T>(data);
		if (head == NULL)
		{
			head = newTrain;
			tail = newTrain;
			return;
		}

		tail->next = newTrain;
		newTrain->next = nullptr;
		newTrain->prev = tail;
		tail = newTrain;
	}

	void addBefore(const T& wagon, const T& data) {
		if (head == NULL) {
			cout << "No wagon";
			return;
		}

		
		if (head->data == wagon) {
			auto newTrain = new Node(data);
			newTrain->next = head;
			head->prev = newTrain;
			head = newTrain;
			return;
		}

		
		auto n = head;
		while (n->next != NULL) {
			if (n->next->data == wagon) break;
			n = n->next;
		}

		if (n->next == NULL) {
			cout << "Wagon is not found!" << endl;
		}
		else {
			auto newTrain = new Node(data);
			newTrain->next = n->next;
			newTrain->prev = n;
			n->next->prev = newTrain;
			n->next = newTrain;
		}

	}

	void addAfter(const T& wagon, const T& data) {
		if (head == NULL) {
			cout << "No wagon";
			return;
		}

		auto n = head;
		while (n != NULL) {
			if (n->data == wagon) break;
			n = n->next;
		}

		if (n == NULL) cout << "Wagon is not found!" << endl;
		else {
			auto newTrain = new Node(data);
			newTrain->next = n->next;
			n->next = newTrain;
		}
	}

	void deleteBegin() {
		if (head == NULL) {
			cout << "No wagon";
			return;
		}

		auto temp = head->next;
		delete head;
		head = temp;
		temp = NULL;
	}

	void deleteEnd() {
		if (head == NULL) {
			cout << "No wagon";
			return;
		}

		if (head->next == NULL) {
			delete head;
			head = NULL;
			return;
		}

		auto n = head;
		while (n->next->next != NULL) {
			n = n->next;
		}

		delete n->next;
		n->next = NULL;
	}

};


class Train {
	string _train_name;
public:
	DoubleLinkedList<Wagon> wagons;
	Train() : _train_name(), wagons() {}
	Train(const string& train_name) {
		SetName(train_name);
	}

	string GetName()const { return _train_name; }


	void SetName(const string& train_name) {
		if (train_name.empty()) return;
		_train_name = train_name;

	}
	void SetWagons(DoubleLinkedList<Wagon> wagons) {
		this->wagons = wagons;
	}

	Train(const Train& other) {
		SetName(other.GetName());
		SetWagons(other.wagons);
	}

	Train& operator=(const Train& other) {
		SetName(other.GetName());
		SetWagons(other.wagons);

		return *this;
	}

	Wagon getWagonByNo(const string& wagon_no) {
		auto temp = wagons.head;

		while (temp->data.GetNo() != wagon_no) {
			temp = temp->next;
		}
		return temp->data;

	}

	void showProductsByNo(const string& wagon_no) {
		if (wagons.head == NULL) {
			cout << "No wagon";
			return;
		}
		auto temp = wagons.head;

		while (temp->data.GetNo() != wagon_no) {
			temp = temp->next;
		}
		temp->data.print_only_product();
	}

	void deleteWagonByNo(const string& wagon_no) {
		if (wagons.head == NULL) {
			cout << "No wagon";
			return;
		}

		if (wagons.head->data.GetNo() == wagon_no) {
			if (wagons.head->next == NULL) {
				delete wagons.head;
				wagons.head = NULL;
				return;
			}
			auto temp = wagons.head->next;
			delete wagons.head;
			wagons.head = temp;
			temp = NULL;
		}
		auto temp = wagons.head;

		while (temp->next != NULL) {
			if (temp->next->data.GetNo() == wagon_no) {
				auto temp2 = temp->next->next;
				delete temp->next;
				temp->next = temp2;
				return;
			}
			temp = temp->next;
		}
	}

	void updateSpeedByNo(const string& wagon_no, const double updateSpeed) {
		if (wagons.head == NULL) {
			cout << "No wagon";
			return;
		}

		auto temp = wagons.head;

		while (temp->data.GetNo() != wagon_no) {
			temp = temp->next;
		}
		temp->data.SetSpeed(updateSpeed);
	}

	void updateCountryByNo(const string& wagon_no, const string& updateCountry) {
		if (wagons.head == NULL) {
			cout << "No wagon";
			return;
		}

		auto temp = wagons.head;

		while (temp->data.GetNo() != wagon_no) {
			temp = temp->next;
		}
		temp->data.SetCountry(updateCountry);
	}


	friend ostream& operator<<(ostream& out, const Train& train);

};

ostream& operator<<(ostream& out, const Train& train) {
	cout << "************* Train Info *************" << endl;
	cout << "Train name: " << train.GetName() << endl;
	train.wagons.forwardTravers();

	return out;
}


int main() {
	Product p1(1, "Iphone", 3000, 10, "Kontakt Home");
	Product p2(2, "Samsung", 2400, 12, "Kontakt Home");
	Product p3(3, "Xiaomi", 1500, 8, "Kontakt Home");
	Product p4(4, "Nokia", 700, 5, "Kontakt Home");
	Product p5(5, "Realme", 1000, 15, "Kontakt Home");
	Product p6(6, "Huawei", 500, 13, "Kontakt Home");
	Product p7(7, "Nvidia", 300, 10, "Kontakt Home");
	Product p8(8, "Genius", 800, 9, "Kontakt Home");
	Product p9(9, "Intel", 600, 6, "Kontakt Home");



	Stack<Product> s1;
	s1.push(p1);
	s1.push(p2);
	Stack<Product> s2;
	s2.push(p3);
	s2.push(p4);
	s2.push(p5);
	Stack<Product> s3;
	s3.push(p6);
	Stack<Product> s4;
	s4.push(p7);
	s4.push(p8);
	s4.push(p9);


	Wagon w1("1", 200, "Turkey", s1);
	Wagon w2("2", 150, "Georgia", s2);
	Wagon w3("3", 300, "Azerbaijan", s3);
	Wagon w4("4", 350, "Russia", s4);

	Train train("Express");
	train.wagons.addEnd(w1);
	train.wagons.addEnd(w2);
	train.wagons.addEnd(w3);
	train.wagons.addEnd(w4);

	cout<<train;

	//cout << train.getWagonByNo("2") << endl;
	
	//train.showProductsByNo("2");

	//train.deleteWagonByNo("2");
	//cout << train;

	//train.updateSpeedByNo("2", 250);
	//cout << train;

	//train.updateCountryByNo("2", "Azerbaijan");
	//cout << train;




	return 0;
}