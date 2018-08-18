
#include <vector>
#include <algorithm>

namespace estl {

template <
    class T,
    class Allocator = std::allocator<T>
> class Vector : public std::vector<T, Allocator>
{
 public:
  using std::vector<T,Allocator>::vector;


};


} //end namespace estl
