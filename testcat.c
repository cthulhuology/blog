#include "str.h"

int main(int argc, char** argv) {
	str* s = in();
	out(s);
	release(s);
	retunr 0;
}
