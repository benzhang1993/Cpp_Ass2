#include <iostream>
#include "Tour.hpp"
#include "City.hpp"
#include <random>
#include <set>
#include <algorithm>

constexpr int num = 32;
constexpr int mutation_value = 15;
constexpr double improvement_factor = 1.20;

void select_elite(vector<Tour>&);
Tour select_parents(vector<Tour>&);
Tour cross_parents(Tour, Tour);
void mutate(Tour&);


int main() {

    vector<Tour> tours;
    vector<City> cities;

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> cord(cord_min, cord_max);

    for(int i = 1; i <= num; ++i) {
        string city_name = "City" + to_string(i);
        City c(city_name, cord(rng), cord(rng));
        c.set_mutation();
        cities.push_back(c);
    }

    for(int i = 0; i < num; ++i) {
        Tour t(cities, num);
        cout << "Tour: " << i << " fitness: " << t.get_fitness() << endl;
        tours.push_back(t);
    }

    /**
     * Start of Algorithm
     */

    double base_fitness;
    double current_fitness = 0;
    select_elite(tours);
    base_fitness = tours[0].get_fitness();
    for(int i = 1; i <= 1000; ++i) {
        select_elite(tours);
        cout << "Generation: " << i << ": Elite Fitness: " <<  tours[0].get_fitness() << " Total Distance: " << tours[0].get_total_distance() << endl;
        current_fitness = tours[0].get_fitness();
        if(current_fitness/base_fitness > improvement_factor) {
             break;
        }

        Tour parent1 = select_parents(tours);
        Tour parent2 = select_parents(tours);

        for(int j = 1; j < num; ++j) {
            tours[j] = cross_parents(parent1, parent2);
        }

        uniform_int_distribution<int> select_tour(1, (num - 1));
        uniform_int_distribution<int> num_tours_selected(5, 31);

        for(int j = 0; j <= num_tours_selected(rng); j++) {
            mutate(tours[select_tour(rng)]);
        }
    }

    cout << "Final improvement: " << (current_fitness/base_fitness) * 100 << "%" << endl;

    return 0;
}


void select_elite(vector<Tour>& tours) {
    double last_fitness = 0;
    double current_fitness = 0;
    int index = 0;
    for(int i = 0; i < num; ++i) {
        if((current_fitness = tours[i].get_fitness())  > last_fitness) {
            index = i;
            last_fitness = current_fitness;
        }
    }
    swap(tours[0], tours[index]);
}

Tour select_parents(vector<Tour>& tours) {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<unsigned> rand;
    shuffle(tours.begin(), tours.end(), default_random_engine(rand(rng)));

    // Getting 2 list of potential parents
    int parent_count = 5;
    vector<Tour> parent_list;
    for(int i = 1; i <= parent_count; ++i) {
        parent_list.push_back(tours[i]);
    }

    // Getting the fittest tour within the subset of parents
    double last_fitness = 0;
    double current_fitness = 0;
    int index_parent = 0;
    for(int i = 0; i < 5; ++i) {
        if ((current_fitness = parent_list[i].get_fitness()) > last_fitness) {
            last_fitness = current_fitness;
            index_parent = i;
        }
    }
    return parent_list[index_parent];
}

Tour cross_parents(Tour parent1, Tour parent2) {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> rand_index(0, num);
    vector<City> child;
    child.reserve(num);

    parent1.shuffle_cities();
    parent2.shuffle_cities();

    for(int j = 0; j <= rand_index(rng); ++j) {
        child.push_back(parent1.get_cities()[j]);
    }
    for(int k = 0; child.size() < num; ++k) {
        auto iter = find(child.begin(), child.end(), parent2.get_cities()[k]);
        if(iter == child.end()) {
            child.push_back(parent2.get_cities()[k]);
        }
    }
    Tour tmp(child, num);
    return tmp;
}

void mutate(Tour& evolve) {

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> adjacent(1, 100);

    for(int i = 1; i < num; ++i) {
        evolve.get_cities()[i].set_mutation();
        if(evolve.get_cities()[i].get_mutation() > mutation_value) {
            if(i == 0) {
                swap(evolve.get_cities()[i], evolve.get_cities()[i+1]);
            } else if(i == 31) {
                swap(evolve.get_cities()[i], evolve.get_cities()[i-1]);
            } else if(adjacent(rng) >= 50) {
                swap(evolve.get_cities()[i], evolve.get_cities()[i+1]);
            } else {
                swap(evolve.get_cities()[i], evolve.get_cities()[i-1]);
            }
        }
    }
}