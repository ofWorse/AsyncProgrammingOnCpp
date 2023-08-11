#include <iostream>
namespace app {

	class cout {
	public:
		
		template<typename T>
		cout& operator<<(const T& data) {
			std::cout << data;
			return *this;
		}	
	};
}

int main() {
	app::cout cout;
	cout << "Hello, " << 1234 << '\n';
	std::cout << "Hello from " << "std::cout" << std::endl;
}
