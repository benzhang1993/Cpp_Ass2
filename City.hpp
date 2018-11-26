#ifndef Cpp_Ass2_City_HPP
#define Cpp_Ass2_City_HPP

#include <string>
#include <iostream>

using namespace std;

constexpr int cord_max = 1000;
constexpr int cord_min = 0;

class City {
private:
    string name;
    int xcord;
    int ycord;
    int mutation;

public:
    City(string name, int x, int y);

    string get_name() const;
    int get_x_cord() const;
    int get_y_cord() const;
    void set_mutation();
    int get_mutation();
    friend bool operator==(const City& lhs, const City& rhs);
};


#endif
