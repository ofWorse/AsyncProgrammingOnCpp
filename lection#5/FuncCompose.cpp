/// --- Обработка выражений с помощью шаблонов "Композит" и "Посетитель". --- ///
#include <iostream>
#include <memory>
#include <list>
#include <stack>
#include <functional>
#include <thread>
#include <future>
#include <random>
#include "FuncCompose.h"
using namespace std;

// перечень операций, поддерживаемых вычислителем.
enum class OPERATOR {
	ILLEGAL, PLUS, MINUS, MUL, DIV, UNARY_PLUS, UNARY_MINUS
};

// Хранит стандартное число с плавающей точкой.
class Number;

// Узлы синтаксического дерева.
class BinaryExpr; // Для бинарной операции
class UnaryExpr; // Для унарной операции

class IExprVisitor; // Интерфейс посетителя

// Базовый класс для узлов синтаксического дерева
class Expr {
public:
	virtual double accept(IExprVisitor& exprVis) = 0;
	virtual ~Expr() {}
};

// Интерфейс посетителя с методами для обработки разных типов узлов
struct IExprVisitor {
	virtual double Visit(Number& num) = 0;
	virtual double Visit(BinaryExpr& bin) = 0;
	virtual double Visit(UnaryExpr& un) = 0;
};

class Number : public Expr {
	double NUM;
public:
	double getNUM() { return NUM; }
	void setNUM(double num) { NUM = num; }
	Number(double n) { this->NUM = n; }
	~Number() {}
	double accept(IExprVisitor& exprVis) { return exprVis.Visit(*this); }
};

// Выражение с бинарной операцией 
class BinaryExpr : public Expr {
	Expr* left; Expr* right;
	OPERATOR OP;
public:
	BinaryExpr(Expr* l, Expr* r, OPERATOR op) {
		left = l;
		right = r;
		OP = op;
	}
	OPERATOR getOP() { return OP; }
	Expr& getLeft() { return *left; }
	Expr& getRight() { return *right; }
	~BinaryExpr() {
		delete left;
		delete right;
	}
	double accept(IExprVisitor& exprVis) {
		return exprVis.Visit(*this);
	}
};

class UnaryExpr : public Expr {
	Expr* right;
	OPERATOR op;
public:
	UnaryExpr(Expr* operand, OPERATOR op) {
		right = operand;
		this->op = op;
	}
	Expr& getRight() { return *right; }
	OPERATOR getOP() { return op; }
	virtual ~UnaryExpr() { delete right; right = 0; }
	double accept(IExprVisitor& exprVis) { return exprVis.Visit(*this); }
};

// Посетитель, вычисляющий значение выражения
class TreeEvaluatorVisitor : public IExprVisitor {
public:
	double Visit(Number& num) { return num.getNUM(); }
	double Visit(BinaryExpr& bin) {
		OPERATOR temp = bin.getOP();
		double lval = bin.getLeft().accept(*this);
		double rval = bin.getRight().accept(*this);
		return (temp == OPERATOR::PLUS)
			? lval + rval
			: (temp == OPERATOR::MUL)
			? lval * rval
			: (temp == OPERATOR::DIV)
			? lval / rval
			: lval - rval;
	}
	double Visit(UnaryExpr& un) {
		OPERATOR temp = un.getOP();
		double rval = un.getRight().accept(*this);
		return (temp == OPERATOR::UNARY_PLUS) 
			? +rval 
			: -rval;
	}
};

// Посетитель для перевода выражения в обратную польскую запись 
class ReversePolishEvaluator : public IExprVisitor {
public:
	double Visit(Number& num) {
		cout << num.getNUM() << " " << endl;
		return 42;
	}

	double Visit(BinaryExpr& bin) {
		bin.getLeft().accept(*this);
		bin.getRight().accept(*this);
		OPERATOR temp = bin.getOP();
		auto const op = (temp == OPERATOR::PLUS)
			? " + "
			: (temp == OPERATOR::MUL)
			? " * "
			: (temp == OPERATOR::DIV)
			? " / "	
			: " - ";
		cout << op << endl;
		return 42;
	}
	
	double Visit(UnaryExpr &un) {
		OPERATOR temp = un.getOP();
		un.getRight().accept(*this);
		cout << ((temp == OPERATOR::UNARY_PLUS) ? " (+) " : " (-) ");
		return 42;
	} 
};

int main() {
	unique_ptr<Expr> a( 
			new BinaryExpr( 
				new Number(10.0), 
				new Number(20.0), 
				OPERATOR::PLUS
			)
	);
	unique_ptr<IExprVisitor> eval( new TreeEvaluatorVisitor() );
	double result = a->accept(*eval);
	cout << "Результат вычисления -> " << result << endl;

	unique_ptr<IExprVisitor> exp( new ReversePolishEvaluator() );
	cout << "Выражение в постфиксной записи: " << endl;
	a->accept(*exp);
	return 0;
}
