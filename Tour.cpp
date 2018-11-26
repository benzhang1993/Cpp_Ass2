#include "Tour.hpp"
#include <algorithm>

Tour::Tour(vector<City>& cities, int number){

    list_of_city = cities;
    number_of_city = number;
    shuffle_cities();

    distance_sum = 0;
    for(int i = 0; i < number_of_city - 1; i++) {
        double a = list_of_city[i + 1].get_x_cord() - list_of_city[i].get_x_cord();
        double b = list_of_city[i + 1].get_y_cord() - list_of_city[i].get_y_cord();
        distance_sum += sqrt((a * a) + (b * b));
    }
    double a = list_of_city[0].get_x_cord() - list_of_city[31].get_x_cord();
    double b = list_of_city[0].get_y_cord() - list_of_city[31].get_y_cord();
    distance_sum += sqrt((a * a) + (b * b));
    fitness = 1000000 / distance_sum;

}

vector<City> Tour::get_cities() const {
    return list_of_city;
}

double Tour::get_fitness() const {
    return fitness;
}

void Tour::shuffle_cities() {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<unsigned> seed;
    shuffle(list_of_city.begin(), list_of_city.end(), default_random_engine(seed(rng)));
}

double Tour::get_total_distance() {
    return distance_sum;
}

