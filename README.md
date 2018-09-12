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
erase_safe_for




# test
depend gtets

// 新，老
C++已经30年了，
现代c++的引入给C++这位已经存在30年的语言注入了新的活力
封面
老人和小孩 对比

G
//# Effective Modern C++

TODO

整体课程框架?
 偏技术，知识点

为什么要听你这个课??
听了之后之前看不懂的代码能看懂了，对现代C++核心概念有了进一步的了解，或彻底掌握了
一次全面覆盖上述知识点

* 到底讲什么
  其实不是知识点,而是认识运用这几个知识点能解决什么问题?

* 如果不掌握这几种概念，会怎么样?

* 为什么是这几种概念??

* 个人介绍

* 整体课程大纲(思维导图)

解决问题?
价值?
如何使用
自己的洞察

* 最后使用一个编程例子来把所有的知识点穿起来，应用一下



课程目录
0. 课程概览
   * 目标墙
1. 进入现代C++
   * Why Modern C++?
   * 现代C++新特性总览
   * 与现代C++ sey Hi :

2. 现代C++核心特性概念和使用
    课程知识点:
    1. 右值引用
    2. 类型推到 auto
    3. 移动语义 std::move
    4. 统一引用和引用折叠 T&&
       理解引用折叠
       统一引用的和右值引用的区别
    5. 完美转发 std::forward



1. 是什么 概念
2. 为什么 意图 解决的了什么问题
3. 怎么用 使用


Morder C++
C++11/14/17

---

## Why Modern C++?

现代C++ 语言设计意图
0. 更好的易用性
1. 更高的性能
1. 更强的泛型能力
2. 更丰富的STL


面对更加严峻的技术挑战，我们需要更加强大的屠龙

note:
使用他可以大大提高你的生产力

对于使用者来说,使用现代C++你可以更轻松的进行开发,之前需要些几十行上百行代码才能实现的功能现在几行就搞定.


现代C++对98的改造可以说是 全面的和深入的
c++ 之父甚至说把C++11当做一个新语言来看待
背景 C++之父

---
## 现代C++新特性总览
围绕98的一系列问题，现代C++(C++11/14/17)标准新增了大量特性,主要体现在三个层次
上各方面
1. 语言内核
   右值引用, 移动语义，可变模板参数，,新的关键 conexpiler, ...

2. 语法层面
  lamdba 表达式, rang-base for, conexpil if

3. 标准库
   新的容器unorder_map/set tuple, 算法, 原子库，线程库,正则库...

总结性现代C++ 新增特性45个, 14标准库, 解决大98版本大量不错，引入了大量高级编程特性,并且还在发展中

note:

反过来,
新的特性有催生了一大批使用现代c++特性构建新
 编程方法和的高质量库和程序
 比如
 基于optional/resual 的统一错误处理方法
 基于promis/future概念的异步程序开发方法


大家都了解多少?
现代C++特性知多少

---
## 与现代C++ sey Hi :
note: 我们看段典型代码，来只管感受一下现代C++的使用体验 

