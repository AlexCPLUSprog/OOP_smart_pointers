#include <iostream>
#include <memory>
// auto ptr, weak ptr, unique ptr, shared ptr

class A {
public:
	// A(A& a) = delete; - это пример того, почему unique_ptr не может ссылаться на другой указатель
	A() {
		std::cout << "Constructor A" << '\n';
	}
	~A() {
		std::cout << "Destructor A" << '\n';
	}
};

class Point {
public:
	Point(int x, int y) : _x(x), _y(y) {
		std::cout << "Point constructor" << '\n';
	}

	int getX()const {
		return _x;
	}
	~Point() {
		std::cout << "Point destructor" << '\n';
	}
private:
	int _x;
	int _y;
 };

template <class T>
class SmartPtr {
	T* _ptr;
public:
	SmartPtr(T*t) : _ptr(t) {
		std::cout << "SmartPtr constructor" << '\n';
	}

	T* operator->() {	// стрелочный оператор, если возвращает указатель, то в это случае на указатель снова вызывается стрелочный указатель
		return _ptr;	// ._ptr->operator->
	}	

	~SmartPtr() {
		std::cout << "SmartPtr destructor" << '\n';
		delete _ptr;
	}
	T* get() {
		return _ptr;
	}

};

// unique_ptr, почти как и любой пользовательский тип можно передавать в параметры функции по ссылке


// dinamic_cast<Point*>

class IVehicle {
public:
	virtual int getSpeed() const = 0;
	virtual const std::string& getType() const = 0;
	virtual ~IVehicle(){}
};

class Car : public IVehicle {
public:
	Car(int speed) : _speed(speed) {}

	int getSpeed() const override {
		return _speed;
	}

	const std::string& getType() const override {
		return _type;
	}

private:
	int _speed;
	std::string _type = "Car";
};

class Van : public Car {
public:
	Van(int speed) : Car(speed){}
	const std::string& getType() const override {
		return _type;
	}
private:
	std::string _type = "Van";
};

void funcCar(std::shared_ptr<Car> carPtr) {
	std::cout << "Inside funcCar" << '\n';
	std::cout << carPtr->getSpeed() << '\n';
	std::cout << carPtr->getType() << '\n';
}

int main() {

	// A *a = new A();
	// С++11: Deprecated, C++17 deleted
	// std::auto_ptr<A> p(new A());
	// std::auto_ptr<A> p2 = p;
	
	// shared_ptr - имеет контрольный блок,в котором помимо прочего лежит счетчик указателей
	// unique_ptr - гарантирует, что только один указатель будет владеть объектом

	//std::unique_ptr<A> uptr(new A());

	//std::unique_ptr<Point> pPoint(new Point(5, 4));
	//std::cout << pPoint->getX() << '\n';

	// pPoint.get()->getX();	// get() - метод unique_ptr, вовзращает указатель на объект, которым мы владеем
	// pPoint.release()
	// pPoint.reset()

	/*SmartPtr<Point> sm(new Point(5, 4));
	std::cout << sm->getX() << '\n';*/

	/*std::unique_ptr<Point> p5 = std::make_unique<Point>(5, 4);
	std::shared_ptr<Point> sp1 = std::make_shared<Point>(1, 2);*/

	// Van
	std::shared_ptr<Van> v = std::make_shared<Van>(50);
	std::cout << v->getSpeed() << '\n';
	std::cout << v->getType() << '\n';
	std::cout << "===================\n";
	//std::dynamic_pointer_cast<new-type> (object to cast);
	std::shared_ptr<Car> c = std::dynamic_pointer_cast<Car>(v);	// Car* c = dinamic_cast<Car*>(v);
	std::cout << c->getSpeed() << '\n';
	std::cout << c->getType() << '\n';
	std::cout << "===================\n";
	funcCar(c);

}