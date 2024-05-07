#include <iostream>
#include <vector>
#include <iterator>

namespace merge {
  template<typename it, typename comp>
  std::vector<typename std::iterator_traits<it>::value_type> merge(const it begin, const it& mid, const it& end, comp compare)
  {
    std::vector<typename std::iterator_traits<it>::value_type> buffer;
    buffer.reserve(std::distance(begin, end));
    it it_l{ begin }, it_r{ mid };

    while (it_l != mid && it_r != end)
    {
      buffer.push_back(std::move(compare(*it_l, *it_r) ? *it_l++ : *it_r++));
    }

    buffer.insert(buffer.end(), it_l, mid);
    buffer.insert(buffer.end(), it_r, end);

    return buffer;
  }
}

template<typename it, typename comp = std::less<typename std::iterator_traits<it>::value_type>>
void mergeSort(it begin, it end, comp compare = comp())
{
  auto size = std::distance(begin, end);
  if (size < 2)
    return;

  auto mid = std::next(begin, size / 2);
  mergeSort(begin, mid);
  mergeSort(mid, end);

  auto v = merge::merge(begin, mid, end, compare);
  std::move(v.begin(), v.end(), begin);
}

template<typename it>
void print(it begin, it end) {
  while (begin != end) {
    std::cout << *(begin++) << " ";
  }
  std::cout << '\n';
}