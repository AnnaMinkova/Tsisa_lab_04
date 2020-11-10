#include <iostream>
#include <cmath>
#include <vector>
#include <random>
double myFunction (double x, double y)
{
    return 1.0 / cos(x)*cos(y)*exp(-x*x-y*y);
}
struct Coords
{
    double x,y;
    double fit;
};

std::vector<Coords> population;

double mid_value (const std::vector<Coords>& v)
{
    double res = 0.0;
    for (const auto& elem : v)
    {
        res += elem.fit;
    }
    return res / 6;
}

bool CompareCoords (const Coords& c1, const Coords& c2)
{
    return c1.fit > c2.fit;
};

void print (const std::vector<Coords>& v, size_t it)
{
    std::cout << "N: " << it << " Average: " << mid_value(v) << " Max: " << v[0].fit << std::endl;
    for (const auto& elem : v)
    {
        std::cout << "x: " << elem.x << " y: " << elem.y << " fit: " << elem.fit << std::endl;
    }
}

int main (int argc, const char * argv[])
{
    population.resize(6);
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_real_distribution<double> dis(-2, 2);
    std::uniform_real_distribution<double> dis_mut(-25, 25);
    std::uniform_real_distribution<double> prob(0, 1);

    int n = 100;
    double p_mut = 0.25;

    for (auto i = 0; i < population.size(); i++)
    {
        Coords coord;
        coord.x = dis(gen);
        coord.y = dis(gen);
        coord.fit = myFunction(coord.x, coord.y);
        population[i] = coord;
    }

    std::sort(population.begin(), population.end(), CompareCoords);

    print(population, 0);

    for (auto i = 1; i <= n; i++)
    {
        for (auto j = 0; j < population.size(); j++)
        {
            auto p = prob(gen);

            if (p < p_mut)
            {
                population[j].x = fmod(population[j].x * dis_mut(gen), 1);
                population[j].y = fmod(population[j].y * dis_mut(gen), 1);
                population[j].fit = myFunction(population[j].x, population[j].y);
            }
        }
        std::sort(population.begin(), population.end(), CompareCoords);

        std::vector<Coords> new_pop;

        new_pop.resize(6);

        size_t temp;

        if (population[0].fit != population[1].fit)
        {
            temp = 1;
        } else
            {
            temp = 2;
            }

        new_pop[0].x = population[0].x;
        new_pop[0].y = population[temp].y;
        new_pop[0].fit = myFunction(new_pop[0].x, new_pop[0].y);

        new_pop[1].x = population[temp].x;
        new_pop[1].y = population[0].y;
        new_pop[1].fit = myFunction(new_pop[1].x, new_pop[1].y);

        new_pop[2].x = population[0].x;
        new_pop[2].y = population[temp + 1].y;
        new_pop[2].fit = myFunction(new_pop[2].x, new_pop[2].y);

        new_pop[3].x = population[temp + 1].x;
        new_pop[3].y = population[0].y;
        new_pop[3].fit = myFunction(new_pop[3].x, new_pop[3].y);

        new_pop[4].x = population[0].x;
        new_pop[4].y = population[temp + 3].y;
        new_pop[4].fit = myFunction(new_pop[4].x, new_pop[4].y);

        new_pop[5].x = population[temp + 3].x;
        new_pop[5].y = population[0].y;
        new_pop[5].fit = myFunction(new_pop[5].x, new_pop[5].y);


        std::sort(new_pop.begin(), new_pop.end(), CompareCoords);
        population = new_pop;
        print(population, i);
    }
    return 0;
}
