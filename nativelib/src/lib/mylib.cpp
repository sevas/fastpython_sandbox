#include <iostream>

#include <chrono>
#include <functional>
#include <numeric>
#include <string>
#include <vector>

#include "Eigen/Core"

#include "pybind11/eigen.h"
#include "pybind11/numpy.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;

int add(int i, int j) { return i + j; }

std::vector<int> make_ints(const size_t size) { return std::vector<int>(size); }

float sum_float(const std::vector<float>& values) { return std::accumulate(values.begin(), values.end(), 0.f, std::plus<float>()); }

int sum_int(const std::vector<int>& values)
{
    //    return std::accumulate(values.begin(), values.end(), 0.f, std::plus<int>());
    auto before = std::chrono::high_resolution_clock::now();
    const auto n = values.size();
    int s = 0;
    for (auto i = 0u; i < n; ++i)
    {
        s += values[i];
    }

    auto after = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
    // std::cout << "[sum_int] elapsed: " << elapsed << " us" << std::endl;
    return s;
}

int sum_int_pyarray(const py::array_t<int>& values)
{
    //    return std::accumulate(values.begin(), values.end(), 0.f, std::plus<int>());
    auto before = std::chrono::high_resolution_clock::now();
    const auto n = values.size();
    int s = 0;

    auto* p = values.data();

    for (auto i = 0u; i < n; ++i)
    {
        s += p[i];
    }

    auto after = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
    // std::cout << "[sum_int_pyarray] elapsed: " << elapsed << " us" << std::endl;
    return s;
}

float sum_eigen(Eigen::MatrixXf& m)
{
    //    std::cout << m.rows() << "  " << m.cols() << std::endl;
    return m.sum();
}

int sum_eigen_i(Eigen::MatrixXi& m)
{
    //    std::cout << m.rows() << "  " << m.cols() << std::endl;
    auto before = std::chrono::high_resolution_clock::now();
    auto sum = m.sum();

    auto after = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
    // std::cout << "[sum_eigen_i] elapsed: " << elapsed << " us" << std::endl;

    return sum;
}

Eigen::MatrixX3f mv_mul(const Eigen::Matrix3f& M, const Eigen::MatrixX3f& points) { return M * points; }

void array_add_scalar_stl(std::vector<float>& in, const float val)
{
    for (auto i = 0u; i < in.size(); ++i)
    {
        in[i] += val;
    }
}

void array_add_scalar_eigen(Eigen::MatrixXf& in, const float val)
{
    // std::cout << "ptr: " << &in << std::endl;

    Eigen::MatrixXf values(in.rows(), in.cols());
    values.setConstant(val);
    in += values;
}
struct thing
{
    enum class elem_dtype
    {
        dt_void,
        dt_int,
        dt_float,
        dt_double,
        dt_char
    };
    elem_dtype dtype;
    void* data;
};

// clang-format off
template<thing::elem_dtype dt> struct dtype_to_type{ typedef void elem_type; };
template<> struct dtype_to_type<thing::elem_dtype::dt_int> { typedef int elem_type; };
template<> struct dtype_to_type<thing::elem_dtype::dt_float> { typedef float elem_type; };
template<> struct dtype_to_type<thing::elem_dtype::dt_double> { typedef double elem_type; };
template<> struct dtype_to_type<thing::elem_dtype::dt_char> { typedef char elem_type; };

template<typename T> struct type_to_dtype { static const thing::elem_dtype dtype=thing::elem_dtype::dt_void; };
template<> struct type_to_dtype<int> { static const thing::elem_dtype dtype = thing::elem_dtype::dt_int; };
template<> struct type_to_dtype<float> { static const thing::elem_dtype dtype = thing::elem_dtype::dt_float; };
template<> struct type_to_dtype<double> { static const thing::elem_dtype dtype = thing::elem_dtype::dt_double; };
template<> struct type_to_dtype<char> { static const thing::elem_dtype dtype = thing::elem_dtype::dt_char; };
// clang-format on

class data_manager

{

  public:
    data_manager()
    {
        things["vector_int"] = thing{thing::elem_dtype::dt_int, (void*)new std::vector<int>(10)};
        things["vector_float"] = thing{thing::elem_dtype::dt_float, (void*)new std::vector<float>(10)};
        things["vector_double"] = thing{thing::elem_dtype::dt_double, (void*)new std::vector<double>(10)};
    }

