# EasySTLContainer
An set of STL container wrap class, provied a lot of functional style algorithm member functions.
This append member function name sprite from Ruby,Erlang,Rust api .

# install
just copy xx.hpp file to your project, or system include path


# usage
* namespace
 all contianter in estl

#TODO
借鉴Rust 把迭代函数都放到迭代器中,而不是容器中



# test
depend gtets


//# Effective Modern C++

Why C++?
1. 零开销抽象
2. 泛型
3. 直接操作硬件
4. 多范式开发

Why Modern C++?
1. 更强的零开销抽象能力　
　　a. 可变模板参数
　  b.
2. 自动类型推倒
3. 移动语义
4. 并发能力

目标?
人群?
内容?

Change is Hard

现代C++ 语言设计意图
实现方式，三个层次
1. 语言内核
2. 标准库
3. 编程风格/方法
optional， promis/future

特性多，分布广
OO, 类型， GP（泛型编程),
C++11/14/17


展示例子

1.
  std::vector<int, Proson*> persons;

  for (std::vector<int, Person*>::iterator it = persons.being(); it != persons.end(); ++it) {
      printf("key %d %s", it->first, it->second->GetName());
  }

  for (auto it = persons.being(); it != persons.end(); ++it) {
      printf("key %d %s", it->first, it->second->GetName());
  }

  for (auto &pair : persons) {
      printf("key %d %s", pair.first, pair.second.GetName());
  }

  for (auto &[key, person] : persons)
      printf("key %d %s", key, person->GetName());
  }

2. class A {
    A():fd(-1), buf(NULL), isOk(false);
    int fd;
    char *buf;
    bool isOk;
};

2. class A {
    int fd = -1;
    char *buf = NULL;
    bool isOk =false;
};

2. log 库 python 方式
    sprintf(buf,%s %f %c", "hello", "3.14", 'c');

    std::string s = fmt::format("{} {} {}", "hello", "3.14", 'c');
     类型安全，任意长度参数





* distinguish lvalues and rvalues
    if you can task its address, it's an lvalue
    everthing not an lvalue :-)
      temporary object, return by value, unnamed value

   ```c++
   int x; // x is lv
   x = 10; //10 is rv
   ```
* understand type deduction, auto
* understand std::move and std::forward
* distinguish rvalues reference and universal references
* understand reference collapsing

本次讲解的核心关在语言层面的改动，也是看懂，用好现代C++的重要基础知识点
包括

0. 类型推倒 (Type Deduction)
  通过模板来引入 

98 中就有
  Template Type Deduaciton 

坐下测试
```cpp
template <typename T>
void f(ParamType param);
```

f(expr); //通过 expr 推倒出T和


ParamType 是same T
ParamType 是个引用或者是指针类型
ParamType 是个万能引用/统一引用 (Universal References)

---
ParamType By-Value (not by reference)

```cpp
template <typename T>
void fn(T param) 

int x = 22;
const int cx = x;
const int& rcx = x;

f(x); // T = int ,  param int
f(cx); //T = int, param's type = int
f(rcx);//T = int, param's type = int
```
deduction rules T is ignore reference, const, volatile if exp has.

e.g.
const int * p1;
const int * const p2;
f(p1); // T = const int * 
f(p2); // T = const int * , ignore const

note. 注意区别 const exprs 和 exprs Containing const




---
ParamType 是个引用或者是指针类型

template <typename T>
void fn(T& param) //param is ref

int x = 22;
const int cx = x;
const int& crx = x;

f(x); // T = int ,  param 类型为 const int&
f(cx); //T = const int, param's type = const int&
f(crx);//T = const int, param's type = const int&

 
---
```cpp
template <typename T>
void fn(T* param) //param is ref

int x = 22;
const int* pcx = &x;

f(&x); // T = int ,  param 类型为 int*
f(pcx); //T = const int, param's type = const int*
```

1. auto
   使用场景
   陷阱
   最佳实践

   用于迭代器
   用于lamdba

* 使用auto 进行声明的变量必须进行初始化
* auto 永远不会推到为引用类型，或者const,voilate 如果需要必须显示添加
* auto 推倒数组时会自动退化为指针,除非被声明为引用


auto 会自动去掉引用,cons,


2. 右值引用
右值引用主要用来解决98中的两个问题:
第一个问题就是临时对象非必要的昂贵的拷贝操作，第二个问题是在模板函数中如何按照参数的实际类型进行转发。通过引入右值引用，很好的解决了这两个问题
右值引用的第二个特点
　　右值引用独立于左值和右值。意思是右值引用类型的变量可能是左值也可能是右值。比如下面的例子：
int&& var1 = 1; 
　　var1类型为右值引用，但var1本身是左值，因为具名变量都是左值
3. 统一引用 //为什么要有

void foo(Bar&& b) //rref

tempalte <typename T>
void foo(T&& b) //uref

tempalte <typename T>
void foo(const T&& b) //const rref

tempalte <typename T>
Class Dog {
    void foo(T&&) //rref

    template <typename E>
    void foo(E&&) //uref
}

auto&& //uref
const auto&& //const rref


const T&& 不是
const auto&& 不是

4. 完美转发
同时支持rvalue, lvalue
通过例子
1. no costly and unnecessary copy construction pass value
2. keep same type

```cpp
template <typename T>
void fn(T&& arg)
{
    foo(std::forward<T>(arg)); 
}
```

本质为类型转换，没有运行时消耗
Reference collapsing Rules
lv T&& -> T&
lr T&& -> T&
rv T&& -> rv
rl 