1.
```cpp
  std::map<int, Proson*> persons;

  for (std::map<int, Person*>::iterator it = persons.being(); it != persons.end(); ++it) {
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
    A()
    :fd(-1), 
    buf(NULL), 
    isOk(false)
    {}
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
note: 立即初始化

3. 
```cpp
log 库 python 方式
    sprintf(buf,%s %f %s", "hello", "3.14", msg.c_str());

    format(buf, "{} {} {}", "hello", "3.14", msg);
    类型安全，任意长度参数
    
```
note: 相相有多少个有多少个夜晚你在加班写这种无效代码



---

## 现代C++核心知识点讲解
为什么是者5个知识点,

使用最广泛
最基础
最核心
最难掌握

带着问题


课程收益??


本次课程主要对现代C++11新增的
这几个概念做讲解，这些概念都是现代C++语言重要的核心概念，
市面上大部分教程对这些概念的讲解都不完全，重点散落在各个博客中，解释不透彻。
完全自学需要花费一定的，如果没听懂也没关系，包教包会，可以咨询。

如何实现cont if

带着问题学习
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
这一段小小的代码使用了我们今天要讲的所有知识点
高亮框显示


这段代码是seastart 的他是KVM之父开发的一个通用高性能网络应用框架，比对应的java版本性能高10被
对应的鹅肠也有一个类似项目叫做 fastxxx, 我们来看一下这个项目的负责人是如何评价seastart的



---
## 右值引用
为了避免不必要的对象构造,C++引入了右值引用来提供对一个右值的使用
一个问题引起的血案:
* 左值
* 右值

* 纯右值 :字面值, 没有地址
* 将亡值 : 临时值， 续命

何时需要右值引用?
左值引用

定义一个
type && = rvalue;


```cpp

   int i = 3;
   int & & //error
   int &lr = i;
   int &&rr = lr; //error 右值引用只能引用'右值'


    std::vector<int> seq(int b, int e)
    {
        vector<int> tmp;
        for (int i=b; i< e; ++i) 
            tmp.push_back(i);
        return tmp;
    }

           vector<int> v = seq(1,100); //这种代码的问题 ,又一次copy
    const vector<int> &v = seq(1,100); //为返回的临时值，续命和变量v的声明期一样, 没有copy,直接对tmp操作
         vector<int> &&v = seq(1,100); //为返回的临时值，续命和变量v的声明期一样, 没有copy,直接对tmp操作
   
```

* 注意右值引用不是右值，是左值

* std::move
把一个值无条件的转换成右值,不管之前的


## 移动语义 
用移动替换copy,提供性能
什么是移动 move
移动语义只能由右值触发
对移动语义的支持
 * 移动构造
 * 移动赋值



Syntax
class_name ( class_name && )
class_name ( const class_name && )


//举例子如果通过移动构造来避免copy
```cpp
  class MyVec
  {


      char *p;
  };

```

* 怎么使用
 对自定义类型,copy 消耗较大可以添加移动语义来减少不必要的拷贝

* 没有定义使用copy构造

* 何时需要定义移动构造
  几乎不需要，触发给类型需要支持移动概念

## std::move
强制使用移动语义
不可复制对象

通过智能指针来说明
struct D
{
};

std::move
的特点, 本质是类型转换，无运行时开销
在需要现实使用移动语义的地方显示调用
osities: std::move that doesn't move : Yet Another Coder
std::move 其实并不是移动的意思而是 cast to right reference

 move 更多的并不是用来避免返回值拷贝，而是完成移动
 ---
Copy Elision
主要包含RVO,和参数拷贝优化
 RVO (return value optimization)
 NRVO

 常使用传入变量地址到调用函数
 string ss() {
      ..//
      retun
}

哪些函数不会执行RVO ?
RVO 并不是总会执行,即使到了C++17标准已经涵盖RVO特性
返回一个非函数local 的变量

A (A o)
{
    return o;
}

if (someCond)
    return a;
    else
        return b;
    }

--- 
f(std::string("A"))

看一些代码

```cpp


template <typename Func>
class lambda_task final : public task {
    Func _func;
public:
    lambda_task(const Func& func) : _func(func) {}
    lambda_task(Func&& func) : _func(std::move(func)) {}
    virtual void run() noexcept override { _func(); }
};


/**
 *  Append a C substring.
 *  @param s  The C string to append.
 *  @param n  The number of characters to append.
 *  @return  Reference to this string.
 */
basic_sstring& append (const char_type* s, size_t n) {
    basic_sstring ret(initialized_later(), size() + n);
    std::copy(begin(), end(), ret.begin());
    std::copy(s, s + n, ret.begin() + size());
    *this = std::move(ret);
    return *this;
}

```

Buffer read(Buffer&& buffer) {
    //...
    return std::move( buffer ); //return buffer ref thing
    return buffer ; // return a buffer ref thing's copy
}

return std::move(xxx)??
大部分情况下都不需要，如果显示写反而会阻止RVO
也就是即使返回类型支持移动构造，也不要试使用std::move 强制触发



* 返回类型为&& ??
 永远不要返回一个local 变量的引用

 Return Value Optimization(RVO 进入C++11标准)
  
* 陷阱
 class A {};
 返回一个右值引用类型
 ```cpp
std::vector<A> && func() {
    std::vector<A> v;
    /* fill v */
    return std::move(v);
}
```



---

## 统一引用和引用折叠 T&&
用例


templae

理解引用折叠
统一引用的和右值引用的区别


## 类型推到 auto


5. 完美转发 std::forward

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

---- 不做这个,直接从现代C++开始
Why C++?
0. 多范式开发
1. 零开销抽象
2. 泛型
3. 直接操作硬件

note:
C++虽然不完美但是，目前你也很难找到一个在各方面都比C++好的语言
当然PHP是世界上最好的语言.

---
