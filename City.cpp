#include <random>
#include "City.hpp"

City::City(string name, int x, int y) {

    name = move(name);
    xcord = x;
    ycord = y;
    mutation = 0;
}

string City::get_name() const {
    return name;
}

int City::get_x_cord() const {
    return xcord;
}

int City::get_y_cord() const {
    return ycord;
}

bool operator==(const City& lhs, const City& rhs) {
    return lhs.name == rhs.name;
}

void City::set_mutation() {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<unsigned> mutate(1, 100);
    mutation = mutate(rng);
}

int City::get_mutation() {
    return mutation;
}