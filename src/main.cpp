#include "app/app.h"

int main() {
	try {
		App app;
		app.run();
	}
	catch (...) {
		std::cout << "An unexpected error occured!";
	}
}