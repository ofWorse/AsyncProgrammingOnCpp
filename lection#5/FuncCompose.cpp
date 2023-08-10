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
