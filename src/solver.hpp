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
                    int min_y, int max_y, int rows_y,
                    int fragment_x, int fragment_y,
                    int cpu_num, int proc_id)
        : min_x(min_x)
        , max_x(max_x)
        , rows_x(rows_x)
        , min_y(min_y)
        , max_y(max_y)
        , rows_y(rows_y)
        , dx((max_x - min_x) / rows_x)
        , dy((max_y - min_y) / rows_y)
        , dxdy(dx * dy)
        , dxx(dx * dx)
        , dyy(dy * dy)
        , fragment_x(fragment_x)
        , fragment_y(fragment_y)
        , cpu_num(cpu_num)
        , proc_id(proc_id)
    {}

    virtual ~dir_solver_base(){}

    /**
     * @brief main_function -- return value of main function in equation
     * @param x -- x coord
     * @param y -- y coord
     * @return value of that function
     */
    virtual double main_function(const double &x, const double &y)
    {
        std::cout << "Warning. Main not realised in derived class " << std::endl;
        return 0.0;
    }

    /**
     * @brief border_function -- hardcoded border function
     * @param x -- x coord
     * @param y -- y coord
     * @return value of that function
     */
    virtual double border_function(const double &x, const double &y)
    {
        std::cout << "Warning. Border not realised in derived class " << std::endl;
        return 0.0;
    }

    /**
     * @brief compute -- function for compute equation
     */
    void compute();
private:

    double *scalar_product(double *vec1, double *vec2){}
    double norm(double *vec){}


    int min_x;
    int max_x;
    int rows_x;

    int min_y;
    int max_y;
    int rows_y;

    double dx, dy;
    double dxdy, dxx, dyy;

    int fragment_x, fragment_y;

    int cpu_num;
    int proc_id;
    MPI_Comm comm;
};



#endif /* DIR_SOLVER_HPP */
