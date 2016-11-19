#ifndef DIR_SOLVER_HPP
#define DIR_SOLVER_HPP 1

#include <mpi.h>
#include <iostream>
#include <string>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#define EPS 1e-4

class dir_solver_base
{
public:
    dir_solver_base(int min_x, int max_x, int rows_x,
                    int min_y, int max_y, int rows_y)
        : min_x(min_x)
        , max_x(max_x)
        , rows_x(rows_x)
        , min_y(min_y)
        , max_y(max_y)
        , rows_y(rows_y)
    {}
    virtual ~dir_solver_base(){}

    /**
     * @brief main_function -- return value of main function in equation
     * @param x -- x coord
     * @param y -- y coord
     * @return value of that function
     */
    virtual double main_function(const double &x, const double &y) = 0;

    /**
     * @brief border_function -- hardcoded border function
     * @param x -- x coord
     * @param y -- y coord
     * @return value of that function
     */
    virtual double border_function(const double &x, const double &y) = 0;

    /**
     * @brief compute -- function for compute equation
     */
    void compute(){}
private:
    int min_x;
    int max_x;
    int rows_x;
    int min_y;
    int max_y;
    int rows_y;

};



#endif /* DIR_SOLVER_HPP */
