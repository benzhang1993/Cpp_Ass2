#ifndef Cpp_Ass2_Tour_HPP
#define Cpp_Ass2_Tour_HPP


#include "City.hpp"
#include <vector>
#include <random>

class Tour {
private:
    vector<City> list_of_city;
    double fitness;
    int number_of_city;
    double distance_sum;

public:
    explicit Tour(vector<City>& cities, int num);

    vector<City> get_cities() const;
    double get_fitness() const;
    void shuffle_cities();
    double get_total_distance();
};


#endif
