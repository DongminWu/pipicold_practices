#include <cstdint>
#include <functional>
#include <mutex>
#include <utility>
#include <memory>
#include <iostream>

using namespace std;

//https://cpptruths.blogspot.com/2011/10/multi-dimensional-arrays-in-c11.html
template<typename T, size_t I, size_t...J>
struct MultiDim
{
    using Nested = typename MultiDim<T, J...>::type;
    using type = Nested[I];
    using value_type = T;

    enum
    {
        size = I * MultiDim<T, J...>::size,
        minor = size / I,
        major = I,
        dim =  MultiDim<T, J...>::dim + 1,
    };
    // static constexpr size_t size = I * MultiDim<T, J...>::size;

    inline static void forEach(type &array, std::function<void(T&)> func)
    {
        for (size_t i = 0; i < I; ++i) 
        {
            MultiDim<T, J...>::forEach(array[i], func);
        }
    }
    inline static bool all(type &lhs, type &rhs, std::function<bool(T&, T&)> cmp)
    {
        bool ret = true;
        for (size_t i = 0; i < I; ++i) 
        {
            ret &= MultiDim<T, J...>::all(lhs[i], rhs[i], cmp);
        }
        return ret;
    }
    inline static bool any(type &lhs, type &rhs, std::function<bool(T&, T&)> cmp)
    {
        bool ret = false;
        for (size_t i = 0; i < I; ++i) 
        {
            ret |= MultiDim<T, J...>::any(lhs[i], rhs[i], cmp);
        }
        return ret;
    }

    inline static void binaryOp(type &lhs, type &rhs, std::function<T(T&, T&)> computer, type& output)
    {
        for (size_t i = 0; i < I; ++i) 
        {
            MultiDim<T, J...>::binaryOp(lhs[i], rhs[i], computer, output[i]);
        }
    }
    inline static void run(type &array)
    {
        // cout << I << endl;
        for(size_t i = 0; i < I; ++i)
        {
            MultiDim<T, J...>::run(array[i]);
        }
    }
};
template <typename T, size_t I>
struct MultiDim<T, I> 
{
    using type = T [I];
    using value_type = T;

    enum {
        size = I,
        minor = 1,
        major = I,
        dim = 1,
    };

    inline static void forEach(type &array, std::function<void(T&)> func)
    {
        for (size_t i = 0; i < I; ++i) 
        {
            func(array[i]);
        }
    }

    inline static bool all(type &lhs, type &rhs, std::function<bool(T&, T&)> cmp)
    {
        bool ret = true;
        for (size_t i = 0; i < I; ++i) 
        {
            ret &=cmp(lhs[i], rhs[i]);
        }
        return ret;
    }
    inline static bool any(type &lhs, type &rhs, std::function<bool(T&, T&)> cmp)
    {
        bool ret = false;
        for (size_t i = 0; i < I; ++i) 
        {
            ret |= cmp(lhs[i], rhs[i]);
        }
        return ret;
    }

    inline static void binaryOp(type &lhs, type &rhs, std::function<T(T&, T&)> computer, type& output)
    {
        for (size_t i = 0; i < I; ++i) 
        {
            output[i] = computer(lhs[i], rhs[i]);
        }
    }

    inline static void run(T (&array)[I])
    {
        for (size_t i = 0; i < I; ++i) 
        {
            cout << array[i] << endl;
        }
        cout << "last: " << I <<endl;
    }
};

//https://stackoverflow.com/questions/340943/c-multi-dimensional-arrays-on-the-heap
template<typename T, size_t I, size_t...J>
struct HeapMultiDim
{
    typedef typename HeapMultiDim<T, J...>::Nested Nested[I];
    using ptr_type = typename HeapMultiDim<T, J...>::Nested *;
    using type = Nested;
    // typedef T type Nested[I];

    inline static void run(ptr_type array)
    {
        // cout << I << endl;
        for(size_t i = 0; i < I; ++i)
        {
            MultiDim<T, J...>::run(array[i]);
        }
    }

    inline static void forEach(ptr_type array, std::function<void(T&)> func)
    {
        for (size_t i = 0; i < I; ++i) 
        {
            MultiDim<T, J...>::forEach(array[i], func);
        }
    }
};

template <typename T, size_t I>
struct HeapMultiDim<T, I> 
{
    typedef T Nested[I];
    using ptr_type = T*;
    using type = Nested;
    using value_type = T;


    inline static void run(ptr_type array)
    {
        for (size_t i = 0; i < I; ++i) 
        {
            cout << array[i] << endl;
        }
        cout << "last: " << I <<endl;
    }

     inline static void forEach(ptr_type &array, std::function<void(T&)> func)
    {
        for (size_t i = 0; i < I; ++i) 
        {
            func(array[i]);
        }
    }
};

void func(int (&array)[3][2])
{
    cout << "func: " << array[2][0] << endl;

}
int main()
{
    cout << "welcome to test" << endl;
    using myMatrix = MultiDim<int, 5, 2, 3, 4>;

    myMatrix::type left = {};
    myMatrix::type right = {};


    auto init = [](int& each) -> void{
        static size_t cnt = 0;
        each = cnt++;
    };
    auto init2 = [](int& each) -> void{
        static size_t cnt = 0;
        each = cnt++;
    };
    

    myMatrix::forEach(left, init);
    myMatrix::forEach(right, init2);

    cout << "myMatrix.size = " << myMatrix::size << endl;
    cout << "myMatrix.dim = " << myMatrix::dim << endl;
    cout << "myMatrix.major = " << myMatrix::major << endl;
    cout << "myMatrix.minor = " << myMatrix::minor << endl;

    cout << "all equal: " << myMatrix::all(left, right, std::equal_to<int>()) << endl;

    cout << "1,1,1,1 equal?: " << std::equal_to<int>()(right[1][1][1][1], left[1][1][1][1]) << endl;
    cout << "1,1,1,1 equal?: " << (right[1][1][1][1] == left[1][1][1][1]) << endl;
    cout << left[1][1][1][1] << " vs. " << right[1][1][1][1] << endl;

    right[1][1][1][1] = 0;
    cout << "any not equal: " << myMatrix::any(left, right, std::not_equal_to<int>()) << endl;
    cout << "1,1,1,1 not equal?: " << std::not_equal_to<int>()(right[1][1][1][1], left[1][1][1][1]) << endl;
    cout << left[1][1][1][1] << " vs. " << right[1][1][1][1] << endl;

    myMatrix::type sum = {};

    myMatrix::binaryOp(left, right, std::plus<myMatrix::value_type>(), sum);

    auto printEach = [](int& each){
        printf("%d ", each);
    };

    myMatrix::forEach(sum, printEach);
    printf("\n");



    int* test = new int[32];
    for(int i = 0; i < 32; i++)
    {
        test[i] = i;
    }
    int (*ptr)[4][8];
    // ptr = &test;
    ptr = ((int (*)[4][8])(&test[0]));
    auto ptr_t = *ptr;
  
    cout << "ptr[1][1]: " << ((*ptr)[3][7]) <<endl;

    // int [8](*) ptr3 = (int (*)[8])()test;
    using heapMatrix = HeapMultiDim<int, 2, 2, 3>;
    heapMatrix::type Arr = {};
    heapMatrix::ptr_type ptr_stack  = Arr;
    heapMatrix::ptr_type ptr2  = new heapMatrix::type ;
    heapMatrix::run(Arr);

    heapMatrix::forEach(Arr, init);
    heapMatrix::forEach(Arr, printEach);

}