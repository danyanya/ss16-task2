#include <iostream>

#include "solver.hpp"

class dir_solver : public dir_solver_base
{
public:
    dir_solver(int rows_x, int rows_y, int fragment_x, int fragment_y,
               int cpu_num, int proc_id)
        : dir_solver::dir_solver_base(-2, 2, rows_x, -2, 2, rows_y,
                                      fragment_x, fragment_y, cpu_num, proc_id)
    {}
    virtual ~dir_solver(){}

    virtual double main_function(const double &x, const double &y)
    {
        return (x * x + y * y) * sin(x * y);
    }

    virtual double border_function(const double &x, const double &y)
    {
        return sin(x * y) + 1.0;
    }

};

int main(int argc, char ** argv)
{

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " ROWS_X ROWS_Y " << std::endl;
        return 1;
    }

    int ierr, proc_id, cpu_num;
    int rows_x = std::stoi(argv[1]);
    int rows_y = std::stoi(argv[2]);
    double start_time, finish_time, uptime;
    int fragment_x, fragment_y;

    ierr = MPI_Init(&argc,&argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &cpu_num);

    fragment_x = 1 << int(ceil(log(cpu_num) / 2));
    fragment_y = 1 << int(ceil(log(cpu_num) / 2));
    fragment_y = fragment_x * fragment_y < cpu_num ?
                fragment_y << 1 : fragment_y;
//#ifdef DEBUG
    if (!proc_id) {
        std::cout << cpu_num << std::endl;
        std::cout << fragment_x << std::endl;
        std::cout << fragment_y << std::endl;
    }
//#endif

    auto solver = dir_solver(rows_x, rows_y, fragment_x,
                             fragment_y, cpu_num, proc_id);

    start_time = MPI_Wtime();

    solver.compute();

    finish_time = MPI_Wtime();
    uptime = finish_time - start_time;
    std::cout << "Uptime: " << uptime << std::endl;

    MPI_Finalize();

    return 0;
}
