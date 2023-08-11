/// --- Обработка выражений с помощью шаблонов "Композит" и "Посетитель". --- ///
#include <iostream>
#include <memory>
#include <list>
#include <stack>
#include <functional>
#include <thread>
#include <future>
#include <random>
#include "Map.h"
using namespace std;

// перечень операций, поддерживаемых вычислителем.
enum class OPERATOR {
	ILLEGAL, PLUS, MINUS, MUL, DIV, UNARY_PLUS, UNARY_MINUS
};

// Вид узла: операция или значение.
enum class ExprKind {
	ILLEGAL_EXPR, OPERATOR, VALUE
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

struct EXPR_ITEM {
	ExprKind knd;
	double value;
	OPERATOR op;

	EXPR_ITEM(): op(OPERATOR::ILLEGAL), value(0), knd(ExprKind::ILLEGAL_EXPR) {}
	bool setOperator(OPERATOR op) {
		this->op = op;
		this->knd = ExprKind::OPERATOR;
		return true;
	}
	bool setValue(double value) {
		this->knd = ExprKind::VALUE;
		this->value = value;
		return true;
	}
	string toString() {
		DumpContents();
		return "";
	}
private:
	void DumpContents() { /* Код для краткости опустим */ }
};

// Разглаживающий поесетитель
class FlattenVisitor : public IExprVisitor {
	list<EXPR_ITEM> ils;
	
	EXPR_ITEM MakeListItem(double num) {
		EXPR_ITEM temp;
		temp.setValue(num);
		return temp;
	}
	EXPR_ITEM MakeListItem(OPERATOR op) {
		EXPR_ITEM temp;
		temp.setOperator(op);
		return temp;
	}
public:
	FlattenVisitor() {}

	list<EXPR_ITEM> FlattenedExpr() { return ils; }
	
	double Visit(Number& num) {
		ils.push_back(MakeListItem(num.getNUM()));
		return 42;
	}
	double Visit(BinaryExpr& bin) {
		bin.getLeft().accept(*this);
		bin.getRight().accept(*this);
		ils.push_back(MakeListItem(bin.getOP()));
		return 42;
	}
	double Visit(UnaryExpr& un) {
		un.getRight().accept(*this);
		ils.push_back(MakeListItem(un.getOP()));
		return 42;
	}
};

list<EXPR_ITEM> ExprList(Expr* r) {
	unique_ptr<FlattenVisitor> fl(new FlattenVisitor());
	r->accept(*fl);
	return fl->FlattenedExpr();
}

// Стек для вычисления выражений в обратной польской записи
class DoubleStack : public stack<double> {
public:
	DoubleStack() {}
	void Push(double a) { this->push(a); }
	double Pop() {
		double a = this->top();
		this->pop();
		return a;
	}
};

// Итеративная обработка компонентов выражения
double Evaluate(list<EXPR_ITEM> ls) {
	DoubleStack stk;
	double n;
	for(EXPR_ITEM s : ls) {
		if(s.knd == ExprKind::VALUE) 
			stk.Push(s.value);
		else if(s.op == OPERATOR::PLUS)
			stk.Push(stk.Pop() + stk.Pop());
		else if(s.op == OPERATOR::MINUS)
			stk.Push(stk.Pop() - stk.Pop());
		else if(s.op == OPERATOR::DIV) {
			n = stk.Pop();
			stk.Push(stk.Pop() / n);
		}
		else if(s.op == OPERATOR::MUL) 
			stk.Push(stk.Pop() * stk.Pop());
		else if(s.op == OPERATOR::UNARY_MINUS)
			stk.Push(-stk.Pop());
	}
	return stk.Pop();
}

// Превратить дерево в список и сразу подать его на вычислитель
double Evaluate(Expr* ex) { return Evaluate(ExprList(ex)); }

void Iterate(list<EXPR_ITEM>& s) {
	for(auto n : s) { std::cout << n.toString() << "\n"; }
}

int main() {
	/*unique_ptr<Expr> a( 
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
	*/

	unique_ptr<Expr> a(
			new BinaryExpr(
				new Number(10.0),
				new Number(20.0),
				OPERATOR::PLUS
				)
			);
	double result = Evaluate(&(*a));
	cout << result << endl;
	return 0;
}
