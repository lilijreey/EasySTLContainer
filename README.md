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
select_iter 泛化 使用与所有容器
erase_iter
remove_iter




# test
depend gtets

// 新，老
C++已经30年了，
现代c++的引入给C++这位已经存在30年的语言注入了新的活力
封面
老人和小孩 对比

G
//# Effective Modern C++

Why C++?

0. 多范式开发
1. 零开销抽象
2. 泛型
3. 直接操作硬件

note:
C++虽然不完美但是，目前你也很难找到一个在各方面都比C++好的语言
当然PHP是世界上最好的语言.

---
Morder C++
C++11/14/17

Why Modern C++?
现代C++ 语言设计意图
0. 提高易用性
1. 提高性能
1. 更强的泛型能力
2. 更丰富的STL

note:
现代C++对98的改造可以说是 全面的和深入的
c++ 之父甚至说把C++11当做一个新语言来看待
背景 C++之父

---
围绕98的一系列问题，现代C++(C++11/14/17)标准新增了大量特性,主要体现在三个层次
上各方面
1. 语言内核
   右值引用, 移动语义，可变模板参数，lamdba 表达式,新的关键 conexpiler, ...

2. 标准库
   新的容器unorder_map/set tuple, 算法, 原子库，线程库,正则库...



反过来,
新的特性有催生了一大批使用现代c++特性构建新
 编程方法和的高质量库和程序
 比如
  基于optional/resual 的统一错误处理方法
  基于promis/future概念的异步程序开发方法
--- 


现代C++特性知多少
...
...

大家都了解多少?



---

现代C++ 部分特性展示


1.
```cpp
  std::vector<int, Proson*> persons;

  for (std::vector<int, Person*>::iterator it = persons.being(); it != persons.end(); ++it) {
      printf("key %d %s", it->first, it->second->GetName());
  }

  for (auto it = persons.being(); it != persons.end(); ++it) { //c++11
      printf("key %d %s", it->first, it->second->GetName());
  }

  for (auto &pair : persons) { //c++11 
      printf("key %d %s", pair.first, pair.second.GetName());
  }

  for (auto &[key, person] : persons) //c++17
      printf("key %d %s", key, person->GetName());
  }
  ```

2. 
```cpp
class A {
    A():fd(-1), buf(NULL), isOk(false);
    int fd;
    char *buf;
    bool isOk;
};

class A { //C++11
    int fd = -1;
    char *buf = NULL;
    bool isOk =false;
};

```

3. 
```cpp
log 库 python 方式
    sprintf(buf,%s %f %s", "hello", "3.14", msg.c_str());

    format(buf, "{} {} {}", "hello", "3.14", msg);
    类型安全，任意长度参数
    
```
note: 相相有多少个有多少个夜晚你在加班写这种无效代码









本次课程主要对现代C++11新增的
1. 右值引用
2. 类型推到 auto
3. 移动语义 std::move
4. 统一引用和引用折叠 T&&
5. 完美转发 std::forward
这几个概念做讲解，这些概念都是现代C++语言重要的核心概念，
市面上大部分教程对这些概念的讲解都不完全，重点散落在各个博客中，解释不透彻。
完全自学需要花费一定的，如果没听懂也没关系，包教包会，可以咨询。


TODO 换个例子
```cpp
template<typename T, typename F>
inline
auto do_with(T&& rvalue, F&& f) {
    auto task = std::make_unique<internal::do_with_state<T, std::result_of_t<F(T&)>
        >(std::forward<T>(rvalue));
    auto fut = f(task->data());
    if (fut.available()) {
        return fut;
    }
    auto ret = task->get_future();
    internal::set_callback(fut, std::move(task));
    return ret;
}
```
现代C++代码有个特点就是抽象能力很高，并且是零开销抽象。（不消耗运行时间)


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

// 右值引用 != 右值
// 右值引用 是左值

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


Change is Hard

Q&A

编译器: g++4.8 以上 基本支持C++11
有条件最好g++6.4 以上 完整支持c++14

现代 C++ 的最佳实践
赠送电子书