    ~data_manager() {}

    template <typename T> std::vector<T>& get_data(const std::string& name)
    {
        auto item = things[name];

        typedef std::vector<T> ptr_type;
        if (type_to_dtype<T>::dtype == item.dtype)
        {
            return *reinterpret_cast<ptr_type*>(item.data);
        }

        throw py::index_error("did not find a data named with type T");
    }

    std::vector<std::string> get_names() const
    {
        std::vector<std::string> names;
        for (auto& thing_entry : things)
        {
            names.push_back(thing_entry.first);
        }
        return names;
    }

  private:
    std::map<std::string, thing> things;
};

std::vector<int> get_vector_int(data_manager& dm, const std::string& name) { return dm.get_data<int>(name); }

std::vector<float> get_vector_float(data_manager& dm, const std::string& name) { return dm.get_data<float>(name); }

std::vector<double> get_vector_double(data_manager& dm, const std::string& name) { return dm.get_data<double>(name); }

static int k_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

static int k_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

static int neighbour_idx[3][3][2] = {
    {{-1, -1}, {-1, 0}, {-1, 1}},
    {{0, -1}, {0, 0}, {0, 1}},
    {{1, -1}, {1, 0}, {1, 1}},
};

void sobel(py::array_t<unsigned char>& in, py::array_t<unsigned char>& out)
{
    // h, w = im.shape
    // for y in range(1, h-1):
    //     for x in range(1, w-1):
    //         x_val = 0
    //         y_val = 0
    //         for yy in range(3):
    //             for xx in range(3):
    //                 dx, dy = neighbour_idx[yy, xx]
    //                 x_val += k_x[yy, xx] * im[y+dy, x+dx]
    //                 y_val += k_y[yy, xx] * im[y+dy, x+dx]

    //         out[y, x] = m.sqrt(x_val*x_val + y_val*y_val)
    const auto h = in.shape()[0] - 1;
    const auto w = in.shape()[1] - 1;

    for (auto i = 1; i < h; ++i)
    {
        for (auto j = 1; j < w; ++j)
        {
            unsigned char x_val = 0;
            unsigned char y_val = 0;
            for (auto ii = 0u; ii < 3; ++ii)
            {
                for (auto jj = 0u; jj < 3; ++jj)
                {
                    const int dy = neighbour_idx[ii][jj][0];
                    const int dx = neighbour_idx[ii][jj][1];
                    const auto in_value = in.at(i + dy, j + dx);
                    x_val += k_x[ii][jj] * in_value;
                    y_val += k_y[ii][jj] * in_value;
                }
            }
            auto value = static_cast<int>(sqrt(x_val * x_val + y_val * y_val));
            if (value > 255)
            {
                value = 255;
            }
            out.mutable_at(i, j) = static_cast<unsigned char>(value);
        }
    }
}

#ifdef _DEBUG
#define PY_MODULE_NAME mylib_d
#else
#define PY_MODULE_NAME mylib
#endif

PYBIND11_MODULE(PY_MODULE_NAME, m)
{
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");
    m.def("make_ints", &make_ints, "A function ");
    m.def("sum_int", &sum_int, "Sums the elements in a int vector");
    m.def("sum_float", &sum_float, "Sums the elements in a float vector");
    m.def("sum_eigen", &sum_eigen, "Sums the elements in an arbitrary matrix");
    m.def("sum_eigen_i", &sum_eigen_i, "Sums the elements in an arbitrary matrix");
    m.def("sum_int_pyarray", &sum_int_pyarray, "Sums the elements in an arbitrary matrix");

    m.def("array_add_scalar_stl", &array_add_scalar_stl, "Sums the elements in a vector");
    m.def("array_add_scalar_eigen", &array_add_scalar_eigen, "Sums the elements in an arbitrary matrix");

    m.def("mv_mul", &mv_mul, "Mat x Vec product");

    // clang-format off
    py::class_<data_manager>(m, "DataManager")
		.def(py::init())
		.def("get_names", &data_manager::get_names);
    // clang-format on

    m.def("get_vector_int", &get_vector_int);
    m.def("get_vector_float", &get_vector_float);
    m.def("get_vector_double", &get_vector_double);

    m.def("sobel", &sobel);
}
